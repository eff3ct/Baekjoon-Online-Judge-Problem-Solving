#include <bits/stdc++.h>
#define MAX 4'001

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ppll = pair<ll, pll>;

const ll INF = 1e18;
vector<pll> adj[MAX];

ll dist_fox[MAX];
ll dist_wolf[2][MAX];

void dijkstra() {
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist_fox[1] = 0;
    pq.push({0, 1});

    while(!pq.empty()) {
        ll cur_dist = pq.top().first;
        ll cur_node = pq.top().second;
        pq.pop();

        if(cur_dist > dist_fox[cur_node]) continue;

        for(pll& next : adj[cur_node]) {
            ll next_dist = 2 * next.second + cur_dist;
            ll next_node = next.first;

            if(next_dist < dist_fox[next_node]) {
                dist_fox[next_node] = next_dist;
                pq.push({next_dist, next_node});
            }
        }
    }
}

void dijkstra_wolf() {
    priority_queue<ppll, vector<ppll>, greater<ppll>> pq;
    pq.push({0, {1, 1}});

    while(!pq.empty()) {
        ll cur_dist = pq.top().first;
        ll cur_node = pq.top().second.second;
        ll is_half = pq.top().second.first;
        pq.pop();

        if(cur_dist > dist_wolf[is_half][cur_node]) continue;

        for(pll& next : adj[cur_node]) {
            ll next_dist = next.second * (is_half ? 1 : 4) + cur_dist;
            ll next_node = next.first;

            if(dist_wolf[!is_half][next_node] > next_dist) {
                dist_wolf[!is_half][next_node] = next_dist;
                pq.push({next_dist, {is_half ^ 1, next_node}});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    for(int i = 0; i < M; ++i) {
        ll a, b, d; cin >> a >> b >> d;
        adj[a].push_back({b, d});
        adj[b].push_back({a, d});
    }
    
    fill(dist_fox, dist_fox + MAX, INF);
    fill(dist_wolf[0], dist_wolf[0] + MAX, INF);
    fill(dist_wolf[1], dist_wolf[1] + MAX, INF);

    dijkstra();
    dijkstra_wolf();

    int ans = 0;
    for(int i = 2; i <= N; ++i) {
        if(dist_fox[i] < min(dist_wolf[0][i], dist_wolf[1][i])) ans++;
    }

    cout << ans << '\n';

    return 0;
}