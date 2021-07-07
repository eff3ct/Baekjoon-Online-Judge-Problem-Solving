// https://www.acmicpc.net/problem/19539 //
// UCPC 2020 Qualifier H //

#include <iostream>

using namespace std;

void solve(int* height, int N) {
    int oneCnt = 0, twoCnt = 0;
    for(int i = 0; i < N; ++i) {
        if(height[i] % 2) oneCnt++;
        twoCnt += (int)height[i] / 2;
    } //save maximum quotient of two and minimum of one

    while(true) {
        if(twoCnt == oneCnt) { //'oneCnt == twoCnt' means you can grow trees.
            cout << "YES";
            break;
        }
        twoCnt -= 1; //if not, increase oneCnt (2 = 1 * 2)
        oneCnt += 2;
        if(twoCnt < oneCnt) { //if oneCnt is more than twoCnt, it means you can't grow trees.
            cout << "NO";
            break;
        } 
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, height[100001];

    //input
    cin >> N; 
    for(int i = 0; i < N; ++i) {
        cin >> height[i];
    }

    solve(height, N);

    return 0;
}