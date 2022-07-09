#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve(vector<int>& wire, int N) {
    ll l = 0, r = (1LL << 31);

    while(l + 1 < r) {
        ll mid = (l + r) / 2;

        int cnt = 0;
        for(int& e : wire) cnt += e / mid;

        if(cnt >= N) l = mid;
        else r = mid;
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int K, N;
    cin >> K >> N;

    vector<int> wire(K);
    for(int& e : wire) cin >> e;

    solve(wire, N);

    return 0;
}