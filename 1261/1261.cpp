// https://www.acmicpc.net/problem/1261 //
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <string>

#define INF 987654321

using namespace std;

vector<vector<int>> map(101, vector<int>(101, -1));
vector<vector<int>> cost(101, vector<int>(101, INF));

void solveBFS(int& N, int& M) {
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    queue<pair<int, int>> q;
    cost[1][1] = 0;
    q.push({1, 1});

    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx <= 0 || nx > M || ny <= 0 || ny > N) continue;

            if(map[ny][nx] == 1) {
                if(cost[ny][nx] > (cost[y][x] + 1)) {
                    cost[ny][nx] = cost[y][x] + 1;
                    q.push({nx, ny});
                }
            }
            else {
                if(cost[ny][nx] > cost[y][x]) {
                    cost[ny][nx] = cost[y][x];
                    q.push({nx, ny});
                }
            }
        }
    }

    cout << cost[N][M];
}

int main() {
    int N, M; cin >> M >> N;

    for(int i = 1; i <= N; ++i) {
        string tmp; cin >> tmp;
        for(int j = 1; j <= M; ++j) {
            map[i][j] = (tmp[j - 1] - '0');
        }
    }

    solveBFS(N, M);

    return 0;
}