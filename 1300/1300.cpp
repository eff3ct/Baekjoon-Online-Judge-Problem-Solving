#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll solve(ll N, ll K) {
    ll l = 0, r = 1e9;
    while(l + 1 < r) {
        ll mid = (l + r) / 2LL;
        ll count = 0;

        for(ll i = 1; i <= N; ++i) {
            count += min(mid / i, N);
        }
        
        if(count >= K) r = mid;
        else l = mid;
    }

    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll N, K; cin >> N >> K;
    cout << solve(N, K);

    return 0;
}