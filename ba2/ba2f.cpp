//
// Created by maxim on 28.05.2021.
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

vector<vector<int>> getProfile(int k, vector<int> &motif, vector<string> &data) {
    vector<vector<int>> profile(4, vector<int>(k, 0));
    for (int i = 0; i < motif.size(); i++) {
        for (int j = 0; j < k; j++) {
            profile[getNum(data[i][motif[i] + j])][j]++;
        }
    }
    return profile;
}

int getScore(vector<vector<int>> &motif, int t) {
    int res = 0;
    for (int i = 0; i < motif[0].size(); i++) {
        res += t - max({motif[0][i], motif[1][i], motif[2][i], motif[3][i]});
    }
    return res;
}

vector<int> getMotif(int k, int t, vector<vector<int>> &profile, vector<string> &data) {
    vector<int> res(t);
    for (int i = 0; i < t; i++) {
        double best_prob = 0;
        int best_ind = 0;
        for (int j = 0; j <= data[i].size() - k; j++) {
            string s = data[i].substr(j, k);

            double prob = 1.0;
            for (int ind = 0; ind < k; ind++) {
                prob *= (profile[getNum(s[ind])][ind] + (0.125 / t)) / (t * 1.125);
            }

            if (prob > best_prob) {
                best_prob = prob;
                best_ind = j;
            }
        }
        res[i] = best_ind;
    }
    return res;
}

pair<int, vector<int>> RandomizedMotifSearch(int k, int t, vector<string> &data) {
    vector<int> motif(t);
    for (auto &pos : motif) pos = rand() % (data.back().size() - k + 1);
    vector<vector<int>> profile = getProfile(k, motif, data);
    auto best_score = getScore(profile, t);
    while (true) {
        vector<int> new_motif = getMotif(k, t, profile, data);
        auto new_profile = getProfile(k, new_motif, data);
        int score = getScore(new_profile, t);

        if (score < best_score) {
            best_score = score;
            motif = new_motif;
            profile = new_profile;
        } else {
            return {best_score, motif};
        }
    }
}

vector<int> solve(int k, int t, vector<string> &data) {
    int best_score = k * t;
    vector<int> res;
    for (int i = 0; i < 1000; i++) {
        auto[score, try_res] = RandomizedMotifSearch(k, t, data);
        if (score < best_score) {
            best_score = score;
            res = try_res;
        }
    }
    clog << best_score;
    return res;
}

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int k, t;
    vector<string> data;
    cin >> k >> t;
    string s;
    while (cin >> s) data.emplace_back(s);
    auto res = solve(k, t, data);
    for (int i = 0; i < t; i++) cout << data[i].substr(res[i], k) << '\n';
    return 0;
}


