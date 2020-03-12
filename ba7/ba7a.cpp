#include <iostream>
#include <vector>
#include <set>

using namespace std;
vector<vector<int>> info;
vector<int> p, w, deep;
vector<set<pair<int, int>>> to;

int digit(const string &s) {
    long long res = 0;
    for (const auto &c : s) res = res * 10 + (c - '0');
    return res;
}

vector<int> parse(const string &s) {
    int pos1 = s.find('-'), pos2 = s.find(':');
    auto first = digit(s.substr(0, pos1)), second = digit(s.substr(s.find('-') + 2, pos2 - pos1 - 2)), weight =
            digit(s.substr(pos2 + 1));

    return vector<int>({first, second, weight});
}

void make_tree(const int &v) {
    for (const auto &u : to[v]) {
        to[u.first].erase({v, u.second});
        p[u.first] = v;
        deep[u.first] = deep[v] + 1;
        w[u.first] = u.second;
        make_tree(u.first);
    }
}

long long dist(int u, int v) {
    if (u == v) return 0;
    long long ans = 0;
    if (deep[u] < deep[v]) swap(u, v);
    for (; deep[u] != deep[v]; ans += w[u], u = p[u]);
    if (u == v) return ans;
    for (; u != v; ans += w[u] + w[v], u = p[u], v = p[v]);
    return ans;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n, sz, M = 0;
    cin >> n;
    string s;
    while (cin >> s) {
        info.emplace_back(parse(s));
        M = max(M, info.back()[0] + 1);
    }
    sz = M;
    p.resize(sz);
    w.resize(sz);
    deep.resize(sz);
    to.assign(sz, set<pair<int, int>>());
    for (auto single : info) {
        to[single[0]].insert({single[1], single[2]});
        to[single[1]].insert({single[0], single[2]});
    }
    for (int i = 0; i < sz; i++) {
        if (to[i].size() > 1) {
            deep[i] = 0;
            make_tree(i);
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist(i, j) << ' ';
        }
        cout << '\n';
    }
    return 0;
}
