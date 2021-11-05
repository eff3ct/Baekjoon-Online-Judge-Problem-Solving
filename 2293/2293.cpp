#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k; cin >> n >> k;

    vector<int> dp(10001);
    vector<int> seq(n + 1);
    for(int i = 1; i <= n; ++i) cin >> seq[i];

    dp[0] = 1;
    for(int j = 1; j <= n; ++j) {
        for(int i = 1; i <= k; ++i) {
            if(i >= seq[j]) dp[i] += dp[i - seq[j]];
        }
    }

    cout << dp[k];

    return 0;
}