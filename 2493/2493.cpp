#include <iostream>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

int main() {
    int N; cin >> N;

    vector<int> ret(N + 1);
    stack<pair<int, int>> stk;
    
    for(int i = 1; i <= N; ++i) {
        int x; cin >> x;
        if(!stk.empty()) {
            int stackTop = stk.top().second;
            if(stackTop < x) {
                while(stackTop <= x) {
                    stk.pop();
                    if(stk.empty()) break;
                    stackTop = stk.top().second;
                }

                if(stk.empty()) {
                    ret[i] = 0;
                    stk.push({i, x});
                }
                else {
                    ret[i] = stk.top().first;
                    stk.push({i, x});
                }
            }
            else {
                ret[i] = stk.top().first;
                stk.push({i, x});
            }
        }
        else {
            stk.push({i, x});
            ret[i] = 0;
        }
    }

    for(int i = 1; i <= N; ++i) cout << ret[i] << ' ';

    return 0;
}