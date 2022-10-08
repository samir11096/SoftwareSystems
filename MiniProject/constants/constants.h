#define INITIAL_DAILOGUE "=======Welocome to The Bank.=======\nPlease select your login type:\n1.Admin\t2.Customer\nEnter your option here: "

//using #ifndef to check if its is not defined twice
#ifndef NORMAL_CUSTOMER
#define NORMAL_CUSTOMER
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
    int account_no; // Account number of the customer
    float balance;

};
#endif

#ifndef JOINT_CUSTOMER
#define JOINT_CUSTOMER
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
    int account_no; // Account number of customer
    float balance;
};
#endif


#define ID_FILE_PATH "./database/id.txt"
#define ACCOUTN_NO_FILE_PATH "./database/account_no.txt"
#define NORMAL_CUSTOMER_DETAILS_FILE "./database/normal_customer_details.txt"
#define JOINT_CUSTOMER_DETAILS_FILE "./database/joint_customer_details.txt"