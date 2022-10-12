#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<fcntl.h>
#include<stdbool.h>

#include "../constants/customer_constants.h"
#include "../constants/constants.h"




//declaring requred function handlers
void customer_handler(int connectionFD);
bool customer_login_handler(int connectionFD,int * customer_type , int * customer_id);
bool normal_customer_login_handler(int connectionFD,int * login_id);
bool joint_customer_login_handler(int connectionFD,int * login_id);
void deposit(int connectionFD,int customer_type ,int customer_id);
void withdraw(int connectionFD,int customer_type,int customer_id);
void balance_enquiry(int connectionFD);
void password_change(int connectionFD);
void view_details(int connectionFD);
void exit();//TBD


//defining required function handlers
bool customer_login_handler(int connectionFD,int * customer_type,int * customer_id){
        int readBytes, writeBytes;
        char readBuffer[500] , writeBuffer[500] ;
        int customer_type_choice;

        bzero(readBuffer,sizeof(readBuffer));
        bzero(writeBuffer,sizeof(writeBuffer));

        strcpy(writeBuffer,LOGIN_PROMT);
        strcat(writeBuffer,LOGIN_CHOICE_PROMT);

        writeBytes = write(connectionFD, writeBuffer,strlen(writeBuffer));

        if(writeBytes<0){
            perror("Error while displaying  login choice prompt to customer");
            return false;
        }

        readBytes = read(connectionFD ,readBuffer,sizeof(readBuffer));
        if(readBytes<0){
            perror("Error while entering login choice by customer ");
            return false;
        }

        customer_type_choice = atoi(readBuffer);
        *customer_type = customer_type_choice;  

        switch(customer_type_choice){
            case 1: 
                return normal_customer_login_handler(connectionFD,customer_id);
                break;
            
            case 2:
                return joint_customer_login_handler(connectionFD,customer_id);
                break;
            default:
                //return error for input
                break;
        }

        return false;
}

bool normal_customer_login_handler(int connectionFD,int * login_id){

    int readBytes , writeBytes, customer_id;
    char readBuffer[500], writeBuffer[500],password[500];
    struct Normal_Customer customer;

     
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    strcpy(writeBuffer,LOGIN_ID_PROMT);
    
    writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
    if(writeBytes<0){
        perror("Error while normal customer login id prompt");
        return false;
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));

    if(readBytes<0){
        perror("Error while normal customer login reading!");
        return false;
    }

    customer_id = atoi(readBuffer);
    *login_id = customer_id;

    int customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDONLY);
    if(customerFD<0){
        perror("Error while openining customer details file!");
        return false;
    }

    int offset= lseek(customerFD , (customer_id-1)*(sizeof(struct Normal_Customer)),SEEK_SET);
    if(offset<0){
        writeBytes = write(connectionFD,LOGIN_ID_DOES_NOT_EXISTS,strlen(LOGIN_ID_DOES_NOT_EXISTS));
        return false;
    }
    else{

        struct flock flk ;

        flk.l_type = F_RDLCK;
        flk.l_whence = SEEK_SET;
        flk.l_start = (customer_id-1)*sizeof(struct Normal_Customer);
        flk.l_len = sizeof(struct Normal_Customer);
        flk.l_pid = getpid();


        int lockStatus  = fcntl(customerFD,F_SETLKW,&flk);
        if(lockStatus <0){
            perror("Error while read locking the  Normal Customer file!");
            return false;
        }
        
        offset= lseek(customerFD , (customer_id-1)*(sizeof(struct Normal_Customer)),SEEK_SET);
        if(offset<0){
            perror("Error while trying to reposition the offset of normal customer details file");
        }
        readBytes = read(customerFD,&customer,sizeof(struct Normal_Customer));

        if(readBytes <0){
            perror("Error while reading customer details!");
            return false;
        }
        
        flk.l_type = F_UNLCK;
        fcntl(customerFD,F_SETLKW,&flk);

    }

    close(customerFD);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));
    writeBytes = write(connectionFD , PASSWORD_PROMT,strlen(PASSWORD_PROMT));
    if(writeBytes<0){
        perror("Error while password prompt !");
        return false;
    }

    readBytes = read(connectionFD ,readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading the password!");
        return false;
    }

    strcpy(password,readBuffer);

    if(strcmp(password,customer.password)){
        return true;
    }
    else{
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connectionFD , INVALID_PASSWORD,strlen(INVALID_PASSWORD));
        return false;
    }
    
    return false;

}
    

