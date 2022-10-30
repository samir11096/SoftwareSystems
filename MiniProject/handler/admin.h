#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<fcntl.h>
#include<stdbool.h>
#include <errno.h>

#include "../constants/admin_constants.h"
#include "../constants/constants.h"

 

//declaration of admin handlers

void admin_handler(int connectionFD);//done
bool admin_login_handler(int connectinFD);//done
bool add_customer(int connectionFD);//done
void add_normal_customer(int connectionFD);//done
void add_joint_customer(int connectinFD);//done
void modify_customer_details();//not implementing due to time constraints
void delete_customer(int connectionFD);//done
void delete_normal_customer(int connectionFD);//done
void delete_joint_customer(int connectionFD);//done
void check_customer_details(int connectionFD);//done
void check_normal_customer_details(int connectionFD);//done
void check_joint_customer_details(int connectionFD);//done


bool admin_login_handler(int connectionFD){
    int readBytes , writeBytes;
    char readBuffer[500] , writeBuffer[500];

    int admin_id ;
    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer,ADMIN_LOGIN_WELCOME);
    strcat(writeBuffer,ADMIN_PASSWORD_PROMPT);

    writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));
    if(writeBytes<0){
        perror("Error while displaying Admin Welcome Prompt!");
        return false;
    }
    bzero(readBuffer , sizeof(readBuffer));
    readBytes = read(connectionFD,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading Admin password!");
        return false;
    }
    char password[500];
    bzero(password,sizeof(password));
    strcpy(password , readBuffer);

    if(!strcmp(password, ADMIN_PASSWORD)){
        return true;
    }
    return false;
}


void admin_handler(int connectionFD){
    int readBytes , writeBytes;
    char readBuffer[500], writeBuffer[500];

    if(admin_login_handler(connectionFD)){
        bzero(readBuffer ,sizeof(readBuffer));
        bzero(writeBuffer , sizeof(writeBuffer));

        strcpy(writeBuffer ,ADMIN_LOGIN_SUCCESS);
        strcpy(writeBuffer, ADMIN_MENU);
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying admin menu!");
        }
        readBytes = read(connectionFD , readBuffer ,sizeof(readBuffer));
        if(readBytes<0){
            perror("Error while reading admin choice!");
        }
        
        int admin_choice = atoi(readBuffer);

        switch(admin_choice){
            case 1:
                add_customer(connectionFD);
                break;
            case 2:
                //delete_customer();
                break;
            case 3:
                //check_customer_details();
                check_customer_details(connectionFD);
                break;
            default:
                //wrong input 
                writeBytes  = write(connectionFD, WRONG_INPUT ,strlen(WRONG_INPUT));
                admin_handler(connectionFD);
                break;
        }

        }


    else {
       bzero(writeBuffer,sizeof(writeBuffer));
       writeBytes = write(connectionFD,ADMIN_LOGIN_FAILED, strlen(ADMIN_LOGIN_FAILED));
       admin_handler(connectionFD);
       if(writeBytes<0){
        perror("Error while diplaying admin login failed prompt");
       }
    }
}
    

