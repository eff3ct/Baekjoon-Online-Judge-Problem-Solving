#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int N, M; 

void solve(vector<vector<int>>& adj, vector<int>& count) {
    vector<int> ret;
    queue<int> q;

    for(int i = 1; i <= N; ++i) {
        if(count[i] == 0) q.push(i);
    }

    for(int i = 1; i <= N; ++i) {
        if(q.empty()) {
            cout << 0;
            return;
        }

        int nowNode = q.front();
        ret.push_back(nowNode);
        q.pop();

        for(auto& nextNode : adj[nowNode]) {
            if(--count[nextNode] == 0) q.push(nextNode);
        }
    }

    for(auto& element : ret) cout << element << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    vector<vector<int>> adj(N + 1);
    vector<int> count(N + 1);
    for(int i = 0; i < M; ++i) {
        int cnt; cin >> cnt;
        int prev; cin >> prev;
        for(int j = 0; j < cnt - 1; ++j) {
            int now; cin >> now;
            adj[prev].push_back(now);
            count[now]++;
            prev = now;
        }
    }

    solve(adj, count);
    
    return 0;
}