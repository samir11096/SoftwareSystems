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


//defining customer structure for file storage
struct Normal_Customer
{
    int id; // 0, 1, 2 ....
    char name[25];
    char gender; // M -> Male, F -> Female, O -> Other
    int age;
    // Login Credentials
    char login[30]; // same as id
    char password[30];
    // Bank data
    int account; // Account number of the customer
    int balance;
    
};

struct Joint_Customer
{
    int id; // 0 , 1 , 2 ....
    char primary_name[25]; // Name of one account holder
    char secondary_name[25];// Name of another account holder
    char gender;// M -> Male , F -> Female 
    int age;

    //Login Credentials
    char login[30]; // same as id
    char password[30];
    int account; // Account number of customer
};


//declaring requred function handlers
bool customer_handler(int connectionFD);
bool customer_login_handler(int connectionFD);
bool normal_customer_login_handler(int connectionFD);
bool joint_customer_login_handler(int connectionFD);


//defining required function handlers
bool customer_login_handler(int connectionFD){
        int readBytes, writeBytes;
        char readBuffer[500] , writeBuffer[500] ;
        int customer_type_choice;

        bzero(readBuffer,sizeof(readBuffer));
        bzero(writeBuffer,sizeof(writeBuffer));

        strcpy(writeBuffer,LOGIN_PROMT);
        strcat(writeBuffer,LOGIN_CHOICE_PROMT);

        writeBytes = write(connectionFD, writeBuffer,sizeof(writeBuffer));

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

        switch(customer_type_choice){
            case 1: 
                return normal_customer_login_handler(connectionFD);
                break;
            
            case 2:
                return joint_customer_login_handler(connectionFD);
                break;
            default:
                break;
        }

        return false;
}

bool normal_customer_login_handler(int connectionFD){

    int readBytes , writeBytes, customer_id;
    char readBuffer[500], writeBuffer[500],password[500];
    struct Normal_Customer customer;

     
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    strcpy(writeBuffer,LOGIN_ID_PROMT);
    
    writeBytes = write(connectionFD,writeBuffer,sizeof(writeBuffer));
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

    int customerFD = open(NORMAL_CUSTOMER_DETAILS_FILE,O_RDONLY);
    if(customerFD<0){
        perror("Error while openining customer details file!");
        return false;
    }

    int offset= lseek(customerFD , customer_id*(sizeof(struct Normal_Customer)),SEEK_SET);
    if(offset<0){
        writeBytes = write(connectionFD,LOGIN_ID_DOES_NOT_EXISTS,sizeof(LOGIN_ID_DOES_NOT_EXISTS));
        return false;
    }
    else{

        struct flock flk ;

        flk.l_type = F_RDLCK;
        flk.l_whence = SEEK_SET;
        flk.l_start = customer_id*sizeof(struct Normal_Customer);
        flk.l_len = sizeof(struct Normal_Customer);
        flk.l_pid = getpid();


        int lockStatus  = fcntl(customerFD,F_SETLKW,&flk);
        if(lockStatus <0){
            perror("Error while read locking the  Normal Customer file!");
            return false;
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
    writeBytes = write(connectionFD , PASSWORD_PROMT,sizeof(PASSWORD_PROMT));
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
        writeBytes = write(connectionFD , INVALID_PASSWORD,sizeof(INVALID_PASSWORD));
        return false;
    }
    
    return false;

}
    

bool joint_customer_login_handler(int connectionFD){
    
    int readBytes , writeBytes, customer_id;
    char readBuffer[500], writeBuffer[500],password[500];
    struct Joint_Customer customer;

     
    bzero(readBuffer,sizeof(readBuffer));
    bzero(writeBuffer,sizeof(writeBuffer));

    strcpy(writeBuffer,LOGIN_ID_PROMT);
    
    writeBytes = write(connectionFD,writeBuffer,sizeof(writeBuffer));
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

    int customerFD = open(JOINT_CUSTOMER_DETAILS_FILE,O_RDONLY);
    if(customerFD<0){
        perror("Error while openining customer details file!");
        return false;
    }

    int offset= lseek(customerFD , customer_id*(sizeof(struct Normal_Customer)),SEEK_SET);
    if(offset<0){
        writeBytes = write(connectionFD,LOGIN_ID_DOES_NOT_EXISTS,sizeof(LOGIN_ID_DOES_NOT_EXISTS));
        return false;
    }
    else{

        struct flock flk ;

        flk.l_type = F_RDLCK;
        flk.l_whence = SEEK_SET;
        flk.l_start = customer_id*sizeof(struct Joint_Customer);
        flk.l_len = sizeof(struct Joint_Customer);
        flk.l_pid = getpid();


        int lockStatus  = fcntl(customerFD,F_SETLKW,&flk);
        if(lockStatus <0){
            perror("Error while read locking the Joint Customer file!");
            return false;
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
    writeBytes = write(connectionFD , PASSWORD_PROMT,sizeof(PASSWORD_PROMT));
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
        writeBytes = write(connectionFD , INVALID_PASSWORD,sizeof(INVALID_PASSWORD));
        return false;
    }
    
    return false;
}





