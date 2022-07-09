#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll solve(vector<int>& seq) {
    stack<pll> stk;
    ll ret = 0;

    for(int i = 0; i < (int)seq.size(); ++i) {
        while(!stk.empty() && stk.top().first < seq[i]) {
            ret += stk.top().second;
            stk.pop();
        }

        if(stk.empty()) stk.push({seq[i], 1});
        else {
            if(stk.top().first > seq[i]) {
                stk.push({seq[i], 1});
                ret++;
            }
            else {
                ret += stk.top().second;
                stk.top().second++;
                if((int)stk.size() >= 2) ret++;
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> seq(N);
    for(int& e : seq) cin >> e;

    cout << solve(seq) << '\n';

    return 0;
}