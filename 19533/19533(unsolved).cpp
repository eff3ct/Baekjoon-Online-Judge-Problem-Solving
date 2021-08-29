// https://www.acmicpc.net/problem/19533 //
// UCPC 2020 Qualifier B //
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<string> dp(1000, "n");

string solve(int n) {
    if(dp[n] != "n") return dp[n];

    string tail = '-' + to_string(n);

    dp[n] = solve(n - (floor(log10(n)) + 2)) + tail;

    return dp[n];
}

int main() {
    int a, b; cin >> a >> b;

    dp[0] = "";
    dp[1] = "1";
    dp[2] = "-2";

    int n;
    if((a < 21 && b == 0) || (a <= 2 && b == 1)) {
        n = a * pow(10, b);
        cout << solve(n);
    }
    else {
        
    }

    return 0;
}
