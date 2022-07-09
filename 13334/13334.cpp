#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int solve(vector<pii>& lines, int n, int d) {
    sort(lines.begin(), lines.end(), [&](const pii& a, const pii& b) {
        return a.second < b.second;
    });

    priority_queue<int, vector<int>, greater<int>> pq;
    int ans = 0;
    for(int i = 0; i < n; ++i) {
        int s = lines[i].first;
        int e = lines[i].second;
        while(!pq.empty() && pq.top() < e - d) pq.pop();
        if(e - s <= d) pq.push(s);

        ans = max(ans, (int)pq.size());
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<pii> lines(n);
    for(pii& e : lines) {
        cin >> e.first >> e.second;
        if(e.first > e.second) swap(e.first, e.second);
    }
    int d; cin >> d;

    cout << solve(lines, n, d) << '\n';

    return 0;
}