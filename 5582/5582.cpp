#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> dp;

int solve(string& a, string& b, int i, int j) {
    if(i < 0 || j < 0) return 0;

    int& ret = dp[i][j];
    if(ret != -1) return ret;

    if(a[i] == b[j]) return ret = solve(a, b, i - 1, j - 1) + 1;
    else return ret = 0;
}

int main() {
    string a, b; cin >> a >> b;

    dp.resize((int)a.size(), vector<int>((int)b.size(), -1));

    int ret = 0;
    for(int x = 0; x < (int)a.size(); ++x) {
        for(int y = 0; y < (int)b.size(); ++y) {
            ret = max(ret, solve(a, b, x, y));
        }
    }
    
    cout << ret;

    return 0;
}