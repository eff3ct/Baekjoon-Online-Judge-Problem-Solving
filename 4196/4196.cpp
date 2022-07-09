#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(int node, vector<bool>& visit, vector<vector<int>>& adj, stack<int>& stk) {
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        DFS(next, visit, adj, stk);
    }
    stk.push(node);
}

void backward_DFS(int node, vector<bool>& visit, vector<vector<int>>& adj, vector<int>& group, int& group_number) {
    group[node] = group_number;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        backward_DFS(next, visit, adj, group, group_number);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T --> 0) {
        int N, M; cin >> N >> M;

        vector<vector<int>> forward_adj(N + 1), backward_adj(N + 1);

        for(int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            forward_adj[a].push_back(b);
            backward_adj[b].push_back(a);
        }

        stack<int> stk;
        vector<bool> visit(N + 1, false);

        for(int i = 1; i <= N; ++i) {
            if(visit[i]) continue;
            visit[i] = true;
            DFS(i, visit, forward_adj, stk);
        }

        fill(visit.begin(), visit.end(), false);
        vector<int> group(N + 1, -1);
        int group_number = 1;
        while(!stk.empty()) {
            int node = stk.top();
            stk.pop();

            if(visit[node]) continue;
            visit[node] = true;
            backward_DFS(node, visit, backward_adj, group, group_number);
            group_number++;
        }

        vector<int> indegree(N + 1);
        for(int i = 1; i <= N; ++i) {
            for(auto& next : forward_adj[i]) {
                if(group[i] != group[next]) indegree[group[next]]++;
            }
        }

        int cnt = 0;
        for(int i = 1; i < group_number; ++i) {
            if(indegree[i] == 0) cnt++;
        }

        cout << cnt << '\n';
    }

    return 0;
}