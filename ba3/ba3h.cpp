#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    map<string, vector<string>> store, to;
    vector<string> all, ans;
    int k;
    cin >> k;
    string s;
    map<string, int> deg;

    while (cin >> s) {
        all.emplace_back(s);
        store[s.substr(0, s.size() - 1)].emplace_back(s);
    }
    for (auto S : all) deg[S] = 0;
    for (auto S : all) {
        to[S] = store[S.substr(1)];
        for (auto x : to[S]) {
            deg[x]++;
        }
    }

    bool started = false;
    int M = INT32_MAX;
    string cur = "failed";
    for (auto x : deg) {
        if (x.second < M) {
            M = x.second;
            cur = x.first;
        }
    }

    for (; !to[cur].empty();) {
        cout << (started ? cur.substr(k - 1) : cur);
        started = true;
        string nxt = to[cur].front();
        to[cur].erase(to[cur].begin());
        cur = nxt;
    }
    cout << (started ? cur.substr(k - 1) : cur);

    return 0;
}
