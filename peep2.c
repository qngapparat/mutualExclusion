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

    int shmid;
    key_t key;
    int* sharedInt;
    char* shmaddr;
    const char* shmPath = "/home/qngapparat/Documents/git/mutualExclusion/shmem";

    key = 2001;

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
    printf("peep 2: int is %d\n", *sharedInt);

    if((shmdt(sharedInt)) == -1){
        perror("shmdt");
        return EXIT_FAILURE;
    }



    return EXIT_SUCCESS;
}
