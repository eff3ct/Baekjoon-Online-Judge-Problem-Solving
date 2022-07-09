#include <bits/stdc++.h>

using namespace std;

struct query {
    int idx, start, end;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> tmp(N);
    for(int& e : tmp) cin >> e;

    vector<int> comp(tmp);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    vector<int> A(N);
    for(int i = 0; i < N; ++i) A[i] = lower_bound(comp.begin(), comp.end(), tmp[i]) - comp.begin();

    int M; cin >> M;
    vector<query> Q(M);
    for(int i = 0; i < M; ++i) {
        cin >> Q[i].start >> Q[i].end;
        Q[i].start--; Q[i].end--;
        Q[i].idx = i;
    }

    int k = sqrt(N);

    sort(Q.begin(), Q.end(), [&](const query& a, const query& b) {
        return (a.start / k == b.start / k ? a.end < b.end : a.start / k < b.start / k);
    });

    vector<int> visit(1'000'001);
    vector<int> ans(M);
    int res = 0;
    int s = Q[0].start, e = Q[0].end;
    for(int i = s; i <= e; ++i) {
        if(visit[A[i]] == 0) res++;
        visit[A[i]]++;
    }

    ans[Q[0].idx] = res;

    for(int i = 1; i < M; ++i) {
        //범위를 줄여야하는 경우 s++
        while(s < Q[i].start) {
            visit[A[s]]--;
            if(visit[A[s++]] == 0) res--;
        }
        //범위를 늘려야하는 경우 s--
        while(s > Q[i].start) {
            if(visit[A[--s]] == 0) res++;
            visit[A[s]]++; 
        }
        //범위를 늘려야하는 경우
        while(e < Q[i].end) {
            if(visit[A[++e]] == 0) res++;
            visit[A[e]]++;
        }
        //범위를 줄여야하는 경우
        while(e > Q[i].end) {
            visit[A[e]]--;
            if(visit[A[e--]] == 0) res--;
        }
        ans[Q[i].idx] = res;
    }

    for(int i = 0; i < M; ++i) cout << ans[i] << '\n';

    return 0;
}