#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int C, N; cin >> C >> N;
    vector<int> weight(N + 1);
    vector<int> cnt(N + 1);
    for(int i = 1; i <= N; ++i) cin >> weight[i] >> cnt[i];

    int ans = 987654321;

    vector<vector<int>> dp(N + 1, vector<int>(int(1e5) + 1, 0));

    for(int i = 1; i <= N; ++i) {
        for(int w = 1; w <= 1e5; ++w) {
            if(weight[i] <= w) dp[i][w] = max(dp[i - 1][w], dp[i][w - weight[i]] + cnt[i]);
            else dp[i][w] = dp[i - 1][w];

            if(dp[i][w] >= C) ans = min(ans, w);
        }
    }

    cout << ans << '\n';

    return 0;
}