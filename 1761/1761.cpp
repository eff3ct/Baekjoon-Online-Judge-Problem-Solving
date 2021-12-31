#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

vector<vector<int>> parent;
vector<int> depth;
vector<int> dist_to_root;
int sz;

void dfs(int node, vector<vector<pair<int, int>>>& adj) {
    for(auto& nextNode : adj[node]) {
        if(depth[nextNode.first] == -1) {
            dist_to_root[nextNode.first] = dist_to_root[node] + nextNode.second;
            depth[nextNode.first] = depth[node] + 1;
            parent[nextNode.first][0] = node;
            dfs(nextNode.first, adj);
        }
    }
}

int lca(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);

    int diff = depth[a] - depth[b];
    
    int size = int(ceil(log2(diff)));
    for(int i = 0; i <= size; ++i) {
        if(diff & (1 << i)) a = parent[a][i];
    }

    if(a != b) {
        for(int i = sz; i >= 0; --i) {
            if(parent[a][i] != -1 && parent[a][i] != parent[b][i]) {
                a = parent[a][i];
                b = parent[b][i];
            }
        }
    }
    else return a;

    return parent[a][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<vector<pair<int, int>>> adj(N + 1);
    for(int i = 0; i < N - 1; ++i) {
        int a, b, dist; cin >> a >> b >> dist;
        adj[a].push_back({b, dist});
        adj[b].push_back({a, dist});
    }

    sz = int(ceil(log2(N)));
    parent.resize(N + 1, vector<int>(sz + 1, -1));
    depth.resize(N + 1, -1);
    dist_to_root.resize(N + 1, -1);

    dist_to_root[1] = 0;
    depth[1] = 0;
    dfs(1, adj);
    for(int j = 1; j <= sz; ++j) {
        for(int i = 1; i <= N; ++i) {
            if(parent[i][j - 1] != -1) {
                parent[i][j] = parent[ parent[i][j - 1] ][j - 1];
            }
        }
    }

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        int w = lca(a, b);
        cout << abs(dist_to_root[a] - dist_to_root[w]) + abs(dist_to_root[b] - dist_to_root[w]) << '\n';
    }

    return 0;
}