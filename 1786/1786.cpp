#include <iostream>
#include <vector>
#include <string>

using namespace std;

void getFail(string& P, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)P.length(); ++i) {
        while(j && P[i] != P[j]) j = fail[j - 1];
        if(P[i] == P[j]) fail[i] = ++j;
    }
}

void solve(string& T, string& P) {
    int Tlength = (int)T.length();
    int Plength = (int)P.length();

    vector<int> fail(Plength);
    getFail(P, fail);

    vector<int> ret;

    for(int i = 0, j = 0; i < Tlength; ++i) {
        while(j && T[i] != P[j]) j = fail[j - 1];

        if(T[i] == P[j]) {
            if(j == Plength - 1) {
                ret.push_back(i - Plength + 2);
                j = fail[j];
            }
            else j++;
        }
    }

    cout << (int)ret.size() << '\n';
    for(auto& element : ret) cout << element << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string T; getline(cin, T, '\n');
    string P; getline(cin, P, '\n');

    solve(T, P);

    return 0;
}