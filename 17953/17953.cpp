#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> dp(N, vector<int>(M));
    vector<vector<int>> seq(N, vector<int>(M));

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> seq[j][i];
        }
    }

    for(int i = 0; i < M; ++i) dp[0][i] = seq[0][i];

    for(int i = 1; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            for(int k = 0; k < M; ++k) {
                if(j == k) dp[i][j] = max(dp[i - 1][k] + seq[i][j] / 2, dp[i][j]);
                else dp[i][j] = max(dp[i - 1][k] + seq[i][j], dp[i][j]);
            }
        }
    }

    cout << *max_element(dp[N - 1].begin(), dp[N - 1].end());

}