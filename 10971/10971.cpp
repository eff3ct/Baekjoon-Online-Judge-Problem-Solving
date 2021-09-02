#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;
int N;

vector<bool> visited;

int solve(vector<vector<int>>& cost, vector<int>& path, int dist) {
    if(path.size() == N) {
        if(cost[path.back()][path[0]]) return dist + cost[path.back()][path[0]];
        else return INF;
    }

    int ret = INF;

    for(int next = 0; next < N; ++next) {
        if(visited[next]) continue;

        int now = path.back();
        if(cost[now][next] == 0) continue;

        path.push_back(next);
        
        visited[next] = true;
        ret = min(ret, solve(cost, path, dist + cost[now][next]));
        visited[next] = false;
        
        path.pop_back();
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    visited.resize(N, false);
    vector<vector<int>> cost(N, vector<int>(N));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> cost[i][j];
        }
    }

    vector<int> path = {0};
    visited[0] = true;
    int ret = solve(cost, path, 0);

    cout << ret;

    return 0;
}