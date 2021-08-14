// https://www.acmicpc.net/problem/14002 //
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void solve(vector<int>& A, int& N) {
    vector<int> dp(N, 1);
    vector<int> history(N, -1);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            if(A[i] > A[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                history[i] = j;
            }
        }
    }

    int maxIdx = max_element(dp.begin(), dp.end()) - dp.begin();
    int maxElement = dp[maxIdx];

    cout << maxElement << '\n';

    int next = history[maxIdx];
    vector<int> seq;
    seq.push_back(A[maxIdx]);
    while(next != -1) {
        seq.push_back(A[next]);
        next = history[next];
    }

    reverse(seq.begin(), seq.end());
    for(auto& element : seq) cout << element << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    solve(A, N);

    return 0;
}
