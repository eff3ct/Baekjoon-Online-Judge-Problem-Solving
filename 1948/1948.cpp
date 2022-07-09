#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> pii;
const int MIN = -987654321;

void solve(int s, int e, vector<vector<pii>>& adj, vector<int>& in_degree) {
    int n = int(adj.size());
    vector<vector<int>> prev_node(n);
    vector<int> dist(n, MIN); //distance,  count
    queue<int> q;

    q.push(s);
    dist[s] = 0;

    while(!q.empty()) {
        int now_node = q.front();
        q.pop();

        for(auto& next : adj[now_node]) {
            int next_node = next.first;
            int weight = next.second;

            if(dist[next_node] < dist[now_node] + weight) {
                dist[next_node] = dist[now_node] + weight;
                if(!prev_node[next_node].empty()) prev_node[next_node].clear();
                prev_node[next_node].push_back(now_node);
            }
            else if(dist[next_node] == dist[now_node] + weight) {
                prev_node[next_node].push_back(now_node);
            }
            
            if(--in_degree[next_node] == 0) q.push(next_node);
        }
    }

    vector<vector<bool>> visit(n, vector<bool>(n, false));
    int cnt = 0;
    
    q.push(e);
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(auto& prev : prev_node[node]) {
            if(visit[node][prev]) continue;
            cnt++;
            visit[node][prev] = true;
            q.push(prev);
        }
    }

    cout << dist[e] << '\n' << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n + 1);
    vector<int> in_degree(n + 1);

    for(int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        in_degree[v]++;
    }

    int s, e; cin >> s >> e;

    solve(s, e, adj, in_degree);

    return 0;
}