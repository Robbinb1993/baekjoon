#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1500;
const int DX[4] = {-1, 0, 1, 0};
const int DY[4] = {0, 1, 0, -1};

int N, M;
vector<string> grid;
int swan1 = -1;
int swan2 = -1;

bool seen[MAXN][MAXN];

class DSU {
private:
    std::vector<int> parent, size;

public:
    DSU(const int n) {
        parent.assign(n, 0);
        size.assign(n, 1);
        std::iota(parent.begin(), parent.end(), 0);
    }
    int getSetSize(int v);
    int findSetParent(int v);
    bool sameSet(int a, int b);
    void uniteSets(int a, int b);
};

int DSU::getSetSize(int v) {
    int p = findSetParent(v);
    return size[p];
}

int DSU::findSetParent(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findSetParent(parent[v]);
}

bool DSU::sameSet(int a, int b) {
    return findSetParent(a) == findSetParent(b);
}

void DSU::uniteSets(int a, int b) {
    a = findSetParent(a);
    b = findSetParent(b);
    if (a != b) {
        if (size[a] < size[b])
            std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}

int toIndex(int r, int c) {
    return r * M + c;
}

void init(DSU& dsu, vector<pair<int, int>>& meltToday) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (grid[x][y] == 'X')
                continue;
            for (int k = 0; k < 4; k++) {
                int nx = x + DX[k];
                int ny = y + DY[k];

                if (!(nx >= 0 && nx < N && ny >= 0 && ny < M))
                    continue;

                if (!seen[nx][ny] && grid[nx][ny] == 'X') {
                    seen[nx][ny] = true;
                    meltToday.emplace_back(nx, ny);
                }
                else if (grid[nx][ny] != 'X')
                    dsu.uniteSets(toIndex(x, y), toIndex(nx, ny));
            }
        }
    }
}

int solve(DSU& dsu, vector<pair<int, int>>& meltToday) {
    if (dsu.sameSet(swan1, swan2))
        return 0;

    vector<pair<int, int>> meltTomorrow;
    int day = 0;

    while (!meltToday.empty()) {
        while (!meltToday.empty()) {
            auto [x, y] = meltToday.back();
            meltToday.pop_back();

            grid[x][y] = '.';

            for (int k = 0; k < 4; k++) {
                int nx = x + DX[k];
                int ny = y + DY[k];

                if (!(nx >= 0 && nx < N && ny >= 0 && ny < M))
                    continue;

                if (!seen[nx][ny] && grid[nx][ny] == 'X') {
                    seen[nx][ny] = true;
                    meltTomorrow.emplace_back(nx, ny);
                }
                else if (grid[nx][ny] != 'X')
                    dsu.uniteSets(toIndex(x, y), toIndex(nx, ny));
            }
        }

        meltToday.swap(meltTomorrow);
        day++;

        if (dsu.sameSet(swan1, swan2))
            return day;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    string S;

    for (int i = 0; i < N; i++) {
        cin >> S;
        grid.push_back(S);
        for (int j = 0; j < M && swan2 == -1; j++) {
            if (S[j] == 'L') {
                if (swan1 == -1) {
                    swan1 = toIndex(i, j);
                }
                else {
                    swan2 = toIndex(i, j);
                    break;
                }
            }
        }
    }

    DSU dsu(N * M);
    vector<pair<int, int>> meltToday;

    init(dsu, meltToday);

    cout << solve(dsu, meltToday) << '\n';

    return 0;
}
