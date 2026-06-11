#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int ids[10], periods[10], exec_times[10], deadlines[10], weights[10], n, sim_time;
int gantt[MAX];

void print_gantt(const char* name) {
    printf("\n=== %s Gantt Chart ===\n", name);
    for(int i = 0; i < sim_time; i++)
        if(gantt[i] != 0) printf("| T%d ", gantt[i]); else printf("| I  ");
    printf("|\n");
    for(int i = 0; i <= sim_time; i++) printf("%-5d", i);
    printf("\n");
}

void rate_monotonic() {
    int rem[10];
    for (int i = 0; i < n; i++) rem[i] = exec_times[i];

    for (int t = 0; t < sim_time; t++) {
        for (int i = 0; i < n; i++) if (t > 0 && t % periods[i] == 0) rem[i] = exec_times[i];

        int sel = -1, min_p = 999999;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && periods[i] < min_p) { min_p = periods[i]; sel = i; }
        }
        gantt[t] = (sel != -1) ? (rem[sel]--, ids[sel]) : 0;
    }
    print_gantt("Rate Monotonic");
}

void earliest_deadline_first() {
    int rem[10], abs_d[10];
    for (int i = 0; i < n; i++) { rem[i] = exec_times[i]; abs_d[i] = deadlines[i]; }

    for (int t = 0; t < sim_time; t++) {
        for (int i = 0; i < n; i++) {
            if (t > 0 && t % periods[i] == 0) { rem[i] = exec_times[i]; abs_d[i] = t + deadlines[i]; }
        }

        int sel = -1, min_d = 999999;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0 && abs_d[i] < min_d) { min_d = abs_d[i]; sel = i; }
        }
        gantt[t] = (sel != -1) ? (rem[sel]--, ids[sel]) : 0;
    }
    print_gantt("Earliest Deadline First");
}

void proportional_scheduling() {
    int total_w = 0, t = 0, done = 0;
    for (int i = 0; i < n; i++) total_w += weights[i];

    int share[10];
    for (int i = 0; i < n; i++) share[i] = (weights[i] * sim_time + total_w / 2) / total_w;

    while (!done) {
        done = 1;
        for (int i = 0; i < n && t < sim_time; i++) {
            if (share[i] > 0) { gantt[t++] = ids[i]; share[i]--; done = 0; }
        }
    }
    while (t < sim_time) gantt[t++] = 0;
    print_gantt("Proportional Scheduling");
}

int main() {
    printf("Enter number of tasks & sim time: ");
    scanf("%d %d", &n, &sim_time);

    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        printf("Task %d (Period, Exec, Deadline, Weight): ", i+1);
        scanf("%d %d %d %d", &periods[i], &exec_times[i], &deadlines[i], &weights[i]);
    }

    rate_monotonic();
    earliest_deadline_first();
    proportional_scheduling();
    return 0;
}