// https://www.acmicpc.net/problem/15657 //
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printPicked(vector<int>& picked) {
    int size = picked.size();
    for(int i = 0; i < size; ++i) {
        cout << picked[i] << " ";
    }
    cout << "\n";
}

void solve(int N, int M, vector<int>& picked, vector<int>& seq, int lastElement) {
    static bool visit[10] = { false, };
    if(M == 0) {
        printPicked(picked);
        return;
    }

    int lowBound = (lastElement == -1) ? 0 : lastElement;

    for(int i = lowBound; i < N; ++i) {
        picked.push_back(seq[i]);
        solve(N, M - 1, picked, seq, i);
        picked.pop_back();
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> v, seq;
    for(int i = 0; i < N; ++i) {
        int tmp;
        cin >> tmp;
        seq.push_back(tmp);
    }
    sort(seq.begin(), seq.end());
    solve(N, M, v, seq, -1);
    return 0;
}