#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool flag = false;

int BFS(pair<int, int> start, vector<vector<bool>>& visit, vector<vector<char>>& map, string& key) {
    int ret = 0;
    int h = (int)map.size(), w = (int)map[0].size();

    queue<pair<int, int>> q;

    if(map[start.second][start.first] == '$') {
        ret++;
        map[start.second][start.first] = '.';
    }
    else if('A' <= map[start.second][start.first] && map[start.second][start.first] <= 'Z') {
        int keyIdx = key.find((char)(map[start.second][start.first] + ('a' - 'A')));
        if(keyIdx != string::npos) map[start.second][start.first] = '.';
        else return 0;
    }
    else if('a' <= map[start.second][start.first] && map[start.second][start.first] <= 'z') {
        int keyIdx = key.find(map[start.second][start.first]);
        if(keyIdx == string::npos) {
            key += map[start.second][start.first];
            flag = true;
        }
        map[start.second][start.first] = '.';
    }

    visit[start.second][start.first] = true;
    q.push(start);

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];

            if(nextX < 0 || nextX >= w || nextY < 0 || nextY >= h) continue;
            if(visit[nextY][nextX] || map[nextY][nextX] == '*') continue;

            if(map[nextY][nextX] == '$') {
                ret++;
                map[nextY][nextX] = '.';
            }
            else if('A' <= map[nextY][nextX] && map[nextY][nextX] <= 'Z') {
                int keyIdx = key.find((char)(map[nextY][nextX] + ('a' - 'A')));
                if(keyIdx != string::npos) map[nextY][nextX] = '.';
                else continue;
            }
            else if('a' <= map[nextY][nextX] && map[nextY][nextX] <= 'z') {
                int keyIdx = key.find(map[nextY][nextX]);
                if(keyIdx == string::npos) {
                    key += map[nextY][nextX];
                    flag = true;
                }
                map[nextY][nextX] = '.';
            }

            visit[nextY][nextX] = true;
            q.push({nextX, nextY});
        }
    }

    return ret;
}

void solve(vector<vector<char>>& map, string& key) {
    int cnt = 0;
    int h = (int)map.size(), w = (int)map[0].size();

    while(true) {
        flag = false;
        vector<vector<bool>> visit(h, vector<bool>(w, false));

        for(int i = 0; i < h; ++i) {
            if(map[i][0] != '*' && !visit[i][0]) cnt += BFS({0, i}, visit, map, key);
            if(map[i][w - 1] != '*' && !visit[i][w - 1]) cnt += BFS({w - 1, i}, visit, map, key);
        }

        for(int i = 0; i < w; ++i) {
            if(map[0][i] != '*' && !visit[0][i]) cnt += BFS({i, 0}, visit, map, key);
            if(map[h - 1][i] != '*' && !visit[h - 1][i]) cnt += BFS({i, h - 1}, visit, map, key);
        }

        if(!flag) break;
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        int h, w; cin >> h >> w;
        vector<vector<char>> map(h, vector<char>(w));

        string tmp;
        for(int i = 0; i < h; ++i) {
            cin >> tmp;
            for(int j = 0; j < w; ++j) {
                map[i][j] = tmp[j];
            }
        }

        string key; cin >> key;
        if(key == "0") key = "";

        solve(map, key);
    }

    return 0;
}