#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string name, sex;
    int dist;
    cin >> name >> sex >> dist;

    vector<string> ret;
    int n; cin >> n;
    while(n --> 0) {
        string p_name, p_sex;
        int p_dist;
        cin >> p_name >> p_sex >> p_dist;

        if(((int)sex.length() == 2 || sex == p_sex) && p_dist <= dist) ret.push_back(p_name);
    }

    if(ret.empty()) cout << "No one yet";
    else {
        sort(ret.begin(), ret.end());
        for(auto& n : ret) cout << n << '\n';
    }

    return 0;
}