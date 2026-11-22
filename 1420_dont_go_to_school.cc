#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int DX[4] = {-1, 0, 1, 0};
const int DY[4] = {0, 1, 0, -1};

class FordFulkerson {
private:
    struct Edge {
        int to;
        long long capacity;
        long long originalCapacity;
        int rev;
    };

    vector<vector<Edge>> adj;
    long long maxFlow = 0;

    long long dfs(int u, int sink, long long flow, vector<bool> &visited) {
        if (u == sink)
            return flow;

        visited[u] = true;

        for (Edge &edge : adj[u]) {
            if (visited[edge.to] || edge.capacity == 0)
                continue;

            long long pushed = dfs(edge.to, sink, min(flow, edge.capacity), visited);

            if (pushed > 0) {
                edge.capacity -= pushed;
                adj[edge.to][edge.rev].capacity += pushed;

                return pushed;
            }
        }

        return 0;
    }

public:
    FordFulkerson(int n) : adj(n) {}

    void addEdge(int u, int v, long long capacity) {
        int forwardIdx = adj[u].size();
        int reverseIdx = adj[v].size();

        adj[u].push_back({v, capacity, capacity, reverseIdx + (u == v)});

        adj[v].push_back({u, 0, 0, forwardIdx});
    }

    void compute(int source, int sink) {
        if (source == sink)
            throw invalid_argument("Source equals sink");

        maxFlow = 0;

        for (auto &edges : adj) {
            for (Edge &edge : edges)
                edge.capacity = edge.originalCapacity;
        }

        while (true) {
            vector<bool> visited(adj.size(), false);

            long long pushed = dfs(source, sink, LLONG_MAX, visited);

            if (pushed == 0)
                break;

            maxFlow += pushed;
        }
    }

    long long getMaxFlow() const { return maxFlow; }
};

int getIdx(const int r, const int c, const int M) { return 2 * (r * M + c); }

long long solve(vector<string> &grid, FordFulkerson &ff, const int N, const int M) {
    int source = 0, sink = 0;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == '#')
                continue;
            int idx = getIdx(x, y, M);
            if (grid[x][y] == 'K')
                source = idx;
            else if (grid[x][y] == 'H')
                sink = idx;

            ff.addEdge(idx, idx + 1, (grid[x][y] == 'H' || grid[x][y] == 'K') ? INF : 1);

            for (int k = 0; k < 4; k++) {
                int nx = x + DX[k];
                int ny = y + DY[k];

                if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != '#') {
                    int nIdx = getIdx(nx, ny, M);
                    ff.addEdge(idx + 1, nIdx, INF);
                }
            }
        }
    }

    ff.compute(source, sink);
    long long flow = ff.getMaxFlow();

    return flow >= INF ? -1 : flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<string> grid(N);
    for (int i = 0; i < N; i++)
        cin >> grid[i];

    int tiles = N * M;
    FordFulkerson ff(2 * tiles);

    cout << solve(grid, ff, N, M) << '\n';

    return 0;
}
