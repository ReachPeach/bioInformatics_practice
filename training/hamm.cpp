#include <iostream>

using namespace std;

int main() {
    string s, t;
    cin>>s>>t;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != t[i]) ans++;
    }
    cout<<ans;
    return 0;
}
