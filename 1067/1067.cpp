#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

using namespace std;
typedef complex<double> cpx;
typedef long long ll;

void FFT(vector<cpx>& A, cpx w) {
    int n = (int)A.size();
    if(n == 1) return;
    
    vector<cpx> even(n / 2), odd(n / 2);

    for(int i = 0; i < n; ++i) {
        if(i & 1) odd[i / 2] = A[i];
        else even[i / 2] = A[i];
    }

    FFT(even, w * w);
    FFT(odd, w * w);

    cpx w_i(1, 0);
    for(int i = 0; i < n / 2; ++i) {
        A[i] = even[i] + w_i * odd[i];
        A[i + n / 2] = even[i] - w_i * odd[i];
        w_i *= w;
    }
}

void solve(vector<cpx>& A, vector<cpx>& B) {
    int size = (int)A.size() / 2;
    int n = ceil(log2(size));
    n = pow(2, n + 1);

    A.resize(n);
    B.resize(n);
    vector<cpx> C(n);

    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));

    FFT(A, w);
    FFT(B, w);

    for(int i = 0; i < n; ++i) C[i] = A[i] * B[i];

    FFT(C, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        C[i] /= cpx(n, 0);
        C[i] = cpx(round(C[i].real()), round(C[i].imag()));
    }

    ll ret = 0;
    for(int i = size - 1; i <= 2 * size - 2; ++i) ret = max(ret, (ll)C[i].real());
    
    cout << ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    vector<cpx> A(2 * N);
    vector<cpx> B(2 * N);

    for(int i = 0; i < N; ++i) {
        int tmp; cin >> tmp;
        A[i] = tmp, A[i + N] = tmp;
    }

    for(int i = 0; i < N; ++i) cin >> B[N - i - 1];

    solve(A, B);

    return 0;
}