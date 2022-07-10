#include <bits/stdc++.h>
#define MAX 500'001

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;
using cpx = complex<double>;

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
vector<cpx> product(vector<cpx>& A) {
    int n = ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    vector<cpx> C(n);

    //n th root of unity (euler formula)
    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));
    FFT(A, w);

    //multiply DFT
    for(int i = 0; i < n; ++i) C[i] = A[i] * A[i];

    //Inverse FFT to get Coefficient
    FFT(C, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        C[i] /= cpx(n, 0);
        C[i] = cpx(round(C[i].real()), round(C[i].imag()));
    }

    return C;
}

void get_count(vector<cpx>& A) {
    for(int i = 1; i < MAX; ++i) {
        for(int j = i; j < MAX; j += i) {
            A[j] += 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<cpx> A(MAX);
    get_count(A);

    vector<cpx> convolution = product(A);

    int n; cin >> n;
    while(n --> 0) {
        int l, r; cin >> l >> r;
        
        ll idx = l, ans = 0;
        for(int i = l; i <= r; ++i) {
            if((ll)convolution[i].real() > ans) {
                ans = (ll)convolution[i].real();
                idx = i;
            }
        }
        
        cout << idx << ' ' << ans << '\n';
    }

    return 0;
}