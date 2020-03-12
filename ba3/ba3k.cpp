#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
#define prefix(x) x.substr(0, x.size() - 1)
#define suffix(x) x.substr(1)
#define last(x) x.substr(x.size() - 1)

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    string s;
    vector<string> all;
    map<string, vector<string>> go;
    map<string, int> bdeg;
    while (cin >> s) {
        all.emplace_back(s);
    }
    sort(all.begin(), all.end());
    for (auto &i : all) {
        bdeg[i] = 0;
        go[prefix(i)].emplace_back(i);
    }

    map<string, vector<string>> gr;
    for (auto x : all) {
        gr[x] = go[suffix(x)];
        for (auto y : gr[x]) {
            bdeg[y]++;
        }
    }

    for (auto x : all) {
        if (bdeg[x] != 1) {
            cout << x;
            while (true) {
                if (gr[x].size() == 1) {
                    auto y = gr[x][0];
                    if (bdeg[y] == 1) {
                        cout << last(y);
                        x = y;
                    } else break;
                } else break;
            }
            cout << " ";
        }
    }

    return 0;
}
