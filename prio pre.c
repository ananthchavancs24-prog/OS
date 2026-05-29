#include <stdio.h>

int main() {

    int n, i;
    int at[20], bt[20], pr[20];
    int rt[20], ct[20], tat[20], wt[20];

    int time = 0, completed = 0;
    int highest, min;

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

        rt[i] = bt[i];
    }

    while(completed < n) {

        min = 9999;
        highest = -1;

        for(i = 0; i < n; i++) {

            if(at[i] <= time && rt[i] > 0 && pr[i] < min) {
                min = pr[i];
                highest = i;
            }
        }

        if(highest == -1) {
            time++;
        }
        else {

            rt[highest]--;
            time++;

            if(rt[highest] == 0) {
                completed++;
                ct[highest] = time;
            }
        }
    }

    for(i = 0; i < n; i++) {

        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage TAT = %.2f", total_tat/n);
    printf("\nAverage WT = %.2f", total_wt/n);

    return 0;
}
