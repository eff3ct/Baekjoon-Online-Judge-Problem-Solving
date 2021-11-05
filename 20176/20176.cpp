#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;
typedef complex<double> cpx;
typedef long long ll;
const double PI = acos(-1);

void FFT(vector<cpx>& A, cpx w) {
    int n = (int)A.size();
    if(n == 1) return;

    vector<cpx> even(n / 2), odd(n / 2);

    for(int i = 0; i < n; ++i) (i & 1 ? odd : even)[i / 2] = A[i];

    FFT(even, w * w);
    FFT(odd, w * w);

    cpx w_i(1, 0);
    for(int i = 0; i < n / 2; ++i) {
        A[i] = even[i] + w_i * odd[i];
        A[i + n / 2] = even[i] - w_i * odd[i];
        w_i *= w;
    }
}

void convolution(vector<cpx>& A, vector<cpx>& C, vector<cpx>& conv) {
    int n = ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    C.resize(n);
    conv.resize(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    FFT(A, w);
    FFT(C, w);

    for(int i = 0; i < n; ++i) conv[i] = A[i] * C[i];

    FFT(conv, cpx(1, 0) / w);

    for(int i = 0; i < n; ++i) {
        conv[i] /= cpx(n, 0);
        conv[i] = cpx(round(conv[i].real()), round(conv[i].imag())); 
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a; cin >> a;
    vector<cpx> A(60001);
    for(int i = 0; i < a; ++i) {
        int coord; cin >> coord;
        A[coord + 30000] = cpx(1, 0);
    }

    int b; cin >> b;
    vector<cpx> B(60001);
    for(int i = 0; i < b; ++i) {
        int coord; cin >> coord;
        B[coord + 30000] = cpx(1, 0);
    }

    int c; cin >> c;
    vector<cpx> C(60001);
    for(int i = 0; i < c; ++i) {
        int coord; cin >> coord;
        C[coord + 30000] = cpx(1, 0);
    }

    vector<cpx> conv;
    convolution(A, C, conv);

    ll ret = 0;

    for(int i = 0; i <= 60000; ++i) ret += B[i].real() * conv[2 * i].real();

    cout << ret;

    return 0;
    // count = sigma b[i] * (sigma a[k] * c[2i - k])
    // count = sigma b[i] * conv[2i]
}