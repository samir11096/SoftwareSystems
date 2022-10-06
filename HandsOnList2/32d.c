/*Write a program to implement semaphore to protect any critical section.
d. remove the created semaphore

Name -> Samir Ahmed Ghouri
Roll -> MT2022100
*/

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <unistd.h>  
#include <stdio.h>   

int main()
{
    key_t semKey;
    int id;
    int status;

    semKey = ftok(".", 1);
    if (semKey == -1)
    {
        perror("Error while computing key!");
    }

    printf("Press Enter to create a semaphore\n");
    getchar();

    id = semget(semKey, 1, IPC_CREAT | 0700);

    if (id == -1)
    {
        perror("Error while creating semaphore!");
    }

    printf("Semaphore created with id %d \n",id);

    printf("Press enter to delete the semaphore!\n");
    getchar();

    status = semctl(id, 0, IPC_RMID);

    if (status == -1)
    {
        perror("Error while deleting semaphore!");
    }
    return 0;
}
