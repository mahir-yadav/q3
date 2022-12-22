#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
sem_t spoon[5];

void * philosopher(void * num)
{
    while(1){
        int philo=*(int *)num;

        int k = (philo + 1)%5;

        if(philo==4){
            printf("Philospher %d is trying to pick left spoon\n",philo);
            sem_wait(&spoon[philo]);
            printf("Philospher %d has picked the left spoon\n",philo);
            
            printf("Philospher %d is trying to pick right spoon\n",philo);
            sem_wait(&spoon[k]);
            printf("Philospher %d has picked the right spoon\n",philo);
        }
        
        else{
            printf("Philospher %d is trying to pick right spoon\n",philo);
            sem_wait(&spoon[k]);
            printf("Philospher %d has picked the right spoon\n",philo);
            
            printf("Philospher %d is trying to pick left spoon\n",philo);
            sem_wait(&spoon[philo]);
            printf("Philospher %d has picked the left spoon\n",philo);
        }

        printf("\n");
        printf("Philospher %d eating\n",philo);
        printf("\n");
        sem_post(&spoon[philo]);
        printf("Philospher %d has leave left spoon\n",philo);
        sem_post(&spoon[k]);
        printf("Philospher %d has leave right spoon\n",philo);
        
	
    }
}




int main()
{
	int n[5];
	pthread_t p[5];
	
	for(int i=0;i<5;i++){
        n[i]=i;
		sem_init(&spoon[i],0,1);
    }
		
	for(int i=0;i<5;i++){
		pthread_create(&p[i],NULL,philosopher,(void *)&n[i]);
	}
    
	for(int i=0;i<5;i++)
		pthread_join(p[i],NULL);

    return 0;
}


