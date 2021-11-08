#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int A, B; cin >> A >> B;
    int x1 = (double)(-A) - sqrt(A * A  - B);
    int x2 = (double)(-A) + sqrt(A * A  - B);

    if(x1 == x2) cout << x1;
    else cout << x1 << " " << x2;

    return 0;
}