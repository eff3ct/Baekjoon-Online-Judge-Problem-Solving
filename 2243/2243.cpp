#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class segment_tree {
    private:
        vector<ll> tree;

    public: 
        segment_tree(int N) {
            tree.resize(4 * N);
        }

        void update(int start, int end, int node, int idx, ll diff) {
            if(idx < start || end < idx) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx, diff);
                update(mid + 1, end, node * 2 + 1, idx, diff);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
            else tree[node] += diff;
        }

        ll query(int start, int end, int node, int target) {
            if(start == end) return start;

            int mid = (start + end) / 2;

            if(tree[node * 2] >= target) return query(start, mid, node * 2, target);
            else return query(mid + 1, end, node * 2 + 1, target - tree[node * 2]);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    const int M = 1e6;
    segment_tree tree(M);

    for(int i = 0; i < n; ++i) {
        int A; cin >> A;
        if(A == 1) {
            int B; cin >> B;
            int idx = tree.query(1, M, 1, B);
            tree.update(1, M, 1, idx, -1);
            cout << idx << '\n';
        }
        else {
            int B, C; cin >> B >> C;
            tree.update(1, M, 1, B, C);
        }
    }

    return 0;
}