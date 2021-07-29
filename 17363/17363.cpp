// https://www.acmicpc.net/problem/17363 //
// UCPC 2019 Qualifier B //
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<char> aya = {'|', '-', 92, '/', '<', 'v', '>', '^'};
vector<char> rot = {'-', '|', '/', 92, '^', '<', 'v', '>'};

vector<char> map[101];

char rotateLeft(char c) {
    for(int i = 0; i < 8; ++i) {
        if(c == rot[i]) {
            return aya[i];
        }
    }
    return c;
}

int main() {
    int N, M; cin >> N >> M;
    for(int y = 0; y < N; ++y) {
        string tmp; cin >> tmp;
        for(int x = 0; x < M; ++x) {
            char rotatedValue = rotateLeft(tmp[x]);
            map[y].push_back(rotatedValue);
        }
    }

    for(int x = M - 1; x >= 0; --x) {
        for(int y = 0; y < N; ++y) {
            cout << map[y][x];
        }
        cout << '\n';
    }

    return 0;
}