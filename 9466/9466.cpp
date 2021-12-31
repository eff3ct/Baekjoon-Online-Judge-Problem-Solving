#include <iostream>
#include <vector>

using namespace std;

int cnt;

void DFS(int node, vector<bool>& visit, vector<bool>& isCycle, vector<int>& adj) {
    visit[node] = true;
    
    int nextNode = adj[node];

    if(!visit[nextNode]) DFS(nextNode, visit, isCycle, adj);
    else if(!isCycle[nextNode]) {
        int start = nextNode;
        while(true) {
            cnt++;
            nextNode = adj[nextNode];
            if(start == nextNode) break;
        }
    }

    isCycle[node] = true;
}

void solve(vector<int>& adj) {
    int s = (int)adj.size();

    vector<bool> visit(s, false);
    vector<bool> isCycle(s, false);

    cnt = 0;
    for(int i = 1; i < s; ++i) {
        if(!visit[i]) DFS(i, visit, isCycle, adj);
    }
    
    cout << s - 1 - cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        int n; cin >> n;
        vector<int> adj(n + 1);
        for(int i = 1; i <= n; ++i) cin >> adj[i];
        solve(adj);
    }

    return 0;
}