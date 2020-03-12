#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1, 0);
    a[1] = 1;
    for (int i = 2; i <= n; i++) a[i] = a[i - 1] + a[i - 2] * k;
    cout << a[n];
    return 0;
}
