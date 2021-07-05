// https://www.acmicpc.net/problem/12852 //

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void solve(int n) {
    if(n == 1) {
        cout << 0 << "\n" << 1;
        return;
    }
    else if(n == 2) {
        cout << 1 << "\n" << "2 1";
        return;
    }
    int* dp = new int[n + 1]; //memoization
    int* prevNum = new int[n + 1];
    vector<int> numbers;

    dp[1] = 0; dp[2] = 1;
    prevNum[1] = -1; prevNum[2] = 1;
    int a, b, c;
    for(int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        prevNum[i] = i - 1;
        if((i % 3) == 0) {
            if(dp[i] > (dp[i / 3] + 1)) {
                prevNum[i] = i / 3;
                dp[i] = dp[i / 3] + 1;
            }
        }
        if((i % 2) == 0) {
            if(dp[i] > (dp[i / 2] + 1)) {
                prevNum[i] = i / 2;
                dp[i] = dp[i / 2] + 1;
            }
        }
    }

    cout << dp[n] << "\n";
    cout << n << " ";
    int i = n;
    while(prevNum[i] != -1) {
        cout << prevNum[i] << " ";
        i = prevNum[i];
    }  
    delete[] dp;
    delete[] prevNum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    solve(N);
    return 0;
}