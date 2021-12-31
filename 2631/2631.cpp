#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N; cin >> N;

    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    vector<int> dp(N);

    for(int i = 0; i < N; ++i) {
        dp[i] = 1;
        for(int j = 0; j < i; ++j) {
            if(seq[i] > seq[j]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    int lis = *max_element(dp.begin(), dp.end());

    cout << N - lis;

    return 0;
}