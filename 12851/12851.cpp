// https://www.acmicpc.net/problem/1697 //
#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321

using namespace std;
typedef long long ll;

bool isValid(int a) {
    if(0 <= a && a <= 1000000) return true;
    else return false;
}

void BFS(int N, int K) {
    if(N == K) {
        cout << 0 << '\n' << 1;
        return;
    }

    int *cost;
    cost = new int[1000001];
    fill_n(cost, 1000001, INF);

    vector<ll> cnt(1000001);

    queue<int> q;

    q.push(N);
    cost[N] = 0;
    cnt[N] = 1;

    while(!q.empty()) {
        int nowPoint = q.front();
        q.pop();

        int a = nowPoint - 1;
        int b = nowPoint + 1;
        int c = nowPoint * 2;

        if(isValid(a)) {
            if(cost[a] > cost[nowPoint] + 1) {
                cost[a] = cost[nowPoint] + 1;
                cnt[a] = cnt[nowPoint];
                q.push(a);
            }
            else if(cost[a] == cost[nowPoint] + 1) {
                cnt[a] += cnt[nowPoint];
            }
        }
        if(isValid(b)) {
            if(cost[b] > cost[nowPoint] + 1) {
                cost[b] = cost[nowPoint] + 1;
                cnt[b] = cnt[nowPoint];
                q.push(b);
            }
            else if(cost[b] == cost[nowPoint] + 1) {
                cnt[b] += cnt[nowPoint];
            }
        }
        if(isValid(c)) {
            if(cost[c] > cost[nowPoint] + 1) {
                cost[c] = cost[nowPoint] + 1;
                cnt[c] = cnt[nowPoint];
                q.push(c);
            }
            else if(cost[c] == cost[nowPoint] + 1) {
                cnt[c] += cnt[nowPoint];
            }
        }
    }
    cout << cost[K] << '\n' << cnt[K];
    delete[] cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    BFS(N, K);
    return 0;
}