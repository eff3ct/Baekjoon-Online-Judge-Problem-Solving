// https://www.acmicpc.net/problem/9251 //
#include <iostream>
#include <string>

using namespace std;

int dp[1001][1001];

int LCS(string& str1, string& str2, int idx1, int idx2) {
    if(idx1 < 0 || idx2 < 0) return 0;

    int& res = dp[idx1][idx2];
    if(res != -1) return res;

    if(str1[idx1] == str2[idx2]) return res = LCS(str1, str2, idx1 - 1, idx2 - 1) + 1;
    else return res = max(LCS(str1, str2, idx1 - 1, idx2), LCS(str1, str2, idx1, idx2 - 1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str1, str2;
    cin >> str1 >> str2;

    for(int i = 0; i < 1001; ++i) {
        fill_n(dp[i], 1001, -1);
    }

    cout << LCS(str1, str2, str1.size() - 1, str2.size() -1);

    return 0;
}