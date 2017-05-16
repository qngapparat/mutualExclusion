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

//TODO shmdt() at the end

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
    const char* shmPath = "/home/qngapparat/Documents/git/mutualExclusion/shmem";

    //create file key
    key = 2004;

    //create shared memory
    if((shmid = shmget(key, 1024, 0666 | IPC_CREAT)) == -1){
        perror("shmget");
        return EXIT_FAILURE;
    }

    //attach and cast shared memory as a global variable
    sharedInt = shmat(shmid, NULL, 0);
    if(sharedInt == (int *)(-1)){
        perror("shmat");
        return EXIT_FAILURE;
    }

    //set integer
    *(sharedInt) = 334455;
    printf("shared int: %d\n", *sharedInt);



    //detach form shared memory
    shmdt(sharedInt);

    printf("Creator: proceeding to read\n");

    /*for(int i = 0; i < 5; i++){
        sleep(1);
        printf("resuming in %d\n", (5-i));
    }*/

    //listen on FIFO for integer
    fd = open(fifoPath, O_RDONLY);
    read(fd, fifoBuffer, MAX_FIFO_BUF);
    printf("Creator: String received thru fifo: %s\n", fifoBuffer);
    memset(fifoBuffer, 0, MAX_FIFO_BUF);

    close(fd);
    /*
    if((shmdt(sharedInt)) == -1){
        perror("shmdt");
        return EXIT_FAILURE;
    }*/

    printf("Creator: terminating\n");
    return EXIT_SUCCESS;
}
