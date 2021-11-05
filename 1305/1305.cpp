#include <iostream>
#include <string>
#include <vector>

using namespace std;

void getFail(int& N, vector<int>& fail, string& str) {
    for(int i = 1, j = 0; i < N; ++i) {
        while(j && str[i] != str[j]) j = fail[j - 1];
        if(str[i] == str[j]) fail[i] = ++j;
    }
}

void solve(int& L, string& str) {
    vector<int> fail(L);
    getFail(L, fail, str);

    if(fail[L - 1] == 0) cout << L;
    else cout << L - fail[L - 1];
}  

int main() {
    int L; cin >> L;

    string str; cin >> str;

    solve(L, str);

    return 0;
}