// https://www.acmicpc.net/problem/14003 //
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void solve(vector<int>& A) {
    vector<int> lis;
    vector<int> savedIdx(A.size());

    lis.push_back(A[0]);
    savedIdx[0] = 0;

    for(int i = 1; i < A.size(); ++i) {
        int lowerBound = lower_bound(lis.begin(), lis.end(), A[i]) - lis.begin();
        if(lowerBound == lis.size()) {
            savedIdx[i] = lis.size();
            lis.push_back(A[i]);
        }
        else {
            savedIdx[i] = lowerBound;
            lis[lowerBound] = A[i];
        }
    }

    cout << lis.size() << '\n';
    int last = lis.size() - 1;
    vector<int> ret;
    for(int i = A.size() - 1; i >= 0; --i) {
        if(last < 0) break;
        if(savedIdx[i] == last) {
            ret.push_back(A[i]);
            last--;
        }
    }

    for(int i = ret.size() - 1; i >= 0; --i) cout << ret[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    solve(A);

    return 0;
}
