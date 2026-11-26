#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2501;

int gasPricePerLiter[MAXN];

class Dijkstra {
private:
    static constexpr long long INF = LLONG_MAX;

    vector<vector<pair<int, int>>> adj;
    vector<vector<long long>> dist;

public:
    Dijkstra(int n) : adj(n + 1), dist(n + 1, vector<long long>(MAXN, INF)) {}

    void addEdge(int u, int v, int w) { adj[u].emplace_back(v, w); }

    long long compute(int src, int dst) {
        for (auto &row : dist)
            fill(row.begin(), row.end(), INF);

        using State = tuple<long long, int, int>;

        priority_queue<State, vector<State>, greater<>> pq;
        vector<int> minProcessedPrice(adj.size(), INT_MAX);

        dist[src][gasPricePerLiter[src]] = 0;
        pq.emplace(0, src, gasPricePerLiter[src]);

        while (!pq.empty()) {
            auto [d, u, minPrice] = pq.top();
            pq.pop();

            if (d > dist[u][minPrice])
                continue;

            if (minPrice >= minProcessedPrice[u])
                continue;

            if (u == dst)
                return d;

            minProcessedPrice[u] = minPrice;

            for (auto [v, w] : adj[u]) {
                long long nextD = d + w * minPrice;

                int nextMinPrice = min(minPrice, gasPricePerLiter[v]);

                if (nextD < dist[v][nextMinPrice]) {
                    dist[v][nextMinPrice] = nextD;
                    pq.emplace(nextD, v, nextMinPrice);
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++)
        cin >> gasPricePerLiter[i];

    Dijkstra dijkstra(N);

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dijkstra.addEdge(u, v, w);
        dijkstra.addEdge(v, u, w);
    }

    cout << dijkstra.compute(1, N) << '\n';

    return 0;
}
