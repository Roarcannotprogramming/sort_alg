#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARRAY_LENGTH 1000000

int a[ARRAY_LENGTH];
int b[ARRAY_LENGTH];

int compare(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void q_sort(int *arr,unsigned int len) {
    int *p = arr;
    int *q = arr + len - 1;
    int temp;
    if (len == 1 || len == 0) {
        return;
    }
    while(p < q) {
        while(*p <= *q && p < q) {
            p++;
        }
        if(p != q) {
            temp = *p;
            *p = *q;
            *q = temp;
        }
        while(*q >= *p && p < q) {
            q--;
        }
        if(p != q) {
            temp = *p;
            *p = *q;
            *q = temp;
        }
    }
    q_sort(arr, (unsigned int) (p - arr));
    q_sort(p, (unsigned int)(arr + len - p));
}

void insertion_sort(int *arr, unsigned int len) {
    int j, key;
    unsigned int i;
    for(i=1;i<len;i++) {
        key = arr[i];
        j=i-1;
        while((j>=0) && (arr[j]>key)) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void merge_sort_r(int *arr, int *reg, int start, int end) {
    if (start >= end) {
        return;
    }
    int len = end - start;
    int mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;

    merge_sort_r(arr, reg, start1, end1);
    merge_sort_r(arr, reg, start2, end2);

    int k = start;
    while (start1 <= end1 && start2 <= end2)
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1)
        reg[k++] = arr[start1++];
    while (start2 <= end2)
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = reg[k];
}

void merge_sort(int *arr, unsigned int len) {
    int reg[len];
    merge_sort_r(arr, reg, 0, len - 1);
}

void max_heapify(int *arr, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    int temp;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1])
            son++;
        if (arr[dad] > arr[son])
            return;
        else {
            temp = arr[dad];
            arr[dad] = arr[son];
            arr[son] = temp;
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(int *arr, int len) {
    int i, temp;
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    for (i = len - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        max_heapify(arr, 0, i - 1);
    }
}

int main() {
    int i = 0;
    clock_t start, end;
    srand((unsigned)time(NULL));
    for(i = 0; i < ARRAY_LENGTH; i++) {
        int t = rand();
        a[i] = t;
        b[i] = t;
    }

    start = clock();
    // q_sort(a, ARRAY_LENGTH);
    insertion_sort(a, ARRAY_LENGTH);
    // merge_sort(a, ARRAY_LENGTH);
    // heap_sort(a, ARRAY_LENGTH);
    end = clock();
    printf("%lf\n", ((double)end - start) / CLOCKS_PER_SEC);
    
    // print for debug
    // for(i=0; i < ARRAY_LENGTH; i++) {
    //     printf("%d\t", a[i]);
    // }

    // compare with std_qsort
    start = clock();
    qsort(b, ARRAY_LENGTH, sizeof(int), compare);
    end = clock();
    printf("%lf\n", ((double)end - start) / CLOCKS_PER_SEC);
    return 0;
}
