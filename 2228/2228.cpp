#include <iostream>
#include <vector>

using namespace std;
const int MIN = -987654321;

int N, M; 

int solve(int idx, int cnt, vector<int>& seq, vector<vector<int>>& dp) {
    if(cnt == M) return 0; //base case
    if(cnt < M && idx >= N) return MIN; //base case 2

    int& ret = dp[idx][cnt];

    if(ret != MIN) return ret;

    ret = MIN - 1;
    int summation = 0;
    for(int i = idx; i < N; ++i) {
        summation += seq[i];
        for(int k = 2; k < N; ++k) {
            ret = max(ret, solve(i + k, cnt + 1, seq, dp) + summation);
        }
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    vector<vector<int>> dp(N, vector<int>(M, MIN));
    vector<int> seq(N);

    for(int& e : seq) cin >> e;

    int ret = MIN;
    for(int i = 0; i < N; ++i) {
        ret = max(ret, solve(i, 0, seq, dp));
    }

    cout << ret;

    return 0;
}