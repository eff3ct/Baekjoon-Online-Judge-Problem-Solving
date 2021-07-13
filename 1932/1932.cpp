// https://www.acmicpc.net/problem/1932 //
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int BFS(int**& triangle, int& n) {
    int** cost = new int*[n];
    for(int i = 0; i < n; ++i) {
        cost[i] = new int[n];
        fill_n(cost[i], n, -1);
    }

    bool** visit = new bool*[n];
    for(int i = 0; i < n; ++i) {
        visit[i] = new bool[n];
        fill_n(visit[i], n, false);
    }

    int dx[2] = { 0, 1 };
    int dy[2] = { 1, 1 };

    queue<pair<int, int>> q;
    q.push({ 0, 0 });
    cost[0][0] = triangle[0][0];
    visit[0][0] = true;
    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for(int i = 0; i < 2; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(triangle[ny][nx] == -1) continue;

            cost[nx][ny] = max(cost[nx][ny], cost[x][y] + triangle[ny][nx]);
            if(!visit[nx][ny]) q.push({ nx, ny });
            visit[nx][ny] = true;
        }
    }

    int maximum = -1;
    for(int i = 0; i < n; ++i) {
        maximum = max(maximum, cost[i][n - 1]);
    }

    for(int i = 0; i < n; ++i) {
        delete[] cost[i];
    }
    delete[] cost;

    return maximum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int** triangle = new int*[n];
    for(int i = 0; i < n; ++i) {
        triangle[i] = new int[n];
        fill_n(triangle[i], n, -1);
        for(int j = 0; j < (i + 1); ++j) {
            cin >> triangle[i][j];
        }
    }

    cout << BFS(triangle, n);

    for(int i = 0; i < n; ++i) {
        delete[] triangle[i];
    }
    delete[] triangle;
    return 0;
}