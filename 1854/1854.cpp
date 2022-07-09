#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<vector<pii>> adj(1001);
priority_queue<int> max_heap[1001];

void solve(int k) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 1});
    max_heap[1].push(0);

    while(!pq.empty()) {
        int now_node = pq.top().second;
        int now_dist = pq.top().first;
        pq.pop();

        for(pii& next : adj[now_node]) {
            int next_node = next.first;
            if((int)max_heap[next_node].size() < k) {
                max_heap[next_node].push(now_dist + next.second);
                pq.push({next.second + now_dist, next_node});
            }
            else if(max_heap[next_node].top() > now_dist + next.second) {
                max_heap[next_node].pop();
                max_heap[next_node].push(now_dist + next.second);
                pq.push({next.second + now_dist, next_node});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    solve(k);

    for(int i = 1; i <= n; ++i) {
        if((int)max_heap[i].size() < k) cout << "-1\n";
        else cout << max_heap[i].top() << '\n';
    }

    return 0;
}