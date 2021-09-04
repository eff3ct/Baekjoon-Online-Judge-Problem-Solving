#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;
int N, M;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int id = 1;
vector<int> setCount;
vector<vector<bool>> visit;
vector<vector<int>> sameSet;

void floodFill(vector<vector<int>>& map, int y, int x) {
    int cnt = 1;
    queue<pair<int, int>> q;

    visit[y][x] = true;
    sameSet[y][x] = id;
    q.push({x, y});

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];

            if(nextX < 0 || nextX >= M || nextY < 0 || nextY >= N) continue;
            if(visit[nextY][nextX] || map[nextY][nextX] == 1) continue;

            cnt++;
            sameSet[nextY][nextX] = id;
            visit[nextY][nextX] = true;
            q.push({nextX, nextY});
        }
    }

    id++;
    setCount.push_back(cnt);
}

void solve(vector<vector<int>>& map) {
    sameSet.resize(N, vector<int>(M));
    visit.resize(N, vector<bool>(M));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(map[i][j] == 0 && !visit[i][j]) floodFill(map, i, j);
        }
    }

    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < M; ++x) {
            if(map[y][x] == 1) {
                int cnt = 1;
                vector<int> counted;

                for(int i = 0; i < 4; ++i) {
                    
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if(nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                    if(map[ny][nx] == 1) continue;
                    if(find(counted.begin(), counted.end(), sameSet[ny][nx]) != counted.end()) continue;

                    cnt += setCount[sameSet[ny][nx]];
                    counted.push_back(sameSet[ny][nx]);
                    
                }
                cnt %= 10;
                cout << cnt;
            }
            else cout << 0;
        }
        cout << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    vector<vector<int>> map(N, vector<int>(M));

    setCount.push_back(-1);
    for(int i = 0; i < N; ++i) {
        string temp; cin >> temp;
        for(int j = 0; j < M; ++j) {
            map[i][j] = temp[j] - '0';
        }
    }

    solve(map);
    
    return 0;
}