#include <iostream>
#include <vector>
#define MOD 1000000009LL

using namespace std;
typedef long long ll;

int main() {
    int T; cin >> T;

    vector<vector<ll>> dp(100001, vector<ll>(4));
    //dp[n][stat(1~3)] : numbers of method, which ends with previous stat
    //dp[n][1] = dp[n - 1][2] + dp[n - 1][3];
    //dp[n][2] = dp[n - 2][1] + dp[n - 2][3];
    //dp[n][3] = dp[n - 3][1] + dp[n - 3][2];
    dp[1][1] = 1;
    dp[2][2] = 1;
    dp[3][1] = 1;
    dp[3][2] = 1;
    dp[3][3] = 1;

    for(int i = 4; i <= 100000; ++i) {
        dp[i][1] = (dp[i - 1][2] + dp[i - 1][3]) % MOD;
        dp[i][2] = (dp[i - 2][1] + dp[i - 2][3]) % MOD;
        dp[i][3] = (dp[i - 3][1] + dp[i - 3][2]) % MOD;
    }

    while(T --> 0) {
        int n; cin >> n;
        cout << (dp[n][1] + dp[n][2] + dp[n][3]) % MOD << '\n';
    }

    return 0;
}