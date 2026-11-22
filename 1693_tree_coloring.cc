#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 1;

vector<vector<int>> adj;

int DP[MAXN][21];

int solve(const int u, const int p, const int pCol) {
    if (DP[u][pCol] != -1)
        return DP[u][pCol];

    int tot = 0;
    for (auto& e : adj[u]) {
        if (e == p)
            continue;
        int curr = INT_MAX;
        for (int c = 1; c <= 20; c++) {
            if (c != pCol)
                curr = min(curr, c + solve(e, u, c));
        }
        tot += curr;
    }

    return DP[u][pCol] = tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    adj.assign(N + 1, vector<int>());

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(DP, -1, sizeof(DP));
    int ans = INT_MAX;
    for (int c = 1; c <= 20; c++)
        ans = min(ans, c + solve(1, -1, c));

    cout << ans << '\n';

    return 0;
}
