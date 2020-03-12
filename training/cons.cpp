#include <iostream>
#include <vector>

using namespace std;

int main() {
    char symb;
    string s, t;
    int n;
    vector<int> count[4];
    for (int i = 0; i < 4; i++) count[i].assign(1000 + 10, 0);
    while (true) {
        cin >> t;
        int i = 0;
        char x;
        while (cin >> x && x != '>') {
            if (x == 'A') count[0][i]++;
            if (x == 'C') count[1][i]++;
            if (x == 'G') count[2][i]++;
            if (x == 'T') count[3][i]++;
            i++;
            if (x == '!') break;
        }
        n = i;
        if (x != '>') break;
        if (x == '!') break;
    }
    char indToChar[4] = {'A', 'C', 'G', 'T'};
    string ans;
    for (int i = 0; i < n - 1; i++) {
        int M = -1;
        char x = 'X';
        for (int j = 0; j < 4; j++) {
            if (count[j][i] > M) {
                M = count[j][i];
                x = indToChar[j];
            }
        }
        ans.push_back(x);
    }
    cout << ans << endl;
    for (int j = 0; j < 4; j++) {
        cout << indToChar[j] << ": ";
        for (int i = 0; i < n - 1; i++) cout << " " << count[j][i];
        cout << '\n';
    }
    return 0;
}
