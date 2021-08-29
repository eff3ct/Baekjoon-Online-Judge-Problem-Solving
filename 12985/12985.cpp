// https://www.acmicpc.net/problem/12985 //
#include <iostream>
#include <vector>

using namespace std;

class segTree {
    private:
        vector<int> tree;
        vector<int> lazy;

    public:
        segTree(int N) {
            tree.resize(N * 4, 1);
            lazy.resize(N * 4);
        }

        void updateLazy(int start, int end, int node) {
            if(lazy[node] == 0) return;
            
            tree[node] = lazy[node];

            if(start != end) {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            
            lazy[node] = 0;
        }

        void updateRange(int start, int end, int node, int left, int right, int color) {
            updateLazy(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] = (1 << color);
                
                if(start != end) {
                    lazy[node * 2] = (1 << color);
                    lazy[node * 2 + 1] = (1 << color);
                }

                return;
            }

            int mid = (start + end) / 2;
            updateRange(start, mid, node * 2, left, right, color);
            updateRange(mid + 1, end, node * 2 + 1, left, right, color);
            tree[node] = tree[node * 2] | tree[node * 2 + 1];
        }

        int query(int start, int end, int node, int left, int right) {
            updateLazy(start, end, node);
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) 
            | query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int countOnBit(int bit, int& T) {
    int ret = 0;
    while(bit) {
        if(bit & 1) ret++;
        bit >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, T, Q; cin >> N >> T >> Q;
    segTree Tree(N);

    for(int i = 0; i < Q; ++i) {
        char cmd; cin >> cmd;
        if(cmd == 'C') {
            int x, y, z; cin >> x >> y >> z;
            if(x > y) Tree.updateRange(1, N, 1, y, x, z - 1);
            else Tree.updateRange(1, N, 1, x, y, z - 1);
        }
        else {
            int x, y; cin >> x >> y;

            int bit;
            if(x > y) bit = Tree.query(1, N, 1, y, x);
            else bit = Tree.query(1, N, 1, x, y);
            
            cout << countOnBit(bit, T) << '\n';
        }
    }
    return 0;
}