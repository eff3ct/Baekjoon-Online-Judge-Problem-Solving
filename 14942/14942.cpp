#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int sz = 20;

int parent[100'001][sz + 1];
ll dist[100'001][sz + 1];
int depth[100'001];
int n; 

vector<pll> adj[100'001];

void make_tree_DFS(int cur_node = 1) {
    for(auto& next : adj[cur_node]) {
        int next_node = next.first;
        ll d = next.second;

        if(depth[next_node] != -1) continue;
        
        depth[next_node] = depth[cur_node] + 1;
        parent[next_node][0] = cur_node;
        dist[next_node][0] = d;

        make_tree_DFS(next_node);
    }
}

void init() {
    for(int i = 0; i <= 100'000; ++i) {
        fill(parent[i], parent[i] + sz + 1, -1);
        fill(dist[i], dist[i] + sz + 1, -1);
    }
    fill(depth, depth + 100'001, -1);
    depth[1] = 0;
}

void set_value() {
    for(int j = 0; j <= sz; ++j) {
        for(int i = 1; i <= n; ++i) {
            if(parent[i][j] != -1) {
                parent[i][j + 1] = parent[ parent[i][j] ][j];
                dist[i][j + 1] = dist[ parent[i][j] ][j] + dist[i][j]; 
            }
        }
    }
}

int solve(ll power, int cur_node) {
    for(int i = sz; i >= 0; --i) {
        if(parent[cur_node][i] != -1 && power >= dist[cur_node][i]) {
            power -= dist[cur_node][i];
            cur_node = parent[cur_node][i];
        } 
    }
    return cur_node;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    vector<ll> power(n + 1);
    for(int i = 1; i <= n; ++i) cin >> power[i];

    for(int i = 0; i < n - 1; ++i) {
        ll a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    init();
    make_tree_DFS();
    set_value();

    for(int i = 1; i <= n; ++i) 
        cout << solve(power[i], i) << '\n';
    
    return 0;
}