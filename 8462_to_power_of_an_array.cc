#include <bits/stdc++.h>
using namespace std;

class Mo {
private:
    struct Query {
        int l, r, id;
    };

    int blockSize_;
    vector<Query> queries_;

public:
    Mo(int n, const vector<pair<int, int>> &ranges) : blockSize_(max(1, (int)sqrt(n))) {
        for (int i = 0; i < (int)ranges.size(); ++i) {
            const auto [l, r] = ranges[i];
            queries_.push_back({l, r, i});
        }
    }

    template <class Add, class Remove, class Answer>
    auto solve(Add add, Remove remove, Answer getAnswer) {
        using Result = decltype(getAnswer());

        sort(queries_.begin(), queries_.end(), [&](const Query &a, const Query &b) {
            const int blockA = a.l / blockSize_;
            const int blockB = b.l / blockSize_;

            if (blockA != blockB)
                return blockA < blockB;

            return a.r < b.r;
        });

        vector<Result> results(queries_.size());

        int L = 0, R = -1;

        for (const auto &q : queries_) {
            while (R < q.r)
                add(++R);
            while (L > q.l)
                add(--L);
            while (R > q.r)
                remove(R--);
            while (L < q.l)
                remove(L++);

            results[q.id] = getAnswer();
        }

        return results;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t, l, r;
    cin >> n >> t;

    vector<int> V(n);
    for (int i = 0; i < n; i++)
        cin >> V[i];

    vector<pair<int, int>> queries;
    queries.reserve(t);
    for (int i = 0; i < t; i++) {
        cin >> l >> r;
        queries.emplace_back(l - 1, r - 1);
    }

    Mo mo(n, queries);

    vector<int> freq(1000001, 0);
    long long answer = 0;

    auto results = mo.solve([&](int i) { answer += (2 * freq[V[i]]++ + 1) * (long long)V[i]; },
                            [&](int i) { answer += (1 - 2 * freq[V[i]]--) * (long long)V[i]; },
                            [&]() { return answer; });

    for (auto res : results)
        cout << res << '\n';

    return 0;
}
