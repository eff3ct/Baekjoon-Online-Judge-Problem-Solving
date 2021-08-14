#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define INF 11987654321LL

using namespace std;
typedef long long ll;

vector<vector<pair<int, int>>> adj;

ll solve(int start, int end) {
    vector<ll> dist(adj.size(), INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[start] = 0;
    pq.push({0, start}); //{dist, node}

    while(!pq.empty()) {
        ll curDist = pq.top().first;
        int curNode = pq.top().second;

        pq.pop();

        if(dist[curNode] < curDist) continue;

        for(auto& element : adj[curNode]) {
            int nextNode = element.first;
            ll nextDist = element.second + curDist;

            if(nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                pq.push({nextDist, nextNode});
            }
        }
    }

    return dist[end];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, E; cin >> N >> E;
    
    adj.resize(N + 1);
    for(int i = 0; i < E; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    int v1, v2; cin >> v1 >> v2;

    ll ret = solve(1, v1) + solve(v1, v2) + solve(v2, N);
    ret = min(ret, solve(1, v2) + solve(v2, v1) + solve(v1, N));

    if(ret >= INF) cout << -1;
    else cout << ret;

    return 0;
}