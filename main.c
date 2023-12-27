// C program for insertion sort
#include <math.h>
#include <stdio.h>
#include "insetrionSort.h"
#include "printArray.h"

/* Driver program to test insertion sort */
int main() {
    int arr[] = {12, 11, 13, 5, 5, 5, 5, -1, 0, 0, -999, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, n);
    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
