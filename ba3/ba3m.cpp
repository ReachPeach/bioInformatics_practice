#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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

pair<int, vector<int>> parse(string &s) {
    int from = 0;
    vector<int> to;
    string fr = s.substr(0, s.find('-') - 1),
            t = s.substr(s.find('>') + 2);
    while (t.back() > '9' || t.back() < '0') t.pop_back();
    for (auto c : fr) from = 10 * from + (c - '0');

    auto digs = split(t, ',');
    for (auto dig : digs) {
        int son = 0;
        for (auto c : dig) son = 10 * son + (c - '0');
        to.emplace_back(son);
    }

    return {from, to};
}

vector<vector<int>> go;
vector<int> bdeg;

const string nex = " -> ";

void MaximalNonBranchingPaths(int sz) {
    vector<string> ans;
    vector<int> used(sz, 0);
    for (int i = 1; i < sz; i++) {
        if (bdeg[i] != 1 || go[i].size() != 1) {
            if (!go[i].empty()) {
                for (auto u : go[i]) {
                    used[i] = 1;
                    used[u] = 1;
                    string path = to_string(i) + nex + to_string(u);
                    while (bdeg[u] == 1 && go[u].size() == 1) {
                        path += nex + to_string(go[u][0]);
                        u = go[u][0];
                        used[u] = 1;
                    }
                    ans.emplace_back(path);
                }
            }
        }
    }
    for (int i = 1; i < sz; i++) {
        if (!used[i]) {
            string path = to_string(i);
            used[i] = 1;
            for (int u = go[i][0]; u != i; used[u] = 1, u = go[u][0])
                path += nex + to_string(u);
            path += nex + to_string(i);
            ans.emplace_back(path);
        }
    }
    for (const auto& path : ans) {
        cout << path << '\n';
    }

}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int sz = -1;
    string in;
    while (getline(cin, in)) {
        auto[from, to] = parse(in);
        int maxnum = from;
        for (auto t : to) maxnum = max(maxnum, t);
        while (go.size() <= maxnum) go.emplace_back(vector<int>());
        while (bdeg.size() <= maxnum) bdeg.emplace_back(0);

        for (auto x : to) {
            bdeg[x]++;
            go[from].emplace_back(x);
        }
        sz = max(sz, maxnum + 1);
    }
    MaximalNonBranchingPaths(sz);
    return 0;
}
