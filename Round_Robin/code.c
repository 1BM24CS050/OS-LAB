#include <stdio.h>

#define MAX 100

int main() {
    int n, i;
    int PID[MAX], AT[MAX], BT[MAX];
    int CT[MAX], TAT[MAX], WT[MAX], rem_BT[MAX];
    int completed = 0;
    int time = 0;
    int tq = 4;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        PID[i] = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Burst Time: ");
        scanf("%d", &BT[i]);
        rem_BT[i] = BT[i];
    }

    while(completed < n) {
        int done = 0;
        for(i = 0; i < n; i++) {
            if(AT[i] <= time && rem_BT[i] > 0) {
                int run = rem_BT[i];
                if(run > tq) {
                    run = tq;
                }
                time += run;
                rem_BT[i] -= run;
                if(rem_BT[i] == 0) {
                    CT[i] = time;
                    completed++;
                }
                done = 1;
            }
        }
        if(done) {
            continue;
        }
        int next = 999999;
        for(i = 0; i < n; i++) {
            if(rem_BT[i] > 0 && AT[i] < next) {
                next = AT[i];
            }
        }
        if(next != 999999) {
            time = next;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        PID[i], AT[i], BT[i],
        CT[i], TAT[i], WT[i]);
    }

    return 0;
}