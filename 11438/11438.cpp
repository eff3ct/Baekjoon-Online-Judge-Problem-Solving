#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> parent;
vector<int> depth;
int sz;

void dfs(int node, vector<vector<int>>& adj) {
    for(auto& nextNode : adj[node]) {
        if(depth[nextNode] == -1) {
            depth[nextNode] = depth[node] + 1;
            parent[nextNode][0] = node;
            dfs(nextNode, adj);
        }
    }
}

int lca(int& a, int& b) {
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
    vector<vector<int>> adj(N + 1);
    for(int i = 0; i < N - 1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    sz = int(ceil(log2(N)));
    parent.resize(N + 1, vector<int>(sz + 1, -1));
    depth.resize(N + 1, -1);

    depth[1] = 0;
    dfs(1, adj);
    for(int j = 1; j <= sz; ++j) {
        for(int i = 1; i <= N; ++i) {
            if(parent[i][j - 1] != -1)
                parent[i][j] = parent[ parent[i][j - 1] ][j - 1];
        }
    }

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        cout << lca(a, b) << '\n';
    }

    return 0;
}