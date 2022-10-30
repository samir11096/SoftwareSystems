#define INITIAL_DAILOGUE "=======Welocome to The Bank.=======\nPlease select your login type:\n1.Admin\t2.Customer\nEnter your option here: "
#define WRONG_INPUT "Wrong Input!!\n"

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
    int deleted;

};
#endif

#ifndef JOINT_CUSTOMER//used to avoid redefinitaion  error
#define JOINT_CUSTOMER
struct Joint_Customer
{
    int id; // 0 , 1 , 2 ....
    char primary_name[25]; // Name of one account holder
    char secondary_name[25];// Name of another account holder
    char primmay_customer_gender;// M -> Male , F -> Female 
    char secondary_customer_gender;
    int primary_customer_age;
    int secondary_customer_age;

    //Login Credentials
    char login[30]; // same as id
    char password[30];
    int account_no; // Account number of customer
    float balance;
    int deleted;
};
#endif

//paths
#define NORMAL_ID_FILE_PATH "./database/normal_account_id.txt"
#define NORMAL_ACCOUTN_NO_FILE_PATH "./database/normal_account_no.txt"
#define JOINT_ID_FILE_PATH "./database/joint_account_id.txt"
#define JOINT_ACCOUNT_NO_FILE_PATH "./database/joint_account_no.txt"
#define NORMAL_CUSTOMER_DETAILS_FILE "./database/normal_customer_details.txt"
#define JOINT_CUSTOMER_DETAILS_FILE "./database/joint_customer_details.txt"

#define CUSTOMER_NAME "Customer Name : "
#define CUSTOMER_AGE "Customer Age : "
#define CUSTOMER_GENDER "Customer Gender : "
#define CUSTOMER_LOGIN_ID "Customer Login Id : "
#define CUSTOMER_ACCOUNT_NO "Customer Account No : "
#define CUSTOMER_BALANCE "Customer Account Balance : " 

#define PRIMARY_CUSTOMER_NAME "Primary Customer Name : "
#define SECONDARY_CUSTOMER_NAME "Secondary Customer Name : "
#define PRIMARY_CUSTOMER_GENDER "Primary Customer Gender : "
#define SECONDARY_CUSTOMER_GENDER "Secondary Customer Gender : "
#define PRIMARY_CUSTOMER_AGE "Primary Customer Age : "
#define SECONDARY_CUSTOMER_AGE "Secondary Customer Age : "