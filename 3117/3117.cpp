#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K; cin >> N >> K >> M;

    int sz = int(ceil(log2(M)));
    vector<vector<int>> dp(K + 1, vector<int>(sz + 1));

    vector<int> vid(N);
    for(int i = 0; i < N; ++i) cin >> vid[i];
    for(int i = 1; i <= K; ++i) cin >> dp[i][0];

    for(int j = 1; j <= sz; ++j) {
        for(int i = 1; i <= K; ++i) {
            dp[i][j] = dp[ dp[i][j - 1] ][j - 1];
        }
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j <= sz; ++j) {
            if((M - 1) & (1 << j)) {
                vid[i] = dp[vid[i]][j];
            }
        }
        cout << vid[i] << ' ';
    }

    return 0;
}