#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

ll INF = 12345678987654321LL;
ll MAX = 1000000000LL;

ll getCost(vector<ll>& seq, ll interval) {
    ll cost = 0;
    for(ll i = 0; i < (ll)seq.size(); ++i) {
        cost += abs(seq[i] - interval * i);
    }
    return cost;
}

void solve(vector<ll>& seq) {
    ll left = 1;
    ll right = MAX;

    while(left + 4 < right) {
        ll leftPoint = (2 * left + right) / 3;
        ll rightPoint = (left + 2 * right) / 3;

        ll leftVal = getCost(seq, leftPoint);
        ll rightVal = getCost(seq, rightPoint);

        if(leftVal > rightVal) left = leftPoint;
        else right = rightPoint;
    }

    ll ret = INF;
    for(int i = left; i <= right; ++i) {
        ret = min(ret, getCost(seq, i));
    }

    cout << ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<ll> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    solve(seq);

    return 0;
}