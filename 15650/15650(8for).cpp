// https://www.acmicpc.net/problem/15650 //
#include <iostream>

using namespace std;

int main() {
    int N, M, depth;
    cin >> N >> M;

    for(int a1 = 1; a1 <= (N - M + 1); a1++) {
        depth = 1;
        if(depth == M) cout << a1 << "\n";
        for(int a2 = a1 + 1; a2 <= (N - M + 2); a2++) {
            depth = 2;
            if(depth == M) cout << a1 << " " << a2 << "\n";
            for(int a3 = a2 + 1; a3 <= (N - M + 3); a3++) {
                depth = 3;
                if(depth == M) cout << a1 << " " << a2 << " " << a3 << "\n";
                for(int a4 = a3 + 1; a4 <= (N - M + 4); a4++) {
                    depth = 4;
                    if(depth == M) cout << a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
                    for(int a5 = a4 + 1; a5 <= (N - M + 5); a5++) {
                        depth = 5;
                        if(depth == M) cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << "\n";
                        for(int a6 = a5 + 1; a6 <= (N - M + 6); a6++) {
                            depth = 6;
                            if(depth == M) cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << a6 << "\n";
                            for(int a7 = a6 + 1; a7 <= (N - M + 7); a7++) {
                                depth = 7;
                                if(depth == M) cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << a6 << " " << a7 << "\n";
                                for(int a8 = a7 + 1; a8 <= (N - M + 8); a8++) {
                                    depth = 8;
                                    if(depth == M) cout << a1 << " " << a2 << " " << a3 << " " << a4 << " " << a5 << " " << a6 << " " << a7 << " " << a8 << "\n";
                                    
                                }
                            }
                        }
                    }  
                }
            }
        }
    }

    return 0;
}