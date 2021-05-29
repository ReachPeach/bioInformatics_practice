//
// Created by maxim on 28.05.2021.
//
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;
#define prefix(x) x.substr(0, x.size() - 1)
#define suffix(x) x.substr(1)

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);

    int k, d;
    cin >> k >> d;

    vector<string> pl, pr;
    string t;

    vector<vector<int>> go;
    while (cin >> t) {
        int pos = t.find('|');
        pl.emplace_back(t.substr(0, pos));
        pr.emplace_back(t.substr(pos + 1));
    }

    vector<int> used(pl.size(), 0);
    int used_count = 0;
    int i = 0, pos = k - 1;

    while (used_count < pl.size() - 1) {
        if (!used[i]) {
            auto ileft = pl[i], iright = pr[i];
            auto lek = ileft.substr(ileft.size() - pos), rek = iright.substr(iright.size() - pos);
            for (int j = 0; j < pl.size(); j++) {
                if (!used[j]) {
                    auto jleft = pl[j], jright = pr[j];
                    auto lsk = jleft.substr(0, pos), rsk = jright.substr(0, pos);
                    if (lek == lsk && rek == rsk) {
                        auto pref = ileft + jleft.substr(pos);
                        auto suff = iright + jright.substr(pos);
                        pl[i] = pref;
                        pr[i] = suff;
                        used[j] = 1;
                        used_count++;
                        i--;
                        break;
                    }
                }
            }
        }
        i++;
    }

    int start = find(used.begin(), used.end(), 0) - used.begin();
    cout << pl[start] + pr[start].substr(pr[start].size() - pos - 1 - d);
    return 0;
}

