#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a, b, c; cin >> a >> b >> c;

    int aLength = (int)a.length();
    int bLength = (int)b.length();
    int cLength = (int)c.length();

    bool isExist = false;
    for(int i = 0; i < aLength - cLength + 1; ++i) {
        if(a.substr(i, cLength) == c) isExist = true;
    }

    if(isExist) {
        isExist = false;
        for(int i = 0; i < bLength - cLength + 1; ++i) {
            if(b.substr(i, cLength) == c) isExist = true;
        }
    }

    (isExist) ? cout << "YES" : cout << "NO";

    return 0;
}