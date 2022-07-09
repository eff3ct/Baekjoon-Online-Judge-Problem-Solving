#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

class segment_tree {
    private:
        vector<pii> tree;

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

                int tmp[4] = {tree[node * 2].first, tree[node * 2].second, tree[node * 2 + 1].first, tree[node * 2 + 1].second};
                sort(tmp, tmp + 4, greater<int>());

                tree[node] = {tmp[0], tmp[1]};
            }
            else tree[node] = {val, 0};
        }

        pii query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return {0, 0};

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            pii l = query(start, mid, node * 2, left, right);
            pii r = query(mid + 1, end, node * 2 + 1, left, right);

            int tmp[4] = {l.first, l.second, r.first, r.second};
            sort(tmp, tmp + 4, greater<int>());

            return {tmp[0], tmp[1]};
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    segment_tree tree(N);
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        tree.update(1, N, 1, i, x);
    }

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int i, v; cin >> i >> v;
            tree.update(1, N, 1, i, v);
        }
        else {
            int l, r; cin >> l >> r;
            pii q = tree.query(1, N, 1, l, r);
            cout << q.first + q.second << '\n';
        }
    }

    return 0;
}