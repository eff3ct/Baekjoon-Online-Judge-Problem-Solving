#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll dp[51][51];
const ll MOD = 10007;

ll comb(int n, int r) {
    if(n < r || r < 0) return 0;

    ll& ret = dp[n][r];

    if(ret != -1) return ret;

    if(n == r || r == 0) return ret = 1;
    return ret = (comb(n - 1, r) % MOD + comb(n - 1, r - 1) % MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i = 0; i <= 50; ++i) fill(dp[i], dp[i] + 51, -1);

    int n; cin >> n;
    ll ans = 0;
    ll m = 1;
    for(int i = 1; i <= 13; ++i, m *= -1) {
        ans += m * comb(13, i) * comb(52 - 4 * i, n - 4 * i);
        ans = (ans + MOD) % MOD;
    }

    cout << ans << '\n';

    return 0;
}