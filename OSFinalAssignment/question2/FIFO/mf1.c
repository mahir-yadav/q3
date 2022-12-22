#include<stdio.h>
#include <sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <time.h>
#include <fcntl.h>


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

int main(){
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

    int fd;
    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    char buffer[100];
    char acknow[5];
    int a=0;
    int b=0;
    int received;
    while(1){
        memset(buffer, 0, 40);

        fd = open(myfifo, O_WRONLY);

        int k=0;
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                buffer[k++]=array[a++];
            }
            buffer[k++]='\n';
        }
        printf("Sent string from %d to %d \n",b,b+5);

        write(fd, buffer, strlen(buffer)+1);
        close(fd);


        fd = open(myfifo, O_RDONLY);

        read(fd, acknow, sizeof(acknow));
        received =  atoi(acknow);

        printf("Acknowledge id received:  %d\n", received);

        close(fd);

        if(received==50){
            printf("All strings sent successfuly\n");
            break;
        }


        b+=5;
    }

    printf("P1 completed\n");
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("\nTime for completion in FIFO %llu nanoseconds\n", (long long unsigned int)diff);
    
    return 0;


}