// https://www.acmicpc.net/problem/11003 //
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#define INF 1987654321

using namespace std;

void initSegTree(vector<int>& segTree, int N) {
    for(int i = N - 1; i >= 1; --i) segTree[i] = min(segTree[i << 1], segTree[i << 1 | 1]);
}

int minSeg(vector<int>& segTree, int N, int l, int r) {
    int res = INF;

    l += N;
    r += N;

    for(; l < r; l >>= 1, r >>= 1) {
        if(l & 1) res = min(res, segTree[l++]);
        if(r & 1) res = min(res, segTree[--r]);
    }

    return res;
}

void solve(vector<int>& segTree, int& N, int& L) {
    for(int i = 1; i <= N; ++i) {
        if((i - L + 1) <= 0) cout << minSeg(segTree, N, 0, i) << " ";
        else cout << minSeg(segTree, N, i - L, i) << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, L; cin >> N >> L;

    int h = (int)ceil(log2(N));
    vector<int> segTree(1 << (h + 1), INF);

    for(int i = 0; i < N; ++i) {
        int tmp; cin >> tmp;
        segTree[N + i] = tmp;
    }

    initSegTree(segTree, N);

    solve(segTree, N, L);

    return 0;
}