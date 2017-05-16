#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

    //fifo variables
    const char* fifoPath = "/home/qngapparat/Documents/git/mutualExclusion/myFifo";
    const int MAX_FIFO_BUF = 1024;
    int fd;
    char fifoBuffer[MAX_FIFO_BUF];

    //shm variables
    int shmid;
    key_t key;
    int* sharedInt;
    const char* shmPath = "/home/qngapparat/Documents/git/mutualExclusion/shmem.txt";

    //create file key
    if((key = ftok(shmPath, 'W')) == -1){
        perror("ftok");
        return EXIT_FAILURE;
    }

    //create shared memory
    if((shmid = shmget(key, 1024, 0666 | IPC_CREAT)) == -1){
        perror("shmget");
        return EXIT_FAILURE;
    }

    //attach and cast shared memory as a global variable
    sharedInt = shmat(shmid, (void *)0, 0);
    if(sharedInt == (int *)(-1)){
        perror("shmat");
        return EXIT_FAILURE;
    }


    //set integer
    *(sharedInt) = 69420;
    printf("shared int: %d\n", *sharedInt);

    //detach form shared memory
    shmdt(sharedInt);

    printf("Creator: going to sleep before reading");
    sleep(10);

    //listen on FIFO for integer
    fd = open(fifoPath, O_RDONLY);
    read(fd, fifoBuffer, MAX_FIFO_BUF);
    memset(fifoBuffer, 0, MAX_FIFO_BUF);
    printf("Creator: Integer received thru fifo: %s\n", fifoBuffer);

    printf("Creator: terminating\n");
    return EXIT_SUCCESS;
}
