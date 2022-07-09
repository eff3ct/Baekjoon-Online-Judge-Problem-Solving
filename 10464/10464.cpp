#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T --> 0) {
        int S, F; cin >> S >> F;
        int cS = 0;
        int cF = 0;

        if(F % 4 == 2) cF = F ^ (F - 1) ^ (F - 2);
        else if(F % 4 == 1) cF = F ^ (F - 1);
        else if(F % 4 == 0) cF = F;

        S--;
        if(S % 4 == 2) cS = S ^ (S - 1) ^ (S - 2);
        else if(S % 4 == 1) cS = S ^ (S - 1);
        else if(S % 4 == 0) cS = S;

        cout << (cS ^ cF) << '\n';
    }

    return 0;
}