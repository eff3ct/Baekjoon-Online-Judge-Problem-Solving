#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#define MAX 1000000

using namespace std;
typedef complex<double> cpx;
typedef long long ll;

const double PI = acos(-1);

void getPrime(vector<bool>& isPrime) {
    for(int i = 2; i <= sqrt(MAX); ++i) {
        if(isPrime[i]) {
            for(int j = i * i; j <= MAX; j += i) isPrime[j] = false;
        }
    }
}

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

void convolution(vector<cpx>& A, vector<cpx>& B) {
    int n = (A.size() <= B.size()) ? ceil(log2((double)B.size())) : ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    B.resize(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    FFT(A, w);
    FFT(B, w);

    for(int i = 0; i < n; ++i) A[i] = A[i] * B[i];

    FFT(A, cpx(1, 0) / w);

    for(int i = 0; i < n; ++i) {
        A[i] /= cpx(n, 0);
        A[i] = cpx(round(A[i].real()), round(A[i].imag()));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<bool> isPrime(MAX + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;

    getPrime(isPrime);

    vector<cpx> A(MAX + 1);
    vector<cpx> B(MAX + 1);

    for(int i = 0; i <= MAX; ++i) {
        if(isPrime[i]) {
            A[i] = cpx(1, 0);
            if(2 * i <= MAX) B[2 * i] = cpx(1, 0);
        }
    }

    convolution(A, B);    

    int T; cin >> T;
    while(T --> 0) {
        int odd; cin >> odd;
        cout << (ll)A[odd].real() << '\n';
    }

    return 0;
}