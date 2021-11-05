#include <iostream>
#include <vector>

using namespace std;

int countSub(int node, vector<vector<int>>& adj, vector<bool>& visit, vector<int>& dp) {
    int& ret = dp[node];

    if(ret != -1) return ret;

    ret = 1;

    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        ret += countSub(next, adj, visit, dp);
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, R, Q; cin >> N >> R >> Q;

    vector<vector<int>> adj(N + 1);
    for(int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dp(N + 1, -1);
    vector<bool> visit(N + 1, false);

    visit[R] = true;
    countSub(R, adj, visit, dp);

    for(int i = 0; i < Q; ++i) {
        int node; cin >> node;
        cout << dp[node] << '\n';
    }
    
    return 0;
}