#include <iostream>
#include <vector>
#define MOD 1000000000LL

using namespace std;

int main() {
    int N; cin >> N;
    vector<vector<int>> dp(N + 1, vector<int>(20, 0));

    for(int i = 1; i <= N; ++i) dp[i][0] = 1;
    for(int k = 0; k < 20; ++k) dp[0][k] = 1;

    for(int i = 1; i <= N; ++i) {
        for(int k = 1; k < 20; ++k) {
            if(i - (1 << k) >= 0) dp[i][k] = (dp[i - (1 << k)][k] + dp[i][k - 1]) % MOD;
            else dp[i][k] = dp[i][k - 1];
        }
    }

    cout << dp[N][19];

    return 0;
}