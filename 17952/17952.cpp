#include <iostream>
#include <stack>
#include <utility>

using namespace std;

int main() {
    int ret = 0;
    int N; cin >> N;
    stack<pair<int, int>> stk;
    int score = 0, time = 0;
    for(int i = 0; i < N; ++i) {
        int cmd; cin >> cmd;
        
        if(cmd == 1) {
            if(time > 0) stk.push({score, time});
            cin >> score >> time;

            if(--time == 0) {
                ret += score;

                if(!stk.empty()) {
                    score = stk.top().first;
                    time = stk.top().second;
                    stk.pop();
                }
            }
        }
        else {
            if(--time == 0) {
                ret += score;
                if(!stk.empty()) {
                    score = stk.top().first;
                    time = stk.top().second;
                    stk.pop();
                }
            }
        }
    }

    cout << ret;

    return 0;
}