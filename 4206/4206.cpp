#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll fib[31];
string fib_string[31];
void init_fib() {
    fib[0] = fib[1] = 1;
    for(int i = 2; i < 31; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];

    fib_string[0] = "0", fib_string[1] = "1";
    for(int i = 2; i < 31; ++i) 
        fib_string[i] = fib_string[i - 1] + fib_string[i - 2];
}

void get_fail(string& p, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)p.size(); ++i) {
        while(j && p[i] != p[j]) j = fail[j - 1];
        if(p[i] == p[j]) fail[i] = ++j;
    }
}

ll get_match_count_with_kmp(string& s, string& p) {
    int n = (int)s.size(), m = (int)p.size();

    vector<int> fail(m, 0);
    get_fail(p, fail);

    ll ret = 0;
    for(int i = 0, j = 0; i < n; ++i) {
        while(j && s[i] != p[j]) j = fail[j - 1];

        if(s[i] == p[j]) {
            if(j == m - 1) {
                ret++;
                j = fail[j];
            }
            else j++;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init_fib();

    int n;
    string p;

    int tc = 1;
    while(cin >> n >> p) {
        ll dp[101] = { 0, };
        ll concat_match[2] = { 0, };

        dp[0] = (p == "0"), dp[1] = (p == "1");
        for(int i = 2; i < 28; ++i) {
            dp[i] = get_match_count_with_kmp(fib_string[i], p);
        }

        int k = 28;
        string s1 = fib_string[k - 1].substr(((int)fib_string[k - 1].size()) - ((int)p.size() - 1)) 
        + fib_string[k - 2].substr(0, (int)p.size() - 1);

        string s2 = fib_string[k - 2].substr(((int)fib_string[k - 2].size()) - ((int)p.size() - 1))
        + fib_string[k - 1].substr(0, (int)p.size() - 1);

        concat_match[0] = get_match_count_with_kmp(s1, p);
        concat_match[1] = get_match_count_with_kmp(s2, p);

        for(int i = k, x = 0; i <= n; ++i, x = 1 - x) 
            dp[i] = dp[i - 1] + dp[i - 2] + concat_match[x];

        cout << "Case " << tc++ << ": " << dp[n] << '\n';
    }

    return 0;
}