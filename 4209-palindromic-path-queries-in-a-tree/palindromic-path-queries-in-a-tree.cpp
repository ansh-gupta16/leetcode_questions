class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) < n) LOG++;
        LOG += 1;

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n, 0), tin(n, 0), tout(n, 0), parent(n, 0);
        vector<int> P0(n, 0);

        // Iterative DFS to compute tin/tout/depth/parent/P0
        {
            vector<int> childPtr(n, 0);
            vector<bool> visited(n, false);
            vector<int> stk;
            stk.reserve(n);
            stk.push_back(0);
            visited[0] = true;
            parent[0] = 0;
            depth[0] = 0;
            P0[0] = (1 << (s[0] - 'a'));
            int timer = 0;
            tin[0] = timer++;

            while (!stk.empty()) {
                int u = stk.back();
                if (childPtr[u] < (int)adj[u].size()) {
                    int v = adj[u][childPtr[u]++];
                    if (!visited[v]) {
                        visited[v] = true;
                        parent[v] = u;
                        depth[v] = depth[u] + 1;
                        P0[v] = P0[u] ^ (1 << (s[v] - 'a'));
                        tin[v] = timer++;
                        stk.push_back(v);
                    }
                } else {
                    tout[u] = timer - 1;
                    stk.pop_back();
                }
            }
        }

        // Binary lifting table
        for (int v = 0; v < n; v++) up[0][v] = parent[v];
        for (int k = 1; k < LOG; k++) {
            for (int v = 0; v < n; v++) {
                up[k][v] = up[k-1][up[k-1][v]];
            }
        }

        auto lca = [&](int u, int v) -> int {
            if (depth[u] < depth[v]) swap(u, v);
            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; k++) {
                if ((diff >> k) & 1) u = up[k][u];
            }
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][u] != up[k][v]) {
                    u = up[k][u];
                    v = up[k][v];
                }
            }
            return parent[u];
        };

        // Fenwick tree with XOR range-update / point-query
        vector<int> bit(n + 2, 0);
        auto bitUpdate = [&](int i, int val) {
            for (++i; i <= n; i += i & (-i)) bit[i] ^= val;
        };
        auto bitQuery = [&](int i) -> int {
            int res = 0;
            for (++i; i > 0; i -= i & (-i)) res ^= bit[i];
            return res;
        };
        auto rangeXorUpdate = [&](int l, int r, int val) {
            bitUpdate(l, val);
            if (r + 1 < n) bitUpdate(r + 1, val);
        };

        auto currentP = [&](int x) -> int {
            return P0[x] ^ bitQuery(tin[x]);
        };

        vector<bool> answer;

        for (auto& q : queries) {
            istringstream iss(q);
            string type;
            iss >> type;
            if (type == "update") {
                int u; string c;
                iss >> u >> c;
                char newChar = c[0];
                int oldBit = 1 << (s[u] - 'a');
                int newBit = 1 << (newChar - 'a');
                int delta = oldBit ^ newBit;
                if (delta != 0) {
                    rangeXorUpdate(tin[u], tout[u], delta);
                }
                s[u] = newChar;
            } else {
                int u, v;
                iss >> u >> v;
                int l = lca(u, v);
                int pathMask = currentP(u) ^ currentP(v) ^ (1 << (s[l] - 'a'));
                int oddCount = __builtin_popcount(pathMask);
                answer.push_back(oddCount <= 1);
            }
        }

        return answer;
    }
};