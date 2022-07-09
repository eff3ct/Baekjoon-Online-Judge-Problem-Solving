#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

class segment_tree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segment_tree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void propagate(int start, int end, int node) {
            if(lazy[node] == 0) return;

            tree[node] ^= lazy[node] * ((end - start + 1) & 1);

            if(start != end) {
                lazy[node * 2] ^= lazy[node];
                lazy[node * 2 + 1] ^= lazy[node];
            }
            
            lazy[node] = 0;
        }

        void update(int start, int end, int node, int left, int right, ll val) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] ^= val * ((end - start + 1) & 1);

                if(start != end) {
                    lazy[node * 2] ^= val;
                    lazy[node * 2 + 1] ^= val;
                }

                return;
            }

            int mid = (start + end) / 2;
            update(start, mid, node * 2, left, right, val);
            update(mid + 1, end, node * 2 + 1, left, right, val);
            tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
        }

        int query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            return query(start, mid, node * 2, left, right) ^ query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    segment_tree tree(n);

    for(int i = 0; i < n; ++i) {
        int k; cin >> k;
        tree.update(0, n - 1, 1, i, i, k);
    }

    int m; cin >> m;
    for(int i = 0; i < m; ++i) {
        int t; cin >> t;
        if(t == 1) {
            int a, b, c; cin >> a >> b >> c;
            tree.update(0, n - 1, 1, a, b, c);
        }
        else {
            int a; cin >> a;
            cout << tree.query(0, n - 1, 1, a, a) << '\n';
        }
    }

    return 0;
}