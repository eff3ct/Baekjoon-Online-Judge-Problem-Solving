#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

void solve(vector<int>& seq, int K) {
    vector<vector<int>> dp(K, vector<int>(K, 0));
    vector<int> sum(K + 1, 0);

    for(int i = 1; i <= K; ++i) sum[i] = sum[i - 1] + seq[i - 1];

    for(int length = 1; length < K; ++length) {
        for(int start = 0; start <= K - length - 1; ++start) {
            int end = start + length;
            dp[start][end] = INF;
            for(int pivot = start; pivot + 1 <= end; ++pivot) {
                int cost = dp[start][pivot] + dp[pivot + 1][end] + sum[end + 1] - sum[start];
                dp[start][end] = min(cost, dp[start][end]);
            }
        }
    }

    cout << dp[0][K - 1] << '\n';
}

int main() {
    int T; cin >> T;

    while(T --> 0) {
        int K; cin >> K;
        vector<int> seq(K);
        for(int i = 0; i < K; ++i) cin >> seq[i];

        solve(seq, K);
    }

    return 0;
}