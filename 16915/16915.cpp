#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;
const int MID = 100000;

typedef vector<vector<int>> vvint;
typedef struct _p {
    int a, b;
    int size = 0;
} P;

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
    vector<bool> visit(200001);
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
  
    vvint forward_adj(200001), backward_adj(200001);
    vector<int> light_up(N + 1);
    for(int i = 1; i <= N; ++i) cin >> light_up[i];

    vector<P> switch_info(N + 1);

    for(int i = 1; i <= M; ++i) {
        int K; cin >> K;
        for(int j = 0; j < K; ++j) {
            int x; cin >> x;
            if(switch_info[x].size == 0) {
                switch_info[x].a = i;
                switch_info[x].size++;
            }
            else switch_info[x].b = i;
        }
    }

    for(int i = 1; i <= N; ++i) {
        int a_num = switch_info[i].a, b_num = switch_info[i].b;
        
        if(light_up[i]) {
            forward_adj[MID - a_num].push_back(MID - b_num);
            forward_adj[MID + a_num].push_back(MID + b_num);

            forward_adj[MID + b_num].push_back(MID + a_num);
            forward_adj[MID - b_num].push_back(MID - a_num);

            backward_adj[MID - b_num].push_back(MID - a_num);
            backward_adj[MID + b_num].push_back(MID + a_num);

            backward_adj[MID + a_num].push_back(MID + b_num);
            backward_adj[MID - a_num].push_back(MID - b_num);
        }
        else {
            forward_adj[MID - a_num].push_back(MID + b_num);
            forward_adj[MID + a_num].push_back(MID - b_num);

            forward_adj[MID - b_num].push_back(MID + a_num);
            forward_adj[MID + b_num].push_back(MID - a_num);

            backward_adj[MID + b_num].push_back(MID - a_num);
            backward_adj[MID - b_num].push_back(MID + a_num);

            backward_adj[MID + a_num].push_back(MID - b_num);
            backward_adj[MID - a_num].push_back(MID + b_num);
        }
    }

    vvint scc_adj;
    vector<int> group(200001, -1);

    get_scc(M, forward_adj, backward_adj, group);
    if(is_sat(M, group)) cout << 1 << '\n';
    else cout << 0 << '\n'; 

    return 0;
}