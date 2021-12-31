#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    int N; cin >> N;
    int ret = 0;
    int count = N;
    while(N --> 0) {
        string scr; cin >> scr;
        for(int i = 0; i < (int)scr.size(); ++i) {
            if(scr[i] == '0' || scr[i] == '9' || scr[i] == '6') scr[i] = '9';
        }
        ret += min(stoi(scr), 100);
    }
    cout << int(round((double)ret / count));

    return 0;
}