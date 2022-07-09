#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;
typedef pair<int, int> pii;

int main() {
    int M, t, N;
    cin >> M >> t >> N;

    int lr = 0;
    int now_time = 0;

    vector<int> end_time(N);

    queue<pii> left;
    queue<pii> right;

    for(int i = 0; i < N; ++i) {
        int time; string dir;
        cin >> time >> dir;
        if(dir == "left") left.push({time, i});
        else right.push({time, i});
    }
    
    while(true) {
        int cnt = 0;
        bool flag = false;

        //배에 태울 인원이 있으면 모두 태운다.
        while(cnt < M && !(lr ? right : left).empty() && (lr ? right : left).front().first <= now_time) {
            flag = true;
            end_time[(lr ? right : left).front().second] = now_time + t;
            (lr ? right : left).pop();
            cnt++;
        }

        if(left.empty() && right.empty()) break; //모두 태운 경우

        //태웠으니 반대쪽으로 이동
        if(flag) {
            now_time += t;
            lr ^= 1;
        }
        else { //안태운 경우?
            auto& l = (lr ? right : left);
            auto& r = (lr ? left : right);
            if(l.empty() && !r.empty()) { //왼쪽은 없고 오른쪽만 있는 경우
                now_time = max(now_time, r.front().first) + t; 
                lr ^= 1; //오른쪽 이동
            }
            else if(!l.empty() && r.empty()) now_time = l.front().first; //왼쪽에 있고 오른쪽에 없는 경우
            else if(!l.empty() && !r.empty()) { //왼쪽 오른쪽 둘다
                if(now_time >= r.front().first) { //오른쪽 대기자가 있는 경우
                    now_time += t;
                    lr ^= 1; //오른쪽 이동
                }
                else if(l.front().first <= r.front().first) now_time = l.front().first; //왼쪽이 더 빠른 경우
                else if(l.front().first > r.front().first) { //오른쪽이 더 빠른 경우
                    now_time = r.front().first + t;
                    lr ^= 1;
                } //오른쪽 이동
            }
        }
    }

    for(auto& e : end_time) cout << e << '\n';

    return 0;
}