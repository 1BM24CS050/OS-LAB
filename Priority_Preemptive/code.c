#include <stdio.h>

int main() {
    int n, bt[10], bt_copy[10], wt[10], tat[10], at[10], ct[10], p[10], pr[10], rt[10];
    int i, time = 0, completed = 0, highest, prev = -1;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("\nProcess %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &pr[i]);
        bt_copy[i] = bt[i];
        rt[i] = bt[i];
    }

    printf("\n=== Priority Preemptive Scheduling ===\n\n");

    while(completed < n) {
        highest = -1;

        // Find highest priority process that has arrived and has remaining time
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                if(highest == -1 || pr[i] < pr[highest]) {
                    highest = i;
                }
            }
        }

        if(highest == -1) {
            // No process available, CPU idle
            printf("Time %d: Idle\n", time);
            time++;
            continue;
        }

        // Print context switch if needed
        if(prev != highest) {
            printf("Time %d: Process P%d starts execution (Priority %d)\n", time, p[highest], pr[highest]);
            prev = highest;
        }

        // Execute for 1 unit
        rt[highest]--;
        time++;

        // Check if process completed
        if(rt[highest] == 0) {
            completed++;
            ct[highest] = time;
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt_copy[highest];
            printf("Time %d: Process P%d completed\n", time, p[highest]);
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt_copy[i], pr[i], ct[i], tat[i], wt[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}