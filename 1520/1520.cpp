#include <iostream>
#include <vector>

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int M, N; 

int count(int row, int col, vector<vector<int>>& height, vector<vector<int>>& dp) {
    int& ret = dp[row][col];

    if(ret != -1) return ret;
    if(row == 0 && col == 0) return 1;

    ret = 0;
    for(int i = 0; i < 4; ++i) {
        int new_row = dy[i] + row;
        int new_col = dx[i] + col;

        if(new_row < 0 || new_row >= M || new_col < 0 || new_col >= N) continue;
        if(height[new_row][new_col] <= height[row][col]) continue;

        ret += count(new_row, new_col, height, dp);
    }

    return ret;
}

int main() {
    cin >> M >> N;

    vector<vector<int>> height(M, vector<int>(N));

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> height[i][j];
        }
    }

    vector<vector<int>> dp(M, vector<int>(N, -1));
    cout << count(M - 1, N - 1, height, dp);

    return 0;
}