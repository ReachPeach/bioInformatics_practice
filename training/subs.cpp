#include <iostream>
#include <vector>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    vector<int> positions;
    for (int st = 0, k = s.find(t); k != -1; st = k + 1, k = s.find(t, st)) {
        positions.emplace_back(k);
    }
    for (auto &position : positions) cout << position + 1 << " ";
    return 0;
}
