/*Write a program to implement semaphore to protect any critical section.
 c. protect multiple pseudo resources ( may be two) using counting semaphore

 Name -> Samir Ahmed Ghouri 
 Roll -> MT2022100

 */
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
        int fileDescriptor;
        int readBytes, lseekoffset;

        key_t semKey;
        int status;
        int id;
        int data;

        fileDescriptor = open("ticket.txt", O_RDONLY);
        if (fileDescriptor == -1)
        {
                perror("Error while creating / opening the ticket file!");
        }

        union semun
        {
                int val;
        }

        semSet;

        semKey = ftok(".", 331);
        if (semKey == -1)
        {
                perror("Error while computing key!");
        }

        id = semget(semKey, 1, 0);
        if (id == -1)
        {
                id = semget(semKey, 1, IPC_CREAT | 0700);
                if (id == -1)
                {
                        perror("Error while creating semaphore!");
                }

                semSet.val = 2;
                status = semctl(id, 0, SETVAL, semSet);
                if (status == -1)
                {
                        perror("Error while initializing a binary sempahore!");
                }
        }

        struct sembuf semOp;
        semOp.sem_num = 0;
        semOp.sem_flg = IPC_NOWAIT;

        printf("Press enter to obtain lock for the critical section!\n");
        getchar();

        semOp.sem_op = -1;
        status = semop(id, &semOp, 1);
        if (status == -1)
        {
                perror("Error while operating on semaphore!");
        }

        printf("Obtained lock on critical section!");

        printf("Now entering critical section!");

        readBytes = read(fileDescriptor, &data, 20);
        if (readBytes == -1)
        {
                perror("Error while reading from sample file!");
        }
        else if (readBytes == 0)	// Sample file has no data
                printf("No data exists!\n");
        else
                printf("Sample data: \n %d", data);

        printf("\n\nPress enter key to exit critical section!\n");
        getchar();

        semOp.sem_op = 1;
        status = semop(id, &semOp, 1);
        if (status == -1)
        {
                perror("Error while operating on semaphore!");
        }

        return 0;
}
