// https://www.acmicpc.net/problem/2407 //
#include <iostream>
#include <string>

using namespace std;
typedef unsigned long long ll;

ll combination(int n, int r) {
    ll dp[101][101];
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= r; ++j) {
            if(i == j || j == 0) dp[i][j] = 1;
            else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return dp[n][r];
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << combination(n, m);
    return 0;
}