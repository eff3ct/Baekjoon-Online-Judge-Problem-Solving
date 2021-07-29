// https://www.acmicpc.net/problem/19535 //
// UCPC 2020 Qualifer D //
#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;

using namespace std;

void solveBFS(vector<int>*& adj, int N) {
    ll jieut = 0;
    for(int i = 1; i <= N; ++i) {
        if(adj[i].size() >= 3) {
            ll s = adj[i].size();
            jieut += s * (s - 1) * (s - 2) / 6; //combination(s, 3)
        }
    }

    ll digeud = 0;
    queue<int> q;
    vector<bool> visit(N + 1, false);
    visit[1] = true;
    q.push(1);
    
    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(int i = 0; i < adj[now].size(); ++i) {
            int next = adj[now][i];
            if(visit[next]) continue;
            digeud += (adj[now].size() - 1) * (adj[next].size() - 1);
            visit[next] = true;
            q.push(next);
        }
    }

    if(digeud == 3 * jieut) {
        cout << "DUDUDUNGA";
    }
    else if(digeud > 3 * jieut) {
        cout << "D";
    }
    else cout << "G";
}

int main() {
    int N; cin >> N;

    vector<int>* adj = new vector<int>[N + 1];
    for(int i = 0; i < (N - 1); ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    solveBFS(adj, N);

    return 0;
}