bool add_customer(int connectionFD){

    int readBytes , writeBytes;
    char readBuffer[500] , writeBuffer[500];
    bzero(readBuffer , sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    writeBytes = write(connectionFD ,ADMIN_ADD_CUSOMTER_MENU,strlen(ADMIN_ADD_CUSOMTER_MENU) );
    if(writeBytes<0){
        perror("Error while displaying the ADMIN Add Customer menu");
        return false;
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading ADMIN Add Customer menu");
        return false;
    }

    int choice_add = atoi(readBuffer);
    switch(choice_add){
        case 1:

            //add normal_customer
            add_normal_customer(connectionFD);
            break;

        case 2:
            //add joint customer
            add_joint_customer(connectionFD);
            break;
        default:
            break;
    }

    return false;

}

void add_normal_customer(int connectionFD){
    int readBytes ,writeBytes;
    char readBuffer[500] , writeBuffer[500];
    struct Normal_Customer customer;
    struct flock flk;
    int lockStatus;
    int offSet;

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_CUSTOMER_NAME_PROMT,strlen(ADMIN_CUSTOMER_NAME_PROMT));
    if(writeBytes<0){
        perror("Error while reading normal customer name");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer, sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading normal customer name");
        //send error statement to client
    }
    
    strcpy(customer.name,readBuffer);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_CUSTOMER_AGE_PROMT,strlen(ADMIN_CUSTOMER_AGE_PROMT));
    if(writeBytes<0){
        perror("Error while reading normal customer age");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading normal customer age");
    }
    customer.age =atoi(readBuffer);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    char gender;
    writeBytes = write(connectionFD,ADMIN_CUSTOMER_GENDER_PROMT,strlen(ADMIN_CUSTOMER_GENDER_PROMT));
    if(writeBytes<0){
        perror("Error while reading normal customer gender");
        //send error statement of client 
    }

    readBytes = read(connectionFD , &gender, sizeof(gender));
    if(readBytes<0){
        perror("Error while reading normal customer gender");
    }
    customer.gender = gender;

    
    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

