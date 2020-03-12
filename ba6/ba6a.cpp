#include <iostream>
#include <vector>

using namespace std;

bool check(vector<int> &a) {
    for (int i = 1; i <= a.size(); i++) if (i != a[i - 1]) return false;
    return true;
}

int firstWrong(vector<int> &a) {
    for (int i = 1; i <= a.size(); i++) if (i != a[i - 1]) return i - 1;
}

int findPos(vector<int> &a, int x) {
    for (int i = 1; i <= a.size(); i++) {
        if (abs(a[i - 1]) == x) return i - 1;
    }
}

void show(vector<int> &a) {
    cout << '(';
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > 0) cout << '+';
        cout << a[i];
        if (i != a.size() - 1) cout << " ";
    }
    cout << ")\n";
}

void greedySort(vector<int> &a) {
    if (check(a)) return;

    int pos = firstWrong(a);
    if (a[pos] == -(pos + 1)) {
        a[pos] = -a[pos];
    } else {
        int rev = findPos(a, pos + 1);
        for (int i = pos; i <= (rev + pos) / 2; i++) {
            swap(a[i], a[rev + pos - i]);
            a[i] = -a[i];
            a[rev + pos - i] = -a[rev + pos - i];
        }
        if (!((rev - pos) % 2)) {
            a[(rev + pos) / 2] = -a[(rev + pos) / 2];
        }
    }
    show(a);
    greedySort(a);
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    char x;
    vector<int> a;
    cin >> x;
    int y;
    while (cin >> x >> y) {
        if (x == '-') y = -y;
        a.push_back(y);
    }

    greedySort(a);
    return 0;
}
