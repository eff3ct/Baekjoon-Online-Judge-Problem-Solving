#include <bits/stdc++.h>

using namespace std;
int N; 
bool flag;

void solve(vector<string>& adj, vector<int>& ret, vector<bool>& used, int size) {
    if(flag) return;

    if(size == N) {
        for(int& e : ret) cout << e << ' ';
        flag = true;
        return;
    }

    //ret[i], ret[i + 1] 중앙에 노드 끼워넣는 경우가 가능하냐?
    for(int i = 0; i < int(ret.size()) - 1; ++i) {
        for(int j = 0; j < N; ++j) {
            if(used[j]) continue;
            if(adj[ret[i]][j] == '+' && adj[j][ret[i + 1]] == '+') {
                used[j] = true;
                ret.insert(ret.begin() + i + 1, j);
                solve(adj, ret, used, size + 1);
                if(flag) return;
            }
        }
    }
    //ret[0]이전에 끼워 넣는게 되냐?
    for(int j = 0; j < N; ++j) {
        if(used[j]) continue;
        if(adj[j][ret[0]] == '+') {
            used[j] = true;
            ret.insert(ret.begin(), j);
            solve(adj, ret, used, size + 1);
            if(flag) return;
        }
    }
    //ret[end]뒤에 끼워 넣는게 되냐?
    for(int j = 0; j < N; ++j) {
        if(used[j]) continue;
        if(adj[ret[int(ret.size()) - 1]][j] == '+') {
            used[j] = true;
            ret.push_back(j);
            solve(adj, ret, used, size + 1);
            if(flag) return;
        }
    }
}

int main() {
    cin >> N;
    vector<string> adj(N);
    for(string& e : adj) cin >> e;

    flag = false;
    vector<int> ret = { 0 };
    vector<bool> used(N, false);
    used[0] = true;
    solve(adj, ret, used, 1);

    return 0;
}