#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getFail(string& str, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)str.size(); ++i) {
        while(j && str[i] != str[j]) j = fail[j - 1];
        if(str[i] == str[j]) fail[i] = ++j;
    }
}

void solve(string& str) {
    vector<int> fail((int)str.length());
    getFail(str, fail);

    int size = (int)str.length();

    double p = (double)size / (size - fail[size - 1]);
    
    if(p == (int)p) cout << (int)p << '\n';
    else cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(true) {
        string str;
        cin >> str;
        
        if(str == ".") break;

        solve(str);
    }

    return 0;
}