writeBytes = write(connectionFD,ADMIN_CUSTOMER_PASSWORD_PROMT,strlen(ADMIN_CUSTOMER_PASSWORD_PROMT));
    if(writeBytes<0){
        perror("Error while reading normal customer password");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading normal customer password");
    }
    strcpy(customer.password,readBuffer);

    //fill in id , login id , account no , balance for struct customer

    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer , sizeof(writeBuffer));
    //locking the id file before using 

    int idFD = open(NORMAL_ID_FILE_PATH,O_RDWR);
    if(idFD<0){
        perror("Error while trying to open ID file");
        return;
    }


    flk.l_type =F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start=0;
    flk.l_len=sizeof(char);
    flk.l_pid = getpid();

    lockStatus = fcntl(idFD, F_SETLKW,&flk);

    offSet = lseek(idFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while moving the id file offset ");
    }
    int id_no;
    readBytes = read(idFD,&id_no ,sizeof(id_no));
    if(readBytes<0){
        perror("Error while trying to read ID file ");
    }
    int previous_id;
    if(readBytes==0){
        previous_id = 0;
    }
    else{previous_id = id_no;}
    customer.id = previous_id+1;
    previous_id = previous_id+1;
    sprintf(customer.login,"%d",previous_id);
    
    offSet = lseek(idFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while moving the id file offset ");
    }
    int  new_id = previous_id;
    writeBytes = write(idFD,&new_id,sizeof(new_id));
    if(writeBytes<0){
        perror("Error while writing to new id to ID file");
    }

    flk.l_type =F_UNLCK;
    fcntl(idFD,F_SETLK,&flk);
    close(idFD);


    int accFD = open(NORMAL_ACCOUTN_NO_FILE_PATH,O_RDWR);
    if(accFD<0){
        perror("Error while trying to open account no file");
    }

    
    flk.l_type =F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start=0;
    flk.l_len=sizeof(char);
    flk.l_pid = getpid();

    bzero(readBuffer,sizeof(readBuffer));

    lockStatus = fcntl(accFD, F_SETLKW,&flk);

    offSet = lseek(accFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while changing the acc file offset to start");
    }
    int value;
    readBytes = read(accFD,&value ,sizeof(value));
    if(readBytes<0){
        perror("Error while trying to account no file ");
    }
    int previous_account_no;
    if(readBytes==0){
        previous_account_no= 99;//so the account start with 100 for normal users
    }
    else{previous_account_no = value;}
    customer.account_no = previous_account_no+1;
    int new_account_no = previous_account_no+1;

    offSet = lseek(accFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while changing the acc file offset to start");
    }
    
    writeBytes = write(accFD,&new_account_no,sizeof(new_account_no));
    if(writeBytes<0){
        perror("Error while writing to new account no to account no file");
    }

    flk.l_type =F_UNLCK;
    fcntl(accFD,F_SETLK,&flk);
    close(accFD);


    customer.balance=0.0;
    customer.deleted=0;

    //add to file the new customer

    int customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDWR|O_CREAT); 
    if(customerFD<0){
        perror("Error while opening normal customer file");
    }


    flk.l_type =F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start=(customer.id-1)*sizeof(struct Normal_Customer);
    flk.l_len=sizeof(struct Normal_Customer);
    flk.l_pid = getpid();

    lockStatus = fcntl(customerFD,F_SETLKW,&flk);
    if(lockStatus<0){
        perror("Error while locking on normal customer file");
    }

    //see if it works or we need to use char*
    offSet = lseek(customerFD,0,SEEK_END);
    if(offSet<0){
        perror("Error while moving the file off set to the end");
    }
    writeBytes = write(customerFD,&customer,sizeof(customer));
    if(writeBytes<0){
        perror("Error while writing to the normal customer file");
    }

    flk.l_type=F_UNLCK;
    fcntl(customerFD,F_SETLK,&flk);

    //writing on successfull creaing of customer
    writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_CREATION_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_CREATION_PROMT));
    if(writeBytes<0){
        perror("Error while creation of noraml customer");
    }


}

 void add_joint_customer(int connectionFD){

    int readBytes ,writeBytes;
    char readBuffer[500] , writeBuffer[500];
    struct Joint_Customer customer;
    struct flock flk;
    int lockStatus,offSet;

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_PRIMARY_NAME_PROMT,strlen(ADMIN_JOINT_CUSTOMER_PRIMARY_NAME_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint customer primary name prompt");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer, sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading joint customer primary name");
        //send error statement to client
    }
    
    strcpy(customer.primary_name,readBuffer);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_SECONDARY_NAME_PROMT,strlen(ADMIN_JOINT_CUSTOMER_SECONDARY_NAME_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint customer secondary name prompt");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer, sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading joint customer secondary name prompt");
        //send error statement to client
    }

    strcpy(customer.secondary_name,readBuffer);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOIMER_PRIMARY_AGE_PROMT,strlen(ADMIN_JOINT_CUSTOIMER_PRIMARY_AGE_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint primary customer age prompt");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading joint primary customer age");
    }
    customer.primary_customer_age =atoi(readBuffer);



    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_SECONDARY_AGE_PROMT,strlen(ADMIN_JOINT_CUSTOMER_SECONDARY_AGE_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint secondary customer age prompt");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading joint secondary customer age");
    }
    customer.secondary_customer_age =atoi(readBuffer);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));


    char gender;
    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_PRIMARY_GENDER_PROMT,strlen(ADMIN_JOINT_CUSTOMER_PRIMARY_GENDER_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint primary customer gender");
        //send error statement of client 
    }


    readBytes = read(connectionFD , &gender, sizeof(gender));
    if(readBytes<0){
        perror("Error while reading joint primary customer gender");
    }
    customer.primmay_customer_gender = gender;
    
    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));


    
    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_SECONDARY_GENDER_PROMT,strlen(ADMIN_JOINT_CUSTOMER_SECONDARY_GENDER_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint secondary customer gender");
        //send error statement of client 
    }


    readBytes = read(connectionFD , &gender, sizeof(gender));
    if(readBytes<0){
        perror("Error while reading joint secondary customer gender");
    }
    customer.secondary_customer_gender = gender;

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_CUSTOMER_PASSWORD_PROMT,strlen(ADMIN_CUSTOMER_PASSWORD_PROMT));
    if(writeBytes<0){
        perror("Error while displaying joint customer password");
        //send error statement of client 
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading joint customer password");
    }
    strcpy(customer.password,readBuffer);

    //fill in id , login id , account no , balance for struct customer

    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer , sizeof(writeBuffer));
    //locking the id file before using 

    int idFD = open(JOINT_ID_FILE_PATH,O_RDWR);
    if(idFD<0){
        perror("Error while trying to open ID file");
        return;
    }


    flk.l_type =F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start=0;
    flk.l_len=sizeof(char);
    flk.l_pid = getpid();

    lockStatus = fcntl(idFD, F_SETLKW,&flk);
    
    offSet = lseek(idFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while changing the id file offset to start");
    }
    int id_no;
    readBytes = read(idFD,&id_no ,sizeof(id_no));
    if(readBytes<0){
        perror("Error while trying to read ID file ");
    }
    int previous_id;
    if(readBytes==0){
        previous_id = 0;
    }
    else{previous_id = id_no;}
    customer.id = previous_id+1;
    previous_id = previous_id+1;
    sprintf(customer.login,"%d",previous_id);
    
    offSet = lseek(idFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while changing the id file offset to start");
    }
    int  new_id = previous_id;
    writeBytes = write(idFD,&new_id,sizeof(new_id));
    if(writeBytes<0){
        perror("Error while writing to new id to ID file");
    }

    flk.l_type =F_UNLCK;
    fcntl(idFD,F_SETLK,&flk);
    close(idFD);


    int accFD = open(JOINT_ACCOUNT_NO_FILE_PATH,O_RDWR);
    if(accFD<0){
        perror("Error while trying to open account no file");
    }

    
    flk.l_type =F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start=0;
    flk.l_len=sizeof(char);
    flk.l_pid = getpid();

    bzero(readBuffer,sizeof(readBuffer));

    lockStatus = fcntl(accFD, F_SETLKW,&flk);
    offSet = lseek(accFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while changing the account file offset to start");
    }
    int account_no;
    readBytes = read(accFD,&account_no ,sizeof(account_no));
    if(readBytes<0){
        perror("Error while trying to account no file ");
    }
    int previous_account_no;
    if(readBytes==0){
        previous_account_no= 199;//so that joint user account no start with 200
    }
    else{previous_account_no = account_no;}
    customer.account_no = previous_account_no+1;
    previous_account_no = previous_account_no+1;
    
    offSet = lseek(accFD,0,SEEK_SET);
    if(offSet<0){
        perror("Error while changing the account file offset to start");
    }
    int new_account_no = previous_account_no+1;
    writeBytes = write(accFD,&new_account_no,sizeof(new_account_no));
    if(writeBytes<0){
        perror("Error while writing to new account no to account no file");
    }

    flk.l_type =F_UNLCK;
    fcntl(accFD,F_SETLK,&flk);
    close(accFD);


    customer.balance=0.0;
    customer.deleted=0;

    //add to file the new customer

    int customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDWR|O_CREAT); 
    if(customerFD<0){
        perror("Error while opening normal customer file");
    }


    flk.l_type =F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start=(customer.id-1)*sizeof(struct Normal_Customer);
    flk.l_len=sizeof(struct Normal_Customer);
    flk.l_pid = getpid();

    lockStatus = fcntl(customerFD,F_SETLKW,&flk);
    if(lockStatus<0){
        perror("Error while locking on joint customer file");
    }

    //see if it works or we need to use char*
    writeBytes = write(customerFD,&customer,sizeof(customer));
    if(writeBytes<0){
        perror("Error while writing to the joint customer file");
    }

    flk.l_type=F_UNLCK;
    fcntl(customerFD,F_SETLK,&flk);

    //writing on successfull creaing of customer
    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_CREATION_PROMT,strlen(ADMIN_JOINT_CUSTOMER_CREATION_PROMT));
    if(writeBytes<0){
        perror("Error while creation of joint customer");
    }

 }

