#include <iostream>

using namespace std;

int main() {
    long double n, k, m;
    cin >> k >> m >> n;
    long double ans = 1 - (n * (n - 1) + n * m + m * (m - 1) / 4) / ((k + m + n) * (k + m + n - 1));
    cout << ans;
    return 0;
}
