#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int *a, int n, long long *swaps);
void insertion_sort(int *a, int n, long long *swaps);
void merge_sort(int *a, int left, int right, long long *swaps);
void merge(int *a, int left, int mid, int right, long long *swaps);
void copy_array(int *src, int *dst, int n);

int main() {
    int sizes[4] = {10, 1000, 10000, 100000};
    
    printf("-------------------------------------------------------------------------------\n");
    printf("| Размер |       Алгоритм        | Время (сек) | Перестановок |\n");
    printf("-------------------------------------------------------------------------------\n");

    srand(time(NULL));

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];

        int *arr = (int*)malloc(n * sizeof(int));
        int *a_bubble = (int*)malloc(n * sizeof(int));
        int *a_insert = (int*)malloc(n * sizeof(int));
        int *a_merge = (int*)malloc(n * sizeof(int));

        if (arr == NULL || a_bubble == NULL || a_insert == NULL || a_merge == NULL) {
            printf("Ошибка памяти!\n");
            return 1;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = rand();
        }

        copy_array(arr, a_bubble, n);
        copy_array(arr, a_insert, n);
        copy_array(arr, a_merge, n);

        clock_t start, end;
        double time_spent;
        long long swaps = 0;

        swaps = 0;
        start = clock();
        bubble_sort(a_bubble, n, &swaps);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("| %-6d | Сортировка пузырьком   | %-11.4f | %-12lld |\n", n, time_spent, swaps);

        swaps = 0;
        start = clock();
        insertion_sort(a_insert, n, &swaps);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("|        | Сортировка вставками  | %-11.4f | %-12lld |\n", time_spent, swaps);

        swaps = 0;
        start = clock();
        merge_sort(a_merge, 0, n - 1, &swaps);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("|        | Сортировка слиянием   | %-11.4f | %-12lld |\n", time_spent, swaps);

        printf("-------------------------------------------------------------------------------\n");

        free(arr);
        free(a_bubble);
        free(a_insert);
        free(a_merge);
    }

    return 0;
}

void copy_array(int *src, int *dst, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

// сортировка пузырьком
void bubble_sort(int *a, int n, long long *swaps) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                (*swaps)++;
            }
        }
    }
}

// сортировка вставками
void insertion_sort(int *a, int n, long long *swaps) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            (*swaps)++;
        }
        a[j + 1] = key;
    }
}

// сортировка слиянием
void merge(int *a, int left, int mid, int right, long long *swaps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
            (*swaps)++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++; k++;
    }

    free(L);
    free(R);
}

void merge_sort(int *a, int left, int right, long long *swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid, swaps);
        merge_sort(a, mid + 1, right, swaps);
        merge(a, left, mid, right, swaps);
    }
}