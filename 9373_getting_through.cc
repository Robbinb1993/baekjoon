#include <bits/stdc++.h>
using namespace std;

bool connected(int u, int v, const vector<tuple<int, int, int>> &sensors, const int w,
               const double mid) {
    if (u > v)
        swap(u, v);

    if (u == 0 && v == 1) {
        return 2 * mid >= w;
    }

    if (u == 0 || u == 1) { // wall
        auto [x, y, r] = sensors[v - 2];

        if (u == 0)
            return x - r <= 2 * mid;

        return w - x - r <= 2 * mid;
    }

    auto [x1, y1, r1] = sensors[u - 2];
    auto [x2, y2, r2] = sensors[v - 2];

    double dx = (double)x1 - x2;
    double dy = (double)y1 - y2;
    double drSquared = dx * dx + dy * dy;

    double radiusSum = r1 + r2 + 2 * mid;
    return drSquared <= radiusSum * radiusSum;
}

bool pos(const vector<tuple<int, int, int>> &sensors, int w, double mid) {
    int n = sensors.size();
    vector<bool> visited(n + 2, false);

    stack<int> st;
    st.push(0);
    visited[0] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (u == 1)
            return false; // Left wall and right wall are connected by blockades

        for (int v = 1; v < n + 2; ++v) {
            if (!visited[v] && connected(u, v, sensors, w, mid)) {
                visited[v] = true;
                st.push(v);
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int w, n;
        cin >> w >> n;

        vector<tuple<int, int, int>> sensors(n);

        for (auto &[x, y, r] : sensors)
            cin >> x >> y >> r;

        double L = 0.0, R = w / 2.0;

        while (R - L > 1e-7) {
            double mid = (L + R) / 2.0;

            if (pos(sensors, w, mid))
                L = mid;
            else
                R = mid;
        }

        cout << fixed << setprecision(6) << L << '\n';
    }

    return 0;
}
