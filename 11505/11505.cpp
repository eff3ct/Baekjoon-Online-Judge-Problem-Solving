// https://www.acmicpc.net/problem/11505 //
#include <iostream>
#include <vector>
#define DNM 1000000007LL

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;
        vector<ll> A;

    public:
        segTree(int N) {
            tree.resize(N * 4);
            A.resize(N + 1);
        }

        void pushValue(ll idx, ll val) {
            A[idx] = val;
        }

        ll init(int start, int end, int node) {
            if(start == end) return tree[node] = A[start];

            int mid = (int)(start + end) / 2;

            return tree[node] = init(start, mid, node * 2) 
            * init(mid + 1, end, node * 2 + 1) % DNM;
        }

        ll multiply(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 1;
            if(left <= start && end <= right) return tree[node];

            int mid = (int)(start + end) / 2;

            return multiply(start, mid, node * 2, left, right) 
            * multiply(mid + 1, end, node * 2 + 1, left, right) % DNM;
        }

        ll update(int start, int end, int node, int idx) {
            if(idx < start || idx > end) return tree[node];

            int mid = (int)(start + end) / 2;

            if(start != end) {
                return tree[node] = update(start, mid, node * 2, idx) 
                * update(mid + 1, end, node * 2 + 1, idx) % DNM;
            }
            else return tree[node] = A[idx];
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    segTree Tree(N);
    for(int i = 1; i <= N; ++i) {
        ll tmp; cin >> tmp;
        Tree.pushValue(i, tmp);
    }
    Tree.init(1, N, 1);

    for(int i = 0; i < M + K; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1) {
            Tree.pushValue(b, c);
            Tree.update(1, N, 1, b);
        }
        else cout << Tree.multiply(1, N, 1, b, c) << '\n';
    }

    return 0;
} 