#include <iostream>
#include <vector>
#include <map>

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

vector<vector<int>> cycles(vector<vector<int>> &P, vector<vector<int>> &Q) {
    vector<vector<int>> result;
    auto red = makeGraph(P);
    auto blue = makeGraph(Q);
    vector<int> mark(red.size(), 0);

    for (int i = 0; i < red.size(); i++) {
        if (!mark[i]) {
            result.emplace_back();
            dfs(i, result.back(), mark, red, blue);
        }
    }

    return result;
}

bool differ(vector<vector<int>> &P, vector<vector<int>> &Q) {
    return cycles(P, P) != cycles(P, Q);
}

void show(vector<vector<int>> &a) {
    for (auto single : a) {
        cout << '(';
        for (int i = 0; i < single.size(); i++) {
            if (single[i] > 0) cout << '+';
            cout << single[i];
            if (i != single.size() - 1) cout << " ";
        }
        cout << ")";
    }
    cout << '\n';
}

void simple_dfs(int v, vector<int> &cycle, map<int, int> &go, vector<int> &used) {
    if (used[v]) return;
    used[v] = used[v ^ 1] = 1;

    if (cycle.empty()) {
        cycle.push_back(v / 2 + 1);
    } else {
        bool inv = go.find(v)->second % 2 == v % 2;
        int sgn = ((cycle.back() < 0) ^ inv) ? -1 : 1;
        cycle.push_back((v / 2 + 1) * sgn);
    }

    simple_dfs(go.find(v ^ 1)->second, cycle, go, used);
}

vector<vector<int>> makePermutation(map<int, int> &go) {
    vector<int> used(2 * go.size(), 0);
    vector<vector<int>> result;
    for (auto &pair : go) {
        if (!used[pair.first]) {
            result.emplace_back();
            simple_dfs(pair.first, result.back(), go, used);
        }
    }

    return result;
}

vector<vector<int>> apply_two_break(vector<vector<int>> &P, int &a, int &b, int &c, int &d) {
    auto graph = makeGraph(P);
    graph[a] = c;
    graph[c] = a;
    graph[b] = d;
    graph[d] = b;
    return makePermutation(graph);
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    auto P = cin_permutation();
    auto Q = cin_permutation();

    while (differ(P, Q)) {
        for (auto &cycle : cycles(P, Q)) {
            if (cycle.size() > 3) {
                show(P);
                P = apply_two_break(P, cycle[0], cycle[1], cycle[3], cycle[2]);
                break;
            }
        }
    }
    show(P);
    return 0;
}
