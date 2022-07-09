#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int h, w;

ll dp[12 * 12 + 1][1 << 12 + 1];

ll solve(int idx, int bitmask) {
    if(idx >= h * w) {
        if(idx == h * w && bitmask == 0) return 1;
        else return 0;
    }

    ll& ret = dp[idx][bitmask];

    if(ret != -1) return ret;

    ret = 0;
    if(bitmask & (1 << 0)) {
        ret = solve(idx + 1, bitmask >> 1);
        return ret;
    }

    //1 x 2 tile
    if((idx % w) != (w - 1) && (bitmask & (1 << 1)) == 0) {
        ret += solve(idx + 2, bitmask >> 2);
    }

    //2 x 1 tile
    ret += solve(idx + 1, (bitmask >> 1) | (1 << (w - 1)));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(true) {
        cin >> h >> w;
        if(h == 0 && w == 0) break;
        for(int i = 0; i < 12 * 12 + 1; ++i) {
            fill(dp[i], dp[i] + (1 << 12) + 1, -1);
        }
        cout << solve(0, 0) << '\n';
    }

    return 0;
}

