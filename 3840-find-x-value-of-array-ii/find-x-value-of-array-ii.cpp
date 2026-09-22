class Solution {
    struct Node {
        int prod;
        int mat[5][5];
    };

    int n, k;
    vector<int> a;
    vector<Node> tree;

    Node makeLeaf(int val) {
        Node nd;
        int v = val % k;
        nd.prod = v;
        for (int x = 0; x < k; x++)
            for (int b = 0; b < k; b++)
                nd.mat[x][b] = ((x * v) % k == b) ? 1 : 0;
        return nd;
    }

    Node combine(const Node& L, const Node& R) {
        Node res;
        res.prod = (L.prod * R.prod) % k;
        for (int x = 0; x < k; x++) {
            int aP = (x * L.prod) % k;
            for (int b = 0; b < k; b++) {
                res.mat[x][b] = L.mat[x][b] + R.mat[aP][b];
            }
        }
        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = makeLeaf(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = makeLeaf(val);
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2*node, l, mid, idx, val);
        else update(2*node+1, mid+1, r, idx, val);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        if (qr <= mid) return query(2*node, l, mid, ql, qr);
        if (ql > mid) return query(2*node+1, mid+1, r, ql, qr);
        Node leftRes = query(2*node, l, mid, ql, qr);
        Node rightRes = query(2*node+1, mid+1, r, ql, qr);
        return combine(leftRes, rightRes);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k_, vector<vector<int>>& queries) {
        n = nums.size();
        k = k_;
        a = nums;
        tree.assign(4 * n, Node());
        build(1, 0, n - 1);

        vector<int> result;
        result.reserve(queries.size());
        int startRem = 1 % k;

        for (auto& q : queries) {
            int idx = q[0], val = q[1], start = q[2], x = q[3];
            update(1, 0, n - 1, idx, val);
            Node res = query(1, 0, n - 1, start, n - 1);
            result.push_back(res.mat[startRem][x]);
        }
        return result;
    }
};