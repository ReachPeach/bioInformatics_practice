#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long ans = 1;
    cin >> n;
    vector<int> a;
    for (int i = 1; i <= n; i++) {
        a.push_back(i);
        ans *= i;
    }
    cout << ans << '\n';
    do {
        for (auto &x : a) cout << x << " ";
        cout << '\n';
    } while (next_permutation(a.begin(), a.end()));
    return 0;
}
