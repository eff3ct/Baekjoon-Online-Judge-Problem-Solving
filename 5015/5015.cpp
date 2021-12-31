#include <iostream>
#include <string>
#include <vector>

using namespace std;
string s, w;
vector<vector<int>> dp;

bool matchStr(int a, int b) {
    int& ret = dp[a][b];

    if(ret != -1) return ret;

    while(a < (int)w.size() && b < (int)s.size() && (w[a] == s[b] || w[a] == '?')) { a++; b++; }

    if(a == w.size()) return ret = (b == (int)s.size());

    if(w[a] == '*') {
        for(int i = 0; b + i <= (int)s.size(); ++i) {
            if(matchStr(a + 1, b + i)) return ret = 1;
        }
    }

    return ret = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> w;

    dp.resize(101, vector<int>(101, -1));

    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j <= 100; ++j) fill(dp[j].begin(), dp[j].end(), -1);
        cin >> s;
        if(matchStr(0, 0)) cout << s << '\n';
    }

    return 0;
}