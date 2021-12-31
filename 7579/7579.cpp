#include <iostream>
#include <vector>

using namespace std;

int N, M; 

void solve(vector<int>& memseq, vector<int>& cost) {
    int ret = 1987654321;
    vector<vector<int>> dp(N + 1, vector<int>(10001));

    for(int i = 1; i <= N; ++i) {
        for(int j = 0; j <= 10000; ++j) {
            if(j - cost[i] >= 0) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost[i]] + memseq[i]);
            else dp[i][j] = dp[i - 1][j];

            if(dp[i][j] >= M) ret = min(ret, j);
        }
    }

    cout << ret;
}

int main() {
    cin >> N >> M;

    vector<int> memseq(N + 1);
    for(int i = 1; i <= N; ++i) cin >> memseq[i];

    vector<int> cost(N + 1);
    for(int i = 1; i <= N; ++i) cin >> cost[i];

    solve(memseq, cost);

    return 0;
}