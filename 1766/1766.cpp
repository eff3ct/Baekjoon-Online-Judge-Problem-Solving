#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

void solve(int N, vector<vector<int>>& adj, vector<int>& in_deg) {
    vector<int> ret;

    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= N; ++i) {
        if(in_deg[i] == 0) q.push(i);
    }

    for(int i = 1; i <= N; ++i) {
        int now = q.top();
        q.pop();

        ret.push_back(now);

        for(auto& next : adj[now]) {
            if(--in_deg[next] == 0) q.push(next);
        }
    }

    for(auto& x : ret) cout << x << ' ';
}

int main() {
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N + 1);
    vector<int> in_deg(N + 1, 0);

    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        in_deg[b]++;
    }

    for(int i = 1; i <= N; ++i) sort(adj[i].begin(), adj[i].end());

    solve(N, adj, in_deg);

    return 0;
}