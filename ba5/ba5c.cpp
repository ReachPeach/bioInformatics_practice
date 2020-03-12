#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string LCS(const string &s, const string &t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> ind(n + 1, vector<pair<int, int>>(m + 1, {0, 0}));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                ind[i][j] = {i - 1, j - 1};
            } else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
                if (lcs[i - 1][j] >= lcs[i][j - 1]) {
                    ind[i][j] = {i - 1, j};
                } else ind[i][j] = {i, j - 1};
            }
        }
    }

    string res;
    while (n * m != 0) {
        if (ind[n][m] == make_pair(n - 1, m - 1)) {
            res += s[n - 1];
            n--, m--;
        } else {
            if (ind[n][m] == make_pair(n - 1, m)) {
                n--;
            } else {
                m--;
            }
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    string s, t;
    cin >> s >> t;
    cout << LCS(s, t);
    return 0;
}
