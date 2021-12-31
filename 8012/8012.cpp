#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> parent;
vector<vector<int>> adj;
vector<int> dist;

int sz = int(ceil(log2(5000)));

void dfs(int node) {
    for(auto& next : adj[node]) {
        if(dist[next] != -1) continue;
        parent[next][0] = node;
        dist[next] = dist[node] + 1;
        dfs(next);
    }
}

int lca(int a, int b) {
    if(dist[a] < dist[b]) swap(a, b);

    int diff = dist[a] - dist[b];
    int s = int(ceil(log2(diff)));

    for(int i = 0; i <= s; ++i) {
        if(diff & (1 << i)) a = parent[a][i];
    }

    if(a != b) {
        for(int i = sz; i >= 0; --i) {
            if(parent[a][i] != -1 && parent[a][i] != parent[b][i]) {
                a = parent[a][i];
                b = parent[b][i];
            }
        }
        return parent[a][0];
    }
    else return a;
}

int main() {
    int n; cin >> n;
    adj.resize(n + 1);
    parent.resize(n + 1, vector<int>(sz + 1, -1));
    dist.resize(n + 1, -1);

    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dist[1] = 0;
    dfs(1);

    for(int j = 1; j <= sz; ++j) {
        for(int i = 1; i <= n; ++i) {
            if(parent[i][j - 1] != -1)
                parent[i][j] = parent[ parent[i][j - 1] ][j - 1];
        }
    }

    int m; cin >> m;
    int time = 0;
    int x; cin >> x;
    for(int i = 0; i < m - 1; ++i) {
        int y; cin >> y;
        int w = lca(x, y);
        time += abs(dist[x] - dist[w]) + abs(dist[y] - dist[w]);
        x = y;
    }

    cout << time;

    return 0;
}