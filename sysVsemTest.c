#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>


int main(int argc, char const *argv[]) {

    int someNumber = 1;
    int semId;
    key_t key = 120;

    //sembuf structs are an array of pointers to variables (?)
    struct sembuf sem_lock = { semId, -1, SEM_UNDO };

    struct sembuf sem_unlock = { semId, 1, SEM_UNDO };

    //create semaphore
    if((semId = semget(key, 1, IPC_CREAT | 0660)) == -1){
        perror("semget");
        return EXIT_FAILURE;
    }

    //initialize semaphore
    //union that includes the semaphore value to be set
    union semun init;
    init.val = 1;
    //use union among others to SETVAL semaphone #0 to value init.val (1)
    semctl(semId, 0, SETVAL, init);

    //create lock
    if((semop(semId, &sem_lock, 1) == -1)){
        perror("semop locking");
        return EXIT_FAILURE;
    }

    //critical region

    someNumber += 1;

    //end critical region

    //create unlock
    if((semop(semId, &sem_unlock, 1) == -1)){
        perror("semop locking");
        return EXIT_FAILURE;
    }



    return EXIT_SUCCESS;
}
