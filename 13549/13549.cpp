// https://www.acmicpc.net/problem/13549 //
#include <iostream>
#include <utility>
#include <queue>
#define INF 987654321

using namespace std;

bool isValid(int a) {
    if(0 <= a && a <= 1000000) return true;
    else return false;
}

int BFS(int N, int K) {
    if(N == K) return 0;
    int *cost;
    cost = new int[1000001];
    fill_n(cost, 1000001, INF);
    priority_queue<pair<int, int>> q; //{ cost, node }

    cost[N] = 0;
    q.push({ -cost[N], N });

    while(!q.empty()) {
        int nowPoint = q.top().second;
        int nowCost = -q.top().first;
        q.pop();

        if(cost[nowPoint] < nowCost) continue;

        int a = nowPoint - 1;
        int b = nowPoint + 1;
        int c = nowPoint * 2;

        if(isValid(a)) {
            int tmpCost = nowCost + 1;
            if(tmpCost < cost[a]) {
                cost[a] = tmpCost;
                q.push({ -tmpCost, a });
            }
        }
        if(isValid(b)) {
            int tmpCost = nowCost + 1;
            if(tmpCost < cost[b]) {
                cost[b] = tmpCost;
                q.push({ -tmpCost, b });
            }
        }
        if(isValid(c)) {
            int tmpCost = nowCost;
            if(tmpCost < cost[c]) {
                cost[c] = tmpCost;
                q.push({ -tmpCost, c });
            }
        }
    }
    int result = cost[K];
    delete[] cost;
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    cout << BFS(N, K);
    return 0;
}