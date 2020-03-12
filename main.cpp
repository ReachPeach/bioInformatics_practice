#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define all(x) x.begin(), x.end()
vector<vector<int>> D;

struct cluster {
    cluster(int id_, int age_, vector<int> nodes_) : id(id_), age(age_), nodes(std::move(nodes_)) {}

    int id, age;
    vector<int> nodes;

};

double dist_by_clusters(cluster &from, cluster &to) {
    int ans = 0;
    for (auto i : from.nodes) {
        for (auto j : to.nodes) {
            ans += D[i][j];
        }
    }
    return (ans) / (double) (from.nodes.size() * to.nodes.size());
}

cluster merge(cluster &c1, cluster &c2, int id, int age) {
    vector<int> a(c1.nodes);
    a.insert(a.end(), all(c2.nodes));
    return cluster(id, age, a);
}

pair<cluster, cluster> find_closest(vector<cluster>, );




int main() {
    freopen("../inputs/test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n;
    cin >> n;
    D.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> D[i][j];
    }


    return 0;
}
