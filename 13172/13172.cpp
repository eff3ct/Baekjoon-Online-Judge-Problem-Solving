// https://www.acmicpc.net/problem/13172 //
#include <iostream>
#define DNM 1000000007LL

using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll power(ll a, ll n) {
    if(n == 1) return a;

    ll tmp = power(a, n / 2);

    if(n & 1) return (tmp * tmp % DNM) * a % DNM;
    else return tmp * tmp % DNM;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int M; cin >> M;

    ll ret = 0;
    for(int i = 0; i < M; ++i) {
        ll N, S; cin >> N >> S;

        ll Q = gcd(N, S);
        N /= Q, S /= Q;

        ll NInv = power(N, DNM - 2);
        ll res = S * NInv % DNM;

        ret += res;
        ret %= DNM;
    }

    cout << ret;

    return 0;
}