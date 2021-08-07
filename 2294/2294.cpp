// https://www.acmicpc.net/problem/2294 //
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;

int solve(vector<int>& coinValue, int k) {
    vector<int> dp(k + 1, INF);
    dp[0] = 0;

    for(int i = 0; i < coinValue.size(); ++i) {
        for(int j = coinValue[i]; j <= k; ++j) {
            dp[j] = min(dp[j - coinValue[i]] + 1, dp[j]);
        }
    }

    return (dp[k] == INF) ? -1 : dp[k];
}

int main() { 
    int n, k; cin >> n >> k;

    vector<int> coinValue(n);
    for(int i = 0; i < n; ++i) cin >> coinValue[i];

    sort(coinValue.begin(), coinValue.end());
    cout << solve(coinValue, k);

    return 0;
}