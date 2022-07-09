#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    /*input*/
    int M, N, B; cin >> N >> M >> B;

    vector<vector<int>> h(N, vector<int>(M));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            cin >> h[i][j];
        }
    }

    /*brute-force algorithm*/
    int ans_time = 987654321; //답으로 저장할 시간
    int ans_height = -1; //답으로 저장할 높이
    
    //시간복잡도 O(NMH) (N = row, M = column, H = height)
    //500 * 500 * 256번 반복을 도니 1초안에 풀려요. (보통 컴퓨터는 1억번 연산을 1초만에 계산합니다.)
    for(int cur_height = 0; cur_height <= 256; ++cur_height) {
        int cur_item = B; //현재 가지고 있는 블록의 개수
        int cur_time = 0; //현재 걸린 시간

        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < M; ++c) {
                //현재 만드려는 높이보다 (r, c)지점의 높이가 더 큰 경우, 그 차이만큼 블록을 캐야합니다. (블록마다 2초 걸림)
                //그렇지 않고 (r, c)지점의 높이가 더 작은 경우, 그 차이만큼 블록을 설치해야합니다. (블록마다 1초 걸림)
                //이 과정에서 cur_item, cur_time을 각각 따로 관리 해주셔야 해요.
            }
        }

        if(cur_item < 0) continue; //현재 아이템 개수가 음수면 불가능한 경우니 패스!
        else if(/*어떤 조건이 들어가야할까요?*/) {
            //답을 갱신해줍니다.
        }
    }

    /* output */
    cout << ans_time << ' ' << ans_height << '\n';

    return 0;
}