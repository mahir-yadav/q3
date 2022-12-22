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

#define BILLION 1000000000L
long double t1;


char Choices[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char array[300];

void generator(){
    srand(time(NULL));
    for(int i=0;i<250;i++){
        array[i] = Choices[rand() % 52];
    }
}


struct shmseg {
   char buffer[40];
   int receive;
};

int main(int argc, char *argv[]) {
    generator();
    int l=0;
    for(int i=0;i<50;i++){
        for(int j=0;j<5;j++){
            printf("%c",array[l++]);
        }
        printf("\n");
    }

    long long int diff;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int shmid;
    struct shmseg *shmp;
    
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
  
   
   shmp = shmat(shmid, NULL, 0);
   
   
    int a=0;
    int b=0;
   while(1){

        memset(shmp->buffer, 0, 40);
        int k=0;
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                shmp->buffer[k++]=array[a++];
            }
            shmp->buffer[k++]='\n';
        }

        printf("Sent string from %d to %d \n",b,b+5);
        // printf("%s",shmp->buffer);
            
        sleep(3);

        // memset(shmp->buffer, 0, 40);

        printf("Maximum id received:  %d\n", shmp->receive);
        
        printf("\n");

        if(shmp->receive ==50){
            printf(" All Strings sent successfuly\n");
            break;
        }


        b+=5;

}

    printf("P1 completed\n");
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("\nTime for completion in Shared Memory %llu nanoseconds\n", (long long unsigned int)diff);
    
    return 0;
}
