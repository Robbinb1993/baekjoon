#include <bits/stdc++.h>
using namespace std;

class Dijkstra {
private:
    static constexpr long long INF = LLONG_MAX;

    vector<vector<pair<int, int>>> adj;
    vector<long long> dist;
    vector<vector<int>> parentsOnShortestPath;

public:
    Dijkstra(int n) : adj(n), dist(n, INF), parentsOnShortestPath(n) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    void compute(int src, int dest = -1) {
        fill(dist.begin(), dist.end(), INF);

        for (auto& parents : parentsOnShortestPath)
            parents.clear();

        priority_queue<pair<long long, int>,
            vector<pair<long long, int>>, greater<>> pq;

        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u])
                continue;

            if (u == dest)
                break;

            for (auto [v, w] : adj[u]) {
                long long nextD = d + w;

                if (nextD < dist[v]) {
                    dist[v] = nextD;
                    pq.emplace(nextD, v);
                    parentsOnShortestPath[v].clear();
                    parentsOnShortestPath[v].push_back(u);
                }
                else if (nextD == dist[v]) {
                    parentsOnShortestPath[v].push_back(u);
                }
            }
        }
    }

    long long getDistance(int v) const {
        if (dist[v] == INF) return -1;
        return dist[v];
    }

    vector<pair<int, int>> getShortestPathEdges(int src, int dest) const {
        vector<pair<int, int>> result;
        vector<bool> visited(adj.size(), false);
        vector<int> stack = {dest};

        visited[dest] = true;

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();

            if (v == src)
                continue;

            for (int u : parentsOnShortestPath[v]) {
                result.emplace_back(u, v);

                if (!visited[u]) {
                    visited[u] = true;
                    stack.push_back(u);
                }
            }
        }

        return result;
    }

    const vector<long long>& getDistances() const {
        return dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, src, dest;

    while (cin >> N >> M && (N != 0 || M != 0)) {
        cin >> src >> dest;

        Dijkstra d1(N);

        vector<vector<pair<int, int>>> adj(N);

        for (int i = 0; i < M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
            d1.addEdge(u, v, w);
        }

        d1.compute(src, dest);
        vector<pair<int, int>> edgesOnShortestPath = d1.getShortestPathEdges(src, dest);

        vector<vector<bool>> blocked(N, vector<bool>(N, false));

        for (auto [u, v] : edgesOnShortestPath)
            blocked[u][v] = true;

        Dijkstra d2(N);

        for (int u = 0; u < N; u++) {
            for (auto [v, w] : adj[u]) {
                if (!blocked[u][v])
                    d2.addEdge(u, v, w);
            }
        }

        d2.compute(src, dest);
        cout << d2.getDistance(dest) << '\n';
    }

    return 0;
}
