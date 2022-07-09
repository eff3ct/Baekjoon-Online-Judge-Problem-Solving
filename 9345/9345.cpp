#include <iostream>
#include <vector>

using namespace std;
const int INF = 987654321;
const int MIN = -1;

class segment_tree {
    private:
        vector<int> min_tree;
        vector<int> max_tree;

    public:
        segment_tree(int N) {
            min_tree.resize(4 * N);
            max_tree.resize(4 * N);
        }

        void update_min(int start, int end, int node, int idx, int value) {
            if(idx < start || idx > end) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update_min(start, mid, node * 2, idx, value);
                update_min(mid + 1, end, node * 2 + 1, idx, value);
                min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
            }
            else min_tree[node] = value;
        }

        void update_max(int start, int end, int node, int idx, int value) {
            if(idx < start || idx > end) return;

            if(start != end) {
                int mid = (start + end) / 2;
                update_max(start, mid, node * 2, idx, value);
                update_max(mid + 1, end, node * 2 + 1, idx, value);
                max_tree[node] = max(max_tree[node * 2], max_tree[node * 2 + 1]);
            }
            else max_tree[node] = value;
        }

        int query_min(int start, int end, int node, int left, int right) {
            if(right < start || end < left) return INF;

            if(left <= start && end <= right) return min_tree[node];

            int mid = (start + end) / 2;
            return min(query_min(start, mid, node * 2, left, right), 
                query_min(mid + 1, end, node * 2 + 1, left, right));
        }

        int query_max(int start, int end, int node, int left, int right) {
            if(right < start || end < left) return MIN;

            if(left <= start && end <= right) return max_tree[node];

            int mid = (start + end) / 2;
            return max(query_max(start, mid, node * 2, left, right), 
                query_max(mid + 1, end, node * 2 + 1, left, right));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;

    while(T --> 0) {
        int N, K; cin >> N >> K;
        segment_tree tree(N);

        for(int i = 0; i < N; ++i) {
            tree.update_min(0, N - 1, 1, i, i);
            tree.update_max(0, N - 1, 1, i, i);
        }

        for(int i = 0; i < K; ++i) {
            int Q, A, B; cin >> Q >> A >> B;
            if(Q) {
                int M = tree.query_max(0, N - 1, 1, A, B);
                int m = tree.query_min(0, N - 1, 1, A, B);
                if(m == A && M == B) cout << "YES\n";
                else cout << "NO\n";
            }
            else {
                int actual_value_A = tree.query_min(0, N - 1, 1, A, A);
                int actual_value_B = tree.query_min(0, N - 1, 1, B, B);

                tree.update_min(0, N - 1, 1, A, actual_value_B);
                tree.update_min(0, N - 1, 1, B, actual_value_A);
                tree.update_max(0, N - 1, 1, A, actual_value_B);
                tree.update_max(0, N - 1, 1, B, actual_value_A);
            }
        }
    }

    return 0;
}