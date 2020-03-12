#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string s, t;
    cin >> s;
    reverse(s.begin(), s.end());
    for (auto &c : s) {
        if (c == 'T' || c == 'A') t.push_back((char) ('A' + 'T' - c));
        if (c == 'G' || c == 'C') t.push_back((char) ('G' + 'C' - c));
    }
    cout << t;
    return 0;
}
