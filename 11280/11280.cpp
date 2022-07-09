#include <iostream>
#include <vector>
#include <stack>

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

void get_scc(int N, vvint& f_adj, vvint& b_adj, vector<int>& group) {
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

    get_scc(N, forward_adj, backward_adj, group);
    if(is_sat(N, group)) cout << 1;
    else cout << 0;

    return 0;
}