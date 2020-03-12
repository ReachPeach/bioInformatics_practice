#include <iostream>
#include <vector>

using namespace std;

int dist(char a, char b, char c) {
    return a == b && b == c && a == c ? 1 : 0;
}

void LCS(const string &s, const string &t, const string &p) {
    int n = s.size(), m = t.size(), k = p.size();
    vector<vector<vector<int>>> lcs(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, 0)));
    for (int i = 0; i <= n; i++) lcs[i][0][0] = 0;
    for (int i = 0; i <= m; i++) lcs[0][i][0] = 0;
    for (int i = 0; i <= k; i++) lcs[0][0][i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int l = 1; l <= k; l++) {
                if (dist(s[i - 1], t[j - 1], p[l - 1])) lcs[i][j][l] = lcs[i - 1][j - 1][l - 1] + 1;
                else {
                    lcs[i][j][l] = max(lcs[i - 1][j][l], max(lcs[i][j - 1][l], lcs[i][j][l - 1]));
                }
            }
        }
    }
    cout << lcs[n][m][k];

    string ansA, ansB, ansC;
    while (n > 0 && m > 0 && k > 0) {
        if (lcs[n][m][k] == lcs[n - 1][m - 1][k - 1] + dist(s[n - 1], t[m - 1], p[k - 1])) {
            ansA = s[n - 1] + ansA;
            ansB = t[m - 1] + ansB;
            ansC = p[k - 1] + ansC;
            n--;
            m--;
            k--;
        } else if (lcs[n][m][k] == lcs[n - 1][m][k]) {
            ansA = s[n - 1] + ansA;
            ansB = '-' + ansB;
            ansC = '-' + ansC;
            n--;
        } else if (lcs[n][m][k] == lcs[n][m - 1][k]) {
            ansA = '-' + ansA;
            ansB = t[m - 1] + ansB;
            ansC = '-' + ansC;
            m--;
        } else {
            ansA = '-' + ansA;
            ansB = '-' + ansB;
            ansC = p[k - 1] + ansC;
            k--;
        }
    }


    while (n > 0) {
        ansA = s[n - 1] + ansA;
        ansB = '-' + ansB;
        n--;
        ansC = '-' + ansC;
    }
    while (m > 0) {
        ansA = '-' + ansA;
        ansB = t[m - 1] + ansB;
        ansC = '-' + ansC;
        m--;
    }
    while (k > 0) {
        ansA = '-' + ansA;
        ansB = '-' + ansB;
        ansC = p[k - 1] + ansC;
        k--;
    }
    cout << '\n' << ansA << '\n' << ansB << '\n' << ansC;
}


int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    string a, b, c;
    cin >> a >> b >> c;
    LCS(a, b, c);
    return 0;
}
