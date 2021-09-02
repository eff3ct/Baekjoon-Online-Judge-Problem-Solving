#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
int R, C;

int oneBitCount(int bit) {
    int ret = 0;
    while(bit != 0) {
        if(bit & 1) ret++;
        bit = bit >> 1;
    }
    return ret;
}

int BFS(vector<vector<char>>& map) {
    int ret = 1;

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    queue<pair<pair<int, int>, int>> q;

    q.push({ {1, 1} , 1 << (map[1][1] - 'A') });
    while(!q.empty()) {
        int curX = q.front().first.first;
        int curY = q.front().first.second;
        int history = q.front().second;
        q.pop();
        
        for(int i = 0; i < 4; ++i) {
            int nextX = curX + dx[i];
            int nextY = curY + dy[i];
            
            if(nextX <= 0 || nextX > C || nextY <= 0 || nextY > R) continue;
            if(history & (1 << (map[nextY][nextX] - 'A'))) continue;
            
            int temp = history;
            temp |= (1 << (map[nextY][nextX] - 'A'));
            ret = max(ret, oneBitCount(temp));
            q.push({ {nextX, nextY} , temp });
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C;
    vector<vector<char>> map(R + 1, vector<char>(C + 1));

    for(int i = 1; i <= R; ++i) {
        string temp; cin >> temp;
        for(int j = 1; j <= C; ++j) map[i][j] = temp[j - 1];
    }

    int ret = BFS(map);
    cout << ret;

    return 0;
}