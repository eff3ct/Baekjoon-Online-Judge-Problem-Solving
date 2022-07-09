#include <bits/stdc++.h>

using namespace std;
using ppii = pair<int, pair<int, int>>;

int find(int a, vector<int>& parent) {
    if(a == parent[a]) return a;
    else return parent[a] = find(parent[a], parent);
}

void uni(int a, int b, vector<int>& parent) {
    int a_parent = find(a, parent);
    int b_parent = find(b, parent);

    if(a_parent == b_parent) return;

    if(a_parent < b_parent) parent[b_parent] = a_parent;
    else parent[a_parent] = b_parent;
}

void get_mst(vector<vector<int>>& adj_mat, vector<vector<int>>& adj, int& N) {
    vector<int> parent(N + 1);
    iota(parent.begin(), parent.end(), 0);

    priority_queue<ppii, vector<ppii>, greater<ppii>> pq;

    for(int i = 1; i <= N; ++i) {
        for(int j = i + 1; j <= N; ++j) {
            pq.push({adj_mat[i][j], {i, j}});
        }
    }

    uni(pq.top().second.first, pq.top().second.second, parent);
    adj[pq.top().second.first].push_back(pq.top().second.second);
    adj[pq.top().second.second].push_back(pq.top().second.first);
    pq.pop();

    while(!pq.empty()) {
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();

        if(find(u, parent) != find(v, parent)) {
            uni(u, v, parent);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<vector<int>> adj_mat(N + 1, vector<int>(N + 1));
    for(int i = 1; i <= N; ++i) {
        for(int j = i + 1; j <= N; ++j) {
            cin >> adj_mat[i][j];
        }
    }

    vector<vector<int>> adj(N + 1);
    get_mst(adj_mat, adj, N);

    for(int i = 1; i <= N; ++i) {
        cout << adj[i].size() << ' ';
        sort(adj[i].begin(), adj[i].end());
        for(int j = 0; j < int(adj[i].size()); ++j) {
            cout << adj[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}