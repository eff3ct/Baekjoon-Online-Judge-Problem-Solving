// https://www.acmicpc.net/problem/19541 //
// UCPC 2020 Qualifier J //
#include <iostream>
#include <vector>

using namespace std;

void solve(vector<vector<int>>& meet, vector<int>& iInfo, int N, int M);

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> mt; //meeting
    for(int i = 0; i < M; ++i) {
        vector<int> mtTmp;
        int tmp; cin >> tmp;
        for(int j = 0; j < tmp; ++j) {
            int pInfo; cin >> pInfo;
            mtTmp.push_back(pInfo);
        }
        mt.push_back(mtTmp);
    }

    vector<int> infectedInfo;
    infectedInfo.push_back(-1); //to make start from idx = 1
    for(int i = 1; i <= N; ++i) {
        int infected; cin >> infected;
        infectedInfo.push_back(infected);
    }

    solve(mt, infectedInfo, N, M);

    return 0;
}

void solve(vector<vector<int>>& meet, vector<int>& iInfo, int N, int M) {
    bool* visitCheck = new bool[N + 1];
    fill_n(visitCheck, N + 1, false);

    int* firstInfectedInfo = new int[N + 1];
    fill_n(firstInfectedInfo, N + 1, 1);

    for(int i = M - 1; i >= 0; --i) {
        vector<int> nowMeet = meet[i];
        for(int p : nowMeet) {
            if(iInfo[p] == 0 || firstInfectedInfo[p] == 0) {
                for(int x : nowMeet) {
                    firstInfectedInfo[x] = 0;
                    visitCheck[x] = true;
                }
                break;
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(!visitCheck[i]) firstInfectedInfo[i] = iInfo[i];
    }

    fill_n(visitCheck, N + 1, false);
    int* checkInfected = new int[N + 1];
    fill_n(checkInfected, N + 1, 0);
    for(int i = 0; i < M; ++i) {
        vector<int> nowMeet = meet[i];
        for(int p : nowMeet) {
            if(firstInfectedInfo[p] == 1 || checkInfected[p] == 1) {
                for(int x : nowMeet) {
                    checkInfected[x] = 1;
                    visitCheck[x] = true;
                }
                break;
            }
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(!visitCheck[i]) checkInfected[i] = firstInfectedInfo[i];
    }

    for(int i = 1; i <= N; ++i) {
        if(checkInfected[i] != iInfo[i]) {
            cout << "NO";
            return;
        }
    }
    cout << "YES" << "\n";
    for(int i = 1; i <= N; ++i) {
        cout << firstInfectedInfo[i] << " ";
    }

    delete[] visitCheck;
    delete[] firstInfectedInfo;
    delete[] checkInfected;
}