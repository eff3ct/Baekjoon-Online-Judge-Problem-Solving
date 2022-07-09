#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void adjustment(ll& A, ll& B, ll d, ll* s) {
    while(A % 10 != 0 && A <= B) {
        string tmp = to_string(A);
        for(char& e : tmp) s[e - '0'] += d;
        A++;
    }

    if(A > B) return;

    while(B % 10 != 9 && A <= B) {
        string tmp = to_string(B);
        for(char& e : tmp) s[e - '0'] += d;
        B--;
    }
}

void calculate(ll A, ll B, ll d, ll* s) {
    ll cnt_A = A / 10;
    ll cnt_B = B / 10;
    for(int i = 0; i < 10; ++i) s[i] += (cnt_B - cnt_A + 1) * d;
}

void solve(ll N) {
    ll ret[10] = { 0, };

    ll A = 1, B = N;
    ll d = 1;
    while(A <= B) {
        adjustment(A, B, d, ret);
        if(A > B) break;
        calculate(A, B, d, ret);

        d *= 10;
        A /= 10, B /= 10;
    }

    for(ll& e : ret) cout << e << ' ';
}

int main() {
    ll N; cin >> N;

    solve(N);

    return 0;
}