// https://www.acmicpc.net/problem/2263 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(const vector<int>& inOrder, int s1, int e1, const vector<int>& postOrder, int s2, int e2) {
    if(s1 == e1) return;
    
    int root = postOrder[e2 - 1];

    int L = find(inOrder.begin() + s1, inOrder.begin() + e1, root) - (inOrder.begin() + s1);

    cout << root << " ";
    solve(inOrder, s1, s1 + L, postOrder, s2, s2 + L);
    solve(inOrder, s1 + L + 1, e1, postOrder, s2 + L, e2 - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<int> inOrder(N, 0), postOrder(N, 0);
    for(int i = 0; i < N; ++i) cin >> inOrder[i]; //L root R
    for(int i = 0; i < N; ++i) cin >> postOrder[i]; //L R root

    solve(inOrder, 0, N, postOrder, 0, N);

    return 0;
}