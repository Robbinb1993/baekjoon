#include <bits/stdc++.h>
using namespace std;


struct Edge {
    int from, to, weight;
};

class MST {
private:
    vector<vector<Edge>> adj, tree;
    vector<int> parent, key;
    long long totalWeight = 0;

public:
    MST(int n)
        : adj(n), tree(n), parent(n, -1), key(n, INT_MAX) {
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
    }

    void compute() {
        totalWeight = 0;
        fill(parent.begin(), parent.end(), -1);
        fill(key.begin(), key.end(), INT_MAX);
        for (auto& edges : tree)
            edges.clear();

        if (adj.empty())
            return;

        priority_queue<pair<int, int>,
            vector<pair<int, int>>, greater<>> pq;

        vector<bool> inMST(adj.size(), false);

        key[0] = 0;
        pq.emplace(0, 0);

        while (!pq.empty()) {
            auto [currentKey, u] = pq.top();
            pq.pop();

            if (inMST[u])
                continue;

            inMST[u] = true;
            totalWeight += currentKey;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int w = edge.weight;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.emplace(w, v);
                }
            }
        }

        for (int v = 1; v < static_cast<int>(parent.size()); v++) {
            if (parent[v] == -1)
                continue;

            tree[parent[v]].push_back({parent[v], v, key[v]});
            tree[v].push_back({v, parent[v], key[v]});
        }
    }

    long long getTotalWeight() const {
        return totalWeight;
    }

    const vector<vector<Edge>>& getTree() const {
        return tree;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<pair<int, int>> X, Y, Z;
    int x, y, z;

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> x >> y >> z;
        X.emplace_back(x, i);
        Y.emplace_back(y, i);
        Z.emplace_back(z, i);
    }

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());

    MST mst(N);

    for (int i = 0; i < int(X.size()) - 1; i++) {
        mst.addEdge(X[i].second, X[i + 1].second, X[i + 1].first - X[i].first);
        mst.addEdge(Y[i].second, Y[i + 1].second, Y[i + 1].first - Y[i].first);
        mst.addEdge(Z[i].second, Z[i + 1].second, Z[i + 1].first - Z[i].first);
    }

    mst.compute();

    cout << mst.getTotalWeight() << '\n';

    return 0;
}
