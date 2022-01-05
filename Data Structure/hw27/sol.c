#include <stdio.h>
#include <stdlib.h>
#define maxN 1000000
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))

int min(int x, int y) { return x < y ? x : y; }

void InsertSort(int* arr, int len)
{
    int tmp;
    for (int i = 2; i <= len; i++) {
        tmp = arr[i];
        for (int j = i - 1; j >= 0; j--)
            if (tmp < arr[j])
                arr[j + 1] = arr[j];
            else {
                arr[j + 1] = tmp;
                break;
            }
    }
}

void QuickSort(int* arr, int L, int R)
{
    if (L < R) {
        int i = L, j = R, pivot = arr[(L + R) >> 1];
        while (i < j) {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i < j)
                swap(arr[i], arr[j]), i++, j--;
        }
        QuickSort(arr, L, pivot - 1);
        QuickSort(arr, pivot + 1, R);
    }
}

void _merge(int* arr, int L, int R, int mid)
{
    int* tmp = (int*)malloc(sizeof(int) * (R - L + 1));
    int idx = 0, p1 = L, p2 = mid + 1;
    while (p1 <= mid && p2 <= R)
        tmp[idx++] = (arr[p1] < arr[p2] ? arr[p1++] : arr[p2++]);
    while (p1 <= mid)
        tmp[idx++] = arr[p1++];
    while (p2 <= R)
        tmp[idx++] = arr[p2++];
    for (int i = 0; i < idx; i++)
        arr[L + i] = tmp[i];
}

void RMergeSort(int* arr, int L, int R)
{
    if (L < R) {
        int mid = (L + R) >> 1;
        RMergeSort(arr, L, mid);
        RMergeSort(arr, mid + 1, R);
        _merge(arr, L, R, mid);
    }
}

void IMergeSort(int* arr, int L, int R)
{
    for (int i = 1; i <= R - L; i <<= 1)
        for (int j = L; j <= R; j += i << 1)
            _merge(arr, j, min(j + (i << 1) - 1, R), j + i - 1);
}

void Heapfy(int* arr, int idx, int len)
{
    if (idx << 1 <= len) {
        while ((idx <<= 1) <= len) {
            if (idx + 1 <= len && arr[idx + 1] > arr[idx])
                idx += 1;
            if (arr[idx >> 1] < arr[idx])
                swap(arr[idx], arr[idx >> 1]);
            else
                break;
        }
    }
}

void HeapSort(int* arr, int len)
{
    for (int i = len >> 1; i >= 1; i--)
        Heapfy(arr, i, len);
    for (int i = len; i > 1; i--)
        swap(arr[1], arr[i]), Heapfy(arr, 1, i - 1);
}

int t, idx = 1, arr[maxN];

int main()
{
    scanf("%d", &t);
    while (~scanf("%d", arr + idx))
        idx++;

    idx -= 1;
    if (t == 0)
        InsertSort(arr, idx);
    if (t == 1)
        QuickSort(arr, 1, idx);
    if (t == 2)
        RMergeSort(arr, 1, idx);
    if (t == 3)
        IMergeSort(arr, 1, idx);
    if (t == 4)
        HeapSort(arr, idx);

    for (int i = 1; i <= idx; i++)
        printf("%d ", arr[i]);
    puts("");
}