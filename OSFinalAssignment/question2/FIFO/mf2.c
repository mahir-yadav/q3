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


int main(){
    int fd1;

    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    char buffer[100];
    char acknow[5];
    int idx=0;
    while (idx < 50)
    {
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, buffer , 100);
        printf("Received Strings are: \n") ;
        printf("%s\n",buffer);
        close(fd1);
        memset(buffer, 0, 100);

        idx += 5;
        char ind[5];
        sprintf(ind,"%d",idx);
	    strcpy(acknow,ind);

        fd1 = open(myfifo,O_WRONLY);
        write(fd1, acknow, strlen(acknow)+1);
        close(fd1);

    }

    printf("P2 completed\n");
   

    return 0;
}