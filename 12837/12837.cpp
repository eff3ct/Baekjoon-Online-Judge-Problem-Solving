#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class fenwickTree {
    private:
        vector<ll> tree;
    
    public:
        fenwickTree(int N) {
            tree.resize(N + 1);
        }

        void update(int p, ll diff) {
            while(p <= tree.size()) {
                tree[p] += diff;
                p += (p & (-p));
            }
        }

        ll query(int p) {
            ll ret = 0;
            while(p) {
                ret += tree[p];
                p -= (p & (-p));
            }
            return ret;
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q; cin >> N >> Q;
    fenwickTree Tree(N);

    for(int i = 0; i < Q; ++i) {
        ll a, b, c; cin >> a >> b >> c;
        if(a == 1) {
            Tree.update(b, c);
        }
        else {
            ll summation = Tree.query(c) - Tree.query(b - 1);
            cout << summation << '\n';
        }
    }
    return 0;
}