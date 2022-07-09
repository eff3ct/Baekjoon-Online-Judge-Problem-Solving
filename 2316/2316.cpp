#include <bits/stdc++.h>
#define MAX 1001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int INF = 987654321;

int edmonds_karp(vector<vector<int>>& adj, int (*flow)[MAX], int (*capacity)[MAX]) {
    int ret = 0;
    int s = 2, t = 5;
    capacity[2][3] = INF;
    capacity[4][5] = INF;
    while(true) {
        vector<int> parent(MAX, -1);
        queue<int> q;
        q.push(s);
        parent[s] = s;

        while(!q.empty()) {
            int cur_node = q.front();
            q.pop();

            for(int& next_node : adj[cur_node]) {
                if(parent[next_node] != -1) continue;
                if(capacity[cur_node][next_node] - flow[cur_node][next_node] > 0) {
                    q.push(next_node);
                    parent[next_node] = cur_node;
                    if(next_node == t) break; 
                }
            }
        }

        if(parent[t] == -1) break;

        int min_flow = INF;

        for(int i = t; i != s; i = parent[i]) {
            min_flow = min(min_flow, capacity[parent[i]][i] - flow[parent[i]][i]);
        }

        for(int i = t; i != s; i = parent[i]) {
            flow[parent[i]][i] += min_flow;
            flow[i][parent[i]] -= min_flow;
        }

        ret += min_flow;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, P; cin >> N >> P;
    vector<vector<int>> adj(MAX);
    int flow[MAX][MAX];
    int capacity[MAX][MAX];
    for(int i = 0; i < MAX; ++i) {
        memset(flow[i], 0, sizeof(flow[i]));
        memset(capacity[i], 0, sizeof(capacity[i]));
    }

    for(int i = 1; i <= N; ++i) {
        adj[2 * i].push_back(2 * i + 1);
        adj[2 * i + 1].push_back(2 * i);
        capacity[2 * i][2 * i + 1] = 1;
    }

    for(int i = 0; i < P; ++i) {
        int u, v; cin >> u >> v;
        capacity[2 * u + 1][2 * v] = INF;
        capacity[2 * v + 1][2 * u] = INF;
        adj[2 * u + 1].push_back(2 * v);
        adj[2 * v].push_back(2 * u + 1);

        adj[2 * v + 1].push_back(2 * u);
        adj[2 * u].push_back(2 * v + 1);
    }

    cout << edmonds_karp(adj, flow, capacity) << '\n';

    return 0;
}