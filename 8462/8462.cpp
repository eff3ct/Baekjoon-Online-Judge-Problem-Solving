#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

struct query {
    int start, end, idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, t; cin >> n >> t;
    vector<ll> A(n);
    for(auto& e : A) cin >> e;

    vector<query> Q(t);
    for(int i = 0; i < t; ++i) {
        cin >> Q[i].start >> Q[i].end;
        Q[i].start--; Q[i].end--;
        Q[i].idx = i;
    }

    int k = sqrt(n);
    sort(Q.begin(), Q.end(), [&](const query& a, const query& b) {
        return (a.start / k == b.start / k ? a.end < b.end : a.start / k < b.start / k);
    });

    vector<int> cnt(1'000'001);
    vector<ll> ans(t);
    ll res = 0;
    int s = Q[0].start, e = Q[0].end;
    for(int i = s; i <= e; ++i) {
        res += (2 * cnt[A[i]] + 1) * A[i];
        cnt[A[i]]++;
    }

    ans[Q[0].idx] = res;

    for(int i = 1; i < t; ++i) {
        //범위를 줄여야하는 경우 s++
        while(s < Q[i].start) {
            res -= (2 * cnt[A[s]] - 1) * A[s];
            cnt[A[s]]--;
            s++;
        }
        //범위를 늘려야하는 경우 s--
        while(s > Q[i].start) {
            s--;
            res += (2 * cnt[A[s]] + 1) * A[s];
            cnt[A[s]]++;
        }
        //범위를 늘려야하는 경우
        while(e < Q[i].end) {
            e++;
            res += (2 * cnt[A[e]] + 1) * A[e];
            cnt[A[e]]++;
        }
        //범위를 줄여야하는 경우
        while(e > Q[i].end) {
            res -= (2 * cnt[A[e]] - 1) * A[e];
            cnt[A[e]]--;
            e--;
        }
        ans[Q[i].idx] = res;
    }

    for(int i = 0; i < t; ++i) cout << ans[i] << '\n';

    return 0;
}