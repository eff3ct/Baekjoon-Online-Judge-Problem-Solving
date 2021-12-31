#include <iostream>
#include <vector>

using namespace std;

int solve(int a, int b, int c, vector<vector<vector<int>>>& dp) {
    if(a <= 0 || b <= 0 || c <= 0) return 1;
    if(a > 20 || b > 20 || c > 20) return solve(20, 20, 20, dp);

    int& ret = dp[a][b][c];
    if(ret != -1) return ret;

    if(a < b && b < c) return ret = solve(a, b, c - 1, dp) + solve(a, b - 1, c - 1, dp) - solve(a, b - 1, c, dp);
    else return ret = solve(a - 1, b, c, dp) + solve(a - 1, b - 1, c, dp) + solve(a - 1, b, c - 1, dp) - solve(a - 1, b - 1, c - 1, dp); 
}

int main() {
    vector<vector<vector<int>>> dp(21, vector<vector<int>>(21, vector<int>(21, -1)));

    while(true) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == -1 && b == -1 && c == -1) break;

        cout << "w(" << a << ", " << b << ", " << c << ") = " << solve(a, b, c, dp) << '\n';
    }

    return 0;
}