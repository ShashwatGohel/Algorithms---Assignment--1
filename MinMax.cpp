#include <iostream>
using namespace std;
void findMinMax(int arr[], int n, int &minVal, int &maxVal, int &comparisons) {
    comparisons = 0;
    if (n == 1) {
        minVal = maxVal = arr[0];
        return;
    }
    
    if (arr[0] < arr[1]) {
        minVal = arr[0];
        maxVal = arr[1];
    } else {
        minVal = arr[1];
        maxVal = arr[0];
    }
    comparisons++;

    for (int i = 2; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            comparisons++;
        } else if (arr[i] > maxVal) {
            maxVal = arr[i];
            comparisons++;
        }
    }
}

int main() {
    int arr[] = {3, 5, 1, 8, 7, 9, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int minVal, maxVal, comparisons;
    
    findMinMax(arr, n, minVal, maxVal, comparisons);
    
    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Number of comparisons: " << comparisons << endl;
    
    return 0;
}
