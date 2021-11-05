#include <iostream>
#include <vector>

using namespace std;

class segTree {
    private:
        vector<int> tree;
        vector<int> lazy;

    public:
        segTree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        void propagate(int start, int end, int node) {
            if(lazy[node] == 0) return;

            tree[node] ^= lazy[node] * ((end - start + 1) % 2);

            if(start != end) {
                lazy[node * 2] ^= lazy[node];
                lazy[node * 2 + 1] ^= lazy[node];
            }

            lazy[node] = 0;   
        }

        int query(int start, int end, int node, int left, int right) {
            propagate(start, end, node);

            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) ^ query(mid + 1, end, node * 2 + 1, left, right);
        }
        
        void updateRange(int start, int end, int node, int left, int right, int k) {
            propagate(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                lazy[node] ^= k;

                propagate(start, end, node);
            
                return;
            }

            int mid = (start + end) / 2;

            updateRange(start, mid, node * 2, left, right, k);
            updateRange(mid + 1, end, node * 2 + 1, left, right, k);
            tree[node] = tree[node * 2] ^ tree[node * 2 + 1];
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    segTree Tree(N);

    for(int i = 0; i < N; ++i) {
        int k; cin >> k;
        Tree.updateRange(0, N - 1, 1, i, i, k);
    }

    int M; cin >> M;

    while(M --> 0) {
        int cmd; cin >> cmd;
        if(cmd == 1) {
            int i, j, k; cin >> i >> j >> k;
            Tree.updateRange(0, N - 1, 1, i, j, k);
        }
        else {
            int i, j; cin >> i >> j;
            cout << Tree.query(0, N - 1, 1, i, j) << '\n';
        }
    }

    return 0;
}