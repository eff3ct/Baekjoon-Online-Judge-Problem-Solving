// https://www.acmicpc.net/problem/1916 //
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define INF 1987654321LL

using namespace std;
typedef long long ll;

int solveBFS(int& start, int& end, vector<vector<pair<int, int>>>& adj, int& N) {
    vector<ll> cost(N + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    cost[start] = 0;
    pq.push({0, start});

    while(!pq.empty()) {
        ll nowCost = pq.top().first;
        int nowNode = pq.top().second;
        pq.pop();

        if(cost[nowNode] < nowCost) continue;

        for(auto& element : adj[nowNode]) {
            ll nextCost = element.second + nowCost;
            int nextNode = element.first;

            if(nextCost < cost[nextNode]) {
                cost[nextNode] = nextCost;
                pq.push({nextCost, nextNode});
            }
        }
    }

    return cost[end];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> adj(N + 1);

    for(int i = 0; i < M; ++i) {
        int s, e, cost; cin >> s >> e >> cost;
        adj[s].push_back({e, cost});
    }

    int start, end; cin >> start >> end;
    cout << solveBFS(start, end, adj, N);

    return 0;
}