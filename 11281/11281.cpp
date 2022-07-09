#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
const int MID = 10000;

typedef vector<vector<int>> vvint;

void forward_DFS(int node, vvint& adj, vector<bool>& visit, stack<int>& stk) {
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        forward_DFS(next, adj, visit, stk);
    }
    stk.push(node);
}

void backward_DFS(int node, vvint& adj, vector<bool>& visit, vector<int>& group, int& group_number) {
    group[node] = group_number;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        backward_DFS(next, adj, visit, group, group_number);
    }
}

void get_scc(int N, vvint& f_adj, vvint& b_adj, vector<int>& group, vvint& scc_adj) {
    vector<bool> visit(20001);
    stack<int> stk;
    for(int node = 1; node <= N; ++node) {
        if(!visit[MID + node]) {
            visit[MID + node] = true;
            forward_DFS(MID + node, f_adj, visit, stk);
        }
        
        if(!visit[MID - node]) {
            visit[MID - node] = true;
            forward_DFS(MID - node, f_adj, visit, stk);
        }
    }

    int group_number = 1;
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
    for(int node = 1; node <= N; ++node) {
        for(auto& next : f_adj[MID + node]) {
            if(group[MID + node] != group[next]) {
                scc_adj[group[MID + node]].push_back(group[next]);
            }
        }

        for(auto& next : f_adj[MID - node]) {    
            if(group[MID - node] != group[next]) {
                scc_adj[group[MID - node]].push_back(group[next]);
            }
        }
    }
}

bool is_sat(int N, vector<int>& group) {
    for(int node = 1; node <= N; ++node) {
        if(group[MID + node] == group[MID - node]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    
    vvint forward_adj(20001), backward_adj(20001);
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        forward_adj[MID - a].push_back(MID + b);
        forward_adj[MID - b].push_back(MID + a);
        backward_adj[MID + b].push_back(MID - a);
        backward_adj[MID + a].push_back(MID - b);
    }

    vvint scc_adj;
    vector<int> group(20001, -1);

    get_scc(N, forward_adj, backward_adj, group, scc_adj);
    if(is_sat(N, group)) {
        int size = scc_adj.size();
        vector<int> tf_value(N + 1, -1);
        vector<int> in_degree(size);
        vvint components(size);

        for(int node = 1; node <= N; ++node) {
            components[group[MID + node]].push_back(MID + node);
            components[group[MID - node]].push_back(MID - node);
        }

        for(int node = 1; node < size; ++node) {
            for(auto& next : scc_adj[node]) in_degree[next]++;
        }

        queue<int> q;
        for(int node = 1; node < size; ++node) {
            if(in_degree[node] == 0) q.push(node);
        }

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(auto& var : components[node]) {
                if(var < MID && tf_value[MID - var] == -1) tf_value[MID - var] = 1;
                else if(var > MID && tf_value[var - MID] == -1) tf_value[var - MID] = 0;
            }

            for(auto& next : scc_adj[node]) {
                if(--in_degree[next] == 0) q.push(next);
            }
        }

        cout << 1 << '\n';
        for(int node = 1; node <= N; ++node) {
            cout << tf_value[node] << ' ';
        }
    }
    else cout << 0;

    return 0;
}