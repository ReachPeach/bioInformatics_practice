//
// Created by maxim on 28.05.2021.
//
#include <bits/stdc++.h>

using namespace std;

string Viterbi(vector<char> &O, vector<char> &S, vector<double> &PI, string &Y,
               vector<vector<double>> &A, vector<unordered_map<char, double>> &B) {
    vector<vector<double>> T(S.size(), vector<double>(Y.size()));
    vector<vector<int>> P(S.size(), vector<int>(Y.size()));

    for (int i = 0; i < S.size(); i++) {
        T[i][0] = B[i][Y[0]] / S.size();
        P[i][0] = -1;
    }

    for (int o = 1; o < Y.size(); o++) {
        for (int s = 0; s < S.size(); s++) {
            int from;
            double best = 0;
            for (int prev = 0; prev < S.size(); prev++) {
                double val = T[prev][o - 1] * A[prev][s] * B[s][Y[o]];
                if (val >= best) {
                    best = val;
                    from = prev;
                }
            }
            P[s][o] = from;
            T[s][o] = best;
        }

    }
    string just;
    int last;
    double best = 0;
    for (int k = 0; k < S.size(); k++) {
        if (T[k][Y.size() - 1] > best) {
            best = T[k][Y.size() - 1];
            last = k;
        }
    }
    just = S[last];
    for (int o = Y.size() - 1; o > 0; o--) {
        just += S[P[last][o]];
        last = P[last][o];
    }
    reverse(just.begin(), just.end());
    return just;
}

vector<char> parse(string &s) {
    vector<char> res;

    for (auto &c : s) {
        if (c != ' ' && c != '\t') res.emplace_back(c);
    }

    return res;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);


    vector<char> S, O;
    vector<vector<double>> A;
    vector<double> PI;
    vector<unordered_map<char, double>> B;
    string Y;

    string tmp;
    getline(cin, Y);
    Y.pop_back();
    getline(cin, tmp);
    getline(cin, tmp);
    tmp.pop_back();
    O = parse(tmp);
    getline(cin, tmp);
    getline(cin, tmp);
    tmp.pop_back();
    S = parse(tmp);
    getline(cin, tmp);
    A.assign(S.size(), vector<double>(S.size()));
    for (int i = 0; i <= S.size(); i++) {
        for (int j = 0; j <= S.size(); j++) {
            char t;
            if (!i || !j) cin >> t;
            else
                cin >> A[i - 1][j - 1];
        }
    }
    getline(cin, tmp);
    getline(cin, tmp);

    B.assign(S.size(), unordered_map<char, double>(O.size()));
    for (int i = 0; i <= S.size(); i++) {
        for (int j = 0; j <= O.size(); j++) {
            char t;
            if (!i || !j) {
                cin >> t;
                continue;
            }
            double x;
            cin >> x;
            B[i - 1][O[j - 1]] = x;
        }
    }
    // for (int i = 0; i <= 1000; i++) {
    // PI.assign({i / 1000.0, (1000 - i) / 1000.0});
    string X = Viterbi(O, S, PI, Y, A, B);
    cout << X << '\n';
    // }
}