void check_customer_details(int connectionFD){

    int readBytes,writeBytes;
    char readBuffer[500],writeBuffer[500];
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    writeBytes = write(connectionFD,ADMIN_CHECK_CUSTOMER_MENU,strlen(ADMIN_CHECK_CUSTOMER_MENU));
    if(writeBytes<0){
        perror("Error while displaying the customer details menu");
        //send error to client if wanted
    }

    readBytes  = read(connectionFD ,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to read customer check details option");
        //client error if wanted
    }

    int choice = atoi(readBuffer);

    switch(choice){
        case 1:
            check_normal_customer_details(connectionFD);
            break;
        case 2:
            //check_joint_customer_details(connectionFD);
            check_joint_customer_details(connectionFD);
            break;
        default:
            //error message to client
            break;
    }


}


void check_normal_customer_details(int connectionFD){
    
    int readBytes,writeBytes;
    char readBuffer[500],writeBuffer[500];
    struct Normal_Customer customer;
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    writeBytes = write(connectionFD, ADMIN_NORMAL_CUSTOMER_ID_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_ID_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the normal customer id prompt");
    }

    readBytes = read(connectionFD ,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading the normal customer id ");
    }
    int customer_id = atoi(readBuffer);

    //lock the normal customer details file 
    //extract the customer struct in local struct
    //display name , gender  ,age,loginid ,account_no,balance
    //give error message when customer id not present

    int normal_customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDWR);
    if(normal_customerFD<0){
        perror("Error while tring to open normal customer details file");
    }

    struct flock flk;
    flk.l_type = F_RDLCK;
    flk.l_whence=SEEK_SET;
    flk.l_start = (customer_id-1)*sizeof(struct Normal_Customer);
    flk.l_len=sizeof(struct Normal_Customer);
    flk.l_pid= getpid();

    int lockStatus = fcntl(normal_customerFD,F_SETLKW,&flk);    
    if(lockStatus<0){
        perror("Error while locking the normal customer details file");
        //client side error to check if id exits or not 
    }
    
    //setting the file offset to require customer details
    int offSet_value = (customer_id-1)*sizeof(struct Normal_Customer);
    int offSet = lseek(normal_customerFD,offSet_value,SEEK_SET);
    if(offSet<0){
        perror("Error while placing the file offset in normal customer file");
    }

    readBytes = read(normal_customerFD,&customer,sizeof(customer));
    if(readBytes<0){
        perror("Error while trying to read the normal customer deatils for given id");
    }

    flk.l_type=F_UNLCK;
    lockStatus = fcntl(normal_customerFD,F_SETLK,&flk);
    if(lockStatus<0){
        perror("Error while trying to unlock the file ");
    }
    if(customer.deleted==0){

        //display all the necessary details to admin
        bzero(writeBuffer,sizeof(writeBuffer));
        bzero(readBuffer,sizeof(readBuffer));

        writeBytes = write(connectionFD,CUSTOMER_NAME,strlen(CUSTOMER_NAME));
        if(writeBytes<0){
            perror("Error while trying to prompt customer name");
        }
        strcpy(writeBuffer,customer.name);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the name of normal customer ");
        }
        //age (error in this part , some kind of delay)
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,CUSTOMER_AGE,strlen(CUSTOMER_AGE));
        if(writeBytes<0){
            perror("Error while displaying the customer age prompt");
        }
        sprintf(writeBuffer,"%d",customer.age);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Errorw while displaying the age of normal customeR");
        }
        //gender
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,CUSTOMER_GENDER,strlen(CUSTOMER_GENDER));
        if(writeBytes<0){
            perror("Error while displaying customer gender prompt");
        }
        sprintf(writeBuffer,"%c",customer.gender);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the gender of noraml customer");
        }

        //login id
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,CUSTOMER_LOGIN_ID,strlen(CUSTOMER_LOGIN_ID));
        if(writeBytes<0){
            perror("Error while displaying login id prompt");
        }
        strcpy(writeBuffer,customer.login);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the login id of normal customer");
        }

        //account no
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connectionFD,CUSTOMER_ACCOUNT_NO,strlen(CUSTOMER_ACCOUNT_NO));
        if(writeBytes<0){
            perror("Error while displaying the account number prompt");
        }
        sprintf(writeBuffer,"%d",customer.account_no);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes= write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the normal customer account no");
        }

        //balance
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes= write(connectionFD, CUSTOMER_BALANCE,strlen(CUSTOMER_BALANCE));
        if(writeBytes<0){
            perror("Error whlie displaying the balance prompt");
        }
        sprintf(writeBuffer,"%f",customer.balance);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the balance of normal customer");
        }
    }
    else{
        writeBytes=write(connectionFD,ADMIN_NORMAL_CUSTOMER_NOT_PRESENT_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_NOT_PRESENT_PROMT));
        if(writeBytes<0){
            perror("Error while displaying the normal customer not present prompt");
        }
    }
    
    
}

