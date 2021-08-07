// https://www.acmicpc.net/problem/2042 //
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class segTree {
    private:
        vector<ll> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        ll init(vector<ll>& A, int start, int end, int node) {
            if(start == end) return tree[node] = A[start];

            int mid = (int)(start + end) / 2;

            return tree[node] = init(A, start, mid, node * 2) 
            + init(A, mid + 1, end, node * 2 + 1);
        }

        ll summation(int start, int end, int left, int right, int node) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (int)(start + end) / 2;

            return summation(start, mid, left, right, node * 2) 
            + summation(mid + 1, end, left, right, node * 2 + 1);
        }

        void update(int start, int end, int idx, int node, ll diff) {
            if(idx < start || idx > end) return;

            tree[node] += diff;
            
            if(start != end) {
                int mid = (int)(start + end) / 2;
                update(start, mid, idx, node * 2, diff);
                update(mid + 1, end, idx, node * 2 + 1, diff);
            } 
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<ll> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    segTree Tree(N);
    Tree.init(A, 0, N - 1, 1);

    for(int i = 0; i < M + K; ++i) {
        ll a, b, c; 
        cin >> a >> b >> c;

        if(a == 1) {
            ll diff = c - A[b - 1];
            A[b - 1] = c;
            Tree.update(0, N - 1, b - 1, 1, diff);
        }
        else {
            cout << Tree.summation(0, N - 1, b - 1, c - 1, 1) << '\n';
        }
    }

    return 0;
}