#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int MAX = (1 << 17);
vector<int> tree[MAX * 2];

void add(int idx, int v) {
    idx += MAX;
    tree[idx].push_back(v);
}

void build(int n, vector<int>& seq) {
    for(int i = 1; i <= n; ++i) add(i, seq[i]);
    for(int i = MAX - 1; i; --i) {
        tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());

        merge(tree[i * 2].begin(), tree[i * 2].end(),
        tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(),
        tree[i].begin());
    }
}

int query(int l, int r, int k) {
    l += MAX, r += MAX;
    int ret = 0;
    while(l <= r) {
        if(l & 1) {
            ret += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), k);
            l++;
        }

        if(~r & 1) {
            ret += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), k);
            r--;
        }

        l >>= 1, r >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> seq(N + 1);
    for(int i = 1; i <= N; ++i) cin >> seq[i];

    build(N, seq);
    
    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int a, b, c; cin >> a >> b >> c;
        cout << query(a, b, c) << '\n';
    }

    return 0;
}