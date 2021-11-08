#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int solve(vector<int>& seq, int K) {
    int r = 20 * 1e5;
    int l = 1;

    int ret = -1;

    while(l <= r) {
        int partition = 0;
        int mid = (l + r) / 2;
        int cnt = 0;

        for(int i = 0; i < (int)seq.size(); ++i) {
            partition += seq[i];
            if(partition >= mid) {
                cnt++;
                partition = 0;
            }
        }

        if(cnt >= K) {
            ret = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    return ret;
}

int main() {
    int N, K; cin >> N >> K;
    vector<int> seq(N);

    for(int i = 0; i < N; ++i) cin >> seq[i];

    cout << solve(seq, K);

    return 0;
}