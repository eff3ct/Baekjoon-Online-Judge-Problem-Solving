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

    int N, t; cin >> N >> t;
    vector<ll> A(N);
    for(auto& e : A) cin >> e;

    vector<query> Q(t);
    for(int i = 0; i < t; ++i) {
        cin >> Q[i].start >> Q[i].end;
        Q[i].start--; Q[i].end--;
        Q[i].idx = i;
    }

    int k = sqrt(N);
    sort(Q.begin(), Q.end(), [&](const query& a, const query& b) {
        return (a.start / k == b.start / k ? a.end < b.end : a.start / k < b.start / k);
    });

    vector<ll> comp(A);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    vector<int> num(N);
    for(int i = 0; i < N; ++i) {
        num[i] = lower_bound(comp.begin(), comp.end(), A[i]) - comp.begin();
    }

    vector<int> cnt(500'001);
    vector<ll> ans(t);
    ll res = 0;
    int s = Q[0].start, e = Q[0].end;
    for(int i = s; i <= e; ++i) {
        if(cnt[num[i]] == 2) res--;
        cnt[num[i]]++;
        if(cnt[num[i]] == 2) res++;
    }

    ans[Q[0].idx] = res;

    for(int i = 1; i < t; ++i) {
        //범위를 줄여야하는 경우 s++
        while(s < Q[i].start) {
            if(cnt[num[s]] == 2) res--;
            cnt[num[s]]--;
            if(cnt[num[s]] == 2) res++;
            s++;
        }
        //범위를 늘려야하는 경우 s--
        while(s > Q[i].start) {
            s--;
            if(cnt[num[s]] == 2) res--;
            cnt[num[s]]++;
            if(cnt[num[s]] == 2) res++;
        }
        //범위를 늘려야하는 경우 
        while(e < Q[i].end) {
            e++;
            if(cnt[num[e]] == 2) res--;
            cnt[num[e]]++;
            if(cnt[num[e]] == 2) res++;
        }
        //범위를 줄여야하는 경우
        while(e > Q[i].end) {
            if(cnt[num[e]] == 2) res--;
            cnt[num[e]]--;
            if(cnt[num[e]] == 2) res++;
            e--;
        }
        ans[Q[i].idx] = res;
    }

    for(int i = 0; i < t; ++i) cout << ans[i] << '\n';

    return 0;
}