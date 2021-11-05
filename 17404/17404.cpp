#include <iostream>
#include <algorithm>
#include <vector>
#define INF 987654321

using namespace std;

int N; 

void solve(vector<vector<int>>& cost) {
    int ret = INF;

    vector<vector<int>> dp(3, vector<int>(N));
    dp[0][0] = cost[0][0], dp[1][0] = INF, dp[2][0] = INF;
    for(int i = 1; i < N; ++i) {
        for(int color = 0; color < 3; ++color) {
            dp[color][i] = cost[color][i] + min(dp[(color + 1) % 3][i - 1], dp[(color + 2) % 3][i - 1]);
        }
    }
    ret = min({ret, dp[1][N - 1], dp[2][N - 1]});

    fill(dp.begin(), dp.end(), vector<int>(N));
    dp[0][0] = INF, dp[1][0] = cost[1][0], dp[2][0] = INF;
    for(int i = 1; i < N; ++i) {
        for(int color = 0; color < 3; ++color) {
            dp[color][i] = cost[color][i] + min(dp[(color + 1) % 3][i - 1], dp[(color + 2) % 3][i - 1]);
        }
    }
    ret = min({ret, dp[0][N - 1], dp[2][N - 1]});

    fill(dp.begin(), dp.end(), vector<int>(N));
    dp[0][0] = INF, dp[1][0] = INF, dp[2][0] = cost[2][0];
    for(int i = 1; i < N; ++i) {
        for(int color = 0; color < 3; ++color) {
            dp[color][i] = cost[color][i] + min(dp[(color + 1) % 3][i - 1], dp[(color + 2) % 3][i - 1]);
        }
    }
    ret = min({ret, dp[0][N - 1], dp[1][N - 1]});

    cout << ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    vector<vector<int>> cost(3, vector<int>(N));
    for(int i = 0; i < N; ++i) cin >> cost[0][i] >> cost[1][i] >> cost[2][i];

    solve(cost);

    return 0;
}