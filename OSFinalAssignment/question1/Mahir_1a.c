#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define EATING_TIME 1

int chopsticks[5];

void taking(int n)
{
    chopsticks[n] = 1;
    printf("Philospher %d has taken left chopstick\n", n);
    chopsticks[(n + 1) % 5] = 1;
    printf("Philospher %d has taken right chopstick\n", (n + 1) % 5);
}

void putting(int n)
{
    chopsticks[n] = 1;
    printf("Philospher %d has leave the left chopstick\n", n);
    chopsticks[(n + 1) % 5] = 1;
    printf("Philospher %d has leave the right chopstick\n", (n + 1) % 5);
}

void *philosopher(void *arg)
{
    int id = *((int *)arg);

    while (1)
    {
        printf("Philospher %d is thinking\n", id);
        sleep(1);

        taking(id);
        printf("Philospher %d is eating\n", id);
        sleep(EATING_TIME);

        putting(id);
    }

    return NULL;
}

int main(void)
{
    pthread_t philosophers[5];
    int ids[5];

    for (int i = 0; i < 5; i++)
    {
        chopsticks[i] = 0;
    }

    for (int i = 0; i < 5; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
