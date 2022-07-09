#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T --> 0) {
        int n; cin >> n;
        vector<pii> A(n);
        for(int i = 0; i < n; ++i) cin >> A[i].first >> A[i].second;

        vector<bool> visit(n, false);
        int m; cin >> m;
        int cnt = 0;
        for(int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            for(int j = 0; j < n; ++j) {
                if(visit[j]) continue;
                if(x - 50 <= A[j].first && A[j].first <= x + 50 && y - 50 <= A[j].second && A[j].second <= y + 50) {
                    visit[j] = true;
                    cnt++;
                }
            }
        }

        cout << cnt << '\n';
    }

    return 0;
}