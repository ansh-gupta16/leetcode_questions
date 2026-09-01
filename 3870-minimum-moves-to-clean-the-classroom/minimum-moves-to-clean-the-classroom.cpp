class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        int mn = m * n;

        // Flatten grid for faster access
        vector<char> grid(mn);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                grid[i * n + j] = classroom[i][j];

        int sr = -1, sc = -1;
        vector<int> litBit(mn, -1);
        int L = 0;

        for (int idx = 0; idx < mn; idx++) {
            char ch = grid[idx];
            if (ch == 'S') {
                sr = idx / n; sc = idx % n;
            } else if (ch == 'L') {
                litBit[idx] = L++;
            }
        }

        int fullMask = (L == 0) ? 0 : ((1 << L) - 1);
        if (fullMask == 0) return 0;

        int maskCount = 1 << L;
        int eCount = energy + 1;

        // Flat index: ((r*n+c) * eCount + e) * maskCount + mask
        long long totalStates = (long long)mn * eCount * maskCount;
        vector<bool> visited(totalStates, false);

        auto encode = [&](int r, int c, int e, int mask) -> int {
            return ((r * n + c) * eCount + e) * maskCount + mask;
        };

        // Array-based BFS queue: store state code and moves in parallel arrays
        vector<int> queueState(totalStates);
        vector<int> queueMoves(totalStates);
        int head = 0, tail = 0;

        int startCode = encode(sr, sc, energy, 0);
        visited[startCode] = true;
        queueState[tail] = startCode;
        queueMoves[tail] = 0;
        tail++;

        static const int dr[4] = {-1, 1, 0, 0};
        static const int dc[4] = {0, 0, -1, 1};

        while (head < tail) {
            int code = queueState[head];
            int moves = queueMoves[head];
            head++;

            int mask = code % maskCount;
            int tmp = code / maskCount;
            int e = tmp % eCount;
            int rc = tmp / eCount;
            int r = rc / n;
            int c = rc % n;

            if (mask == fullMask) {
                return moves;
            }

            if (e == 0) continue;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;

                int nIdx = nr * n + nc;
                char ch = grid[nIdx];
                if (ch == 'X') continue;

                int newE = (ch == 'R') ? energy : (e - 1);
                int newMask = mask;
                int bit = litBit[nIdx];
                if (bit >= 0) newMask |= (1 << bit);

                int ncode = encode(nr, nc, newE, newMask);
                if (!visited[ncode]) {
                    visited[ncode] = true;
                    queueState[tail] = ncode;
                    queueMoves[tail] = moves + 1;
                    tail++;
                }
            }
        }

        return -1;
    }
};