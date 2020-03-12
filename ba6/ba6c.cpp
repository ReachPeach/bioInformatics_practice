#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int, int> makeGraph(vector<vector<int>> &a) {
    map<int, int> go;
    for (auto &cycle : a) {
        int u = (abs(cycle.back()) - 1) * 2 + (0 < cycle.back()),
                v = (abs(cycle[0]) - 1) * 2 + (cycle[0] < 0);
        go[u] = v;
        go[v] = u;

        for (int i = 1; i < cycle.size(); i++) {
            u = (abs(cycle[i - 1]) - 1) * 2 + (0 < cycle[i - 1]),
                    v = (abs(cycle[i]) - 1) * 2 + (cycle[i] < 0);
            go[u] = v;
            go[v] = u;
        }
    }
    return go;
}

vector<string> split(string &s, char x) {
    int pos = 0;
    vector<string> res;
    while (s.find(x, pos) != -1) {
        res.emplace_back(s.substr(pos, s.find(x, pos) - pos));
        pos = s.find(x, pos) + 1;
    }
    res.emplace_back(s.substr(pos));
    return res;
}

int parse(string &s) {
    int ans = 0, mn = 1;
    int pos = 0, n = s.size();
    if (s.empty()) return ans;
    if (s[n - 1] == ')') n--;
    if (s[pos] == '(') pos++;
    if (s[pos] == '-') mn = -1;
    pos++;
    for (; pos < n; pos++) ans = 10 * ans + s[pos] - '0';
    return ans * mn;
}

vector<vector<int>> cin_permutation() {
    vector<vector<int>> res;
    string s;
    getline(cin, s);
    s.pop_back();
    auto t = split(s, ')');
    for (auto x : t) {
        res.emplace_back(vector<int>());
        auto p = split(x, ' ');
        for (auto z : p) {
            auto v = parse(z);
            if (v) res.back().emplace_back(v);
        }
        if (res.back().empty()) res.resize(res.size() - 1);
    }
    return res;
}

void dfs(int &v, vector<int> &cycle, vector<int> &used,
         map<int, int> &red, map<int, int> &blue) {
    if (used[v]) return;
    used[v] = 1;
    used[red[v]] = 1;
    cycle.emplace_back(v);
    cycle.emplace_back(red[v]);
    dfs(blue[red[v]], cycle,
        used, red, blue);

}

vector<vector<int>> cycles(map<int, int> &red, map<int, int> &blue) {
    vector<vector<int>> result;
    vector<int> mark(red.size(), 0);

    for (int i = 0; i < red.size(); i++) {
        if (!mark[i]) {
            result.emplace_back();
            dfs(i, result.back(), mark, red, blue);
        }
    }

    return result;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    char x;
    auto P = cin_permutation();
    auto Q = cin_permutation();

    auto red = makeGraph(P), blue = makeGraph(Q);

    cout << cycles(red, red).size() - cycles(red, blue).size();
    return 0;
}
