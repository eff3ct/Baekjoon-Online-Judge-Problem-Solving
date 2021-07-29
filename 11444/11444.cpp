// https://www.acmicpc.net/problem/11444 //
#include <iostream>
#include <vector>

#define DNM 1000000007

using namespace std;
typedef long long ll;

class Matrix {
    private:
        vector<ll> m[2];
    
    public:
        Matrix() {
            m[0] = {1, 1};
            m[1] = {1, 0};
        }
        Matrix(char i) {
            if(i == 'I') {
                m[0] = {1, 0};
                m[1] = {0, 1};
            }
        }
        void printAns() {
            cout << m[0][1];
        }
        Matrix operator*(Matrix &a) {
            Matrix result;
            result.m[0][0] = (m[0][0] * a.m[0][0] + m[0][1] * a.m[1][0]) % DNM;
            result.m[0][1] = (m[0][0] * a.m[0][1] + m[0][1] * a.m[1][1]) % DNM;
            result.m[1][0] = (m[1][0] * a.m[0][0] + m[1][1] * a.m[1][0]) % DNM;
            result.m[1][1] = (m[1][0] * a.m[0][1] + m[1][1] * a.m[1][1]) % DNM;
            return result;
        }
};

int main() {
    ll n; cin >> n;
    Matrix fibMatrix, result('I');
    while(true) {
        if(n == 0) break;

        if(n % 2) result = result * fibMatrix;

        fibMatrix = fibMatrix * fibMatrix;

        n /= 2;
    }
    result.printAns();
    return 0;
}