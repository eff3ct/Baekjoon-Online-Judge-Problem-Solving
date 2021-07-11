// https://www.acmicpc.net/problem/1107 //
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define INF 987654321

using namespace std;

int getLength(int n) {
    if(n == 0) return 1;
    return ((int)log10(n) + 1);
}

int getMinimum(int N, const bool (&btn)[10]) {
    while(true) {
        int tmp = N;
        bool endCond = false;
        int size = getLength(tmp);
        for(int i = 0; i < size; ++i) {
            if(!btn[tmp % 10]) {
                endCond = true;
                break;
            }
            tmp /= 10;
        }

        if(endCond) N--;
        else return N;
        
        if(N < 0) return INF;
    }
}

int getMaximum(int N, const bool (&btn)[10]) {
    while(true) {
        int tmp = N;
        bool endCond = false;
        int size = getLength(tmp);
        for(int i = 0; i < size; ++i) {
            if(!btn[tmp % 10]) {
                endCond = true;
                break;
            }
            tmp /= 10;
        }
        
        if(endCond) N++;
        else return N;
    }
}

int solve(int N, int M, const bool (&btn)[10]) {
    if(M == 10) return fabs(N - 100);
    if(M == 9 && btn[0]) {
        return min((int)fabs(N - 100), N + 1);
    }
    int minimum, minCnt, maximum, maxCnt;
    int broken = 0;
    minimum = getMinimum(N, btn);
    maximum = getMaximum(N, btn);
    minCnt = getLength(minimum);
    maxCnt = getLength(maximum);
    int ans = min({fabs(N - 100), fabs(N - minimum) + minCnt, fabs(N - maximum) + maxCnt});
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int tmp;
    bool btn[10];
    fill_n(btn, 10, true);
    for(int i = 0; i < M; ++i) {
        cin >> tmp;
        btn[tmp] = false;
    }

    cout << solve(N, M, btn);
    
    return 0;
}