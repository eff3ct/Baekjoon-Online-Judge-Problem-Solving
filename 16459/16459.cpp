#include <iostream>
#include <string>

using namespace std;

int main() {
    string str, temp;
    while(true) {
        getline(cin, temp, '\n');
        if(temp == "0") break;
        
        str += temp + '\n';
    }

    string who, where, what;
    getline(cin, who, '\n');
    getline(cin, where, '\n');
    getline(cin, what, '\n');

    for(int i = 0; i < (int)str.size(); ++i) {
        if(str[i] == 'W') {
            if(i + 2 < (int)str.size() && str.substr(i, 3) == "WHO") {
                str = str.substr(0, i) + who + str.substr(i + 3);
                i = -1;
            }
            else if(i + 4 < (int)str.size() && str.substr(i, 5) == "WHERE") {
                str = str.substr(0, i) + where + str.substr(i + 5);
                i = -1;
            }
            else if(i + 3 < (int)str.size() && str.substr(i, 4) == "WHAT") {
                str = str.substr(0, i) + what + str.substr(i + 4);
                i = -1;
            }
        }
    }

    cout << str;

    return 0;
}