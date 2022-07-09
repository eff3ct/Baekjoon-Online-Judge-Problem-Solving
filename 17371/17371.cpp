#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;
using pll = pair<ll, ll>;

const ll INF = 1e18;

ll get_dist(const pll& a, const pll& b) {
    ll dist = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<pll> coords(n);
    for(pll& e : coords) cin >> e.first >> e.second;

    pll ans = coords[0];
    ll min_dist = INF;
    for(int i = 0; i < n; ++i) {
        ll cur_dist = -1;
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            cur_dist = max(cur_dist, get_dist(coords[i], coords[j]));
        }

        if(cur_dist < min_dist) {
            min_dist = cur_dist;
            ans = coords[i];
        }
    }

    cout << ans.first << ' ' << ans.second << '\n';

    return 0;
}