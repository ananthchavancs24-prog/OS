#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] = 0;
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] = 0;
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processes; i++) allocation[i] = -1;

    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i] && blockSize[j] != -1) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] = -1;
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < processes; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to Block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

int main() {
    int blocks, processes;
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter sizes of memory blocks: ");
    for (int i = 0; i < blocks; i++) scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of processes: ");
    for (int i = 0; i < processes; i++) scanf("%d", &processSize[i]);

    // Copy block sizes for each strategy
    int blockCopy1[MAX_BLOCKS], blockCopy2[MAX_BLOCKS], blockCopy3[MAX_BLOCKS];
    for (int i = 0; i < blocks; i++) {
        blockCopy1[i] = blockSize[i];
        blockCopy2[i] = blockSize[i];
        blockCopy3[i] = blockSize[i];
    }

    firstFit(blockCopy1, blocks, processSize, processes);
    bestFit(blockCopy2, blocks, processSize, processes);
    worstFit(blockCopy3, blocks, processSize, processes);

    return 0;
}
