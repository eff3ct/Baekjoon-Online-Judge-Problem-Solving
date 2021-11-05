#include <iostream>
#include <vector>
#include <string>
#define MAX 2500

using namespace std;

int dp[MAX];
bool isPldr[MAX][MAX];
string str;

void isPalindrome(string& str, int a, int b) {
    for(int i = 0; i <= (b - a) / 2; ++i) {
        if(str[a + i] != str[b - i]) {
            isPldr[a][b] = false;
            return;
        }
    }
    isPldr[a][b] = true;
}

int solve(string& str, int n) {
    if(n < 0) return 0;

    int& ret = dp[n];
    if(ret != -1) return ret;

    ret = MAX + 1;
    for(int k = 0; k <= n; ++k) {
        if(isPldr[k][n]) ret = min(ret, 1 + solve(str, k - 1));
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i = 0; i < MAX; ++i) dp[i] = -1; //init

    cin >> str;

    for(int i = 0; i < (int)str.size(); ++i) {
        for(int j = i; j < (int)str.size(); ++j) {
            isPalindrome(str, i, j);
        }
    }
    
    cout << solve(str, (int)str.size() - 1);

    return 0;
}