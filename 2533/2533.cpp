#include <bits/stdc++.h>
#define MAX 1'000'001
#define INF 987654321

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<int> adj[MAX];
vector<int> child[MAX];
int dp[MAX][2];
bool vst[MAX];

int DFS(int cur, int stat) {
    if(dp[cur][stat] != -1) return dp[cur][stat];

    int& ret = dp[cur][stat];
    ret = (stat == 1);

    for(int& next : child[cur]) {
        if(stat) ret += min(DFS(next, stat), DFS(next, !stat));
        else ret += DFS(next, !stat);
    }

    return ret;
}

void reconstruct_DFS(int cur = 1) {
    for(int& next : adj[cur]) {
        if(vst[next]) continue;
        vst[next] = true;
        child[cur].push_back(next);
        reconstruct_DFS(next);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    for(int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vst[1] = true;
    reconstruct_DFS();

    for(int i = 0; i < MAX; ++i) dp[i][0] = -1, dp[i][1] = -1;
    int ans = min(DFS(1, 0), DFS(1, 1));
    cout << ans << '\n';

    return 0;
}