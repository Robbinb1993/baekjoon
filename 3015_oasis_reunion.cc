#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<pair<int, int>> st;
    long long ans = 0;

    while (N--) {
        int v;
        cin >> v;
        while (!st.empty() && st.back().first < v) {
            ans += st.back().second;
            st.pop_back();
        }
        if (!st.empty())
            ans += (st.back().first == v) ? st.back().second : 1;
        if (!st.empty() && st.back().first == v) {
            st.back().second++;
            if (st.size() > 1)
                ans++;
        }
        else
            st.push_back({v, 1});
    }

    cout << ans << '\n';

    return 0;
}
