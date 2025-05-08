#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void to_lower(char *str) {
    int i = 0;
    for ( i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int fcfs(int requests[], int n, int head) {
    int total = 0;
    int i;
    for (i = 0; i < n; i++) {
        total += abs(requests[i] - head);
        head = requests[i];
    }
    return total;
}

int scan(int requests[], int n, int head, int cylinders) {
    int total = 0;
    int sorted[1000];
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        sorted[i] = requests[i];
    }
    qsort(sorted, n, sizeof(int), compare);

    int idx = 0;
    while (idx < n && sorted[idx] < head)
    {
        idx++;
    }

    for (j = idx - 1; j >= 0; j--) {
        total += abs(head - sorted[j]);
        head = sorted[j];
    }

    if (idx > 0) {
        total += abs(head - 0);
        head = 0;
    }

    for (k = idx; k < n; k++) {
        total += abs(head - sorted[k]);
        head = sorted[k];
    }

    return total;
}

int cscan(int requests[], int n, int head, int cylinders) {
    int total = 0;
    int sorted[1000];
    int i, l, m;
    for (i = 0; i < n; i++) sorted[i] = requests[i];
    qsort(sorted, n, sizeof(int), compare);

    int idx = 0;
    while (idx < n && sorted[idx] < head) idx++;

    for (l = idx; l < n; l++) {
        total += abs(head - sorted[l]);
        head = sorted[l];
    }

    if (idx > 0) {
        total += (cylinders - 1 - head);
        total += (cylinders - 1);
        head = 0;
        for (m = 0; m < idx; m++) {
            total += abs(head - sorted[m]);
            head = sorted[m];
        }
    }

    return total;
}

int main() {
    int cylinders, queue_size, head, i;
    int requests[1000];
    char algo[20];

    printf("Enter number of cylinders: ");
    scanf("%d", &cylinders);

    printf("Enter number of requests: ");
    scanf("%d", &queue_size);

    if (queue_size > 1000) {
        printf("Queue size too large (max 1000).\n");
        return 1;
    }

    printf("Enter request queue (space separated):\n");
    for (i = 0; i < queue_size; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= cylinders) {
            printf("Invalid request: must be between 0 and %d\n", cylinders - 1);
            return 1;
        }
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);
    if (head < 0 || head >= cylinders) {
        printf("Invalid head position: must be between 0 and %d\n", cylinders - 1);
        return 1;
    }

    printf("Enter algorithm (FCFS / SCAN / C-SCAN): ");
    scanf("%s", algo);
    to_lower(algo);

    int total = 0;

    if (strcmp(algo, "fcfs") == 0) {
        total = fcfs(requests, queue_size, head);
    } else if (strcmp(algo, "scan") == 0) {
        total = scan(requests, queue_size, head, cylinders);
    } else if (strcmp(algo, "c-scan") == 0 || strcmp(algo, "cscan") == 0) {
        total = cscan(requests, queue_size, head, cylinders);
    } else {
        printf("Invalid algorithm name.\n");
        return 1;
    }

    printf("Total head movement using %s: %d\n", algo, total);

    return 0;
}
