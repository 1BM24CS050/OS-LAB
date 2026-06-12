#include <stdio.h>

#define MAX 100

int main() {
    int n, i;
    int PID[MAX], AT[MAX], BT[MAX], TYPE[MAX];
    int CT[MAX], TAT[MAX], WT[MAX], rem_BT[MAX];
    int completed = 0;
    int time = 0;
    int tq = 3;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        PID[i] = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Burst Time: ");
        scanf("%d", &BT[i]);
        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &TYPE[i]);
        rem_BT[i] = BT[i];
    }

    while(completed < n) {
        int done = 0;
        for(i = 0; i < n; i++) {
            if(TYPE[i] == 0 && AT[i] <= time && rem_BT[i] > 0) {
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
        int idx = -1;
        for(i = 0; i < n; i++) {
            if(TYPE[i] == 1 && AT[i] <= time && rem_BT[i] > 0) {
                if(idx == -1 || AT[i] < AT[idx]) {
                    idx = i;
                }
            }
        }
        if(idx != -1) {
            time += 1;
            rem_BT[idx] -= 1;
            if(rem_BT[idx] == 0) {
                CT[idx] = time;
                completed++;
            }
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

    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        PID[i], AT[i], BT[i], TYPE[i],
        CT[i], TAT[i], WT[i]);
    }

    return 0;
}