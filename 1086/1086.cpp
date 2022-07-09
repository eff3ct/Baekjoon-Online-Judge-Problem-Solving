#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

ll dp[1 << 15 + 1][101];
ll mod_val[16];
ll len[16];
ll mod_digit[51];

int N; 
ll K;

ll solve(int bitmask, int cur_num) {
    if(bitmask == ((1 << N) - 1)) {
        if(cur_num) return 0;
        else return 1;
    }

    ll& ret = dp[bitmask][cur_num];
    
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < N; ++i) {
        if(bitmask & (1 << i)) continue;
        ll next_num = cur_num * mod_digit[len[i]] + mod_val[i];
        next_num %= K;
        ret += solve(bitmask | (1 << i), next_num);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    vector<string> S(N);
    for(string& e : S) cin >> e;
    cin >> K;

    for(int i = 0; i < N; ++i) {
        len[i] = (ll)S[i].size();

        for(char& c : S[i]) {
            mod_val[i] *= 10 % K;
            mod_val[i] += (c - '0') % K;
            mod_val[i] %= K;
        }
    }

    mod_digit[0] = 1 % K;
    for(int i = 1; i <= 50; ++i) mod_digit[i] = ((mod_digit[i - 1] % K) * (10 % K)) % K;

    for(int i = 0; i <= 1 << 15; ++i) fill(dp[i], dp[i] + 101, -1);

    ll q = solve(0, 0);
    ll p = 1;
    for(ll i = 1; i <= N; ++i) p *= i;

    ll GCD = __gcd(p, q);

    q /= GCD, p /= GCD;

    cout << q << "/" << p << '\n';

    return 0;
}