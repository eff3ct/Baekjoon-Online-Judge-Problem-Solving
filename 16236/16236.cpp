// https://www.acmicpc.net/problem/16236 //
#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define INF 987654321

using namespace std;

void eatFish(int& result, int N, int**& map, int& sharkSize, pair<int, int>& start, int& eatCnt, int**& cost, vector<pair<int, int>>& fish) {
    int INFCnt = 0;
    int fishCnt = fish.size();
    int minimum = INF;
    int minX, minY;
    int eraseIdx = 0;
    for(int i = 0; i < fishCnt; ++i) {
        int fishX = fish[i].first;
        int fishY = fish[i].second;

        if(sharkSize <= map[fishY][fishX] || cost[fishX][fishY] == INF) INFCnt++;
        else {
            if(minimum > cost[fishX][fishY]) {
                minimum = cost[fishX][fishY];
                minX = fishX; minY = fishY;
                eraseIdx = i;
            }
            else if(minimum == cost[fishX][fishY]) {
                if(minY > fishY) {
                    minX = fishX;
                    minY = fishY;
                    eraseIdx = i;
                }
                else if(minY == fishY) {
                    if(minX > fishX) {
                        minX = fishX;
                        minY = fishY;
                        eraseIdx = i;
                    }    
                }
            }
        }
    }

    if(fishCnt == INFCnt) {
        fish.clear();
        return;
    }

    eatCnt++;
    if(eatCnt == sharkSize) {
        eatCnt = 0;
        sharkSize++;
    }

    fish.erase(fish.begin() + eraseIdx);
    map[minY][minX] = 0;
    result = cost[minX][minY];
    start = { minX, minY };
}

void BFS(int N, int**& map, pair<int, int> start, int sharkSize, int**& cost) {
    bool** visit = new bool*[N];
    for(int i = 0; i < N; ++i) {
        visit[i] = new bool[N];
        fill_n(visit[i], N, false);
    }
    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, 1, 0, -1 };
    queue<pair<int, int>> q;
    q.push(start);
    while(!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int newX = curX + dx[i];
            int newY = curY + dy[i];

            if(newX < 0 || newX >= N || newY < 0 || newY >= N) continue;
            if(map[newY][newX] > sharkSize || visit[newX][newY]) continue;

            visit[newX][newY] = true;
            cost[newX][newY] = cost[curX][curY] + 1;
            q.push({ newX, newY });
        }
    }

    for(int i = 0; i < N; ++i) {
        delete[] visit[i];
    }
    delete[] visit;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, int>> fish;
    int** map = new int*[N];
    for(int i = 0; i < N; ++i) {
        map[i] = new int[N];
    }

    int** cost = new int*[N];
    for(int i = 0; i < N; ++i) {
        cost[i] = new int[N];
        fill_n(cost[i], N, INF);
    }

    pair<int, int> start;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> map[i][j];
            if(1 <= map[i][j] && map[i][j] <= 6) {
                fish.push_back({ j, i });
            }
            if(map[i][j] == 9) {
                start = { j, i };
                cost[j][i] = 0;
                map[i][j] = 0;
            }
        }
    }

    int result = 0;
    int sharkSize = 2;
    int eatCnt = 0;

    while(true) {
        if(fish.empty()) break;
        BFS(N, map, start, sharkSize, cost);
        eatFish(result, N, map, sharkSize, start, eatCnt, cost, fish);
    }

    cout << result;

    for(int i = 0; i < N; ++i) {
        delete[] map[i];
    }
    delete[] map;

    for(int i = 0; i < N; ++i) {
        delete[] cost[i];
    }
    delete[] cost;

    return 0;
}