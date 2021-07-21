// https://www.acmicpc.net/problem/19538 //
// UCPC 2020 Qualifier G //
#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321

using namespace std;

void updateStatus(int*& cost, vector<int>*& adj, int x, queue<int>& tmpq) {
    if(cost[x] != INF) return;
    
    int count = 0;
    for(int element : adj[x]) {
        if(cost[element] != INF) count += 1;
    }

    if(count >= (double)adj[x].size() / 2) {
        tmpq.push(x);
    }
}

void BFS(const int N, queue<int> start, vector<int>*& adj) {
    int* cost = new int[N + 1];
    fill_n(cost, N + 1, INF);
    queue<int> q = start;
    queue<int> tmpq;
    while(!start.empty()) {
        cost[start.front()] = 0;
        start.pop();
    }

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(int element : adj[now]) {
            updateStatus(cost, adj, element, tmpq);
        }

        if(q.empty()) {
            while(!tmpq.empty()) {
                int updateElement = tmpq.front();
                tmpq.pop();
                cost[updateElement] = cost[now] + 1;
                q.push(updateElement);
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(cost[i] == INF) cout << -1 << " ";
        else cout << cost[i] << " ";
    }

    delete[] cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<int>* adj = new vector<int>[N + 1];

    for(int i = 1; i <= N; ++i) {
        while(true) {
            int tmp;
            cin >> tmp;
            if(tmp) adj[i].push_back(tmp);
            else break;
        }
    }

    int M;
    cin >> M;

    queue<int> start;
    for(int i = 0; i < M; ++i) {
        int tmp;
        cin >> tmp;
        start.push(tmp);
    }

    BFS(N, start, adj);

    delete[] adj;
}