void check_joint_customer_details(int connectionFD){

    int readBytes,writeBytes;
    char readBuffer[500],writeBuffer[500];
    struct Joint_Customer customer;
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    writeBytes = write(connectionFD, ADMIN_JOINT_CUSTOMER_ID_PROMT,strlen(ADMIN_JOINT_CUSTOMER_ID_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the joint customer id prompt");
    }

    readBytes = read(connectionFD ,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading the joint customer id ");
    }
    int customer_id = atoi(readBuffer);

    //lock the joint customer details file 
    //extract the customer struct in local struct
    //display primary and secondary name , gender  ,age,loginid ,account_no,balance
    //give error message when customer id not present

    int joint_customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDONLY);
    if(joint_customerFD<0){
        perror("Error while tring to open joint customer details file");
    }

    struct flock flk;
    flk.l_type = F_RDLCK;
    flk.l_whence=SEEK_SET;
    flk.l_start = (customer_id-1)*sizeof(struct Joint_Customer);
    flk.l_len=sizeof(struct Joint_Customer);
    flk.l_pid= getpid();

    int lockStatus = fcntl(joint_customerFD,F_SETLKW,&flk);    
    if(lockStatus<0){
        perror("Error while locking the Joint customer details file");
        //client side error to check if id exits or not 
    }
    
    //setting the file offset to require customer details
    int offSet_value = (customer_id-1)*sizeof(struct Joint_Customer);
    int offSet = lseek(joint_customerFD,offSet_value,SEEK_SET);
    if(offSet<0){
        perror("Error while placing the file offset in joint customer file");
    }

    readBytes = read(joint_customerFD,&customer,sizeof(customer));
    if(readBytes<0){
        perror("Error while trying to read the joint customer deatils for given id");
    }

    flk.l_type=F_UNLCK;
    lockStatus = fcntl(joint_customerFD,F_SETLK,&flk);
    if(lockStatus<0){
        perror("Error while trying to unlock the file ");
    }
    if(customer.deleted ==0){
        //display all the necessary details to admin
        bzero(writeBuffer,sizeof(writeBuffer));
        bzero(readBuffer,sizeof(readBuffer));

        writeBytes = write(connectionFD,PRIMARY_CUSTOMER_NAME,strlen(PRIMARY_CUSTOMER_NAME));
        if(writeBytes<0){
            perror("Error while trying to prompt primary customer name");
        }
        strcpy(writeBuffer,customer.primary_name);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the primary name of joint customer ");
        }
        //secondary name
        writeBytes = write(connectionFD,SECONDARY_CUSTOMER_NAME,strlen(SECONDARY_CUSTOMER_NAME));
        if(writeBytes<0){
            perror("Error while trying to prompt secondary customer name");
        }
        strcpy(writeBuffer,customer.secondary_name);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the secondary name of joint customer ");
        }
        //primary age (error in this part , some kind of delay)
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,PRIMARY_CUSTOMER_AGE,strlen(PRIMARY_CUSTOMER_AGE));
        if(writeBytes<0){
            perror("Error while displaying the primary customer age prompt");
        }
        sprintf(writeBuffer,"%d",customer.primary_customer_age);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Errorw while displaying the age of joint primary customer");
        }
        //secondary customer age 

        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,SECONDARY_CUSTOMER_AGE,strlen(SECONDARY_CUSTOMER_AGE));
        if(writeBytes<0){
            perror("Error while displaying the primary customer age prompt");
        }
        sprintf(writeBuffer,"%d",customer.secondary_customer_age);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Errorw while displaying the age of joint secondary customer");
        }
        //primary customer gender
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,PRIMARY_CUSTOMER_GENDER,strlen(PRIMARY_CUSTOMER_GENDER));
        if(writeBytes<0){
            perror("Error while displaying primary customer gender prompt");
        }
        sprintf(writeBuffer,"%c",customer.primmay_customer_gender);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the gender of primary joint customer");
        }

        //secondary customer gender
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,SECONDARY_CUSTOMER_GENDER,strlen(SECONDARY_CUSTOMER_GENDER));
        if(writeBytes<0){
            perror("Error while displaying secondary customer gender prompt");
        }
        sprintf(writeBuffer,"%c",customer.secondary_customer_gender);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the gender of secondary joint customer");
        }
        //login id
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes = write(connectionFD,CUSTOMER_LOGIN_ID,strlen(CUSTOMER_LOGIN_ID));
        if(writeBytes<0){
            perror("Error while displaying login id prompt");
        }
        strcpy(writeBuffer,customer.login);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the login id of joint customer");
        }

        //account no
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connectionFD,CUSTOMER_ACCOUNT_NO,strlen(CUSTOMER_ACCOUNT_NO));
        if(writeBytes<0){
            perror("Error while displaying the account number prompt");
        }
        sprintf(writeBuffer,"%d",customer.account_no);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes= write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the joint customer account no");
        }

        //balance
        bzero(writeBuffer,sizeof(writeBuffer));
        writeBytes= write(connectionFD, CUSTOMER_BALANCE,strlen(CUSTOMER_BALANCE));
        if(writeBytes<0){
            perror("Error whlie displaying the balance prompt");
        }
        sprintf(writeBuffer,"%f",customer.balance);
        strcat(writeBuffer,"\n");//appending newline to each field
        writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
        if(writeBytes<0){
            perror("Error while displaying the balance of joint customer");
        }
    }
    else{
        writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_NOT_PRESETN_PROMT,strlen(ADMIN_JOINT_CUSTOMER_NOT_PRESETN_PROMT));
        if(writeBytes<0){
            perror("Error while displaying that Joint customer not present prompt");
        }
    }
}


