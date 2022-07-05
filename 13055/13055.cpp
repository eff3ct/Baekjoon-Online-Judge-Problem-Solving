//#pragma GCC optimize ("Ofast")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,avx,avx2")
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
void solve(vector<cpx>& A, vector<cpx>& B, int N) {
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

    for(int i = N - 2; i >= 0; --i) cout << (ll)C[i].real() << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    string str; cin >> str;
    vector<cpx> A(str.size());
    vector<cpx> B(str.size());
    for(int i = 0; i < (int)str.size(); ++i) {
        A[i] = (str[i] == 'B');
        B[i] = (str[i] == 'A');
    }

    reverse(B.begin(), B.end());

    solve(A, B, (int)str.size());

    return 0;
}
