#include <bits/stdc++.h>

using namespace std;

int main() {
    string str; cin >> str;
    stack<int> stk;

    stk.push(0);

    int now = 0;
    for(int i = 0; i < int(str.size()); ++i) {
        switch(str[i]) {
            case '(':
                stk.push(0);
                break;

            case ')':
                now = stk.top();
                stk.pop();
                stk.top() += now;
                break;

            case 'H':
                now = 1;
                stk.top() += 1;
                break;

            case 'C':
                now = 12;
                stk.top() += 12;
                break;

            case 'O':
                now = 16;
                stk.top() += 16;
                break;

            default:
                stk.top() += now * (str[i] - '1');
                break;
        }
    }

    cout << stk.top();

    return 0;
}