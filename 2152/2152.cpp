#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
typedef vector<vector<int>> vvint;

void forward_DFS(int node, vector<bool>& visit, vvint& adj, stack<int>& stk) {
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        forward_DFS(next, visit, adj, stk);
    }
    stk.push(node);
}

void backward_DFS(int node, vector<bool>& visit, vvint& adj, vector<int>& group, int& group_number) {
    group[node] = group_number;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        backward_DFS(next, visit, adj, group, group_number);
    }
}

void get_scc(int N, vvint& f_adj, vvint& b_adj, vector<int>& group, vvint& scc_adj) {
    vector<bool> visit(N + 1, false);
    stack<int> stk;
    for(int node = 1; node <= N; ++node) {
        if(visit[node]) continue;
        visit[node] = true;
        forward_DFS(node, visit, f_adj, stk);
    }

    int group_number = 1;
    fill(visit.begin(), visit.end(), false);
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if(visit[node]) continue;

        visit[node] = true;
        backward_DFS(node, visit, b_adj, group, group_number);
        group_number++;
    }

    scc_adj.resize(group_number);
    for(int node = 1; node <= N; ++node) {
        for(auto& next : f_adj[node]) {
            if(group[node] != group[next]) {
                scc_adj[group[node]].push_back(group[next]);
            }
        }
    }
}

int get_max_count(int N, vector<int>& group, vvint& adj, int S, int T) {
    int size = int(adj.size());
    queue<int> q;

    vector<int> count(size);
    for(int i = 1; i <= N; ++i) count[group[i]]++;
    
    vector<bool> is_connected(size, false);
    is_connected[group[S]] = true;
    vector<int> in_degree(size);

    for(int node = 1; node < size; ++node) {
        for(auto& next : adj[node]) in_degree[next]++;
    }

    vector<int> total_count(size);
    total_count[group[S]] = count[group[S]];
    for(auto& next : adj[group[S]]) is_connected[next] = true;

    for(int node = 1; node < size; ++node) {
        if(in_degree[node] == 0) q.push(node);
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(auto& next : adj[node]) {
            if(is_connected[node]) {
                total_count[next] = max(total_count[node] + count[next], total_count[next]);
                is_connected[next] = true;
            }

            if(--in_degree[next] == 0) q.push(next);
        }
    }

    return (is_connected[group[T]] ? total_count[group[T]] : 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, S, T; cin >> N >> M >> S >> T;

    vvint forward_adj(N + 1), backward_adj(N + 1);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        forward_adj[u].push_back(v);
        backward_adj[v].push_back(u);
    }

    vvint scc_adj;
    vector<int> group(N + 1);

    get_scc(N, forward_adj, backward_adj, group, scc_adj);
    cout << get_max_count(N, group, scc_adj, S, T);

    return 0;
}