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

//declaration of admin handlers

void admin_handler(int connectionFD);
bool admin_login_handler(int connectinFD);
bool add_customer(int connectionFD);
void add_noraml_customer(int connectionFD);
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

    bzero(writeBuffer,sizeof(writeBuffer));
    bzero(readBuffer,sizeof(readBuffer));

    writeBytes = write()





}