#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

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

            tree[node] += (ll)(end - start + 1) * lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        void update(int start, int end, int node, int left, int right, ll diff) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += (ll)(end - start + 1) * diff;

                if(start != end) {
                    lazy[node * 2] += diff;
                    lazy[node * 2 + 1] += diff;
                }

                return;
            }

            int mid = (start + end) / 2;

            update(start, mid, node * 2, left, right, diff);
            update(mid + 1, end, node * 2 + 1, left, right, diff);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        ll query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

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

    int N; cin >> N;
    segment_tree Tree(N);

    for(int i = 1; i <= N; ++i) {
        ll tmp; cin >> tmp;
        Tree.update(1, N, 1, i, i, tmp);
    }    

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll i, j, k; cin >> i >> j >> k;
            Tree.update(1, N, 1, i, j, k);
        }
        else {
            int x; cin >> x;
            cout << Tree.query(1, N, 1, x, x) << '\n';
        }
    }

    return 0;
}