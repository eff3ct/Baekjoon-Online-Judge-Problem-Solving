#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
const int INF = 987654321;

void get_dist(vector<vector<pii>>& adj, int s, vector<int>& dist) {
    priority_queue<pii, vector<pii>, greater<pii>> pq; //dist, node
    dist[s] = 0;
    pq.push({0, s});

    while(!pq.empty()) {
        int now_dist = pq.top().first;
        int now_node = pq.top().second;
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
}

void solve(vector<vector<pii>>& adj, int s, int g, int h, vector<int>& canditate) {
    int n = int(adj.size());
    vector<int> dist_s(n, INF);
    vector<int> dist_g(n, INF);
    vector<int> dist_h(n, INF);

    get_dist(adj, s, dist_s);
    get_dist(adj, g, dist_g);
    get_dist(adj, h, dist_h);

    vector<int> ans;

    int x;
    for(int i = 0; i < int(adj[g].size()); ++i) {
        if(adj[g][i].first == h) {
            x = i;
            break;
        }
    }
    int dist_gh = adj[g][x].second;

    //s->g->h->t
    int min_dist_sght = dist_s[g] + dist_gh;
    for(auto& c : canditate) {
        if(min_dist_sght + dist_h[c] == dist_s[c]) ans.push_back(c);
    }

    //s->h->g->t
    int min_dist_shgt = dist_s[h] + dist_gh;
    for(auto& c : canditate) {
        if(min_dist_shgt + dist_g[c] == dist_s[c]) ans.push_back(c);
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    for(auto& e : ans) cout << e << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int T; cin >> T;

    while(T --> 0) {
        int n, m, t; cin >> n >> m >> t;
        int s, g, h; cin >> s >> g >> h;
        vector<vector<pii>> adj(n + 1);
        for(int i = 0; i < m; ++i) {
            int a, b, d; cin >> a >> b >> d;
            adj[a].push_back({b, d});
            adj[b].push_back({a, d});
        }

        vector<int> canditate(t);
        for(int& e : canditate) cin >> e;

        solve(adj, s, g, h, canditate);
    }

    return 0;
}