#include <iostream>
#include <vector>
#define MOD 9901

using namespace std;

int main() {
    int N; cin >> N;

    vector<int> dp(100001);
    dp[1] = 3;
    dp[2] = 7;

    int s = dp[1];
    for(int i = 3; i <= N; ++i) {
        dp[i] = (dp[i - 1] + 2 * s + 4) % MOD;
        s += dp[i - 1];
        s %= MOD;
    }

    cout << dp[N];

    return 0;
}