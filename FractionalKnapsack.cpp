#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
};

bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item>& arr) {
    sort(arr.begin(), arr.end(), compare);
    double totalValue = 0.0;
    
    for (int i = 0; i < arr.size(); i++) {
        if (W >= arr[i].weight) {
            totalValue += arr[i].value;
            W -= arr[i].weight;
        } else {
            totalValue += arr[i].value * ((double)W / arr[i].weight);
            break;
        }
    }
    return totalValue;
}

int main() {
    vector<Item> arr = {{60, 10}, {100, 20}, {120, 30}};
    int W = 50;
    cout << "Maximum value: " << fractionalKnapsack(W, arr) << endl;
    return 0;
}