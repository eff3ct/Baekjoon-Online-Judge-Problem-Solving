#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    ll p = 0;
    for(int i = 0; i < N; ++i) {
        ll _p; cin >> _p;
        p ^= _p;
    }
    cout << (p ? "koosaga" : "cubelover") << '\n';

    return 0;
}