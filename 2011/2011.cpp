#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MOD = 1e6;

int count(int idx, string& str, vector<int>& dp) {
    if(idx >= int(str.size())) return 1;

    int& ret = dp[idx];

    if(ret != -1) return ret;
    if(str[idx] == '0') return ret = 0;
    if(idx == int(str.size()) - 1) return ret = 1;

    ret = 0;
    if(idx + 1 < int(str.size()) && str[idx + 1] != '0') ret += count(idx + 1, str, dp);
    ret %= MOD;

    if(1 <= stoi(str.substr(idx, 2)) && stoi(str.substr(idx, 2)) <= 26 
    && (idx + 2 == int(str.size()) || str[idx + 2] != '0')) ret += count(idx + 2, str, dp);
    ret %= MOD;

    return ret;
}

int main() {
    string str; cin >> str;

    vector<int> dp(int(str.size()), -1);
    cout << count(0, str, dp) % MOD;

    return 0;
}