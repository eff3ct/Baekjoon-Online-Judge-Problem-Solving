#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

void forward_DFS(int node, vector<vector<int>>& adj, stack<int>& stk, vector<bool>& visit) {
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        forward_DFS(next, adj, stk, visit);
    }
    stk.push(node);
}

void backward_DFS(int node, vector<vector<int>>& adj, vector<bool>& visit, vector<int>& group, int& group_number) {
    group[node] = group_number;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        backward_DFS(next, adj, visit, group, group_number);
    }
}

void get_SCC(int N, vector<vector<int>>& f_adj, vector<vector<int>>& b_adj, 
    vector<int>& group, vector<vector<int>>& scc_adj, vector<int>& cost, vector<int>& money) {

    stack<int> stk;
    vector<bool> visit(N + 1, false);
    for(int i = 1; i <= N; ++i) {
        if(visit[i]) continue;
        visit[i] = true;
        forward_DFS(i, f_adj, stk, visit);
    }

    fill(visit.begin(), visit.end(), false);
    
    int group_number = 1;
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if(visit[node]) continue;
        
        visit[node] = true;
        backward_DFS(node, b_adj, visit, group, group_number);
        group_number++;
    }
    
    scc_adj.resize(group_number);
    cost.resize(group_number);

    vector<int> in_degree(group_number);

    for(int i = 1; i <= N; ++i) {
        cost[group[i]] += money[i];
        for(auto& j : f_adj[i]) {
            if(group[i] != group[j]) {
                in_degree[group[j]]++;
                scc_adj[group[i]].push_back(group[j]);
            }
        }
    }
}

int get_max(int start_node, vector<vector<int>>& adj, vector<int>& cost, vector<bool>& is_restaurant) {
    vector<bool> is_reachable(int(adj.size()));
    is_reachable[start_node] = true;
    for(auto& next : adj[start_node]) is_restaurant[next] = true;

    vector<int> total_cost = cost;

    vector<int> in_degree(int(adj.size()), 0);
    for(int i = 1; i < int(adj.size()); ++i) {
        for(auto& j : adj[i]) in_degree[j]++;
    }

    queue<int> q;
    for(int i = 1; i < int(adj.size()); ++i) {
        if(in_degree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(auto& next : adj[node]) {
            if(is_reachable[node]) {
                is_reachable[next] = true;
                total_cost[next] = max(total_cost[next], total_cost[node] + cost[next]);
            }
            if(--in_degree[next] == 0) q.push(next);
        }
    }
    
    int ret = 0;
    for(int i = 1; i < int(adj.size()); ++i) {
        if(is_restaurant[i] && is_reachable[i])
            ret = max(ret, total_cost[i]);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> forward_adj(N + 1), backward_adj(N + 1);
    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        forward_adj[a].push_back(b);
        backward_adj[b].push_back(a);
    }

    vector<int> money(N + 1);
    for(int i = 1; i <= N; ++i) cin >> money[i];

    int S, P; cin >> S >> P;
    vector<bool> is_restaurant(N + 1, false);
    for(int i = 0; i < P; ++i) {
        int a; cin >> a;
        is_restaurant[a] = true;
    }

    vector<vector<int>> scc_adj;
    vector<int> cost;
    vector<int> group(N + 1);

    get_SCC(N, forward_adj, backward_adj, group, scc_adj, cost, money);

    vector<bool> temp(int(scc_adj.size()), false);
    for(int i = 1; i <= N; ++i) {
        if(is_restaurant[i]) temp[group[i]] = true;
    }
    is_restaurant = temp;

    cout << get_max(group[S], scc_adj, cost, is_restaurant);

    return 0;
}