#include <iostream>
#include <vector>
#define MOD 10007

using namespace std;

int main() {
    int N, K; cin >> N >> K;
    vector<vector<int>> dp(N + 1, vector<int>(K + 1));

    dp[1][0] = 1;
    dp[1][1] = 1;
    for(int i = 2; i <= N; ++i) {
        dp[i][0] = 1;
        for(int j = 1; j <= K; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            dp[i][j] %= 10007;
        }
    }

    cout << dp[N][K];

    return 0;
}