#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    int n_;
    vector<int> S_;

    void build(const vector<int> &a, const int L, const int R, const int idx) {
        if (L == R) {
            S_[idx] = a[L];
            return;
        }

        const int M = (L + R) / 2;

        build(a, L, M, 2 * idx);
        build(a, M + 1, R, 2 * idx + 1);

        S_[idx] = min(S_[2 * idx], S_[2 * idx + 1]);
    }

    void update(const int p, const int v, const int L, const int R, const int idx) {
        if (L == R) {
            S_[idx] = v;
            return;
        }

        const int M = (L + R) / 2;

        if (p <= M)
            update(p, v, L, M, 2 * idx);
        else
            update(p, v, M + 1, R, 2 * idx + 1);

        S_[idx] = min(S_[2 * idx], S_[2 * idx + 1]);
    }

    int query(const int l, const int r, const int L, const int R, const int idx) const {
        if (l <= L && R <= r)
            return S_[idx];

        const int M = (L + R) / 2;
        int res = INT_MAX;

        if (l <= M)
            res = min(res, query(l, r, L, M, 2 * idx));

        if (r > M)
            res = min(res, query(l, r, M + 1, R, 2 * idx + 1));

        return res;
    }

public:
    explicit SegmentTree(const vector<int> &a) : n_((int)a.size()), S_(4 * n_, INT_MAX) {
        if (n_ > 0)
            build(a, 0, n_ - 1, 1);
    }

    void update(const int p, const int v) { update(p, v, 0, n_ - 1, 1); }

    int query(const int l, const int r) const {
        if (l > r || n_ == 0)
            return INT_MAX;

        return query(l, r, 0, n_ - 1, 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> X(N);
    for (int &id : X)
        cin >> id;

    vector<int> Y(N + 1), Z(N + 1);
    for (int score = 1; score <= N; score++) {
        int id;
        cin >> id;
        Y[id] = score;
    }
    for (int score = 1; score <= N; score++) {
        int id;
        cin >> id;
        Z[id] = score;
    }

    SegmentTree st(vector<int>(N + 1, INT_MAX));
    int ans = 0;

    for (const int id : X) {
        const int y = Y[id];
        const int z = Z[id];

        const int bestZ = st.query(1, y - 1);
        if (bestZ >= z) {
            ans++;
        }

        st.update(y, z);
    }

    cout << ans << '\n';

    return 0;
}
