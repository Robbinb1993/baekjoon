#include <bits/stdc++.h>
using namespace std;

class MonotoneCHT {
private:
    struct Line {
        long long a, c;

        long long eval(int x) const { return a * x + c; }
    };

    deque<Line> hull_;

    static bool obsolete(const Line &a, const Line &b, const Line &c) {
        return ((__int128)b.c - a.c) * (b.a - c.a) >= ((__int128)c.c - b.c) * (a.a - b.a);
    }

public:
    // Add lines with non-increasing slopes
    void addLine(int a, long long c) {
        if (!hull_.empty() && hull_.back().a == a) {
            if (hull_.back().c <= c)
                return;

            hull_.pop_back();
        }

        Line line{a, c};

        while (hull_.size() >= 2 && obsolete(hull_[hull_.size() - 2], hull_.back(), line)) {
            hull_.pop_back();
        }

        hull_.push_back(line);
    }

    // Query minimum with non-decreasing x
    long long query(int x) {
        while (hull_.size() >= 2 && hull_[1].eval(x) <= hull_[0].eval(x)) {
            hull_.pop_front();
        }

        return hull_.front().eval(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> A(N), B(N);

    for (int i = 0; i < N; i++)
        cin >> A[i];
    for (int i = 0; i < N; i++)
        cin >> B[i];

    MonotoneCHT cht;

    cht.addLine(A[N - 1], 0);
    long long answer = 0;

    for (int i = N - 2; i >= 0; --i) {
        answer = cht.query(B[i]);
        cht.addLine(A[i], answer);
    }

    cout << answer << '\n';

    return 0;
}
