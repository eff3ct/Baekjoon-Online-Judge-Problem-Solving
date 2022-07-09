#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int INF = 987654321;

int edmonds_karp(vector<vector<int>>& adj, int (*flow)[100], int (*capacity)[100]) {
    int ret = 0;
    int s = 0, t = 25;
    while(true) {
        vector<int> parent(100, -1);
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

    int N; cin >> N;
    vector<vector<int>> adj(100);
    int flow[100][100];
    int capacity[100][100];
    for(int i = 0; i < 100; ++i) {
        memset(flow[i], 0, sizeof(flow[i]));
        memset(capacity[i], 0, sizeof(capacity[i]));
    }

    for(int i = 0; i < N; ++i) {
        char u, v; int w;
        cin >> u >> v >> w;
        capacity[u - 'A'][v - 'A'] += w;
        capacity[v - 'A'][u - 'A'] += w;
        adj[u - 'A'].push_back(v - 'A');
        adj[v - 'A'].push_back(u - 'A');
    }

    cout << edmonds_karp(adj, flow, capacity) << '\n';

    return 0;
}