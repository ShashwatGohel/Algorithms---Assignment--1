#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    char id;
    int deadline, profit;
};
bool comparison(Job a, Job b) {
    return (a.profit > b.profit);
}

void jobScheduling(vector<Job>& arr, int n) {
    sort(arr.begin(), arr.end(), comparison);
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        maxDeadline = max(maxDeadline, arr[i].deadline);
    
    vector<char> result(maxDeadline, ' ');
    int totalProfit = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = min(maxDeadline, arr[i].deadline) - 1; j >= 0; j--) {
            if (result[j] == ' ') {
                result[j] = arr[i].id;
                totalProfit += arr[i].profit;
                break;
            }
        }
    }
    
    cout << "Scheduled Jobs: ";
    for (char c : result) if (c != ' ') cout << c << " ";
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    vector<Job> arr = {{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27},
                      {'d', 1, 25}, {'e', 3, 15}};
    jobScheduling(arr, arr.size());
    return 0;
}