#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<int> adj[100001];
int in[100001];
vector<pii> is_cut;
int cnt_n;

int DFS(int cur, int parent) {
    in[cur] = ++cnt_n;
    int ret = in[cur];

    for(int& next : adj[cur]) {
        if(next == parent) continue;

        if(in[next]) {
            ret = min(ret, in[next]);
            continue;
        }

        int prev = DFS(next, cur);

        if(prev > in[cur]) 
            is_cut.push_back({min(cur, next), max(cur, next)});
        
        ret = min(ret, prev);
    }

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
        if(!in[i]) DFS(i, -1);
    }

    sort(is_cut.begin(), is_cut.end());
    cout << is_cut.size() << '\n';
    for(auto& e : is_cut) cout << e.first << ' ' << e.second << '\n';

    return 0;
}