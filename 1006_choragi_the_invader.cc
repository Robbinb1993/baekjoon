#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 10000;

int N, W;
int enemies[2 * MAXN];
int DP[MAXN][4][4];

int solve(const int outerIdx, const int startBm, const int bm) {
    if (outerIdx == N) {
        if ((startBm | bm) == 3) {
            return 0;
        }
        return INF;
    }

    if (DP[outerIdx][startBm][bm] != -1)
        return DP[outerIdx][startBm][bm];

    int innerIdx = outerIdx + N;

    DP[outerIdx][startBm][bm] = INF;
    for (int soldierCoverage = 0; soldierCoverage < (1 << 5); soldierCoverage++) {
        int currBm = bm;
        int nextBm = 0;
        int soldiersUsed = 0;

        if (soldierCoverage & 1) {
            currBm |= 1;
            soldiersUsed++;
        }
        if (soldierCoverage & (1 << 1)) {
            currBm |= 2;
            soldiersUsed++;
        }
        if (soldierCoverage & (1 << 2)) {
            int nxtOuterIdx = (outerIdx + 1) % N;
            if (enemies[outerIdx] + enemies[nxtOuterIdx] > W)
                continue;
            soldiersUsed++;
            currBm |= 1;
            nextBm |= 1;
        }
        if (soldierCoverage & (1 << 3)) {
            int nxtInnerIdx = N + (outerIdx + 1) % N;
            if (enemies[innerIdx] + enemies[nxtInnerIdx] > W)
                continue;
            soldiersUsed++;
            currBm |= 2;
            nextBm |= 2;
        }
        if (soldierCoverage & (1 << 4)) {
            if (enemies[outerIdx] + enemies[innerIdx] > W)
                continue;
            soldiersUsed++;
            currBm |= 3;
        }

        if (outerIdx != 0 && currBm != 3)
            continue;
        else if (outerIdx == 0)
            DP[outerIdx][startBm][bm] =
            min(DP[outerIdx][startBm][bm], soldiersUsed +
                solve(outerIdx + 1, currBm, nextBm));
        else
            DP[outerIdx][startBm][bm] =
            min(DP[outerIdx][startBm][bm], soldiersUsed +
                solve(outerIdx + 1, startBm, nextBm));
    }

    return DP[outerIdx][startBm][bm];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> W;
        for (int i = 0; i < 2 * N; i++)
            cin >> enemies[i];
        memset(DP, -1, N * sizeof(DP[0]));
        cout << solve(0, 0, 0) << '\n';
    }

    return 0;
}
