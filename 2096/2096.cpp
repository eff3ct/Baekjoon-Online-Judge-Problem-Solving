// https://www.acmicpc.net/problem/2096 //
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N; cin >> N;
    int a, b, c; cin >> a >> b >> c;
    int minA = a, minB = b, minC = c;

    int resA = a, resB = b, resC = c;
    int resMinA = a, resMinB = b, resMinC = c;

    for(int i = 1; i < N; ++i) {
        int tmpA, tmpB, tmpC; cin >> tmpA >> tmpB >> tmpC;

        resA = max(a, b) + tmpA;
        resB = max({a, b, c}) + tmpB;
        resC = max(b, c) + tmpC;

        a = resA; b = resB; c = resC;

        resMinA = min(minA, minB) + tmpA;
        resMinB = min({minA, minB, minC}) + tmpB;
        resMinC = min(minB, minC) + tmpC;

        minA = resMinA; minB = resMinB; minC = resMinC;
    }

    cout << max({resA, resB, resC}) << " " << min({resMinA, resMinB, resMinC});

    return 0;
}