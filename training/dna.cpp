//
// Created by Максим on 24.02.2020.
//

#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    long long count[4] = {0, 0, 0, 0};
    // A - 0 ; C - 1; G - 2; T - 3;
    for (auto &c : s) {
        if (c == 'A') count[0]++;
        if (c == 'C') count[1]++;
        if (c == 'G') count[2]++;
        if (c == 'T') count[3]++;
    }
    for (long long i : count) cout << i << " ";
    return 0;
}