void delete_customer(int connectionFD){

    int readBytes ,writeBytes;
    char readBuffer[500],writeBuffer[500];

    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));


    writeBytes = write(connectionFD,ADMIN_CUSTOMER_DELETE_PROMT,strlen(ADMIN_CUSTOMER_DELETE_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the delete prompt");
    }

    readBytes = read(connectionFD,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading delete input from client");
    }

    int choice = atoi(readBuffer);

    switch(choice){
        case 1:
            //delete normal customer 
            delete_normal_customer(connectionFD);
            break;
        case 2:
            //delete joint customer
            delete_joint_customer(connectionFD);
            break;
        default:
            break; 
    }
}


void delete_normal_customer(int connectionFD){
    int readBytes , writeBytes;
    char readBuffer[500],writeBuffer[500];
    bzero(writeBuffer , sizeof(writeBuffer));
    bzero(readBuffer ,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_DELETE_ID_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_DELETE_ID_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the prompt for normal customer delete if promt");
    }

    readBytes = read(connectionFD ,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to read delete normal customer id");
    }

    int customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDWR);

    if(customerFD<0){
        perror("Error while opening normal customer details file");
    }

    int customer_id = atoi(readBuffer);

    struct Normal_Customer customer;

    struct flock flk;
    flk.l_type=F_WRLCK;
    flk.l_whence=SEEK_SET;
    flk.l_start = (customer_id-1)*sizeof(struct Normal_Customer);
    flk.l_len = sizeof(struct Normal_Customer);
    flk.l_pid = getpid();

    int lockStatus = fcntl(customerFD,F_SETLKW,&flk);
    if(lockStatus<0){
        perror("Error while trying to get a lock on normal customer file for deletion");
    }


    int offSet = lseek(customerFD,(customer_id-1)*sizeof(struct Normal_Customer),SEEK_SET);
    if(offSet<0){
        perror("Error while positioning the offset of normal customer details file");
    }


    readBytes = read(customerFD,&customer,sizeof(customer));
    if(readBytes<0){
        perror("Error while reading the details of normal customer to delete");
    }
    if(customer.deleted!=1){
        customer.deleted=1;

        offSet = lseek(customerFD,(customer_id-1)*sizeof(struct Normal_Customer),SEEK_SET);
        if(offSet<0){
            perror("Error while positioning the offset of normal customer to delete");
        }

        writeBytes = write(customerFD,&customer,sizeof(customer));
        if(writeBytes<0){
            perror("Error while trying to delete normal customer");
        }
        writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_DELETE_SUCCESS,strlen(ADMIN_NORMAL_CUSTOMER_DELETE_SUCCESS));
        if(writeBytes<0){
            perror("Error while displaying the delete normal customer success prompt");
        }
    }
    else{
        writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_NOT_PRESENT_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_NOT_PRESENT_PROMT));
        if(writeBytes<0){
            perror("Error while displaying normal customer not present promt");
        }
    }
    
    flk.l_type=F_UNLCK;
    lockStatus = fcntl(customerFD,F_SETLK,&flk);
    if(lockStatus<0){
        perror("Error while trying to unlock normal customer details file");
    }

    

}


