#include <iostream>

using namespace std;

int main() {
    char symb;
    long double M = -1;
    string ans;
    while (cin >> symb) {
        int n = 0, cORg = 0;
        string t;
        cin >> t;
        while (cin >> symb) {
            if (symb == '>') break;
            if (symb == 'C' || symb == 'G') cORg++;
            n++;
        }
        long double percentage = ((long double) cORg) / n;
        if (percentage > M) {
            M = percentage;
            ans = t;
        }
    }
    cout << ans << '\n' << 100 * M;
    return 0;
}
