// https://www.acmicpc.net/problem/11054 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int LIS(int (&arr)[1001], int a, int b, bool reversed) {
    vector<int> lis;
    
    if(!reversed) {
        lis.push_back(arr[a]);
        for(int i = a + 1; i < b; ++i) {
            int lb = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
            if(lb != lis.size()) {
                lis[lb] = arr[i];
            }
            else lis.push_back(arr[i]);
        }
        return lis.size();
    }
    else {
        lis.push_back(arr[a]);
        for(int i = a - 1; i > b; --i) {
            int lb = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
            if(lb != lis.size()) {
                lis[lb] = arr[i];
            }
            else lis.push_back(arr[i]);
        }
        return lis.size();
    }
}

int solve(int (&arr)[1001], int n) {
    int maximum = 0;
    for(int i = 0; i < n; ++i) {
        int nowLength = LIS(arr, i, -1, true) + LIS(arr, i, n, false) - 1;
        maximum = max(maximum, nowLength);
    }
    return maximum;
}

int main() {
    int n;
    cin >> n;

    int arr[1001];
    for(int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        arr[i] = -tmp;
    }

    cout << solve(arr, n);

    return 0;
}