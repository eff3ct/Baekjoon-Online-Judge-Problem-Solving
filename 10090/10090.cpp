// https://www.acmicpc.net/problem/10090 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        ll query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right)
            + query(mid + 1, end, node * 2 + 1, left, right);
        }

        void update(int start, int end, int node, int idx) {
            if(start > idx || end < idx) return;

            tree[node] += 1;

            int mid = (start + end) / 2;

            if(start != end) {
                update(start, mid, node * 2, idx);
                update(mid + 1, end, node * 2 + 1, idx);
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    segTree Tree(n);

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        res += Tree.query(1, n, 1, x + 1, n);
        Tree.update(1, n, 1, x);
    }

    cout << res;

    return 0;
}