#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void forward_DFS(int node, vector<vector<int>>& adj, vector<bool>& visit, stack<int>& stk) {
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        forward_DFS(next, adj, visit, stk);
    }
    stk.push(node);
}

void backward_DFS(int node, vector<vector<int>>& adj, vector<bool>& visit,
    vector<int>& group, int& group_number) {
    group[node] = group_number;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        backward_DFS(next, adj, visit, group, group_number);
    }
}

void DFS(int node, vector<vector<int>>& adj, vector<bool>& visit, int& total_count) {
    total_count++;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        DFS(next, adj, visit, total_count);
    }
}

void solve(int N, vector<vector<int>>& f_adj, vector<vector<int>>& b_adj,
    vector<int>& group, vector<vector<int>>& scc_adj) {
    vector<bool> visit(N, false);
    stack<int> stk;
    for(int node = 0; node < N; ++node) {
        if(visit[node]) continue;
        visit[node] = true;
        forward_DFS(node, f_adj, visit, stk);
    }

    int group_number = 0;
    fill(visit.begin(), visit.end(), false);
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if(visit[node]) continue;
        
        visit[node] = true;
        backward_DFS(node, b_adj, visit, group, group_number);
        group_number++;
    }

    scc_adj.resize(group_number);
    vector<int> in_degree(group_number);
    for(int node = 0; node < N; ++node) {
        for(auto& next : f_adj[node]) {
            if(group[node] != group[next]) {
                scc_adj[group[node]].push_back(group[next]);
                in_degree[group[next]]++;
            }
        }
    }

    int cnt = 0;
    int group_no = -1;
    for(int node = 0; node < group_number; ++node) {
        if(in_degree[node] == 0) {
            group_no = node;
            cnt++; 
        }
    }

    bool is_possible = true;

    if(cnt == 1) {
        vector<bool> scc_visit(group_number);
        int total_count = 0;
        scc_visit[group_no] = true;
        DFS(group_no, scc_adj, scc_visit, total_count);
        if(total_count != group_number) is_possible = false;
    }
    else is_possible = false;

    if(is_possible) {
        for(int node = 0; node < N; ++node) {
            if(group[node] == group_no) cout << node << '\n'; 
        }
    }
    else cout << "Confused\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        int N, M; cin >> N >> M;

        vector<vector<int>> forward_adj(N), backward_adj(N);
        for(int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            forward_adj[a].push_back(b);
            backward_adj[b].push_back(a);
        }

        vector<vector<int>> scc_adj;
        vector<int> group(N);

        solve(N, forward_adj, backward_adj, group, scc_adj);
        cout << '\n';
    }

    return 0;
}