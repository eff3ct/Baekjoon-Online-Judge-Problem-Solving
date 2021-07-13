// https://www.acmicpc.net/problem/16953 //
#include <iostream>

using namespace std;

int solve(int A, int B) {
    int cnt = 0;
    while(true) {
        if(A == B) return (cnt + 1);

        if(B < A) return -1;

        if((B % 2) == 0) {
            B /= 2;
            cnt++;
        }
        else if(((B - 1) % 10) == 0) {
            B = (B - 1) / 10;
            cnt++;
        }
        else return -1;
    }
}

int main() {
    int A, B;
    cin >> A >> B;
    cout << solve(A, B);
    return 0;
}