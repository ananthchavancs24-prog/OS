#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[20], deadline[20], period[20];
    int ct[20], wt[20], tat[20];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &burst[i]);
        printf("Period (for RMS): ");
        scanf("%d", &period[i]);
        printf("Deadline (for EDF): ");
        scanf("%d", &deadline[i]);
        ct[i] = 0; // initialize
    }

    // ===== EDF Scheduling =====
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("ID  BT  Deadline  CT  WT  TAT\n");

    int time = 0;
    for (int i = 0; i < n; i++) {
        int min_deadline = 9999, idx = -1;
        for (int j = 0; j < n; j++) {
            if (deadline[j] < min_deadline && ct[j] == 0) {
                min_deadline = deadline[j];
                idx = j;
            }
        }
        time += burst[idx];
        ct[idx] = time;
        tat[idx] = ct[idx];
        wt[idx] = tat[idx] - burst[idx];
        printf("%d   %d   %d        %d   %d   %d\n", idx, burst[idx], deadline[idx], ct[idx], wt[idx], tat[idx]);
    }

    // ===== RMS Scheduling =====
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("ID  BT  Period  CT  WT  TAT\n");

    time = 0;
    for (int i = 0; i < n; i++) {
        int min_period = 9999, idx = -1;
        for (int j = 0; j < n; j++) {
            if (period[j] < min_period && ct[j] > 0) {
                min_period = period[j];
                idx = j;
            }
        }
        time += burst[idx];
        ct[idx] = time;
        tat[idx] = ct[idx];
        wt[idx] = tat[idx] - burst[idx];
        printf("%d   %d   %d       %d   %d   %d\n", idx, burst[idx], period[idx], ct[idx], wt[idx], tat[idx]);
        ct[idx] = -2; // mark scheduled
    }
    return 0;
}
