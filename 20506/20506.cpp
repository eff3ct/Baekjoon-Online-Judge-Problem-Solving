#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll DFS(int node, vector<ll>& size, vector<vector<int>>& adj) {
    size[node] = 1;
    for(int& next_node : adj[node]) 
        size[node] += DFS(next_node, size, adj);
    return size[node];
}

int main() {
    int N; cin >> N;
    int root = -1;

    vector<vector<int>> adj(N + 1);
    for(int i = 1; i <= N; ++i) {
        int par; cin >> par;
        if(par == 0) {
            root = i;
            continue;
        }
        adj[par].push_back(i);
    }

    vector<ll> subtree_size(N + 1);
    DFS(root, subtree_size, adj);

    ll even_ans = 0;
    ll odd_ans = 0;
    int parity = 1;
    for(int i = 1; i <= N; ++i) {
        ll ans = subtree_size[i] * subtree_size[i];
        ll tmp = 0;
        for(auto& next : adj[i]) {
            tmp += subtree_size[next] * subtree_size[next];
        }

        ll cnt = ans - tmp;
        if(parity) {
            if(cnt & 1) {
                odd_ans += (cnt / 2 + 1) * i;
                even_ans += (cnt / 2) * i;
                parity ^= 1;
            }
            else {
                odd_ans += (cnt / 2) * i;
                even_ans += (cnt / 2) * i;
            }
        }
        else {
            if(cnt & 1) {
                even_ans += (cnt / 2 + 1) * i;
                odd_ans += (cnt / 2) * i;
                parity ^= 1;
            }
            else {
                odd_ans += (cnt / 2) * i;
                even_ans += (cnt / 2) * i;
            }
        }
    }

    cout << even_ans << ' ' << odd_ans << '\n';

    return 0;
}