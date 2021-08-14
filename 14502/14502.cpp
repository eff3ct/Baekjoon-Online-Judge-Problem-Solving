#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

vector<pair<int, int>> virus;
vector<vector<int>> map;
vector<vector<bool>> visit;
int res = 0;
int ret = 0;
int N, M; 

void BFS(int sx, int sy) {
    if(map[sy][sx] == 1) return;
    if(visit[sy][sx]) return;

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    int delta = (map[sy][sx] == 0) ? 1 : 0;
    int r = (map[sy][sx] == 0) ? 1 : 0;


    queue<pair<int, int>> q;
    visit[sy][sx] = true;
    q.push({sx, sy});

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int newX = curX + dx[i];
            int newY = curY + dy[i];

            if(newX < 0 || newX >= M || newY < 0 || newY >= N) continue;
            if(visit[newY][newX]) continue;
            if(map[newY][newX] == 1) continue;

            r += delta;
            visit[newY][newX] = true;
            q.push({newX, newY});
        }
    }
    res += r;
}

void solve(int x, int y, int cnt, vector<pair<int, int>>& wall) {
    if(cnt == 3) {
        for(auto& element : wall) map[element.second][element.first] = 1;

        for(int i = 0; i < N; ++i) fill(visit[i].begin(), visit[i].end(), false);

        res = 0;
        for(auto& element : virus) BFS(element.first, element.second);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                BFS(j, i);
            }
        }
        ret = max(res, ret);

        for(auto& element : wall) map[element.second][element.first] = 0;
        return;
    }

    if(x >= M) {x = 0; y++;}
    if(y >= N) return;

    int j = x;
    for(int i = y; i < N; ++i) {
        while(true) {
            if(j >= M) {j = 0; break;}

            if(map[i][j] == 1 || map[i][j] == 2) {j++; continue;}

            wall.push_back({j, i});
            solve(j + 1, i, cnt + 1, wall);
            wall.pop_back();

            j++;
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    map.resize(N);
    visit.resize(N);
    for(int i = 0; i < N; ++i) {map[i].resize(M); visit[i].resize(M);}

    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < M; ++x) {
            cin >> map[y][x];
            if(map[y][x] == 2) virus.push_back({x, y});
        }
    }

    vector<pair<int, int>> wall;
    solve(0, 0, 0, wall);

    cout << ret;

    return 0;
}