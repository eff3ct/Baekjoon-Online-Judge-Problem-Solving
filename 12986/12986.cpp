#include <bits/stdc++.h>

using namespace std;

struct query {
    int idx, start, end;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<int> tmp(N);
    for(int& e : tmp) cin >> e;

    vector<int> comp(tmp);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    vector<int> A(N);
    for(int i = 0; i < N; ++i) A[i] = lower_bound(comp.begin(), comp.end(), tmp[i]) - comp.begin();

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

    vector<int> cnt(200'001);
    vector<int> num_cnt(200'001);
    int max_cnt = 0;

    vector<int> ans(M);
    int s = Q[0].start, e = Q[0].end;
    for(int i = s; i <= e; ++i) {
        cnt[ num_cnt[A[i]] ] = max(0, cnt[ num_cnt[A[i]] ] - 1);
        num_cnt[A[i]]++;
        cnt[ num_cnt[A[i]] ]++;
        max_cnt = max(max_cnt, num_cnt[A[i]]);
    }

    ans[Q[0].idx] = max_cnt;

    for(int i = 1; i < M; ++i) {
        //범위를 줄여야하는 경우 s++
        while(s < Q[i].start) {
            //카운트 감소
            cnt[ num_cnt[A[s]] ]--;
            num_cnt[A[s]]--;
            cnt[ num_cnt[A[s]] ]++;
            //만약 max_cnt에서 값이 0이면 답을 max_cnt - 1로 바꿈
            if(cnt[max_cnt] == 0) max_cnt--;
            s++;
        }
        //범위를 늘려야하는 경우 s--
        while(s > Q[i].start) {
            //왼쪽으로 한칸 옮기기
            --s;
            cnt[ num_cnt[A[s]] ]--;
            //카운트 증가
            num_cnt[A[s]]++;
            cnt[ num_cnt[A[s]] ]++;
            max_cnt = max(max_cnt, num_cnt[A[s]]);
        }
        //범위를 늘려야하는 경우
        while(e < Q[i].end) {
            //오른쪽으로 한칸 옮기기
            ++e;
            cnt[ num_cnt[A[e]] ]--;
            //카운트 증가
            num_cnt[A[e]]++;
            cnt[ num_cnt[A[e]] ]++;
            max_cnt = max(max_cnt, num_cnt[A[e]]);
        }
        //범위를 줄여야하는 경우
        while(e > Q[i].end) {
            //카운트 감소
            cnt[ num_cnt[A[e]] ]--;
            num_cnt[A[e]]--;
            cnt[ num_cnt[A[e]] ]++;
            //만약 max_cnt에서 값이 0이면 답을 max_cnt - 1로 바꿈
            if(cnt[max_cnt] == 0) max_cnt--;
            e--;
        }
        
        ans[Q[i].idx] = max_cnt;
    }

    for(int i = 0; i < M; ++i) cout << ans[i] << '\n';

    return 0;
}