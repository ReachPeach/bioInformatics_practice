//
// Created by maxim on 17.05.2021.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

int getNum(char c) {
    if (c == 'A') return 0;
    if (c == 'G') return 1;
    if (c == 'C') return 2;
    if (c == 'T') return 3;
    exit(1);
}

char getChar(int x) {
    if (x == 0) return 'A';
    if (x == 1) return 'G';
    if (x == 2) return 'C';
    if (x == 3) return 'T';
    exit(1);
}

string getString(int x, int count) {
    if (!count) return "";
    return getString(x / 4, count - 1) + getChar(x % 4);
}

int getNum(string &s, int pos = 0) {
    if (pos == s.size()) return 0;
    return getNum(s[s.size() - 1 - pos]) + 4 * getNum(s, pos + 1);
}

int getDist(string &s, string &t) {
    int r = 0;
    for (int i = 0; i < s.size(); i++) if (s[i] != t[i]) r++;
    return r;
}

string solve(int k, vector<string> &data) {
    int sz = 1 << k;
    sz *= sz;

    string best_str = getString(0, k);
    int best_ans = k * data.size() + 1;
    for (int cur = 0; cur < sz; cur++) {
        int ans = 0;
        string w = getString(cur, k);
        for (auto &s : data) {
            int m = k;
            for (int i = 0; i <= s.size() - k; i++) {
                string t = s.substr(i, k);
                m = min(m, getDist(t, w));
            }
            ans += m;
        }
        if (ans < best_ans) {
            best_ans = ans;
            best_str = w;
        }
    }
    return best_str;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int k;
    vector<string> data;
    cin >> k;
    string t;
    while (cin >> t) data.emplace_back(t);
    cout << solve(k, data);
    return 0;
}

