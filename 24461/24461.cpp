#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
int N; 

void solve(vector<vector<int>>& adj, vector<int>& in_degree) {
    bool is_lined = true;
    for(int i = 0; i < N; ++i) {
        if(in_degree[i] > 2) {
            is_lined = false;
            break;
        }
    }

    //check
    if(is_lined) {
        for(int i = 0; i < N; ++i) {
            if(in_degree[i] == 1 || in_degree[i] == 2) cout << i << ' ';
        }
        return;
    }

    vector<int> one_degree;
    for(int i = 0; i < N; ++i) {
        if(in_degree[i] == 1) one_degree.push_back(i);
    }
    
    while(true) {
        vector<int> temp;
        for(int& now : one_degree) {
            for(int& next : adj[now]) {
                if(in_degree[next]) {
                    in_degree[next]--;
                    in_degree[now]--;

                    if(in_degree[next] == 0) {
                        cout << next;
                        return;
                    }
                    else if(in_degree[next] == 1) temp.push_back(next);
                }
            }
        }

        if(int(temp.size()) > 2) {
            swap(one_degree, temp);
            continue;
        }

        for(int i = 0; i < N; ++i) {
            if(in_degree[i] == 1 || in_degree[i] == 2) cout << i << ' ';
        }
        break;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    vector<vector<int>> adj(N + 1);
    vector<int> in_degree(N + 1);

    for(int i = 0; i < N - 1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        in_degree[a]++;
        in_degree[b]++;
    }

    solve(adj, in_degree);

    return 0;
}