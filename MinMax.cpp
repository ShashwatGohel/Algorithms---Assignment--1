#include <iostream>
using namespace std;

struct MinMax {
    int min;
    int max;
};

MinMax findMinMax(int arr[], int start, int end) {
    MinMax result, left, right;
    
    if (start == end) {
        result.min = result.max = arr[start];
        return result;
    }
    
    if (end == start + 1) {
        if (arr[start] > arr[end]) {
            result.max = arr[start];
            result.min = arr[end];
        } else {
            result.max = arr[end];
            result.min = arr[start];
        }
        return result;
    }
    
    int mid = (start + end) / 2;
    left = findMinMax(arr, start, mid);
    right = findMinMax(arr, mid + 1, end);
    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);
    return result;
}

int main() {
    int arr[] = {12, 5, 78, 34, 2, 45, 90, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    MinMax result = findMinMax(arr, 0, n - 1);
    cout << "Minimum element: " << result.min << endl;
    cout << "Maximum element: " << result.max << endl;
    return 0;
}
