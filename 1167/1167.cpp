// https://www.acmicpc.net/problem/1167 //
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<pair<int, int>> adj[100001];

void treeDist(int n) {
    vector<bool> visit(100001, false);
    vector<int> dist(100001, 0);

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

    for(int i = 1; i <= n; ++i) {
        int st; cin >> st;
        while(true) {
            int ed; cin >> ed;
            if(ed == -1) break;
            int w; cin >> w;
            adj[st].push_back({ed, w});
            adj[ed].push_back({st, w});
        }
    }

    treeDist(n);

    return 0;
}