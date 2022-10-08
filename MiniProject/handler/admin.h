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

void admin_handler(int connectionFD);
bool admin_login_handler(int connectinFD);
bool add_customer(int connectionFD);
void add_normal_customer(int connectionFD);
void add_joint_customer(int connectinFD);
void modify_customer_details();
bool delete_customer();
void check_customer_details();


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
       //using while loop 
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
                //modify_customer_details();
                break;
            case 3:
                //delete_customer();
                break;
            case 4:
                //check_customer_details();
                break;
            default:
                break;
        }

        }


    else {
       bzero(writeBuffer,sizeof(writeBuffer));
       strcpy(writeBuffer,ADMIN_LOGIN_FAILED);

       writeBytes = write(connectionFD,writeBuffer , strlen(writeBuffer));
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

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_NAME_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_NAME_PROMT));
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

    writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_AGE_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_AGE_PROMT));
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
    writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_GENDER_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_GENDER_PROMT));
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

    writeBytes = write(connectionFD,ADMIN_NORMAL_CUSTOMER_PASSWORD_PROMT,strlen(ADMIN_NORMAL_CUSTOMER_PASSWORD_PROMT));
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

    int idFD = open(ID_FILE_PATH,O_RDWR);
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

    readBytes = read(idFD,readBuffer ,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to read ID file ");
    }
    int previous_id;
    if(readBytes==0){
        previous_id = 0;
    }
    else{previous_id = atoi(readBuffer);}
    customer.id = previous_id+1;
    previous_id = previous_id+1;
    sprintf(customer.login,"%d",previous_id);
    
    char new_id = previous_id;
    writeBytes = write(idFD,&new_id,sizeof(new_id));
    if(writeBytes<0){
        perror("Error while writing to new id to ID file");
    }

    flk.l_type =F_UNLCK;
    fcntl(idFD,F_SETLK,&flk);
    close(idFD);


    int accFD = open(ACCOUTN_NO_FILE_PATH,O_RDWR);
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

    readBytes = read(accFD,readBuffer ,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to account no file ");
    }
    int previous_account_no;
    if(readBytes==0){
        previous_account_no= 0;
    }
    else{previous_account_no = atoi(readBuffer);}
    customer.account_no = previous_account_no+1;
    previous_account_no = previous_account_no+1;
    
    char new_account_no = previous_account_no+1;
    writeBytes = write(accFD,&new_account_no,sizeof(new_account_no));
    if(writeBytes<0){
        perror("Error while writing to new account no to account no file");
    }

    flk.l_type =F_UNLCK;
    fcntl(accFD,F_SETLK,&flk);
    close(accFD);


    customer.balance=0.0;

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

 