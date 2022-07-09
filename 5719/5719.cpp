#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
const int INF = 987654321;

void solve(vector<vector<pii>>& adj, int s, int d, int N) {
    priority_queue<pii, vector<pii>, greater<pii>> pq; //dist, node
    vector<int> dist(N + 1, INF);
    dist[s] = 0;
    pq.push({0, s});

    while(!pq.empty()) {
        int now_node = pq.top().second;
        int now_dist = pq.top().first;
        pq.pop();

        if(now_dist > dist[now_node]) continue;

        for(auto& next : adj[now_node]) {
            int next_node = next.first;
            int next_dist = next.second + now_dist;

            if(next_dist < dist[next_node]) {
                dist[next_node] = next_dist;
                pq.push({next_dist, next_node});
            }
        }
    }

    cout << (dist[d] == INF ? -1 : dist[d]) << '\n';
}

void dijkstra_erase(vector<vector<pii>>& adj, int s, int d, int N) {
    priority_queue<pii, vector<pii>, greater<pii>> pq; //dist, node
    vector<vector<int>> history(N + 1);
    vector<int> dist(N + 1, INF);
    dist[s] = 0;
    pq.push({0, s});

    while(!pq.empty()) {
        int now_node = pq.top().second;
        int now_dist = pq.top().first;
        pq.pop();

        if(now_dist > dist[now_node]) continue;

        for(auto& next : adj[now_node]) {
            int next_node = next.first;
            int next_dist = next.second + now_dist;

            if(next_dist < dist[next_node]) {
                dist[next_node] = next_dist;
                history[next_node].clear();
                history[next_node].push_back(now_node);
                pq.push({next_dist, next_node});
            }
            else if(next_dist == dist[next_node]) {
                history[next_node].push_back(now_node);
            }
        }
    }
    
    //tracing from D, and delete edges which constitute shortest path.
    queue<int> q;
    q.push(d);
    while(!q.empty()) {
        int now_node = q.front();
        q.pop();

        for(auto& next_node : history[now_node]) {
            int x = -1;
            for(int i = 0; i < int(adj[next_node].size()); ++i) {
                if(adj[next_node][i].first == now_node) {
                    x = i;
                    break;
                }
            }
            if(x == -1) continue;
            adj[next_node].erase(adj[next_node].begin() + x);
            q.push(next_node);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(true) {
        int N, M; cin >> N >> M;
        if(N == 0 && M == 0) break;

        int S, D; cin >> S >> D;

        vector<vector<pii>> adj(N + 1);
        for(int i = 0; i < M; ++i) {
            int U, V, P; cin >> U >> V >> P;
            adj[U].push_back({V, P});
        }

        dijkstra_erase(adj, S, D, N);    
        solve(adj, S, D, N);
    }

    return 0;
}