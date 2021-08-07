// https://www.acmicpc.net/problem/2357 //
#include <iostream>
#include <vector>
#define INF 1000000001

using namespace std;

class segTree {
    private:
        vector<int> minTree;
        vector<int> maxTree;

    public:
        segTree(int N) {
            minTree.resize(N * 4);
            maxTree.resize(N * 4);
        }

        int minTreeInit(vector<int>& A, int start, int end, int node) {
            if(start == end) return minTree[node] = A[start];

            int mid = (int)(start + end) / 2;

            return minTree[node] = min(minTreeInit(A, start, mid, node * 2), 
            minTreeInit(A, mid + 1, end, node * 2 + 1));
        }

        int maxTreeInit(vector<int>& A, int start, int end, int node) {
            if(start == end) return maxTree[node] = A[start];

            int mid = (int)(start + end) / 2;

            return maxTree[node] = max(maxTreeInit(A, start, mid, node * 2), 
            maxTreeInit(A, mid + 1, end, node * 2 + 1));
        }
        
        int getMin(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return INF;
            if(left <= start && end <= right) return minTree[node];

            int mid = (int)(start + end) / 2;

            return min(getMin(start, mid, node * 2, left, right), 
            getMin(mid + 1, end, node * 2 + 1, left, right));
        }

        int getMax(int start, int end, int node, int left, int right) {
            if(start > right || end < left) return 0;
            if(left <= start && end <= right) return maxTree[node];

            int mid = (int)(start + end) / 2;

            return max(getMax(start, mid, node * 2, left, right), 
            getMax(mid + 1, end, node * 2 + 1, left, right));
        }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    segTree Tree(N);
    Tree.minTreeInit(A, 0, N - 1, 1);
    Tree.maxTreeInit(A, 0, N - 1, 1);

    for(int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        cout << Tree.getMin(0, N - 1, 1, a - 1, b - 1) << " " 
        << Tree.getMax(0, N - 1, 1, a - 1, b - 1) << '\n';
    }

    return 0;
}