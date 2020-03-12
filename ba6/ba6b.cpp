#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    char x;
    vector<int> a;
    cin >> x;
    int y;
    a.push_back(0);
    while (cin >> x >> y) {
        if (x == '-') y = -y;
        a.push_back(y);
    }
    a.push_back(a.size());
    y = 0;
    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i + 1] - a[i] != 1) y++;
    }
    cout << y;

    return 0;
}
