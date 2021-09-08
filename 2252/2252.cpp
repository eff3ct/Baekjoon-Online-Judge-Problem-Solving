// https://www.acmicpc.net/problem/2252 //
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int N, M;

void topologySort(vector<vector<int>>& adj, vector<int>& count) {
    vector<int> ret;
    queue<int> q;
    for(int i = 1; i <= N; ++i) {
        if(count[i] == 0) q.push(i);
    }

    for(int i = 0; i < N; ++i) {
        int now = q.front();
        q.pop();

        ret.push_back(now);
        
        for(int j = 0; j < (int)adj[now].size(); ++j) {
            count[adj[now][j]]--;
            if(count[adj[now][j]] == 0) q.push(adj[now][j]);
        }
    }

    for(auto& element : ret) cout << element << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    vector<vector<int>> adj(N + 1, vector<int>());
    vector<int> count(N + 1, 0);

    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        count[v]++;
    }

    topologySort(adj, count);

    return 0;
}