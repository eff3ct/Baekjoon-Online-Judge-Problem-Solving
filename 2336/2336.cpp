#include <iostream>
#include <vector>

using namespace std;

class segTree {
    private:
        vector<int> tree;

    public:
        segTree(int N) {
            tree.resize(4 * N);
        }

        void update(int s, int e, int node, int idx) {
            if(e < idx || idx < s) return;

            if(s != e) {
                int m = (s + e) / 2;
                update(s, m, node * 2, idx);
                update(m + 1, e, node * 2 + 1, idx);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
            else tree[node] = 1;
        }

        int query(int s, int e, int node, int l, int r) {
            if(e < l || r < s) return 0;

            if(l <= s && e <= r) return tree[node];

            int m = (s + e) / 2;
            return query(s, m, node * 2, l, r) + query(m + 1, e, node * 2 + 1, l, r);
        }
};

int main() {
    int N; cin >> N;

    vector<vector<int>> data(3, vector<int>(N));
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> data[i][j];
        }
    }



}