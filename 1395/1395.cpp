#include <iostream>
#include <vector>

using namespace std;

class segTree {
    private:
        vector<int> tree;
        vector<bool> lazy;

    public:
        segTree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void propagate(int start, int end, int node) {
            if(lazy[node] == false) return;

            tree[node] = end - start + 1 - tree[node];

            if(start != end) {
                lazy[node * 2] = !lazy[node * 2];
                lazy[node * 2 + 1] = !lazy[node * 2 + 1];
            }
            
            lazy[node] = false;
        }

        void updateRange(int start, int end, int node, int left, int right) {
            propagate(start, end, node);
            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] = end - start + 1 - tree[node];
                
                if(start != end) {
                    lazy[node * 2] = !lazy[node * 2];
                    lazy[node * 2 + 1] = !lazy[node * 2 + 1];
                }

                return;
            }

            int mid = (start + end) / 2;

            updateRange(start, mid, node * 2, left, right);
            updateRange(mid + 1, end, node * 2 + 1, left, right);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        int query(int start, int end, int node, int left, int right) {
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

    int N, M; cin >> N >> M;
    segTree Tree(N);

    for(int i =  0; i < M; ++i) {
        int cmd, s, t; cin >> cmd >> s >> t;
        if(cmd) cout << Tree.query(1, N, 1, s, t) << '\n';
        else Tree.updateRange(1, N, 1, s, t);
    }

    return 0;
}