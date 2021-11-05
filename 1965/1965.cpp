#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> seq(n);
    for(int i = 0; i < n; ++i) cin >> seq[i];

    vector<int> dp(n, 1);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            if(seq[j] < seq[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}