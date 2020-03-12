#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int k;
    string txt, t;
    cin >> k >> txt;
    map<string, vector<string>> store;
    t = txt.substr(0, k - 1);
    for (int i = k - 2; i < txt.size() - 1; i++) {
        string nxt = t.substr(1) + txt[i + 1];
        store[t].emplace_back(nxt);
        t = nxt;
    }
    for (auto x : store) {
        cout << x.first << " -> ";
        sort(x.second.begin(), x.second.end());
        for (int i = 0; i < x.second.size(); i++) {
            cout << (i == 0 ? "" : ",") << x.second[i];
        }
        cout << '\n';
    }

    return 0;
}
