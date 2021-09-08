#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int N, K;

int topologySort(vector<vector<int>>& adj, vector<int>& count, vector<int>& cost, int W) {
    vector<int> timeCost(N + 1, 0);
    queue<int> q;

    for(int i = 1; i <= N; ++i) {
        if(count[i] == 0) {
            timeCost[i] = cost[i];
            q.push(i);
        }
    }

    for(int i = 0; i < N; ++i) {
        int now = q.front();
        q.pop();

        for(auto& next : adj[now]) {
            timeCost[next] = max(timeCost[next], timeCost[now] + cost[next]);
            if(--count[next] == 0) q.push(next);
        }
    }

    return timeCost[W];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cin >> N >> K;

        vector<int> cost(N + 1, 0);
        for(int i = 1; i <= N; ++i) cin >> cost[i];

        vector<vector<int>> adj(N + 1, vector<int>());
        vector<int> count(N + 1, 0);
        for(int i = 0; i < K; ++i) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            count[v]++;
        }

        int W; cin >> W;

        cout << topologySort(adj, count, cost, W) << '\n';
    }

    return 0;
}