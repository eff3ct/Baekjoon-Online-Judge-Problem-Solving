// https://www.acmicpc.net/problem/10999 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;
        vector<ll> lazy;

    public:
        segTree(int N) {
            tree.resize(N * 4);
            lazy.resize(N * 4);
        }

        ll init(vector<ll>& A, int start, int end, int node) {
            if(start == end) return tree[node] = A[start];

            int mid = (start + end) / 2;

            return tree[node] = init(A, start, mid, node * 2) 
            + init(A, mid + 1, end, node * 2 + 1);
        }

        void updateLazy(int start, int end, int node) {
            if(lazy[node] == 0) return;
            
            tree[node] += (end- start + 1) * lazy[node];

            if(start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            
            lazy[node] = 0;
        }

        void updateRange(int start, int end, int node, int left, int right, ll diff) {
            updateLazy(start, end, node);

            if(start > right || end < left) return;

            if(left <= start && end <= right) {
                tree[node] += (end - start + 1) * diff;
                
                if(start != end) {
                    lazy[node * 2] += diff;
                    lazy[node * 2 + 1] += diff;
                }

                return;
            }

            int mid = (start + end) / 2;
            updateRange(start, mid, node * 2, left, right, diff);
            updateRange(mid + 1, end, node * 2 + 1, left, right, diff);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

        ll query(int start, int end, int node, int left, int right) {
            updateLazy(start, end, node);
            if(start > right || end < left) return 0;

            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) 
            + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;

    vector<ll> A(N + 1);
    for(int i = 1; i <= N; ++i) cin >> A[i];

    segTree Tree(N);
    Tree.init(A, 1, N, 1);

    for(int i = 0; i < M + K; ++i) {
        int a; cin >> a;
        if(a == 1) {
            int b, c, d; cin >> b >> c >> d;
            Tree.updateRange(1, N, 1, b, c, d);
        }
        else {
            int b, c; cin >> b >> c;
            cout << Tree.query(1, N, 1, b, c) << '\n';
        }
    }

    return 0;
}