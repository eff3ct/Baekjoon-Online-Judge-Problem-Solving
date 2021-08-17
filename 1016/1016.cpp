#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

void solve(ll m, ll M) {
    vector<bool> isJegopNoNo(M - m + 1, true);

    for(ll i = 2; i <= sqrt(M); ++i) {
        ll k = ceil(double(m) / double(i * i));
        
        for(ll j = (i * i) * k; j <= M; j += (i * i)) {
            isJegopNoNo[j - m] = false;
        }
    }

    int ret = 0;
    for(int i = 0; i < isJegopNoNo.size(); ++i) {
        if(isJegopNoNo[i]) ret++;
    }

    cout << ret;
}

int main() {
    ll m, M; cin >> m >> M;

    solve(m, M);

    return 0;
}