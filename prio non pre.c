#include <stdio.h>

int main() {
    int n, i, j;
    int at[20], bt[20], pr[20], ct[20], tat[20], wt[20], p[20];
    int temp;

    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority (Lower number = Higher priority): ");
        scanf("%d", &pr[i]);

        p[i] = i + 1;
    }

    // Sort according to priority
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(pr[i] > pr[j]) {

                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;

                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;

                temp = at[i]; at[i] = at[j]; at[j] = temp;

                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    // Completion time
    ct[0] = at[0] + bt[0];

    for(i = 1; i < n; i++) {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    // Calculate TAT and WT
    for(i = 0; i < n; i++) {

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f", total_tat/n);
    printf("\nAverage WT = %.2f", total_wt/n);

    return 0;
}
