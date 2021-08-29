// https://www.acmicpc.net/problem/13555 //
#include <iostream>
#include <vector>
#define DNM 5000000

using namespace std;

class fenwickTree {
    private:
        vector<int> dpTree[51];
        int MAX;

    public:
        fenwickTree(int N, int K) {
            for(int i = 0; i <= K; ++i) {
                dpTree[i].resize(100001);
            }
            MAX = 100000;
        }

        int query(int idx, int k) {
            int res = 0;

            if(k == 0) return 1;

            while(idx) {
                res += dpTree[k][idx];
                res %= DNM;
                idx -= (idx & (-idx));
            }

            return res;
        }

        void update(int idx, int k, int diff) {
            while(idx <= MAX) {
                dpTree[k][idx] += diff;
                dpTree[k][idx] %= DNM;
                idx += (idx & (-idx));
            }
        }

};

int main() {
    int N, K; cin >> N >> K;

    fenwickTree Tree(N, K);

    vector<int> A(N + 1);
    for(int i = 1; i <= N; ++i) cin >> A[i];

    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= K; ++j) {
            Tree.update(A[i], j, Tree.query(A[i] - 1, j - 1));
        }
    }

    cout << Tree.query(100000, K);

    return 0;
}