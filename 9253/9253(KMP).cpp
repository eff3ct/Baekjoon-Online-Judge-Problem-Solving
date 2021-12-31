#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getFail(vector<int>& fail, string& str) {
    for(int i = 1, j = 0; i < (int)str.size(); ++i) {
        while(j && str[i] != str[j]) j = fail[j - 1];
        if(str[i] == str[j]) fail[i] = ++j;
    }
}

bool isExist(string& str, string& segStr, vector<int>& fail) {
    for(int i = 0, j = 0; i < (int)str.length(); ++i) {
        while(j && str[i] != segStr[j]) j = fail[j - 1];

        if(str[i] == segStr[j]) {
            if(j == (int)segStr.length() - 1) return true;
            else j++;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a, b, c; cin >> a >> b >> c;

    int aLength = (int)a.length();
    int bLength = (int)b.length();
    int cLength = (int)c.length();

    vector<int> fail(cLength);
    getFail(fail, c);

    (isExist(a, c, fail) && isExist(b, c, fail)) ? cout << "YES" : cout << "NO";

    return 0;
}