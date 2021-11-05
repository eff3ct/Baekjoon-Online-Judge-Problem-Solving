#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define MAX 200001

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
void product(vector<cpx>& A, vector<cpx>& ret) {
    //get n, which satisfies n > 2 ^ ceil(log_2(size)) (when n = 2^k)
    int n = ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    ret.resize(n);

    //n th root of unity (euler formula)
    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));
    FFT(A, w);

    //multiply DFT
    for(int i = 0; i < n; ++i) ret[i] = A[i] * A[i];

    //Inverse FFT to get Coefficient
    FFT(ret, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        ret[i] /= cpx(n, 0);
        ret[i] = cpx(round(ret[i].real()), round(ret[i].imag()));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<cpx> knob(MAX);
    for(int i = 0; i < N; ++i) {
        int tmp; cin >> tmp;
        knob[tmp] = cpx(1, 0);
    }

    knob[0] = cpx(1, 0);

    vector<cpx> prod;

    product(knob, prod);

    int res = 0;
    int M; cin >> M;

    for(int i = 0; i < M; ++i) {
        int dist; cin >> dist;
        if(prod[dist].real() > 0) res++;
    }

    cout << res;

    return 0;
}