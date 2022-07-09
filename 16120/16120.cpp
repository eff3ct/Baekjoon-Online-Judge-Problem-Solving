#include <bits/stdc++.h>

using namespace std;

char stk[1000010];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str; cin >> str;

    stk[0] = str[0];
    if(int(str.size()) > 1) stk[1] = str[1];
    
    int idx = 2;
    for(int i = 2; i < int(str.size()); ++i) {
        bool isPPA = false;
        if(idx >= 3) isPPA = (stk[idx - 3] == 'P' && stk[idx - 2] == 'P' && stk[idx - 1] == 'A');
        if(isPPA && str[i] == 'P') idx -= 2;
        else stk[idx++] = str[i];
    }

    if(idx == 1 && stk[0] == 'P' || (int(str.size()) == 1 && str[0] == 'P')) cout << "PPAP\n";
    else cout << "NP\n";

    return 0;
}