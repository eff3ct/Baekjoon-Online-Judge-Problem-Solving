// https://www.acmicpc.net/problem/4386 //
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;
int n;
const double INF = 987654321.0;

double starDist(pair<double, double> a, pair<double, double> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

double solve(vector<vector<double>>& dist) {
    vector<bool> visit(n, false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    double ret = 0;

    visit[0] = true;
    pq.push({0, 0});
    while(!pq.empty()) {
        int now = pq.top().second;

        if(!visit[now]) {
            ret += pq.top().first;
            visit[now] = true;
        }

        pq.pop();

        for(int i = 0; i < n; ++i) {
            if(visit[i]) continue;
            pq.push({dist[now][i], i});
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    vector<pair<double, double>> star(n, {0.0, 0.0});
    for(int i = 0; i < n; ++i) cin >> star[i].first >> star[i].second;

    vector<vector<double>> dist(n, vector<double>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            dist[i][j] = starDist(star[i], star[j]);
        }
    }

    cout << fixed;
    cout.precision(6);

    cout << solve(dist);

    return 0;
}