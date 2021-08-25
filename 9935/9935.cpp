// https://www.acmicpc.net/problem/9935 //
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string strBomb(string original, string bomb) {
    string ret;
    for(int i = 0; i < original.size(); ++i) {
        ret += original[i];
        if(ret.size() >= bomb.size() && ret[ret.size() - 1] == bomb[bomb.size() - 1]) {
            if(ret.substr(ret.size() - bomb.size(), bomb.size()) == bomb) {
                ret.erase(ret.size() - bomb.size(), bomb.size());
            }
        }
    }

    if(ret.size() == 0) ret = "FRULA";
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string original, bomb;
    cin >> original >> bomb;
    cout << strBomb(original, bomb);
    return 0;
}
