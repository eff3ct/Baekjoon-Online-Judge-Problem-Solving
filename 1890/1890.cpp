#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
int N; 

ll count(int row, int col, vector<vector<int>>& jump, vector<vector<ll>>& dp) {
    ll& ret = dp[row][col];

    if(ret != -1) return ret;
    if(row == N - 1 && col == N - 1) return ret = 1;

    ret = 0;

    int new_row = jump[row][col] + row, new_col = jump[row][col] + col;

    if(0 <= new_row && new_row <= N - 1) ret += count(new_row, col, jump, dp);
    if(0 <= new_col && new_col <= N - 1) ret += count(row, new_col, jump, dp);

    return ret;
}

int main() {
    cin >> N;

    vector<vector<int>> jump(N, vector<int>(N));
    vector<vector<ll>> dp(N, vector<ll>(N, -1));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> jump[i][j];
        }
    }

    cout << count(0, 0, jump, dp);

    return 0;
}