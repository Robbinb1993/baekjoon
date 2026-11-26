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
            S_[idx] = {v, v, v, v};
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<long long> S(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> S[i];

    SegmentTree st(S);

    int Q;
    cin >> Q;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << st.query(l, r).maxSubarray << '\n';
    }

    return 0;
}
