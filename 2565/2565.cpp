#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> dp(N, 1);

    vector<pair<int, int>> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i].first >> seq[i].second;
    sort(seq.begin(), seq.end());

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            if(seq[i].second > seq[j].second) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
    }

    int lis = *max_element(dp.begin(), dp.end());

    cout << N - lis << '\n';

    return 0;
}