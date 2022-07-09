#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

struct line {
    ll m, n;
    long double s;
};

ll dp[100'001];
line line_stack[100'001];

long double get_intersection(const line& a, const line& b) {
    return (long double)(a.n - b.n) / (long double)(b.m - a.m);
}

ll solve(vector<ll>& a, vector<ll>& b, int n) {
    int top = 0, cur = 0;

    for(int i = 2; i <= n; ++i) {
        line g = {b[i - 1], dp[i - 1], 0};

        while(top > 0) {
            g.s = get_intersection(line_stack[top - 1], g);

            if(line_stack[top - 1].s < g.s) break;

            if(--top == cur) cur--;
        }

        line_stack[top++] = g;

        ll x = a[i];

        while(cur + 1 < top && line_stack[cur + 1].s < x) cur++;

        dp[i] = line_stack[cur].m * a[i] + line_stack[cur].n;
    }

    return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; ++i) cin >> a[i];

    vector<ll> b(n + 1);
    for(int i = 1; i <= n; ++i) cin >> b[i];

    cout << solve(a, b, n) << '\n';

    return 0;
}