bool joint_customer_login_handler(int connectionFD,int * login_id){
    
    int readBytes , writeBytes, customer_id;
    char readBuffer[500], writeBuffer[500],password[500];
    struct Joint_Customer customer;

     
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    strcpy(writeBuffer,LOGIN_ID_PROMT);
    
    writeBytes = write(connectionFD,writeBuffer,strlen(writeBuffer));
    if(writeBytes<0){
        perror("Error while joint customer login id prompt");
        return false;
    }

    readBytes = read(connectionFD , readBuffer , sizeof(readBuffer));

    if(readBytes<0){
        perror("Error while joint customer login reading!");
        return false;
    }

    customer_id = atoi(readBuffer);
    *login_id = customer_id;

    int customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDONLY);
    if(customerFD<0){
        perror("Error while openining customer details file!");
        return false;
    }

    int offset= lseek(customerFD , (customer_id-1)*(sizeof(struct Joint_Customer)),SEEK_SET);
    if(offset<0){
        writeBytes = write(connectionFD,LOGIN_ID_DOES_NOT_EXISTS,strlen(LOGIN_ID_DOES_NOT_EXISTS));
        return false;
    }
    else{

        struct flock flk ;

        flk.l_type = F_RDLCK;
        flk.l_whence = SEEK_SET;
        flk.l_start = (customer_id-1)*sizeof(struct Joint_Customer);
        flk.l_len = sizeof(struct Joint_Customer);
        flk.l_pid = getpid();


        int lockStatus  = fcntl(customerFD,F_SETLKW,&flk);
        if(lockStatus <0){
            perror("Error while read locking the Joint Customer file!");
            return false;
        }
        offset = lseek(customerFD,(customer_id-1)*(sizeof(struct Joint_Customer)),SEEK_SET);
        if(offset<0){
            perror("Error while trying to position the offset of joint customer details");
        }
        readBytes = read(customerFD,&customer,sizeof(struct Joint_Customer));

        if(readBytes <0){
            perror("Error while reading customer details!");
            return false;
        }

        flk.l_type = F_UNLCK;
        fcntl(customerFD,F_SETLKW,&flk);

    }

    close(customerFD);

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));
    writeBytes = write(connectionFD , PASSWORD_PROMT,strlen(PASSWORD_PROMT));
    if(writeBytes<0){
        perror("Error while password prompt !");
        return false;
    }

    readBytes = read(connectionFD ,readBuffer , sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while reading the password!");
        return false;
    }

    strcpy(password,readBuffer);

    if(strcmp(password,customer.password)){
        return true;
    }
    else{
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connectionFD , INVALID_PASSWORD,strlen(INVALID_PASSWORD));
        return false;
    }
    
    return false;
}

void customer_handle(int connectionFD){
    int readBytes,writeBytes;
    char readBuffer[500],writeBuffer[500];

    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    int customer_type ;//normal user = 1 , joint user =2
    int customer_id;
    if(customer_login_handler(connectionFD,&customer_type,&customer_id)){
        writeBytes= write(connectionFD,CUSTOMER_MENU_PROMT,strlen(CUSTOMER_MENU_PROMT));
        if(writeBytes<0){
            perror("Error while displaying  customer menu prompt");
        }

        readBytes = read(connectionFD,readBuffer,sizeof(readBuffer));
        if(readBytes<0){
            perror("Error while reading customer menu input");
        }
        int menu_choice = atoi(readBuffer);
        switch(menu_choice){
            case 1:
                deposit(connectionFD,customer_type,customer_id);
                break;
            
            case 2:
                //Withdraw
                withdraw(connectionFD,customer_type,customer_id);
                break;
            
            case 3:
                //balance enquiry
                break;
            
            case 4:
                //password changes
                break;
            case 5:
                //View account details
                break;
            default:
                break;
        }
        
    }

}


