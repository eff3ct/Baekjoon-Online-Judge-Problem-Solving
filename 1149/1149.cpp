// https://www.acmicpc.net/problem/1149 //
#include <iostream>
#include <algorithm>

using namespace std;

void solve(int**& cost, int n) {
    int** dp = new int*[n];
    for(int i = 0; i < n; ++i) {
        dp[i] = new int[3];
    }

    dp[0][0] = cost[0][0]; dp[0][1] = cost[0][1]; dp[0][2] = cost[0][2];

    for(int i = 1; i < n; ++i) {
        dp[i][0] = cost[i][0] + min(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = cost[i][1] + min(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = cost[i][2] + min(dp[i - 1][0], dp[i - 1][1]);
    }

    cout << min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});

    for(int i = 0; i < n; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
}

int main() {
    int n; cin >> n;
    
    int** cost = new int*[n];
    for(int i = 0; i < n; ++i) {
        cost[i] = new int[3];
    }

    for(int i = 0; i < n; ++i) {
        int r, g, b;
        cin >> r >> g >> b;
        cost[i][0] = r; cost[i][1] = g; cost[i][2] = b;
    }

    solve(cost, n);

    for(int i = 0; i < n; ++i) {
        delete[] cost[i];
    }
    delete[] cost;
}