#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segTree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void updateLazy(int start, int end, int node) {
            if(lazy[node] == 0) return;
            
            tree[node] += (end- start + 1) * lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            
            lazy[node] = 0;
        }

        void updateRange(int start, int end, int node, int left, int right, ll diff) {
            updateLazy(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += (end - start + 1) * diff;
                
                if(start != end) {
                    lazy[node * 2] += diff;
                    lazy[node * 2 + 1] += diff;
                }

                return;
            }

            int mid = (start + end) / 2;
            updateRange(start, mid, node * 2, left, right, diff);
            updateRange(mid + 1, end, node * 2 + 1, left, right, diff);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        ll query(int start, int end, int node, int left, int right) {
            updateLazy(start, end, node);
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

    int N; cin >> N;
    segTree Tree(N + 1);

    vector<int> seq(N + 1);
    for(int i = 1; i <= N; ++i) cin >> seq[i];
    for(int i = 1; i <= N; ++i) {
        Tree.updateRange(1, N, 1, i, i, seq[i] - seq[i - 1]);
    }

    int Q; cin >> Q;
    while(Q--) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            ll l, r; cin >> l >> r;
            Tree.updateRange(1, N, 1, l, r, 1);
            Tree.updateRange(1, N, 1, r + 1, r + 1, -(r - l + 1));
        }
        else {
            int x; cin >> x;
            cout << Tree.query(1, N, 1, 1, x) << '\n';
        }
    }

    return 0;
}