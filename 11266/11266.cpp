#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<int> adj[10001];
bool is_cut[10001];
int in[10001];

int cnt_n;

int DFS(int cur, bool is_root = false) {
    in[cur] = ++cnt_n;
    int ret = in[cur];
    int child = 0;

    for(int& next : adj[cur]) {
        if(in[next]) {
            ret = min(ret, in[next]);
            continue;
        }

        child++;
        int prev = DFS(next);

        if(!is_root && prev >= in[cur]) 
            is_cut[cur] = true;
        
        ret = min(ret, prev);
    }

    if(is_root && child > 1) is_cut[cur] = true;

    return ret; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int V, E; cin >> V >> E;
    for(int i = 0; i < E; ++i) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    for(int i = 1; i <= V; ++i) {
        if(!in[i]) DFS(i, true);
    }

    int cnt = 0;
    for(int i = 1; i <= V; ++i) if(is_cut[i]) cnt++;

    cout << cnt << '\n';
    for(int i = 1; i <= V; ++i) if(is_cut[i]) cout << i << ' ';   

    return 0;
}