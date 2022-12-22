#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

typedef struct
{
    int id;
    int bowls[2];
} Philosopher;

void *run_philosopher(void *ptr)
{
    Philosopher *philosopher = (Philosopher *)ptr;
    int i = philosopher->id;
    int left_bowl = philosopher->bowls[0];
    int right_bowl = philosopher->bowls[1];

    while (1)
    {
        printf("Philosopher %d is thinking\n", i);
        if (left_bowl > right_bowl)
        {
            printf("Philosopher %d is eating from bowl %d\n", i, right_bowl);
            printf("Philosopher %d is eating from bowl %d\n", i, left_bowl);
        }
        else
        {
            printf("Philosopher %d is eating from bowl %d\n", i, left_bowl);
            printf("Philosopher %d is eating from bowl %d\n", i, right_bowl);
        }
    }
    return NULL;
}

int main()
{
    Philosopher philosophers[NUM_PHILOSOPHERS];
    pthread_t threads[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosophers[i].id = i;
        philosophers[i].bowls[0] = i;
        philosophers[i].bowls[1] = (i + 1) % NUM_PHILOSOPHERS;
        pthread_create(&threads[i], NULL, run_philosopher, &philosophers[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}