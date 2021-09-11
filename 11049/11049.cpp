#include <iostream>
#include <utility>
#include <vector>
#define INF 2147483647

using namespace std;
vector<vector<int>> dp;

int solve(int start, int end, vector<pair<int, int>>& seq) {
    if(start == end) return 0;

    int& ret = dp[start][end];
    if(ret != INF) return ret;

    for(int i = start; i < end; ++i) {
        ret = min(ret, solve(start, i, seq) + solve(i + 1, end, seq) + seq[start].first * seq[i + 1].first * seq[end].second);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<pair<int, int>> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i].first >> seq[i].second;

    dp.resize(N, vector<int>(N, INF));
    cout << solve(0, N - 1, seq);

    return 0;
}