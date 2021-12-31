#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

typedef struct _Matrix {
    vector<vector<ll>> m;

    _Matrix() {
        m.resize(8, vector<ll>(8, 0));
    }

    _Matrix operator*(const _Matrix a) {
        _Matrix ret;

        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                for(int k = 0; k < 8; ++k) {
                    ret.m[i][j] += m[i][k] * a.m[k][j] % MOD;
                    ret.m[i][j] %= MOD;
                }
            }
        }

        return ret;
    }

    void make_id() {
        for(int i = 0; i < 8; ++i) m[i][i] = 1;
    }
} Matrix;

Matrix power(Matrix x, int n) {
    if(n == 0) {
        Matrix id_mat;
        id_mat.make_id();
        return id_mat;
    }

    if(n & 1) return x * power(x, n - 1);
    else {
        Matrix tmp = power(x, n / 2);
        return tmp * tmp;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Matrix case_matrix;
    case_matrix.m = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 1, 0},
    };

    int D; cin >> D;
    Matrix ret = power(case_matrix, D);
    cout << ret.m[0][0];

    return 0;
}