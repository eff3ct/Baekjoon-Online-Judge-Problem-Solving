#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int MAX = 1e6;

class segment_tree {
    private:
        vector<ll> tree;

    public:
        segment_tree() = default;

        segment_tree(int N) {
            tree.resize(N * 4);
        }

        void resize(int N) {
            tree.resize(N * 4);
        }

        void update(int start, int end, int node, int idx, ll val) {
            if(idx < start || end < idx) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, val);
                update(mid + 1, end, node * 2 + 1, idx, val);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
            else tree[node] += val;
        }

        ll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<pii> X(n + 1);

    for(int i = 1; i <= n; ++i) cin >> X[i].first;
    for(int i = 1; i <= n; ++i) cin >> X[i].second;
    
    sort(X.begin() + 1, X.end(), [&](const pii& a, const pii& b) {
        return (a.first == b.first ? a.second > b.second : a.first < b.first);
    });

    segment_tree tree(MAX + 1);
    vector<ll> cnt(n + 1);
    for(int i = 1; i <= n; ++i) {
        cnt[i] = tree.query(0, MAX, 1, 0, X[i].second - 1);
        tree.update(0, MAX, 1, X[i].second, 1);
    }

    ll ans = 0;
    segment_tree tree_cnt(MAX + 1);
    for(int i = 1; i <= n; ++i) {
        ans += tree_cnt.query(0, MAX, 1, 0, X[i].second - 1);
        tree_cnt.update(0, MAX, 1, X[i].second, cnt[i]);
    }

    cout << ans << '\n';

    return 0;
}