#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class segment_tree {
    private:
        vector<ll> tree;

    public:
        segment_tree(int N) {
            tree.resize(N * 4);
        }

        /*optional*/
        void init(int start, int end, int node, vector<ll>& v) {
            if(start != end) { 
                int mid = (start + end) / 2;
                init(start, mid, node * 2, v);
                init(mid + 1, end, node * 2 + 1, v);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
            else tree[node] = v[start];
        }
        //can be replaced by update query

        void update(int start, int end, int node, int idx, ll val) {
            if(idx < start || end < idx) return;

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

            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;
    vector<ll> A(N + 1);
    for(int i = 1; i <= N; ++i) cin >> A[i];
    
    segment_tree tree(N);
    tree.init(1, N, 1, A);

    for(int i = 0; i < M + K; ++i) {
        ll a, b, c; cin >> a >> b >> c;
        if(a == 1) tree.update(1, N, 1, b, c);
        else cout << tree.query(1, N, 1, b, c) << '\n';
    }

    return 0; 
}