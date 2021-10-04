#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
typedef complex<double> cpx;

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

    cpx w_e(1, 0);

    for(int i = 0; i < n / 2; ++i) {
        A[i] = even[i] + w_e * odd[i];
        A[i + n / 2] = even[i] - w_e * odd[i];
        w_e *= w;
    }
}

void printProduct(vector<cpx>& A) {
    A.resize((int)A.size() + 10);
    for(int i = 0; i <= A.size() - 1; ++i) {
        int up = (int)A[i].real() / 10;
        A[i] = cpx((int)A[i].real() % 10, A[i].imag());
        A[i + 1] += cpx(up, 0);
    }

    int idx = -1;
    for(int i = (int)A.size() - 1; i >= 0; --i) {
        if(real(A[i]) != 0) {
            idx = i;
            break;
        }
    }

    if(idx == -1) {
        cout << 0;
        return;
    }

    for(int i = idx; i >= 0; --i) cout << A[i].real();
}

void product(vector<cpx>& A, vector<cpx>& B) {
    int n = (A.size() <= B.size()) ? ceil(log2((double)B.size())) : ceil(log2((double)A.size()));
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

    printProduct(C);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a, b;
    cin >> a >> b;

    vector<cpx> A((int)a.size());
    vector<cpx> B((int)b.size());

    for(int i = 0; i < (int)a.size(); ++i) A[(int)A.size() - 1 - i] = a[i] - '0';
    for(int i = 0; i < (int)b.size(); ++i) B[(int)B.size() - 1 - i] = b[i] - '0';

    product(A, B);

    return 0;
}