#include <iostream> 
#include <vector>
#define MOD 1000000000

using namespace std;

int main() {
    int N, K; cin >> N >> K;

    vector<vector<int>> dp(201, vector<int>(201));

    for(int i = 0; i <= N; ++i) dp[i][1] = 1;

    for(int i = 0; i <= N; ++i) {
        for(int j = 2; j <= K; ++j) {
            for(int a = 0; a <= i; ++a) {
                dp[i][j] += dp[i - a][j - 1];
                dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[N][K] % MOD;

    return 0;
}