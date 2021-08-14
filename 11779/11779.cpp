// https://www.acmicpc.net/problem/11779 //
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#define INF 987654321

using namespace std;

vector<vector<pair<int, int>>> adj;

void solve(int start, int end) {
    vector<int> dist(adj.size(), INF);
    vector<int> history(adj.size());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //dist, node

    history[start] = -1;
    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        int curDist = pq.top().first;
        int curNode = pq.top().second;

        pq.pop();

        if(dist[curNode] < curDist) continue;

        for(auto& element : adj[curNode]) {
            int nextNode = element.first;
            int nextDist = element.second + curDist;

            if(nextDist < dist[nextNode]) {
                dist[nextNode] = nextDist;
                history[nextNode] = curNode;
                pq.push({nextDist, nextNode});
            }
        }
    }

    vector<int> path;
    int cnt = 1;
    int node = history[end];
    path.push_back(end);
    while(node != -1) {
        path.push_back(node);
        node = history[node];
        cnt++;
    }

    cout << dist[end] << '\n' << cnt << '\n';
    for(int i = cnt - 1; i >= 0; --i) cout << path[i] << " ";
}

int main() {
    int n, m; cin >> n >> m;

    adj.resize(n + 1);
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    int s, e; cin >> s >> e;

    solve(s, e);

    return 0;
}