void deposit(int connectionFD ,int customer_type , int customer_id){
    int readBytes , writeBytes ;
    char readBuffer[500], writeBuffer[500];
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    writeBytes = write(connectionFD,CUSTOMER_AMOUNT_DEPOSIT_PROMT,strlen(CUSTOMER_AMOUNT_DEPOSIT_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the amount promot");
    }
    readBytes = read(connectionFD,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to read deposit amount");
    }
    float amount_to_deposit = atof(readBuffer);//converting string to float

    int customerFD;
    if(customer_type ==1 ){
        struct Normal_Customer customer;
        customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDWR);
        if(customerFD<0){
            perror("Error while trying to open the normla customer details file");
        }
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

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Noraml_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the normal customer details file ");
        }
        readBytes = read(customerFD,&customer,sizeof(struct Normal_Customer));
        if(readBytes<0){
            perror("Error while trying to read noraml customer to deposit");
        }
        //updating the balance
        customer.balance += amount_to_deposit;

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Noraml_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the normal customer details file ");
        }

        writeBytes = write(customerFD,&customer,sizeof(struct Normal_Customer));
        if(writeBytes<0){
            perror("Error while updating the normal customer file for deposit");
        }
        
    }
    else if (customer_type ==2 ){

        struct Joint_Customer customer;
        customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDWR);
        if(customerFD<0){
            perror("Error while trying to open the joint customer details file");
        }
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

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Joint_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the joint customer details file ");
        }
        readBytes = read(customerFD,&customer,sizeof(struct Joint_Customer));
        if(readBytes<0){
            perror("Error while trying to read joint customer to deposit");
        }
        //updating the balance
        customer.balance += amount_to_deposit;

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Joint_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the joint customer details file ");
        }

        writeBytes = write(customerFD,&customer,sizeof(struct Joint_Customer));
        if(writeBytes<0){
            perror("Error while updating the joint customer file for deposit");
        }
        
    }

    writeBytes = write(connectionFD,CUSTOMER_DEPOSIT_SUCCESS_PROMT,strlen(CUSTOMER_DEPOSIT_SUCCESS_PROMT));
    if(writeBytes<0){
        perror("Error while trying to promt deposit sucess");
    }

}

void withdraw(int connectionFD,int customer_type,int customer_id){

    int readBytes , writeBytes ;
    char readBuffer[500], writeBuffer[500];
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    writeBytes = write(connectionFD,CUSTOMER_AMOUNT_WITHDRAW_PROMT,strlen(CUSTOMER_AMOUNT_WITHDRAW_PROMT));
    if(writeBytes<0){
        perror("Error while displaying the amount promot");
    }
    readBytes = read(connectionFD,readBuffer,sizeof(readBuffer));
    if(readBytes<0){
        perror("Error while trying to read deposit amount");
    }
    float amount_to_withdraw = atof(readBuffer);//converting string to float

    int customerFD;
    if(customer_type ==1 ){
        struct Normal_Customer customer;
        customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDWR);
        if(customerFD<0){
            perror("Error while trying to open the normla customer details file");
        }
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

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Noraml_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the normal customer details file ");
        }
        readBytes = read(customerFD,&customer,sizeof(struct Normal_Customer));
        if(readBytes<0){
            perror("Error while trying to read noraml customer to withdraw");
        }
        //updating the balance
        float bal = customer.balance- amount_to_withdraw;
        if(bal<0){
            writeBytes = write(connectionFD,CUSTOMER_INSUFFICIENT_BALANCE,strlen(CUSTOMER_INSUFFICIENT_BALANCE));
            if(writeBytes<0){
                perror("Error while trying to prompt insufficent balance");
            }
            return ;
        }
        //updating the balance on else condition
        customer.balance = bal;

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Noraml_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the normal customer details file ");
        }

        writeBytes = write(customerFD,&customer,sizeof(struct Normal_Customer));
        if(writeBytes<0){
            perror("Error while updating the normal customer file for deposit");
        }
        
    }
    else if (customer_type ==2 ){

        struct Joint_Customer customer;
        customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDWR);
        if(customerFD<0){
            perror("Error while trying to open the Joint customer details file");
        }
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

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Joint_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the joint customer details file ");
        }
        readBytes = read(customerFD,&customer,sizeof(struct Joint_Customer));
        if(readBytes<0){
            perror("Error while trying to read joint customer to withdraw");
        }
        //updating the balance
        float bal = customer.balance- amount_to_withdraw;
        if(bal<0){
            writeBytes = write(connectionFD,CUSTOMER_INSUFFICIENT_BALANCE,strlen(CUSTOMER_INSUFFICIENT_BALANCE));
            if(writeBytes<0){
                perror("Error while trying to prompt insufficent balance");
            }
            return ;
        }
        //updating the balance on else condition
        customer.balance = bal;

        int offSet = lseek(customerFD, (customer_id-1)*(sizeof(struct Joint_Customer)),SEEK_SET);
        if(offSet<0){
            perror("Error while trying reposition the offset of the joint customer details file ");
        }

        writeBytes = write(customerFD,&customer,sizeof(struct Joint_Customer));
        if(writeBytes<0){
            perror("Error while updating the joint customer file for deposit");
        }
        
    }

    writeBytes = write(connectionFD,CUSTOMER_WITHDRAW_SUCCESS,strlen(CUSTOMER_WITHDRAW_SUCCESS));
    if(writeBytes<0){
        perror("Error while trying to promt withdraw sucess");
    }

}


void balance_enquiry(int connectionFD ,int customer_type,int customer_id){}