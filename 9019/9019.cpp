// https://www.acmicpc.net/problem/9019 //
#include <iostream>
#include <string>
#include <utility>
#include <queue>

using namespace std;

string BFS(int A, int B) {
    bool visit[10000];
    fill_n(visit, 10000, false);
    visit[A] = true;

    queue<pair<int, string>> q;
    q.push({ A, "" });

    while(!q.empty()) {
        pair<int, string> now = q.front();
        int n = now.first;
        string cmd = now.second;
        q.pop();

        //case D
        if(2 * n <= 9999) {
            if(!visit[2 * n]) {
                if(2 * n == B) {
                    return (cmd + "D");
                }
                visit[2 * n] = true;
                q.push({ 2 * n, cmd + "D" });
            }
            
        }
        else {
            if(!visit[(2 * n) % 10000]) {
                if(((2 * n) % 10000) == B) {
                    return (cmd + "D");
                }
                visit[(2 * n) % 10000] = true;
                q.push({ (2 * n) % 10000, cmd + "D" });
            }
        }
        //case S
        if(n != 0) {
            if(!visit[n - 1]) {
                if((n - 1) == B) {
                    return (cmd + "S");
                }
                visit[n - 1] = true;
                q.push({ n - 1, cmd + "S" });
            }
        }
        else {
            if(!visit[9999]) {
                if(9999 == B) {
                    return (cmd + "S");
                }
                visit[9999] = true;
                q.push({ 9999, cmd + "S" });
            }
        }
        int d1, d2, d3, d4;
        d1 = (int)n / 1000;
        d2 = (int)n / 100 - d1 * 10;
        d3 = (int)n / 10 - d2 * 10 - d1 * 100;
        d4 = n % 10;

        int LShifted = ((d2 * 10 + d3) * 10 + d4) * 10 + d1;
        int RShifted = ((d4 * 10 + d1) * 10 + d2) * 10 + d3;
        //case L
        if(!visit[LShifted]) {
            if(LShifted == B) {
                return (cmd + "L");
            }
            visit[LShifted] = true;
            q.push({ LShifted, cmd + "L" }); 
        }
        //case R
        if(!visit[RShifted]) {
            if(RShifted == B) {
                return (cmd + "R");
            }
            visit[RShifted] = true;
            q.push({ RShifted, cmd + "R" });
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;

    for(int i = 0; i < T; ++i) {
        int A, B;
        cin >> A >> B;
        cout << BFS(A, B) << "\n";
    }

    return 0;
}