// https://www.acmicpc.net/problem/2268 //
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

vector<ll> A(1000001, 0);

class segTree {
    private:
        vector<ll> tree;

    public:
        segTree(int N) {
            int h = ceil(log2(N));
            tree.resize(1 << (h + 1));
            fill(tree.begin(), tree.end(), 0);
        }

        void modify(int start, int end, int node, int i, ll diff) {
            if(i < start || i > end) return;

            tree[node] += diff;

            int mid = (start + end) / 2;

            if(start != end) {
                modify(start, mid, node*2, i, diff);
                modify(mid + 1, end, node*2 + 1, i, diff);
            }
        }

        ll summation(int start, int end, int node, int left, int right) {
            if(end < left || start > right) return 0;
            if(left <= start && end <= right) return tree[node];
            
            int mid = (start + end) / 2;

            return summation(start, mid, node * 2, left, right) 
            + summation(mid + 1, end, node*2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;

    segTree Tree(N);
    
    for(int i = 0; i < M; ++i) {
        int cmd, a, b;
        cin >> cmd >> a >> b;

        if(cmd == 0) 
            (a < b) ? (cout << Tree.summation(1, N, 1, a, b) << '\n') : (cout << Tree.summation(1, N, 1, b, a) << '\n');
        else {
            int diff = b - A[a];
            A[a] = b;
            Tree.modify(1, N, 1, a, diff);
        }
    }

    return 0;
}