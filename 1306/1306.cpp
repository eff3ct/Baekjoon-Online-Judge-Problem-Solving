// https://www.acmicpc.net/problem/1306 //
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

            return tree[node] = max(init(A, start, mid, node * 2) 
            , init(A, mid + 1, end, node * 2 + 1));
        }

        ll maximum(int start, int end, int left, int right, int node) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (int)(start + end) / 2;

            return max(maximum(start, mid, left, right, node * 2) 
            , maximum(mid + 1, end, left, right, node * 2 + 1));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<ll> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    segTree Tree(N);
    Tree.init(A, 0, N - 1, 1);

    for(int i = M - 1; i <= N - M; ++i) 
        cout << Tree.maximum(0, N - 1, i - (M - 1), i + (M - 1), 1) << " ";

    return 0;
}