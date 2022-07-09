#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;
const int MID = 1000;

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
    vector<bool> visit(2001);
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

    int N, M; 
    while(cin >> N >> M) {
        vvint forward_adj(2001), backward_adj(2001);
        for(int i = 0; i < M; ++i) {
            string a, b; cin >> a >> b;
            int a_num, b_num;
            if(a[0] == '+') a_num = stoi(a.substr(1));
            else a_num = -stoi(a.substr(1));
            if(b[0] == '+') b_num = stoi(b.substr(1));
            else b_num = -stoi(b.substr(1));

            forward_adj[MID - a_num].push_back(MID + b_num);
            forward_adj[MID - b_num].push_back(MID + a_num);
            backward_adj[MID + b_num].push_back(MID - a_num);
            backward_adj[MID + a_num].push_back(MID - b_num);
        }

        vvint scc_adj;
        vector<int> group(2001, -1);

        get_scc(N, forward_adj, backward_adj, group);
        if(is_sat(N, group)) cout << 1 << '\n';
        else cout << 0 << '\n'; 
    }

    return 0;
}