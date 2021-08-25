#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, r; cin >> n >> m >> r;

    vector<int> items(n + 1);
    for(int i = 1; i <= n; ++i) cin >> items[i];

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    for(int i = 0; i < r; ++i) {
        int a, b, l; cin >> a >> b >> l;
        dist[a][b] = l;
        dist[b][a] = l;
    }

    for(int i = 1; i <= n; ++i) dist[i][i] = 0;
    
    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int maxItemCnt = 0;
    int localMax = 0;
    for(int i = 1; i <= n; ++i) {
        localMax = 0;
        for(int j = 1; j <= n; ++j) {
            if(dist[i][j] <= m) localMax += items[j];
        }
        maxItemCnt = max(maxItemCnt, localMax);
    }

    cout << maxItemCnt;

    return 0;
}