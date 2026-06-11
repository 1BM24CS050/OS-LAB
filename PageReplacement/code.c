#include <stdio.h>

void FIFO(int pages[], int n, int frameCount)
{
    int frames[20];
    int front = 0;
    int faults = 0;

    for(int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < frameCount; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frames[front] = pages[i];
            front = (front + 1) % frameCount;
            faults++;
        }
    }

    printf("Total Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int frameCount)
{
    int frames[20], time[20];
    int faults = 0, count = 0;

    for(int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < frameCount; j++)
        {
            if(frames[j] == pages[i])
            {
                count++;
                time[j] = count;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = 0;

            for(int j = 1; j < frameCount; j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            count++;
            frames[pos] = pages[i];
            time[pos] = count;
            faults++;
        }
    }

    printf("Total Page Faults = %d\n", faults);
}

void Optimal(int pages[], int n, int frameCount)
{
    int frames[20];
    int faults = 0;

    for(int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement\n");

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < frameCount; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = -1;

            for(int j = 0; j < frameCount; j++)
            {
                if(frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                int farthest = i + 1;
                int index = -1;

                for(int j = 0; j < frameCount; j++)
                {
                    int k;

                    for(k = i + 1; k < n; k++)
                    {
                        if(frames[j] == pages[k])
                            break;
                    }

                    if(k == n)
                    {
                        index = j;
                        break;
                    }

                    if(k > farthest)
                    {
                        farthest = k;
                        index = j;
                    }
                }

                pos = index;
            }

            frames[pos] = pages[i];
            faults++;
        }
    }

    printf("Total Page Faults = %d\n", faults);
}

int main()
{
    int n, frameCount;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    FIFO(pages, n, frameCount);
    LRU(pages, n, frameCount);
    Optimal(pages, n, frameCount);

    return 0;
}