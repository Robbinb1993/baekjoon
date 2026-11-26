#include <bits/stdc++.h>
using namespace std;

class BinaryLifting {
private:
    int n_, log_;

    vector<vector<pair<int, long long>>> adj_;
    vector<vector<int>> par_;
    vector<int> depth_;
    vector<long long> distToRoot_;

public:
    explicit BinaryLifting(int n)
        : n_(n), log_(1), adj_(n + 1), depth_(n + 1, 0), distToRoot_(n + 1, 0) {

        while ((1LL << log_) <= n_)
            ++log_;

        par_.assign(log_, vector<int>(n_ + 1, 0));
    }

    void addEdge(int u, int v, long long w = 1) {
        adj_[u].emplace_back(v, w);
        adj_[v].emplace_back(u, w);
    }

    void preprocess(int root = 1) {
        queue<int> q;
        q.push(root);

        par_[0][root] = 0;
        depth_[root] = 0;
        distToRoot_[root] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto [v, w] : adj_[u]) {
                if (v == par_[0][u])
                    continue;

                par_[0][v] = u;
                depth_[v] = depth_[u] + 1;
                distToRoot_[v] = distToRoot_[u] + w;

                q.push(v);
            }
        }

        for (int i = 1; i < log_; ++i) {
            for (int u = 1; u <= n_; ++u) {
                par_[i][u] = par_[i - 1][par_[i - 1][u]];
            }
        }
    }

    int kthAncestor(int u, int k) const {
        if (k > depth_[u])
            return 0;

        for (int i = 0; i < log_; ++i) {
            if (k & (1 << i))
                u = par_[i][u];
        }

        return u;
    }

    int lca(int u, int v) const {
        if (depth_[u] < depth_[v])
            swap(u, v);

        u = kthAncestor(u, depth_[u] - depth_[v]);

        if (u == v)
            return u;

        for (int i = log_ - 1; i >= 0; --i) {
            if (par_[i][u] != par_[i][v]) {
                u = par_[i][u];
                v = par_[i][v];
            }
        }

        return par_[0][u];
    }

    long long distance(int u, int v) const {
        int ancestor = lca(u, v);

        return distToRoot_[u] + distToRoot_[v] - 2LL * distToRoot_[ancestor];
    }

    int depth(int u) const { return depth_[u]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    BinaryLifting bl(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        bl.addEdge(u, v, w);
    }

    bl.preprocess();

    int M;
    cin >> M;

    while (M--) {
        int t, u, v, k;
        cin >> t >> u >> v;
        if (t == 1) {
            cout << bl.distance(u, v) << '\n';
        } else {
            cin >> k;

            int lca = bl.lca(u, v);
            int up = bl.depth(u) - bl.depth(lca);

            if (k <= up + 1) {
                cout << bl.kthAncestor(u, k - 1) << '\n';
            } else {
                k -= up + 1;
                int down = bl.depth(v) - bl.depth(lca);
                cout << bl.kthAncestor(v, down - k) << '\n';
            }
        }
    }

    return 0;
}
