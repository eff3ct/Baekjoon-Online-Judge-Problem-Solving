#pragma GCC optimize ("Ofast")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,avx,avx2")

#include <bits/stdc++.h>

using namespace std;
typedef complex<double> cpx;
using ll = long long;

vector<int> ans;

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
void solve_product(vector<cpx>& A, vector<cpx>& B, int N, int M) {
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

    for(int i = 0; i < N; ++i) 
        ans[i] += C[M - 1 + i].real();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    string n_str, m_str; cin >> n_str >> m_str;

    ans.resize(n);

    //rock
    vector<cpx> n_rock(n);
    vector<cpx> m_rock(m);  
    for(int i = 0; i < n; ++i) 
        n_rock[i] = {double(n_str[i] == 'S'), 0};
    for(int i = 0; i < m; ++i) 
        m_rock[i] = {double(m_str[m - i - 1] == 'R'), 0};
    solve_product(n_rock, m_rock, n, m);

    //scissors
    vector<cpx> n_scissors(n);
    vector<cpx> m_scissors(m);  
    for(int i = 0; i < n; ++i) 
        n_scissors[i] = {double(n_str[i] == 'P'), 0};
    for(int i = 0; i < m; ++i) 
        m_scissors[i] = {double(m_str[m - i - 1] == 'S'), 0};
    solve_product(n_scissors, m_scissors, n, m);

    //paper
    vector<cpx> n_paper(n);
    vector<cpx> m_paper(m);  
    for(int i = 0; i < n; ++i) 
        n_paper[i] = {double(n_str[i] == 'R'), 0};
    for(int i = 0; i < m; ++i) 
        m_paper[i] = {double(m_str[m - i - 1] == 'P'), 0};
    solve_product(n_paper, m_paper, n, m);

    cout << *max_element(ans.begin(), ans.end()) << '\n';

    return 0;
}