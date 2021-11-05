#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define MAX 1000000

using namespace std;
typedef complex<double> cpx;
const double PI = acos(-1);

//Cooley-Tukey FFT
void FFT(vector<cpx>& A, bool invert) {
    int n = (int)A.size();

    for(int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;

        while(j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;

        if(i < j) swap(A[i], A[j]);
    }    

    for(int length = 2; length <= n; length <<= 1) {
        double ang = 2 * PI / length * (invert ? -1 : 1);
        cpx w(cos(ang), sin(ang));

        for(int i = 0; i < n; i += length) {
            cpx w_i(1, 0);
            for(int j = 0; j < length / 2; ++j) {
                cpx u = A[i + j], v = A[i + j + length / 2] * w_i;
                A[i + j] = u + v, A[i + j + length / 2] = u - v;
                w_i *= w;
            }
        }
    }
    
    if(invert) {
        for(int i = 0; i < n; ++i) {
            A[i] /= cpx(n, 0);
            A[i] = cpx(round(A[i].real()), round(A[i].imag()));
        }
    }
} // referenced from https://blog.myungwoo.kr/54

void convolution(vector<cpx>& A) {
    int n = ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    //n th root of unity (euler formula)
    FFT(A, false);
    //multiply DFT
    for(int i = 0; i < n; ++i) A[i] = A[i] * A[i];

    //Inverse FFT to get Coefficient
    FFT(A, true);
}

void getPrime(vector<bool>& isPrime) {
    for(int i = 2; i <= sqrt(MAX); ++i) {
        if(isPrime[i]) {
            for(int j = i * i; j <= MAX; j += i) isPrime[j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<bool> isPrime(MAX + 1, true);
    isPrime[0] = false, isPrime[1] = false;
    getPrime(isPrime);

    vector<cpx> A(MAX + 1);
    for(int i = 0; i <= MAX; ++i) {
        if(isPrime[i]) A[i] = cpx(1, 0);
    }

    convolution(A);

    int T; cin >> T;
    while(T --> 0) {
        int N; cin >> N;
        if((int)A[N].real() & 1) cout << (int)A[N].real() / 2 + 1 << '\n';
        else cout << (int)A[N].real() / 2 << '\n';
    }

    return 0;
}