#include <bits/stdc++.h>
#define MAX 100'001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<pii> adj[MAX];
const int sz = 18;

int max_dist[MAX][sz + 1];
int min_dist[MAX][sz + 1];
int parent[MAX][sz + 1];
int depth[MAX];

int N; 

void dfs(int cur_node = 1) {
    for(auto& next : adj[cur_node]) {
        int next_node = next.first;
        int dist = next.second;

        if(depth[next_node] != -1) continue;

        depth[next_node] = depth[cur_node] + 1;
        max_dist[next_node][0] = dist;
        min_dist[next_node][0] = dist;
        parent[next_node][0] = cur_node;

        dfs(next_node);
    }
}

void init() {
    for(int i = 0; i < MAX; ++i) {
        fill(max_dist[i], max_dist[i] + sz + 1, -1);
        fill(min_dist[i], min_dist[i] + sz + 1, 1e9);
        fill(parent[i], parent[i] + sz + 1, -1);
    }
    fill(depth, depth + MAX, -1);

    depth[1] = 0;
    dfs();

    for(int j = 0; j < sz; ++j) {
        for(int i = 1; i <= N; ++i) {
            if(parent[i][j] == -1) continue;
            parent[i][j + 1] = parent[ parent[i][j] ][j];
            max_dist[i][j + 1] = max(max_dist[i][j], max_dist[ parent[i][j] ][j]);
            min_dist[i][j + 1] = min(min_dist[i][j], min_dist[ parent[i][j] ][j]);
        }
    }
}

void solve(int x, int y) {
    if(depth[x] < depth[y]) swap(x, y);
    int diff = depth[x] - depth[y];

    int M = -1, m = 1e9;
    int i = 0;
    while(diff) {
        if(diff & 1) {
            M = max(M, max_dist[x][i]);
            m = min(m, min_dist[x][i]);
            x = parent[x][i];
        }
        diff >>= 1;
        ++i;
    }

    if(x != y) {
        for(int j = sz; j >= 0; --j) {
            if(parent[x][j] != -1 && parent[x][j] != parent[y][j]) {
                M = max({M, max_dist[x][j], max_dist[y][j]});
                m = min({m, min_dist[x][j], min_dist[y][j]});

                x = parent[x][j];
                y = parent[y][j];
            }
        }

        M = max({M, max_dist[x][0], max_dist[y][0]});
        m = min({m, min_dist[x][0], min_dist[y][0]});
    }

    cout << m << ' ' << M << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    for(int i = 0; i < N - 1; ++i) {
        int A, B, C; cin >> A >> B >> C;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }

    init();

    int K; cin >> K;
    while(K --> 0) {
        int D, E; cin >> D >> E;
        solve(D, E);
    }

    return 0;
}