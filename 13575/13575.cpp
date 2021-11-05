#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define MAX 1000

using namespace std;
typedef complex<double> cpx;

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
vector<cpx> convolution(vector<cpx>& A, vector<cpx>& B) {
    //get n, which satisfies n > 2 ^ ceil(log_2(size)) (when n = 2^k)
    int n = (A.size() <= B.size()) ? ceil(log2((double)B.size())) : ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    vector<cpx> a(A);
    vector<cpx> b(B);
    vector<cpx> ret(n);
    a.resize(n);
    b.resize(n);

    //n th root of unity (euler formula)
    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));
    FFT(a, w);
    FFT(b, w);

    //multiply DFT
    for(int i = 0; i < n; ++i) a[i] = a[i] * b[i];

    //Inverse FFT to get Coefficient
    FFT(a, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        a[i] /= cpx(n, 0);
        a[i] = cpx(round(a[i].real()), round(a[i].imag()));
        if(a[i].real()) ret[i] = 1;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K; cin >> N >> K;
    vector<cpx> A(MAX + 1);
    int maxElement = 0;
    for(int i = 0; i < N; ++i) {
        int cost; cin >> cost;
        maxElement = max(maxElement, cost);
        A[cost] = cpx(1, 0);
    }

    int a = K;
    vector<cpx> ret(1, 1);
    while(K) {
        if(K & 1) ret = convolution(ret, A);
        K >>= 1;
        A = convolution(A, A);
    }

    for(int i = 0; i < (int)ret.size(); ++i) if(ret[i].real() > 0) cout << i << ' ';

    return 0;
}