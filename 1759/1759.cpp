    #include <iostream>
    #include <vector>
    #include <algorithm>

    using namespace std;

    vector<char> alphabet;
    vector<char> vowel = {'a', 'e', 'i', 'o', 'u'};
    int L, C;

    void make_perm(int cnt, vector<int> chosen) {
        if(cnt == L) {
            int cnt = 0;
            int a_cnt = 0;
            for(auto& e : chosen) {
                bool flag = false;
                for(auto& x : vowel) {
                    if(alphabet[e] == x) {
                        cnt++;
                        flag = true;
                    }
                }
                if(!flag) a_cnt++;
            }

            if(cnt == 0 || a_cnt < 2) return;

            for(auto& e : chosen) cout << alphabet[e];
            cout << '\n';
            return;
        }

        int lowBound = (chosen.empty()) ? -1 : chosen[(int)chosen.size() - 1];

        for(int i = lowBound + 1; i < C; ++i) {
            chosen.push_back(i);
            make_perm(cnt + 1, chosen);
            chosen.pop_back();
        }
    }

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        cin >> L >> C;
        
        alphabet.resize(C);
        for(int i = 0; i < C; ++i) cin >> alphabet[i];
        sort(alphabet.begin(), alphabet.end());

        vector<int> chosen;
        make_perm(0, chosen);

        return 0;
    }
}