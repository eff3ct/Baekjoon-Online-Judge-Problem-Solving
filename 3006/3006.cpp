// https://www.acmicpc.net/problem/3006 //
#include <iostream>
#include <vector>

using namespace std;

class segTree {
    private:
        vector<int> tree;

    public:
        segTree(int N) {
            tree.resize(N * 4);
        }

        int init(int start, int end, int node) {
            if(start == end) return tree[node] = 1;

            int mid = (start + end) / 2;

            return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
        }

        void update(int start, int end, int node, int idx) {
            if(idx < start || end < idx) return;
            
            tree[node] -= 1;

            if(start != end) {
                int mid = (start + end) / 2;
                update(start, mid, node * 2, idx);
                update(mid + 1, end, node * 2 + 1, idx);
            }
        }

        int query(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return tree[node];

            int mid = (start + end) / 2;

            return query(start, mid, node * 2, left, right) + query(mid + 1, end, node * 2 + 1, left, right);
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    segTree Tree(N);
    Tree.init(1, N, 1);

    vector<int> od(N + 1);
    for(int i = 1; i <= N; ++i) {
        int tmp; cin >> tmp;
        od[tmp] = i;
    }

    int a = 1, b = N, cnt = 0;
    while(true) {
        if(cnt == N) break;
        if(cnt & 1) {
            cout << Tree.query(1, N, 1, od[b], N) - 1 << '\n';
            Tree.update(1, N, 1, od[b]);
            b--;
        }
        else {
            cout << Tree.query(1, N, 1, 1, od[a]) - 1 << '\n';
            Tree.update(1, N, 1, od[a]);
            a++;
        }
        cnt++;
    }

    return 0;
}