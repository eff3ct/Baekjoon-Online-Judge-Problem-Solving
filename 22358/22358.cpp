#include <bits/stdc++.h>
#define MAX 100'001

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

vector<pll> adj[MAX];
ll N, M, K, S, T;
ll dp[11][MAX];
const ll INF = 1e18;

ll solve(ll k, ll cur) {
    ll& ret = dp[k][cur];

    if(ret != -1) return ret;

    if(k == 0) {
        ret = -INF;
        if(cur == T) return ret = 0;
        for(auto& next : adj[cur]) {
            ll next_node = next.first;
            ll time = next.second;
            if(next_node < cur) continue;
            ret = max(ret, time + solve(k, next_node));
        }
    }
    else {
        ret = -INF;
        for(auto& next : adj[cur]) {
            ll next_node = next.first;
            ll time = next.second;
            if(next_node < cur) ret = max(ret, solve(k - 1, next_node));
            else ret = max(ret, time + solve(k, next_node));
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i = 0; i < 11; ++i) {
        fill(dp[i], dp[i] + MAX, -1);
    }

    cin >> N >> M >> K >> S >> T;
    for(int i = 0; i < M; ++i) {
        ll a, b, t; cin >> a >> b >> t;
        adj[a].push_back({b, t});
        adj[b].push_back({a, 0});
    }

    ll ans = solve(K, S);
    cout << (ans >= 0 ? ans : -1) << '\n';

    return 0;
}