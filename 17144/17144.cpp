// https://www.acmicpc.net/problem/17144 //
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
int R, C, T;

void spreadDust(vector<vector<int>>& map) {
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    vector<vector<int>> updated(R, vector<int>(C));
    for(int y = 0; y < R; y++) {
        for(int x = 0; x < C; x++) {
            if(map[y][x] > 0) {
                updated[y][x] += map[y][x];
                for(int i = 0; i < 4; ++i) {
                    int nearX = x + dx[i];
                    int nearY = y + dy[i];
                    
                    if(nearX < 0 || nearX >= C || nearY < 0 || nearY >= R) continue;
                    if(map[nearY][nearX] == -1) continue;

                    updated[nearY][nearX] += map[y][x] / 5;
                    updated[y][x] -= map[y][x] / 5;
                }
            }
            else if(map[y][x] == -1) updated[y][x] = map[y][x];
        }
    }

    map = updated;
}

void cycleDust(vector<vector<int>>& map, vector<pair<int, int>>& airCleaner) {
    pair<int, int> upperCleaner = airCleaner[0];
    pair<int, int> lowerCleaner = airCleaner[1];

    //up
    vector<int> dx = {1, 0, -1, 0};
    vector<int> dy = {0, -1, 0, 1};

    int nextX = upperCleaner.first + 1;
    int nextY = upperCleaner.second;
    int dust = 0;
    int idx = 0;
    while(true) {
        if(map[nextY][nextX] == -1) break;

        int temp = map[nextY][nextX];
        map[nextY][nextX] = dust;
        dust = temp;

        if(nextX + dx[idx] >= C || nextX + dx[idx] < 0 || nextY + dy[idx] < 0) idx++;

        nextX += dx[idx];
        nextY += dy[idx];
    }

    //down
    dy = {0, 1, 0, -1};

    nextX = lowerCleaner.first + 1;
    nextY = lowerCleaner.second;
    dust = 0;
    idx = 0;
    while(true) {
        if(map[nextY][nextX] == -1) break;

        int temp = map[nextY][nextX];
        map[nextY][nextX] = dust;
        dust = temp;


        if(nextX + dx[idx] >= C || nextX + dx[idx] < 0 || nextY + dy[idx] >= R) idx++;

        nextX += dx[idx];
        nextY += dy[idx];

    }
}

int sumDust(vector<vector<int>>& map) {
    int ret = 0;
    for(int y = 0; y < R; ++y) {
        for(int x = 0; x < C; ++x) {
            if(map[y][x] > 0) ret += map[y][x];
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C >> T;

    vector<vector<int>> map(R, vector<int>(C));
    vector<pair<int, int>> airCleaner;
    for(int y = 0; y < R; ++y) {
        for(int x = 0; x < C; ++x) {
            cin >> map[y][x];
            if(map[y][x] == -1) airCleaner.push_back({x, y});
        }
    }

    for(int i = 0; i < T; ++i) {
        spreadDust(map);
        cycleDust(map, airCleaner);
    }

    cout << sumDust(map);

    return 0;
}
