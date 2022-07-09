#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int MAX = 1001;
vector<int> A(MAX, -1), B(MAX, -1);
vector<bool> vst(MAX, false);

bool DFS(int node, vector<vector<int>>& adj) {
    vst[node] = true;
    for(int& next_node : adj[node]) {
        if(B[next_node] == -1 || !vst[B[next_node]] && DFS(B[next_node], adj)) {
            A[node] = next_node;
            B[next_node] = node;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int>> adj(N + 1);

    for(int i = 0; i < N; ++i) {
        int cnt; cin >> cnt;
        for(int j = 0; j < cnt; ++j) {
            int x; cin >> x;
            adj[i + 1].push_back(x);
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; ++i) {
        if(A[i] == -1) {
            fill(vst.begin(), vst.end(), false);
            if(DFS(i, adj)) ans++;
        }
    }

    int cnt = 0;
    for(int i = 1; i <= N; ++i) {
        fill(vst.begin(), vst.end(), false);
            
        if(DFS(i, adj)) {
            cnt++;
            ans++;
        }

        if(cnt == K) break;
    }

    cout << ans << '\n';

    return 0;
}