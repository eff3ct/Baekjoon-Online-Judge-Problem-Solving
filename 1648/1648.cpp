#include <bits/stdc++.h>

using namespace std;
const int MOD = 9901;

int N, M; 

int solve(int idx, int bitmask, vector<vector<int>>& dp) {
    if(idx >= N * M) {
        if(idx == N * M && bitmask == 0) return 1;
        else return 0;
    }

    int& ret = dp[idx][bitmask];

    if(ret != -1) return ret;

    ret = 0;
    if(bitmask & (1 << 0)) {
        ret = solve(idx + 1, bitmask >> 1, dp) % MOD;
        return ret;
    }

    //1 x 2 tile
    if((idx % M) != (M - 1) && (bitmask & (1 << 1)) == 0) {
        ret += solve(idx + 2, bitmask >> 2, dp);
        ret %= MOD;
    }

    //2 x 1 tile
    ret += solve(idx + 1, (bitmask >> 1) | (1 << (M - 1)), dp);
    ret %= MOD;

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    vector<vector<int>> dp(N * M + 1, vector<int>(1 << M, -1));

    int bitmask = 0;
    int ans = solve(0, bitmask, dp);
    cout << ans << '\n';

    return 0;
}