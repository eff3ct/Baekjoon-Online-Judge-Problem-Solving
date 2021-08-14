// https://www.acmicpc.net/problem/1958 //
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int dp[101][101][101];

int LCS(string& str1, string& str2, string& str3, int idx1, int idx2, int idx3) {
    if(idx1 < 0 || idx2 < 0 || idx3 < 0) return 0;

    int& res = dp[idx1][idx2][idx3];
    if(res != -1) return res;

    if(str1[idx1] == str2[idx2] && str2[idx2] == str3[idx3]) return res = LCS(str1, str2, str3, idx1 - 1, idx2 - 1, idx3 - 1) + 1;
    else return res = max({LCS(str1, str2, str3, idx1 - 1, idx2, idx3), LCS(str1, str2, str3, idx1, idx2 - 1, idx3), LCS(str1, str2, str3, idx1, idx2, idx3 - 1)});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str1, str2, str3;
    cin >> str1 >> str2 >> str3;

    for(int i = 0; i < 101; ++i) {
        for(int j = 0; j < 101; ++j) {
            fill_n(dp[i][j], 101, -1);
        }
    }

    cout << LCS(str1, str2, str3, str1.size() - 1, str2.size() -1, str3.size() - 1);

    return 0;
}