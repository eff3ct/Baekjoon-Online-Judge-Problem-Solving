// https://www.acmicpc.net/problem/2206 //
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>

#define INF 987654321

using namespace std;

vector<vector<int>> map(1001, vector<int>(1001, -1));
vector<vector<int>> distA(1001, vector<int>(1001, INF));
vector<vector<int>> distB(1001, vector<int>(1001, INF));
vector<vector<bool>> visitA(1001, vector<bool>(1001, false));
vector<vector<bool>> visitB(1001, vector<bool>(1001, false));

void solve(int& N, int& M) {
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    queue<tuple<int, int, int>> q;
    distA[1][1] = 1;
    visitA[1][1] = true;
    q.push({1, 1, 0});

    while(!q.empty()) {
        int x = get<0>(q.front());
        int y = get<1>(q.front());
        int breaked = get<2>(q.front());
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx <= 0 || nx > M || ny <= 0 || ny > N) continue; //coord check
            if(breaked == 1 && map[ny][nx] == 1) continue; //map check

            if(breaked == 0 && !visitA[ny][nx]) {
                if(map[ny][nx] == 1) {
                    visitB[y][x] = true;
                    visitB[ny][nx] = true;
                    distB[ny][nx] = distA[y][x] + 1;
                    q.push({nx, ny, 1});
                }
                else {
                    distA[ny][nx] = distA[y][x] + 1;
                    visitA[ny][nx] = true;
                    q.push({nx, ny , 0});
                }
            }
            else if(breaked == 1 && !visitB[ny][nx]) {
                visitB[ny][nx] = true;
                distB[ny][nx] = distB[y][x] + 1;
                q.push({nx, ny, 1});
            }
        }
    }

    if((distA[N][M] == INF) && (distB[N][M] == INF)) cout << "-1";
    else cout << min(distA[N][M], distB[N][M]);
}

int main() {
    int N, M; cin >> N >> M;

    for(int i = 1; i <= N; ++i) {
        string tmp; cin >> tmp;
        for(int j = 1; j <= M; ++j) {
            map[i][j] = (tmp[j - 1] - '0');
        }
    }

    solve(N, M);
    
    return 0;
}