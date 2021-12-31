#include <iostream>
#include <vector>
#define MOD 100000007LL

using namespace std;
typedef long long ll;

typedef struct _Matrix{
    int N;
    vector<vector<ll>> matrix;

    _Matrix(int X) {
        N = X;
        matrix.resize(N, vector<ll>(N));
    } // x by x matrix

    _Matrix operator*(const _Matrix& A) {
        _Matrix ret(N);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                for(int k = 0; k < N; ++k) {
                    ret.matrix[i][j] += (matrix[i][k] * A.matrix[k][j]) % MOD;
                }
            }
        }
        return ret;
    }

} Matrix;


Matrix power(Matrix A, int N) {
    if(N == 0) {
        Matrix I(A.N);
        for(int i = 0; i < A.N; ++i) I.matrix[i][i] = 1;
        return I;
    }

    if(N & 1) return A * power(A, N - 1);

    Matrix tmp = power(A, N / 2);
    return tmp * tmp;
}

int main() {
    int T; cin >> T;

    while(T --> 0) {
        int K, N; cin >> K >> N;
        Matrix r(K + 1);
        for(int i = 1; i <= K; ++i) r.matrix[i][i - 1] = 1;
        r.matrix[0][0] += 1, r.matrix[0][K] += 1;

        r = power(r, N);

        cout << r.matrix[0][0] % MOD << '\n';
    }

    return 0;
}