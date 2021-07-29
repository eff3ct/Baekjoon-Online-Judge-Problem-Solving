// https://www.acmicpc.net/problem/11657 //
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;

vector<long long> dist(501, INF);

void solve(vector<pair<int, int>> (&adj)[501], int& N) {
    dist[1] = 0;
    for(int i = 0; i < (N - 1); ++i) {
        for(int j = 1; j <= N; ++j) {
            for(auto edge : adj[j]) {
                if(dist[j] != INF) {
                    dist[edge.first] = min(dist[j] + edge.second, dist[edge.first]);
                }
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        for(auto edge : adj[i]) {
            if(dist[i] != INF && dist[edge.first] > dist[i] + edge.second) {
                cout << "-1\n";
                return;
            }
        }
    }

    for(int i = 2; i <= N; ++i) {
        if(dist[i] != INF) {
            cout << dist[i] << '\n';
        }
        else cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<pair<int, int>> adj[501];
    int N, M; cin >> N >> M;

    for(int i = 0; i < M; ++i) {
        int s, e, t; cin >> s >> e >> t;
        adj[s].push_back({e, t});
    }

    solve(adj, N);

    return 0;
}