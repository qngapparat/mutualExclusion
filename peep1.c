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

//NOTE ftol issues different keys for the two clients. Might have to do with one set to R, one to W. Using fixed key in the meantime

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
    shmaddr = shmat(shmid, NULL, 0);
    if(shmaddr == (char *)(-1)){
        perror("shmat");
        return EXIT_FAILURE;
    }


    //set integer
    /**(sharedInt) = 69420;
    printf("peep 1: set int to %d\n", *sharedInt);
*/

    strcpy(shmaddr, "hallo i bims xd");
    for(int i = 0; i < 10; i++){
            sleep(1);
            printf("resuming in %d\n", (10-i));
    }

    if((shmdt(shmaddr)) == -1){
        perror("shmdt");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
