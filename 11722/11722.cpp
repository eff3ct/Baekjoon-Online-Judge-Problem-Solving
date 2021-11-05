#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int N; cin >> N;
    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    vector<int> dp(N, 1);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            if(seq[j] > seq[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end());
    return 0;
}