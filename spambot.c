#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

    //fork variables
    pid_t pid;

    //fifo variables
    const char* fifoPath = "/home/qngapparat/Documents/git/mutualExclusion/myFifo";
    const int MAX_FIFO_BUF = 1024;
    int fd;
    char fifoBuffer[MAX_FIFO_BUF];


    //shm variables
    int shmid;
    key_t key;
    const char* shmPath = "/home/qngapparat/Documents/git/mutualExclusion/shmem.txt";
    int* sharedInt;

/*
    for(int i = 0; i < 100; i++){
        //child code
        if(!(pid = fork())){
            //initialize shared integer
            if((key = ftok(shmPath, 'W') == -1)){
                perror("child ftok");
                return EXIT_FAILURE;
            }

            if((shmid = shmget(key, 1024, 0666 | IPC_CREAT)) == -1){
                perror("child shmget");
                return EXIT_FAILURE;
            }

            //NOTE possible problem source
            sharedInt = shmat(shmid, NULL, 0);
            if(sharedInt == (int *)(-1)){
                perror("child shmat");
                return EXIT_FAILURE;
            }

            //increase shared integer 100 times
            for(int i = 0; i < 100; i++){
                sharedInt++;
            }

            //exit child threads
            exit(EXIT_SUCCESS);


        }
    }

    //wait for all childs to terminate
    for(int i = 0; i < 100; i++){
        wait(NULL);
    }
*/

    //read shared variable

    //create file key
    key = 2002;

    if((shmid = shmget(key, 1024, 0666 | IPC_CREAT)) == -1){
        perror("child shmget");
        return EXIT_FAILURE;
    }

    sharedInt = shmat(shmid, NULL, 0);
    if(sharedInt == (int *)(-1)){
        perror("child shmat");
        return EXIT_FAILURE;
    }

    printf("Spambot Parent: shared integer: %d\n", *sharedInt);
    //open fifo
    fd = open(fifoPath, O_WRONLY);

    //converting int to string
    char sharedIntString[30];
    sprintf(sharedIntString, "%d", *sharedInt);
    write(fd, sharedIntString, strlen(sharedIntString)+1); //+1 including EOF

    close(fd);

    printf("Spambot: parent: terminating\n");
    return EXIT_SUCCESS;
}
