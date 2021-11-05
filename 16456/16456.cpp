#include <iostream>
#include <vector>
#define MOD 1000000009

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> dp(n + 2);

    dp[0] = dp[1] = 1, dp[2] = 2;   
    for(int i = 3; i < n; ++i) {
        dp[i] = (dp[i - 1] + dp[i - 3]) % MOD;
    }

    cout << dp[n - 1];

    return 0;
}