#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;

    vector<int> dp(100001);
    vector<int> seq(n + 1);
    for(int i = 1; i <= n; ++i) cin >> seq[i];

    int ret = seq[1];
    dp[1] = seq[1];
    for(int i = 2; i <= n; ++i) {
        dp[i] = max(dp[i - 1] + seq[i], seq[i]);
        ret = max(ret, dp[i]);
    }

    cout << ret;
    
    return 0;
}