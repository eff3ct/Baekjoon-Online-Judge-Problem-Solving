#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

class segment_tree {
    private:
        vector<ll> tree;

    public:
        segment_tree(int N) {
            tree.resize(4 * N);
        }

        void update(int start, int end, int node, int idx, ll val) {
            if(idx < start || idx > end) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, val);
                update(mid + 1, end, node * 2 + 1, idx, val);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
            else tree[node] = val;
        }

        ll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            return query(start, mid, node * 2, left, right)
            + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    

    return 0;
}