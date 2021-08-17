#include <iostream>
#include <cmath>
#include <vector>
#define INF 2000000001

using namespace std;

void solve(vector<int>& seq) {
    int low = seq[0], high = seq.back();
    int a = 0, b = seq.size() - 1;
    int nowSum = low + high;
    int lowest = INF;
    int lowRet, highRet;
    while(true) {
        if(abs(nowSum) < lowest) {
            lowRet = low;
            highRet = high;
            lowest = abs(nowSum);
        }
        if(nowSum > 0) {
            if(b == a + 1) break;
            high = seq[--b];
            nowSum = low + high;
        }
        else if(nowSum < 0) {
            if(a + 1 == b) break;
            low = seq[++a];
            nowSum = low + high;
        }
        else {
            lowRet = low;
            highRet = high;
            break;
        }
    }
    cout << lowRet << " " << highRet;
}

int main() {
    int N; cin >> N;

    vector<int> seq(N);
    for(int i = 0; i < N; ++i) cin >> seq[i];

    solve(seq);

    return 0;
}