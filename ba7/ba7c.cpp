#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;
vector<vector<int>> D;
vector<pair<int, int>> p;
int nxt;

int getLimb(int n) {
    int ans = INT32_MAX;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (i == j) continue;
            ans = min(ans, (D[n - 1][i] + D[n - 1][j] - D[i][j]) / 2);
        }
    }

    return ans;
}

set<pair<int, int>> emptySet;

bool addNode(vector<set<pair<int, int>>> &go, pair<int, int> next, int x, int w, int p, int d, int limb) {
    int v = next.first, vv = next.second;
    if (v == vv) {
        if (d == x) {
            go[v].insert({w, limb});
            go[w].insert({v, limb});
        }

        return true;
    }

    for (auto xu : go[v]) {
        int u = xu.first;
        int wu = xu.second;

        if (u == p)
            continue;

        auto go_on = addNode(go, {u, vv}, x, w, v, d + wu, limb);

        if (go_on) {
            if (d == x) {
                go[v].insert({w, limb});
                go[w].insert({v, limb});
            } else if (x > d && x < d + wu) {
                go.emplace_back(set<pair<int, int>>());

                go[v].erase({u, wu});
                go[u].erase({v, wu});

                int c = go.size() - 1;

                go[v].insert({c, x - d});
                go[c].insert({v, x - d});

                go[u].insert({c, d + wu - x});
                go[c].insert({u, d + wu - x});

                go[w].insert({c, limb});
                go[c].insert({w, limb});
            }

            return true;
        }
    }

    return false;
}

vector<set<pair<int, int>>> additivePhylogeny(int n) {
    if (n == 2) {
        vector<set<pair<int, int>>> ans(nxt, set<pair<int, int>>());
        ans[0].insert({1, D[0][1]});
        ans[1].insert({0, D[0][1]});
        return ans;
    }

    int limbLength = getLimb(n);
    pair<int, int> w = {-1, -1};

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (i == j) continue;

            if (D[i][j] == D[i][n - 1] + D[n - 1][j] - 2 * limbLength) {
                w = {i, j};
                break;
            }
        }

        if (w != make_pair(-1, -1))
            break;
    }
    auto go = additivePhylogeny(n - 1);
    addNode(go, w, D[w.first][n - 1] - limbLength, n - 1, -1, 0, limbLength);
    return go;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    cin >> nxt;
    D.resize(nxt, vector<int>(nxt));
    for (int i = 0; i < nxt; i++) {
        for (int j = 0; j < nxt; j++) {
            cin >> D[i][j];
        }
    }
    auto g = additivePhylogeny(nxt);
    for (int i = 0; i < g.size(); i++) {
        for (auto x : g[i]) {
            int j = x.first;
            int w = x.second;
            cout << i << "->" << j << ":" << w << "\n";
        }
    }

    return 0;
}