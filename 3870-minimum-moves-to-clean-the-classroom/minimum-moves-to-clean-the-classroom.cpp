class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
         int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        vector<pair<int,int>> litterCells;
        unordered_map<int,int> litterIndex; // r*n+c -> bit index

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char ch = classroom[i][j];
                if (ch == 'S') {
                    sr = i; sc = j;
                } else if (ch == 'L') {
                    litterIndex[i * n + j] = litterCells.size();
                    litterCells.push_back({i, j});
                }
            }
        }

        int L = litterCells.size();
        int fullMask = (L == 0) ? 0 : ((1 << L) - 1);

        if (fullMask == 0) return 0; // no litter to collect

        // visited[r][c][e][mask]
        // dims: m * n * (energy+1) * (1<<L)
        int maskCount = 1 << L;
        vector<vector<vector<vector<bool>>>> visited(
            m, vector<vector<vector<bool>>>(
                n, vector<vector<bool>>(
                    energy + 1, vector<bool>(maskCount, false)
                )
            )
        );

        struct State {
            int r, c, e, mask, moves;
        };

        queue<State> q;
        int startMask = 0; // S cell is never L per constraints
        visited[sr][sc][energy][startMask] = true;
        q.push({sr, sc, energy, startMask, 0});

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            State cur = q.front();
            q.pop();

            if (cur.mask == fullMask) {
                return cur.moves;
            }

            if (cur.e == 0) {
                continue; // no energy left, can't move further (and not on goal)
            }

            for (int d = 0; d < 4; d++) {
                int nr = cur.r + dr[d];
                int nc = cur.c + dc[d];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                char ch = classroom[nr][nc];
                if (ch == 'X') continue;

                int newE = (ch == 'R') ? energy : (cur.e - 1);
                int newMask = cur.mask;
                if (ch == 'L') {
                    auto it = litterIndex.find(nr * n + nc);
                    if (it != litterIndex.end()) {
                        newMask |= (1 << it->second);
                    }
                }

                if (!visited[nr][nc][newE][newMask]) {
                    visited[nr][nc][newE][newMask] = true;
                    q.push({nr, nc, newE, newMask, cur.moves + 1});
                }
            }
        }

        return -1;
    }
};