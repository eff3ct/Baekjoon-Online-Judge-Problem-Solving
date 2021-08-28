// https://www.acmicpc.net/problem/2638 //
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

int N, M; 
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
queue<pair<int, int>> deleteList;

bool isEmpty(vector<vector<int>>& map) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(map[i][j] == 1) return false;
        }
    }
    return true;
}

void checkOutside(vector<vector<int>>& map) {
    vector<vector<bool>> visit(N, vector<bool>(M, false));
    queue<pair<int, int>> q;

    visit[0][0] = true;
    map[0][0] = 2;
    q.push({0, 0});

    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];

            if(nextX < 0 || nextX >= M || nextY < 0 || nextY >= N) continue; //if out of bound, skip
            if(visit[nextY][nextX]) continue; //if visited, skip
            if(map[nextY][nextX] == 1) continue; //if cheese, skip

            visit[nextY][nextX] = true;
            map[nextY][nextX] = 2; //set this coord as outside
            q.push({nextX, nextY});
        }
    }
}

void deleteCheese(vector<vector<int>>& map, int x, int y) {
    int cnt = 0;
    for(int i = 0; i < 4; ++i) {
        int curX = x + dx[i];
        int curY = y + dy[i];

        if(map[curY][curX] == 2) cnt += 1;
    }
    if(cnt >= 2) deleteList.push({x, y});
}

void printMap(vector<vector<int>>& map) {
    cout << '\n';
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n'; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    vector<vector<int>> map(N, vector<int>(M));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
           cin >> map[i][j]; 
        }
    }

    int ret = 0;
    while(true) {
        if(isEmpty(map)) break;

        checkOutside(map);

        for(int y = 0; y < N; ++y) {
            for(int x = 0; x < M; ++x) {
                if(map[y][x] == 1) deleteCheese(map, x, y);
            }
        }

        while(!deleteList.empty()) {
            int x = deleteList.front().first;
            int y = deleteList.front().second;
            map[y][x] = 2;
            deleteList.pop();
        }

        ret++;
    }

    cout << ret;

    return 0;
}