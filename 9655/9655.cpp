#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int dp[1010];

int solve(int N) {    
    int& ret = dp[N];
    if(ret != -1) return ret;

    if(N == 0) return ret = 0;

    if((N >= 1 && solve(N - 1) == 0) || (N >= 3 && solve(N - 3) == 0)) return ret = 1;

    return ret = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    fill(dp, dp + 1010, -1);
    cout << (solve(N) ? "SK" : "CY") << '\n';

    return 0;
}