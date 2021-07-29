// https://www.acmicpc.net/problem/1967 //
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<pair<int, int>> adj[10001];

void treeDist(int n) {
    vector<bool> visit(10001, false);
    vector<int> dist(10001, 0);

    queue<int> q;
    visit[1] = true;
    q.push(1);

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(auto element : adj[now]) {
            if(visit[element.first]) continue;
            dist[element.first] = dist[now] + element.second;
            visit[element.first] = true;
            q.push(element.first);
        }
    }

    int maxIdx = 1;
    int maximum = 0;
    for(int i = 1; i <= n; ++i) {
        if(dist[i] > maximum) {
            maximum = dist[i];
            maxIdx = i;
        }
    }

    fill(visit.begin(), visit.end(), false);
    fill(dist.begin(), dist.end(), 0);
    visit[maxIdx] = true;
    q.push(maxIdx);

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(auto element : adj[now]) {
            if(visit[element.first]) continue;
            dist[element.first] = dist[now] + element.second;
            visit[element.first] = true;
            q.push(element.first);
        }
    }

    maximum = 0;
    for(int i = 1; i <= n; ++i) {
        if(dist[i] > maximum) {
            maximum = dist[i];
        }
    }

    cout << maximum;
}

int main() {
    int n; cin >> n;

    for(int i = 0; i < (n - 1); ++i) {
        int a, b, w; cin >> a >> b >> w;

        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    treeDist(n);

    return 0;
}