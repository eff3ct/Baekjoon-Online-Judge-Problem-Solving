// https://www.acmicpc.net/problem/11658 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class fenwickTree {
    private:
        vector<vector<ll>> tree;
        int maxSize;

    public:
        fenwickTree(int N) {
            tree.resize(N + 1);
            for(int i = 1; i <= N; ++i) tree[i].resize(N + 1);
            maxSize = N;
        }

        ll query(int x, int y) {
            ll ret = 0;
            for(int i = x; i > 0; i -= (i & (-i))) {
                for(int j = y; j > 0; j -= (j & (-j))) {
                    ret += tree[i][j];
                }
            }
            return ret;
        }

        void update(int x, int y, ll diff) {
            for(int i = x; i <= maxSize; i += (i & (-i))) {
                for(int j = y; j <= maxSize; j += (j & (-j))) {
                    tree[i][j] += diff;
                }
            }
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;

    fenwickTree Tree(N);

    vector<vector<int>> A(N + 1, vector<int>(N + 1));

    for(int x = 1; x <= N; ++x) {
        for(int y = 1; y <= N; ++y) {
            cin >> A[x][y];
            Tree.update(x, y, A[x][y]);
        }
    }

    for(int i = 0; i < M; ++i) {
        int w; cin >> w;
        if(w) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            ll res = Tree.query(x2, y2) - Tree.query(x1 - 1, y2) - Tree.query(x2, y1 - 1) + Tree.query(x1 - 1, y1 - 1);
            cout << res << '\n';
        }
        else {
            ll x, y, c; cin >> x >> y >> c;
            ll diff = c - A[x][y];
            A[x][y] = c;
            Tree.update(x, y, diff);
        }
    }

    return 0;
}