void delete_joint_customer(int connectionFD){
    
    int readBytes , writeBytes;
    char readBuffer[500],writeBuffer[500];
    bzero(writeBuffer , sizeof(writeBuffer));
    bzero(readBuffer ,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_DELETE_ID_PROMT,strlen(ADMIN_JOINT_CUSTOMER_DELETE_ID_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the prompt for joint customer delete if promt");
    }

    readBytes = read(connectionFD ,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to read delete joint customer id");
    }

    int customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDWR);

    if(customerFD<0){
        perror("Error while opening joint customer details file");
    }

    int customer_id = atoi(readBuffer);

    struct Joint_Customer customer;

    struct flock flk;
    flk.l_type=F_WRLCK;
    flk.l_whence=SEEK_SET;
    flk.l_start = (customer_id-1)*sizeof(struct Joint_Customer);
    flk.l_len = sizeof(struct Joint_Customer);
    flk.l_pid = getpid();

    int lockStatus = fcntl(customerFD,F_SETLKW,&flk);
    if(lockStatus<0){
        perror("Error while trying to get a lock on joint customer file for deletion");
    }


    int offSet = lseek(customerFD,(customer_id-1)*sizeof(struct Joint_Customer),SEEK_SET);
    if(offSet<0){
        perror("Error while positioning the offset of joint customer details file");
    }


    readBytes = read(customerFD,&customer,sizeof(customer));
    if(readBytes<0){
        perror("Error while reading the details of joint customer to delete");
    }
    if(customer.deleted!=1){
        customer.deleted=1;

        offSet = lseek(customerFD,(customer_id-1)*sizeof(struct Joint_Customer),SEEK_SET);
        if(offSet<0){
            perror("Error while positioning the offset of joint customer to delete");
        }

        writeBytes = write(customerFD,&customer,sizeof(customer));
        if(writeBytes<0){
            perror("Error while trying to delete joint customer");
        }
        writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_DELETE_SUCCESS,strlen(ADMIN_JOINT_CUSTOMER_DELETE_SUCCESS));
        if(writeBytes<0){
            perror("Error while displaying the delete joint customer success prompt");
        }
    }
    else{
        writeBytes = write(connectionFD,ADMIN_JOINT_CUSTOMER_NOT_PRESETN_PROMT,strlen(ADMIN_JOINT_CUSTOMER_NOT_PRESETN_PROMT));
        if(writeBytes<0){
            perror("Error while displaying joint customer not present promt");
        }
    }
    
    flk.l_type=F_UNLCK;
    lockStatus = fcntl(customerFD,F_SETLK,&flk);
    if(lockStatus<0){
        perror("Error while trying to unlock joint customer details file");
    }

    


}
