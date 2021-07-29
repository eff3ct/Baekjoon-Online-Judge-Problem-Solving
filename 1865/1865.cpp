// https://www.acmicpc.net/problem/1865 //
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;

vector<int> dist(501, INF);

void solve(vector<pair<int, int>> (&adj)[501], int& N) {
    dist[1] = 0;
    for(int i = 1; i <= (N - 1); ++i) {
        for(int j = 1; j <= N; ++j) {
            for(auto edge : adj[j]) {
                dist[edge.first] = min(dist[j] + edge.second, dist[edge.first]);
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        for(auto edge : adj[i]) {
            if(dist[edge.first] > dist[i] + edge.second) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
}

int main() {
    int TC; cin >> TC;
    while(TC--) {
        vector<pair<int, int>> adj[501];
        int N, M, W; cin >> N >> M >> W;

        fill(dist.begin(), dist.end(), INF);

        for(int i = 0; i < M; ++i) {
            int s, e, t; cin >> s >> e >> t;
            adj[s].push_back({e, t});
            adj[e].push_back({s, t});
        }

        for(int i = 0; i < W; ++i) {
            int s, e, t; cin >> s >> e >> t;
            adj[s].push_back({e, -t});
        }

        solve(adj, N);
    }

    return 0;
}