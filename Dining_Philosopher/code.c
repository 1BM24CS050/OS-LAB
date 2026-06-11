#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Deadlock prevention:
        // Last philosopher picks right fork first
        if (id == N - 1)
        {
            sem_wait(&forks[(id + 1) % N]);
            sem_wait(&forks[id]);
        }
        else
        {
            sem_wait(&forks[id]);
            sem_wait(&forks[(id + 1) % N]);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating and put down forks\n", id);
    }

    return NULL;
}

int main()
{
    pthread_t thread_id[N];
    int phil_ids[N];

    for (int i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
        phil_ids[i] = i;
    }

    for (int i = 0; i < N; i++)
    {
        pthread_create(
            &thread_id[i],
            NULL,
            philosopher,
            &phil_ids[i]
        );
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    for (int i = 0; i < N; i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}