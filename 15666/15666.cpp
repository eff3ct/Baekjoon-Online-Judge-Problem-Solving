// https://www.acmicpc.net/problem/15666 //
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

bool isValid(const vector<int>& picked, map<int, bool>& check) {
    int size = picked.size();
    int number = 0;
    for(int i = 0; i < size; ++i) {
        number += picked[i] * pow(10, i);
    }
    if(check.find(number) == check.end()) {
        check.insert({number, true});
        return true;
    }
    else return false;    
}

void printPicked(vector<int>& picked) {
    int size = picked.size();
    for(int i = 0; i < size; ++i) {
        cout << picked[i] << " ";
    }
    cout << "\n";
}

void solve(int N, int M, vector<int>& picked, vector<int>& seq, map<int, bool>& check, int lastElement) {
    if(M == 0) {
        if(isValid(picked, check)) {
            printPicked(picked);
        }
        return;
    }

    int lowBound = (lastElement == -1) ? 0 : lastElement;

    for(int i = lowBound; i < N; ++i) {
        picked.push_back(seq[i]);
        solve(N, M - 1, picked, seq, check, i);
        picked.pop_back();
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> v, seq;
    map<int, bool> check;
    for(int i = 0; i < N; ++i) {
        int tmp;
        cin >> tmp;
        seq.push_back(tmp);
    }
    sort(seq.begin(), seq.end());
    solve(N, M, v, seq, check, -1);
    return 0;
}