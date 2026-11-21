#include <bits/stdc++.h>
using namespace std;

const int MAXN = 14;

int N, M;
int DP[MAXN][MAXN][1 << MAXN];

int solve(const int r, const int c, const int bm) {
    if (c == M) {
        return solve(r + 1, 0, bm);
    }
    if (r == N) {
        return bm == 0;
    }
    if (DP[r][c][bm] != -1) {
        return DP[r][c][bm];
    }
    // Skip this tile when it is already occupied.
    if (bm & (1 << c)) {
        return DP[r][c][bm] = solve(r, c + 1, bm ^ (1 << c));
    }

    long long tot = 0;
    // When tile to the right is not occupied, place a horizontal domino.
    if (c + 1 < M && !(bm & (1 << (c + 1)))) {
        tot += solve(r, c + 1, bm | (1 << (c + 1)));
    }
    // When there is still a row below in the grid, place a vertical domino.
    if (r + 1 < N) {
        tot += solve(r, c + 1, bm ^ (1 << c));
    }
    return DP[r][c][bm] = tot % 9901;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    memset(DP, -1, sizeof(DP));
    cout << solve(0, 0, 0) << '\n';

    return 0;
}
