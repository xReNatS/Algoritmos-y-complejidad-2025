// referencia: https://www.geeksforgeeks.org/quick-sort-algorithm/ y modificado por chatgpt

#include <vector>
#include <algorithm> 
#include <cmath> // para log2
using namespace std;

void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void introSortUtil(vector<int>& arr, int low, int high, int depthLimit) {
    int size = high - low + 1;

    if (size <= 32) {
        insertionSort(arr, low, high);
        return;
    }

    if (depthLimit == 0) {
        // Cambiar a heapsort para evitar mal rendimiento
        make_heap(arr.begin() + low, arr.begin() + high + 1);
        sort_heap(arr.begin() + low, arr.begin() + high + 1);
        return;
    }

    int pi = partition(arr, low, high);
    introSortUtil(arr, low, pi - 1, depthLimit - 1);
    introSortUtil(arr, pi + 1, high, depthLimit - 1);
}

void quickSort(vector<int>& arr) {
    int n = arr.size();
    int depthLimit = 2 * log2(n);
    introSortUtil(arr, 0, n - 1, depthLimit);
}


