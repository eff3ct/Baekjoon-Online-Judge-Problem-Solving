#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int INF = 1e9;

struct Node {
    int l_val, r_val, val, all;
    Node() {
        l_val = -INF;
        r_val = -INF;
        val = -INF;
        all = 0;
    }
    Node(int l_val, int r_val, int val, int all) : l_val(l_val), r_val(r_val), val(val), all(all) {}
};

class segment_tree {
    private:
        vector<Node> tree;
    
    public:
        segment_tree(int N) {
            tree.resize(N * 4);
        }

        Node update(int start, int end, int node, int idx, int v) {
            if(idx < start || end < idx) return tree[node];
            
            if(start != end) {
                int mid = (start + end) / 2;
                Node l = update(start, mid, node * 2, idx, v);
                Node r = update(mid + 1, end, node * 2 + 1, idx, v);
                tree[node].l_val = max(l.l_val, l.all + r.l_val);
                tree[node].r_val = max(r.r_val, r.all + l.r_val);
                tree[node].all = l.all + r.all;
                tree[node].val = max({l.val, r.val, l.r_val + r.l_val});
                return tree[node];
            }
            else return tree[node] = {v, v, v, v};
        }

        Node query(int start, int end, int node, int left, int right) {
            if(right < start || end < left) return {-INF, -INF, -INF, 0};

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;
            Node l = query(start, mid, node * 2, left, right);
            Node r = query(mid + 1, end, node * 2 + 1, left, right);

            Node ret;
            ret.l_val = max(l.l_val, l.all + r.l_val);
            ret.r_val = max(r.r_val, r.all + l.r_val);
            ret.all = l.all + r.all;
            ret.val = max({l.val, r.val, l.r_val + r.l_val});

            return ret;
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q, U, V; cin >> N >> Q >> U >> V;

    segment_tree tree(N);
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        tree.update(1, N, 1, i, U * x + V);
    }

    while(Q --> 0) {
        int C, A, B; cin >> C >> A >> B;
        if(C == 0) cout << tree.query(1, N, 1, A, B).val - V << '\n';
        else tree.update(1, N, 1, A, U * B + V);
    }

    return 0;
}