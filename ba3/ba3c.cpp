#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    map<string, set<string>> store;
    vector<string> all, ans;
    string s;
    while (cin >> s) {
        all.emplace_back(s);
        store[s.substr(0, s.size() - 1)].insert(s);
    }
    sort(all.begin(), all.end());
    for (const auto &S : all) {
        auto suf = S.substr(1);
        if (store.count(suf)) {
            for (const auto &to : store[suf]) {
                if (S != to)
                    cout << S << " -> " << to << '\n';
            }
        }
    }
    return 0;
}
