#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int dp[2001][2001];

int solve(int s, int e, vector<int>& str) {
    int& ret = dp[s][e];

    if(ret != -1) return ret;

    if(s == e) return ret = 1;
    if(str[s] != str[e]) return ret = 0;
    if(s + 1 == e) return ret = 1;

    return ret = solve(s + 1, e - 1, str);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i = 0; i < 2001; ++i) {
        fill(dp[i], dp[i] + 2001, -1);
    }

    int N; cin >> N;
    vector<int> str(N + 1);
    for(int i = 1; i <= N; ++i) cin >> str[i];

    int M; cin >> M;
    while(M --> 0) {
        int S, E; cin >> S >> E;
        cout << solve(S, E, str) << '\n';
    }

    return 0;
}