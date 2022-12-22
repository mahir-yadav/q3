#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <time.h>
#define SHM_KEY 0x1234


struct shmseg {
   char buffer[40];
   int receive;
};

int main(int argc, char *argv[]) {
   sleep(3);            // For simuntaneously
   int shmid;
   struct shmseg *shmp;
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);  //Creating shared memory
   
   shmp = shmat(shmid, NULL, 0);
   int p=0;
   while (p<50) {
        printf("Received Strings are: \n") ;
        printf("%s\n",shmp->buffer);
        memset(shmp->buffer, 0, 40);
        p+=5;
        shmp->receive=p;
        sleep(3);
   }
   printf("P2 completed\n");
   

   return 0;
}

