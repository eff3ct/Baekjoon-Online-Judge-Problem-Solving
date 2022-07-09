#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;
const int INF = 987654321;

int find(int a, vector<int>& parent) {
    if(a == parent[a]) return a;
    else return parent[a] = find(parent[a], parent);
}

void uni(int a, int b, vector<int>& parent) {
    int parent_a = find(a, parent);
    int parent_b = find(b, parent);

    if(parent_a == parent_b) return;

    if(parent_a < parent_b) parent[parent_b] = parent_a;
    else parent[parent_a] = parent_b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N + 1);
    vector<int> parent(N + 1);
    iota(parent.begin(), parent.end(), 0);

    vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF));
    for(int i = 1; i <= N; ++i) dist[i][i] = 0;

    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);

        uni(a, b, parent);
        dist[a][b] = 1;
        dist[b][a] = 1;
    }

    //find K
    int count = 0;
    set<int> cnt;
    for(int i = 1; i <= N; ++i) cnt.insert(find(i, parent));
    count = int(cnt.size());

    //floyd-warshall algorithm
    for(int k = 1; k <= N; ++k) {
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= N; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    vector<int> res;
    for(int now : cnt) {
        int rep;
        int prev = INF;
        for(int i = 1; i <= N; ++i) {
            if(now != find(i, parent)) continue;

            int ret = 0;
            for(int j = 1; j <= N; ++j) {
                if(dist[i][j] != INF) ret = max(ret, dist[i][j]);
            }

            if(ret < prev) {
                prev = ret;
                rep = i;
            }
        }
        res.push_back(rep);
    }

    sort(res.begin(), res.end());

    cout << count << '\n';
    for(int& e : res) cout << e << '\n';
    
    return 0;
}