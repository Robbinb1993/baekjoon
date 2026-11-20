#include <bits/stdc++.h>
using namespace std;

class FloydWarshall {
private:
    static constexpr long long INF = LLONG_MAX / 4;

    int n_;
    vector<int> holdup_;
    vector<bool> active_;
    vector<vector<long long>> dist_, distWithHoldup_;

public:
    FloydWarshall(int n, const vector<int>& holdup)
        : n_(n),
        holdup_(holdup),
        active_(n + 1, false),
        dist_(n + 1, vector<long long>(n + 1, INF)),
        distWithHoldup_(n + 1, vector<long long>(n + 1, INF)) {

        for (int i = 1; i <= n_; i++)
            dist_[i][i] = 0;
    }

    void addEdge(int u, int v, int w) {
        dist_[u][v] = min(dist_[u][v], (long long)w);
        dist_[v][u] = min(dist_[v][u], (long long)w);
    }

    void addNode(int k) {
        active_[k] = true;

        for (int i = 1; i <= n_; i++) {
            for (int j = 1; j <= n_; j++) {
                if (dist_[i][k] != INF && dist_[k][j] != INF) {
                    dist_[i][j] = min(
                        dist_[i][j],
                        dist_[i][k] + dist_[k][j]
                    );
                }

                if (active_[i] && active_[j] && dist_[i][j] != INF) {
                    distWithHoldup_[i][j] = min(
                        distWithHoldup_[i][j],
                        dist_[i][j] + holdup_[k]
                    );
                }
            }
        }
    }

    long long getDist(int u, int v) const {
        return dist_[u][v] == INF ? -1 : dist_[u][v];
    }

    long long getDistWithHoldup(int u, int v) const {
        return distWithHoldup_[u][v] == INF
            ? -1 : distWithHoldup_[u][v];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, Q, t, S, T;

    cin >> N >> M >> Q;

    vector<int> holdup(N + 1);
    vector<pair<int, int>> holdUpTimes(N);

    for (int i = 1; i <= N; i++) {
        cin >> t;
        holdup[i] = t;
        holdUpTimes[i - 1] = {t, i};
    }

    FloydWarshall fw(N, holdup);

    sort(holdUpTimes.begin(), holdUpTimes.end());

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        fw.addEdge(u, v, w);
    }

    for (int i = 0; i < int(holdUpTimes.size()); i++) {
        fw.addNode(holdUpTimes[i].second);
    }

    for (int i = 0; i < Q; i++) {
        cin >> S >> T;
        cout << fw.getDistWithHoldup(S, T) << '\n';
    }

    return 0;
}
