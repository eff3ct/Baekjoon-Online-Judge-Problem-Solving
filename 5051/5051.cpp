#include <bits/stdc++.h>

using namespace std;
typedef complex<double> cpx;
using ll = long long;

//Cooley-Tukey FFT
void FFT(vector<cpx>& A, cpx w) {
    //base case
    int n = (int)A.size();
    if(n == 1) return;

    //split to even and odd
    vector<cpx> even(n / 2), odd(n / 2);
    for(int i = 0; i < n; ++i) {
        if(i & 1) odd[i / 2] = A[i];
        else even[i / 2] = A[i];
    }

    //Divide
    FFT(even, w * w);
    FFT(odd, w * w);

    cpx w_e(1, 0);

    //conquer
    for(int i = 0; i < n / 2; ++i) {
        A[i] = even[i] + w_e * odd[i];
        A[i + n / 2] = even[i] - w_e * odd[i];
        w_e *= w;
    }

    //Time complexity = n log n
}

//get discrete convolution of A and B
vector<cpx> product(vector<cpx> A, vector<cpx> B) {
    //get n, which satisfies n > 2 ^ ceil(log_2(size)) (when n = 2^k)
    int n = (A.size() <= B.size()) ? ceil(log2((double)B.size())) : ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    B.resize(n);
    vector<cpx> C(n);

    //n th root of unity (euler formula)
    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));
    FFT(A, w);
    FFT(B, w);

    //multiply DFT
    for(int i = 0; i < n; ++i) C[i] = A[i] * B[i];

    //Inverse FFT to get Coefficient
    FFT(C, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        C[i] /= cpx(n, 0);
        C[i] = cpx(round(C[i].real()), round(C[i].imag()));
    }

    return C;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n; cin >> n;
    vector<cpx> A(n);
    
    for(ll i = 1; i < n; ++i) {
        ll x = (i * i) % n;
        A[x] = {A[x].real() + 1, 0};
    }

    vector<cpx> B = product(A, A);
    ll X = 0;
    for(int i = 0; i < (int)B.size(); ++i) {
        ll cnt = (ll)B[i].real() * (ll)A[i % n].real();
        X += cnt;
    }

    vector<ll> C(n);
    for(ll i = 1; i < n; ++i) {
        ll x = (i * i * 2) % n;
        C[x] += 1;
    }

    ll Y = 0;
    for(int i = 0; i < n; ++i) 
        Y += C[i] * (ll)A[i].real();
    
    cout << (X - Y) / 2 + Y << '\n';

    return 0;
}