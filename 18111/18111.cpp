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
    int ans_time = 987654321; //������ ������ �ð�
    int ans_height = -1; //������ ������ ����
    
    //�ð����⵵ O(NMH) (N = row, M = column, H = height)
    //500 * 500 * 256�� �ݺ��� ���� 1�ʾȿ� Ǯ����. (���� ��ǻ�ʹ� 1��� ������ 1�ʸ��� ����մϴ�.)
    for(int cur_height = 0; cur_height <= 256; ++cur_height) {
        int cur_item = B; //���� ������ �ִ� ����� ����
        int cur_time = 0; //���� �ɸ� �ð�

        for(int r = 0; r < N; ++r) {
            for(int c = 0; c < M; ++c) {
                //���� ������� ���̺��� (r, c)������ ���̰� �� ū ���, �� ���̸�ŭ ����� ĳ���մϴ�. (��ϸ��� 2�� �ɸ�)
                //�׷��� �ʰ� (r, c)������ ���̰� �� ���� ���, �� ���̸�ŭ ����� ��ġ�ؾ��մϴ�. (��ϸ��� 1�� �ɸ�)
                //�� �������� cur_item, cur_time�� ���� ���� ���� ���ּž� �ؿ�.
            }
        }

        if(cur_item < 0) continue; //���� ������ ������ ������ �Ұ����� ���� �н�!
        else if(/*� ������ �����ұ��?*/) {
            //���� �������ݴϴ�.
        }
    }

    /* output */
    cout << ans_time << ' ' << ans_height << '\n';

    return 0;
}