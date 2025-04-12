#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int partition(vector<int>& arr, int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    swap(arr[pivotIndex], arr[right]); 
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }
    swap(arr[storeIndex], arr[right]); 
    return storeIndex;
}

int findMedianOfSmallGroup(vector<int>& arr, int left, int right) {
    int n = right - left + 1;
    vector<int> temp(n);
    for (int i = 0; i < n; i++) temp[i] = arr[left + i];
    sort(temp.begin(), temp.end());
    return temp[n / 2];
}

int medianOfMedians(vector<int>& arr, int left, int right) {
    if (right - left + 1 <= 5) {
        return findMedianOfSmallGroup(arr, left, right);
    }
    vector<int> medians;
    for (int i = left; i <= right; i += 5) {
        int groupRight = min(i + 4, right);
        medians.push_back(findMedianOfSmallGroup(arr, i, groupRight));
    }
    return medianOfMedians(medians, 0, medians.size() - 1);
}

int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];
    int pivot = medianOfMedians(arr, left, right);
    int pivotIndex = left;
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            pivotIndex = i;
            break;
        }
    }
    pivotIndex = partition(arr, left, right, pivotIndex);
    if (k == pivotIndex) return arr[k];
    else if (k < pivotIndex) return quickSelect(arr, left, pivotIndex - 1, k);
    else return quickSelect(arr, pivotIndex + 1, right, k);
}

int findMedian(vector<int>& arr) {
    int n = arr.size();
    if (n % 2 == 0) {
        int lower = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int upper = quickSelect(arr, 0, n - 1, n / 2);
        return (lower + upper) / 2;
    } else {
        return quickSelect(arr, 0, n - 1, n / 2);
    }
}

int main() {
    vector<int> arr = {7, 3, 1, 4, 5, 9, 2, 8, 6};
    cout << "Median: " << findMedian(arr) << endl;
    return 0;
}