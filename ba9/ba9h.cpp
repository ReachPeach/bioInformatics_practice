//
// Created by maxim on 28.05.2021.
//
#include <bits/stdc++.h>

using namespace std;
const char st = 'A' - 1;
const char star = st - 1;

vector<int> sufArray(const string &s) {
    auto n = s.size();
    vector<int> p(n), count(30, 0), c(n);
    for (int i = 0; i < n; i++) count[s[i] - star]++;
    for (int i = 1; i < 30; i++) count[i] += count[i - 1];
    for (int i = 0; i < n; i++) {
        p[count[s[i] - star] - 1] = i;
        count[s[i] - star]--;
    }

    c[p[0]] = 0;
    int cls = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) cls++;
        c[p[i]] = cls;
    }

    vector<int> new_c(n), p_sec(n);
    for (int k = 0; (1 << k) < n; k++) {
        for (int i = 0; i < n; i++) {
            p_sec[i] = p[i] - (1 << k);
            if (p_sec[i] < 0) p_sec[i] += n;
        }
        count.assign(cls + 1, 0);
        for (int i = 0; i < n; i++) count[c[p_sec[i]]]++;
        for (int i = 1; i <= cls; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            p[count[c[p_sec[i]]] - 1] = p_sec[i];
            count[c[p_sec[i]]]--;
        }
        new_c[p[0]] = 0;
        cls = 0;
        for (int i = 1; i < n; i++) {
            int mid1 = (p[i] + (1 << k)) % n;
            int mid2 = (p[i - 1] + (1 << k)) % n;
            if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
                ++cls;
            new_c[p[i]] = cls;
        }
        c.clear();
        c.assign(new_c.begin(), new_c.end());
    }
    return p;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    string s, t;
    vector<string> ps;
    cin >> s;
    while (cin >> t) ps.emplace_back(t);
    string s_t = s + st;

    auto sufArr = sufArray(s_t);
    for (auto &x : sufArr) clog << x << " " << s_t.substr(x) << '\n';
    for (auto &x : sufArr) clog << x << " ";
    clog << '\n';

    set<int> res;
    for (auto &f : ps) {
        int ind = lower_bound(sufArr.begin(), sufArr.end(), f,
                              [s_t](const int &ind, const string &b) {
                                  auto a = s_t.substr(ind, b.size());
                                  clog << ind << "," << a << " " << (a < b) << " " << b << '\n';
                                  return  a < b;
                              }) - sufArr.begin();
        int cur = sufArr[ind];
        clog << f << " " << ind << '\n';

        do {
            res.insert(cur);
            cur = sufArr[++ind];
        } while (s_t.substr(cur, f.size()) == f);

    }
    for (auto &poss : res) cout << poss << " ";
    return 0;
}
