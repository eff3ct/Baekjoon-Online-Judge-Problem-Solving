// https://www.acmicpc.net/problem/1065 //
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void solve(int N) {
    int res = 0;
    for(int i = 1; i <= N; ++i) {
        int x = i;
        string xStr = to_string(x);
        
        if(xStr.size() == 1 || xStr.size() == 2) {
            res += 1;
            continue;
        }

        int d = xStr[1] - xStr[0];
        bool check = false;
        for(int j = 0; j < xStr.size() - 1; ++j) {
            if(d != xStr[j + 1] - xStr[j]) check = true;
        }

        if(!check) {
            res += 1;
        }
    }
    cout << res;
}

int main() {
    int N; cin >> N;
    solve(N);
    return 0;
}