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

vector<cpx> solve(vector<cpx>& A, vector<cpx>& B) {
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

    return C;    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll N, I, M, W; cin >> N >> I >> M >> W;
    vector<vector<cpx>> T(M, vector<cpx>(N));
    vector<vector<cpx>> P(M, vector<cpx>(N));

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            int x; cin >> x;
            T[i][j] = cpx(x, 0);
        }
    }

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < I; ++j) {
            int x; cin >> x;
            P[i][I - 1 - j] = cpx(x, 0);
        }
    }

    vector<ll> total_w(N);
    for(ll i = 0; i < M; ++i) {
        vector<cpx> w_i = solve(T[i], P[i]);
        for(int j = I - 1; j <= N - 1; ++j) {
            total_w[j] += (ll)w_i[j].real();
        }
    }

    ll cnt = 0;
    for(ll i = I - 1; i <= N - 1; ++i) {
        if(total_w[i] > W) cnt++;
    }

    cout << cnt << '\n';

    return 0;
}