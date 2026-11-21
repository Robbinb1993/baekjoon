#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int N, M;
int grid[MAXN][MAXN];

string zigzagRowByRow() {
    string path;

    for (int r = 0; r < N; r++) {
        char dir = r % 2 == 0 ? 'R' : 'L';
        path.append(M - 1, dir);

        if (r + 1 < N)
            path += 'D';
    }

    return path;
}

string zigzagColByCol() {
    string path;

    for (int c = 0; c < M; c++) {
        char dir = c % 2 == 0 ? 'D' : 'U';
        path.append(N - 1, dir);

        if (c + 1 < M)
            path += 'R';
    }

    return path;
}

pair<int, int> findCellToSkip() {
    int minValue = INT_MAX;
    pair<int, int> skipCell = {-1, -1};

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if ((r + c) % 2 == 1 && grid[r][c] < minValue) {
                minValue = grid[r][c];
                skipCell = {r, c};
            }
        }
    }

    return skipCell;
}

void appendHorizontalRows(string& path, int rowCount, bool startFromLeft) {
    bool moveRight = startFromLeft;

    for (int r = 0; r < rowCount; r++) {
        path.append(M - 1, moveRight ? 'R' : 'L');

        if (r + 1 < rowCount)
            path += 'D';

        moveRight = !moveRight;
    }
}

void appendVerticalZigzag(string& path, int skipCol, bool startFromLeft) {
    char horizontal = startFromLeft ? 'R' : 'L';
    int step = startFromLeft ? 1 : -1;
    int col = startFromLeft ? 0 : M - 1;
    int endCol = startFromLeft ? M - 1 : 0;
    bool goDown = true;

    while (true) {
        if (col == skipCol) {
            if (col == endCol)
                break;

            path += horizontal;
            col += step;
        }

        path += goDown ? 'D' : 'U';
        goDown = !goDown;

        if (col == endCol)
            break;

        path += horizontal;
        col += step;
    }
}

string zigzagSkipCell() {
    auto [skipR, skipC] = findCellToSkip();
    int verticalPatternStartRow = skipR == 0 ? 0 : skipR - 1;

    string path;
    if (verticalPatternStartRow > 0) {
        appendHorizontalRows(path, verticalPatternStartRow, true);
        path += 'D';
    }

    bool startFromLeft = verticalPatternStartRow % 2 == 0;

    appendVerticalZigzag(path, skipC, startFromLeft);

    int rowsRemaining = N - (verticalPatternStartRow + 2);
    if (rowsRemaining > 0) {
        path += 'D';
        appendHorizontalRows(path, rowsRemaining, !startFromLeft);
    }

    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }

    if (N % 2 == 1) {
        cout << zigzagRowByRow() << '\n';
    }
    else if (M % 2 == 1) {
        cout << zigzagColByCol() << '\n';
    }
    else {
        cout << zigzagSkipCell() << '\n';
    }

    return 0;
}
