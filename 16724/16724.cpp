#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <string>
#include <map>

using namespace std;
typedef pair<int, int> pii;
map<char, pii> dir = {{'L', {0, -1}}, {'R', {0, 1}}, {'D', {1, 0}}, {'U', {-1, 0}}};

int get_count(pii s, vector<string>& mp, vector<vector<bool>>& visit, vector<vector<bool>>& cycle, int N, int M) {
    vector<pii> history;

    while(true) {
        visit[s.first][s.second] = true;
        history.push_back(s);

        char cmd = mp[s.first][s.second];
        int ny = s.first + dir[cmd].first;
        int nx = s.second + dir[cmd].second;

        if(nx < 0 || nx >= M || ny < 0 || ny >= N) {
            for(pii& e : history) cycle[e.first][e.second] = true;  
            return 1;
        }

        if(visit[ny][nx]) {
            if(cycle[ny][nx]) {
                for(pii& e : history) cycle[e.first][e.second] = true;  
                return 0;
            }
            else {
                for(pii& e : history) cycle[e.first][e.second] = true;  
                return 1;
            }
        }
        else s = {ny, nx};
    }
}

void solve(int N, int M, vector<string>& mp) {
    vector<vector<bool>> visit(N, vector<bool>(M, false));
    vector<vector<bool>> cycle(visit);

    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(!visit[i][j]) {
                pii s = {i, j};
                cnt += get_count(s, mp, visit, cycle, N, M);
            }
        }
    }

    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    
    vector<string> mp(N);
    for(string& e : mp) cin >> e;

    solve(N, M, mp);

    return 0;
}
