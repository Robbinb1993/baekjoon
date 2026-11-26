#include <bits/stdc++.h>
using namespace std;

class Bitset {
private:
    using Word = unsigned long long;
    static constexpr size_t W = 64;

    size_t n_;
    vector<Word> words;

    void trim() {
        if (n_ % W) {
            words.back() &= (1ULL << (n_ % W)) - 1;
        }
    }

    static Word dilate32(Word x) {
        x &= 0x00000000FFFFFFFFULL;
        x = (x | (x << 16)) & 0x0000FFFF0000FFFFULL;
        x = (x | (x << 8)) & 0x00FF00FF00FF00FFULL;
        x = (x | (x << 4)) & 0x0F0F0F0F0F0F0F0FULL;
        x = (x | (x << 2)) & 0x3333333333333333ULL;
        x = (x | (x << 1)) & 0x5555555555555555ULL;
        return x;
    }

public:
    explicit Bitset(size_t n) : n_(n), words((n + W - 1) / W, 0) {}

    void set(size_t i) { words[i / W] |= 1ULL << (i % W); }

    bool test(size_t i) const { return (words[i / W] >> (i % W)) & 1ULL; }

    void reset() { fill(words.begin(), words.end(), 0); }

    Bitset &operator|=(const Bitset &other) {
        for (size_t i = 0; i < words.size(); ++i) {
            words[i] |= other.words[i];
        }

        return *this;
    }

    friend Bitset operator|(Bitset a, const Bitset &b) {
        a |= b;
        return a;
    }

    Bitset operator<<(size_t k) const {
        Bitset res(n_);
        if (k >= n_)
            return res;

        size_t q = k / W;
        size_t r = k % W;

        for (size_t i = q; i < words.size(); ++i) {
            res.words[i] = words[i - q] << r;

            if (r && i > q) {
                res.words[i] |= words[i - q - 1] >> (W - r);
            }
        }

        res.trim();
        return res;
    }

    Bitset operator>>(size_t k) const {
        Bitset res(n_);
        if (k >= n_)
            return res;

        size_t q = k / W;
        size_t r = k % W;

        for (size_t i = 0; i + q < words.size(); ++i) {
            res.words[i] = words[i + q] >> r;

            if (r && i + q + 1 < words.size()) {
                res.words[i] |= words[i + q + 1] << (W - r);
            }
        }

        return res;
    }

    Bitset multiplyBy2() const {
        Bitset res(n_);

        for (size_t i = 0; i < words.size(); ++i) {
            if (2 * i >= words.size())
                break;

            res.words[2 * i] = dilate32(words[i]);

            if (2 * i + 1 < words.size()) {
                res.words[2 * i + 1] = dilate32(words[i] >> 32);
            }
        }

        res.trim();
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    Bitset bs(500001);
    bs.set(N);

    int toAdd = 1;
    int day = 0;
    int ans = -1;

    while (true) {
        if (bs.test(K)) {
            ans = day;
            break;
        }

        K += toAdd++;
        if (K > 500000)
            break;

        bs = (bs << 1) | (bs >> 1) | bs.multiplyBy2();
        day++;
    }

    cout << ans << '\n';

    return 0;
}
