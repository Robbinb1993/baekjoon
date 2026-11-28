#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    struct State {
        long long sum;
        long long maxPrefix;
        long long maxSuffix;
        long long maxSubarray;
    };

    int n_;
    vector<State> S_;

    static State merge(const State &left, const State &right) {
        State result;

        result.sum = left.sum + right.sum;
        result.maxPrefix = max(left.maxPrefix, left.sum + right.maxPrefix);
        result.maxSuffix = max(right.maxSuffix, left.maxSuffix + right.sum);
        result.maxSubarray =
            max({left.maxSubarray, right.maxSubarray, left.maxSuffix + right.maxPrefix});

        return result;
    }

    void build(const vector<long long> &a, const int L, const int R, const int idx) {
        if (L == R) {
            S_[idx] = {a[L], a[L], a[L], a[L]};
            return;
        }

        const int M = (L + R) / 2;

        build(a, L, M, 2 * idx);
        build(a, M + 1, R, 2 * idx + 1);

        S_[idx] = merge(S_[2 * idx], S_[2 * idx + 1]);
    }

    void update(const int p, const long long v, const int L, const int R, const int idx) {
        if (L == R) {
            const long long sum = S_[idx].sum + v;
            S_[idx] = {sum, sum, sum, sum};
            return;
        }

        const int M = (L + R) / 2;

        if (p <= M)
            update(p, v, L, M, 2 * idx);
        else
            update(p, v, M + 1, R, 2 * idx + 1);

        S_[idx] = merge(S_[2 * idx], S_[2 * idx + 1]);
    }

    State query(const int l, const int r, const int L, const int R, const int idx) const {
        if (l <= L && R <= r)
            return S_[idx];

        const int M = (L + R) / 2;

        if (r <= M)
            return query(l, r, L, M, 2 * idx);

        if (l > M)
            return query(l, r, M + 1, R, 2 * idx + 1);

        State left = query(l, r, L, M, 2 * idx);
        State right = query(l, r, M + 1, R, 2 * idx + 1);

        return merge(left, right);
    }

public:
    explicit SegmentTree(const vector<long long> &a) : n_((int)a.size()), S_(4 * n_) {
        if (n_ > 0)
            build(a, 0, n_ - 1, 1);
    }

    void update(const int p, const long long v) { update(p, v, 0, n_ - 1, 1); }

    State query(const int l, const int r) const { return query(l, r, 0, n_ - 1, 1); }
};

struct Mine {
    int x, y;
    long long w;
};

void compress(vector<int> &coords) {
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
}

int resolveId(const vector<int> &coords, const int value) {
    return lower_bound(coords.begin(), coords.end(), value) - coords.begin();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Mine> mines(N);
    vector<int> X, Y;

    X.reserve(N);
    Y.reserve(N);

    for (auto &[x, y, w] : mines) {
        cin >> x >> y >> w;

        X.push_back(x);
        Y.push_back(y);
    }

    sort(mines.begin(), mines.end(), [](const Mine &a, const Mine &b) { return a.y < b.y; });

    compress(X);
    compress(Y);

    vector<vector<Mine>> bundledMines(Y.size());

    for (auto &[x, y, w] : mines) {
        x = resolveId(X, x);
        y = resolveId(Y, y);

        bundledMines[y].push_back({x, y, w});
    }

    long long ans = LLONG_MIN;
    const int numLevels = (int)bundledMines.size();

    for (int i = 0; i < numLevels; i++) {
        SegmentTree st(vector<long long>(X.size(), 0));

        for (int j = i; j < numLevels; j++) {
            for (const auto &mine : bundledMines[j]) {
                st.update(mine.x, mine.w);
            }

            ans = max(ans, st.query(0, (int)X.size() - 1).maxSubarray);
        }
    }

    cout << ans << '\n';

    return 0;
}
