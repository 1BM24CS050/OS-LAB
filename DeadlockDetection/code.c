#include <stdio.h>
#include <stdbool.h>

int main()
{
    int P, R;

    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resource types: ");
    scanf("%d", &R);

    int allocation[P][R];
    int request[P][R];
    int available[R];
    int work[R];

    bool finish[P];

    printf("Enter Allocation Matrix:\n");
    for(int i = 0; i < P; i++)
        for(int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request Matrix:\n");
    for(int i = 0; i < P; i++)
        for(int j = 0; j < R; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for(int j = 0; j < R; j++)
        scanf("%d", &available[j]);

    for(int j = 0; j < R; j++)
        work[j] = available[j];

    for(int i = 0; i < P; i++)
        finish[i] = false;

    bool found;

    do
    {
        found = false;

        for(int i = 0; i < P; i++)
        {
            if(!finish[i])
            {
                bool canExecute = true;

                for(int j = 0; j < R; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        canExecute = false;
                        break;
                    }
                }

                if(canExecute)
                {
                    for(int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    found = true;
                }
            }
        }
    }
    while(found);

    bool deadlock = false;

    for(int i = 0; i < P; i++)
    {
        if(!finish[i])
        {
            deadlock = true;
            printf("Process P%d is deadlocked\n", i);
        }
    }

    if(!deadlock)
        printf("No deadlock detected\n");

    return 0;
}