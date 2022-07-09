#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

void getFail(string& str, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)str.length(); ++i) {
        while(j && str[i] != str[j]) j = fail[j - 1];
        if(str[i] == str[j]) fail[i] = ++j;
    }
}

bool isExistOnce(string& str, string& segStr, vector<int>& fail) {
    int ret = 0;
    for(int i = 0, j = 0; i < (int)str.length(); ++i) {
        while(j && str[i] != segStr[j]) j = fail[j - 1];

        if(str[i] == segStr[j]) {
            if(j == (int)segStr.length() - 1) {
                ret++;
                j = fail[j];
            }
            else j++;
        }
    }

    return (ret == 1) ? true : false;
}

void solve(string& order, string& origin, string& encoded, int* seq) {
    int sz = (int)order.length();

    vector<int> fail((int)origin.length());
    getFail(origin, fail);

    vector<int> ret;
    for(int i = 0; i < sz; ++i) {
        string compStr(encoded);
        for(int j = 0; j < (int)encoded.length(); ++j) compStr[j] = order[(seq[(int)encoded[j]] - i + sz) % sz];
        if(isExistOnce(compStr, origin, fail)) ret.push_back(i);
    }

    if((int)ret.size() == 1) cout << "unique: " << ret[0] << '\n';
    else if((int)ret.size() >= 2) {
        cout << "ambiguous:";
        for(auto& element : ret) cout << ' ' << element;
        cout << '\n';
    }
    else cout << "no solution\n";
}

int main() {
    int T; cin >> T;

    while(T --> 0) {
        string order, origin, encoded;
        cin >> order >> origin >> encoded;

        int seq[200];
        for(int i = 0; i < (int)order.size(); ++i) seq[(int)order[i]] = i;

        solve(order, origin, encoded, seq);
    }

    return 0;
}