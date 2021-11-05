#include <iostream>
#include <vector>
#include <string>

using namespace std;

void getFail(string& K, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)K.size(); ++i) {
        while(j && K[i] != K[j]) j = fail[j - 1];
        if(K[i] == K[j]) fail[i] = ++j;
    }
}

void KMP(string& S, string& K, vector<int>& fail) {
    for(int i = 0, j = 0; i < (int)S.size(); ++i) {
        while(j && S[i] != K[j]) j = fail[j - 1];
        if(S[i] == K[j]) {
            if(j == (int)K.size() - 1) {
                cout << 1;
                return;
            }
            else j++;
        }
    }
    cout << 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S, K; cin >> S >> K;

    string convertedS;
    for(int i = 0; i < (int)S.size(); ++i) {
        if(!('0' <= S[i] && S[i] <= '9')) convertedS += S[i];
    }

    vector<int> fail((int)K.size());
    getFail(K, fail);

    KMP(convertedS, K, fail);

    return 0;
}