#include <iostream>
#include <string>

using namespace std;

int main() {
    string X; cin >> X;
    int cnt = 0;
    while((int)X.size() != 1) {
        cnt++;
        int convert = 0;
        for(int i = 0; i < (int)X.size(); ++i) convert += X[i] - '0';
        X = to_string(convert);
    }

    cout << cnt << '\n';
    if(stoi(X) % 3 == 0) cout << "YES";
    else cout << "NO";

    return 0;
}