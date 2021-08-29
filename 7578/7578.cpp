// https://www.acmicpc.net/problem/7578 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class fenwickTree {
    private:
        vector<ll> tree;
        int MAX;

    public:
        fenwickTree(int N) {
            tree.resize(N + 1);
            MAX = N + 1;
        }

        void update(int idx) {
            while(idx <= MAX) {
                tree[idx] += 1;
                idx += (idx & (-idx));
            }
        }

        int query(int idx) {
            int res = 0;

            while(idx) {
                res += tree[idx];
                idx -= (idx & (-idx));
            }

            return res;
        }
}; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<int> A(N + 1);
    vector<int> od(1000001);
    for(int i = 1; i <= N; ++i) cin >> A[i];
    for(int i = 1; i <= N; ++i) {
        int tmp; cin >> tmp;
        od[tmp] = i;
    }

    fenwickTree Tree(1000001);

    ll res = 0;
    for(int i = 1; i <= N; ++i) {
        res += Tree.query(N) - Tree.query(od[A[i]]);
        Tree.update(od[A[i]]);
    }

    cout << res;
    return 0;
}