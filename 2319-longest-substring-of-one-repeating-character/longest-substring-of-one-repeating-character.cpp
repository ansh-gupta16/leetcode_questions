struct Node {
    int max_len, pre_len, suf_len, len;
    char pre_char, suf_char;
};

class SegmentTree {
private:
    vector<Node> tree;
    string s;
    int n;

    Node mergeNodes(const Node& left, const Node& right) {
        Node res;
        res.len = left.len + right.len;
        res.pre_char = left.pre_char;
        res.suf_char = right.suf_char;
        
        // Calculate prefix length
        res.pre_len = left.pre_len;
        if (left.pre_len == left.len && left.pre_char == right.pre_char) {
            res.pre_len += right.pre_len;
        }
        
        // Calculate suffix length
        res.suf_len = right.suf_len;
        if (right.suf_len == right.len && right.suf_char == left.suf_char) {
            res.suf_len += left.suf_len;
        }
        
        // Calculate max continuous length
        res.max_len = max(left.max_len, right.max_len);
        if (left.suf_char == right.pre_char) {
            res.max_len = max(res.max_len, left.suf_len + right.pre_len);
        }
        
        return res;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, 1, s[start], s[start]};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = mergeNodes(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            s[idx] = c;
            tree[node] = {1, 1, 1, 1, c, c};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, c);
        } else {
            update(2 * node + 1, mid + 1, end, idx, c);
        }
        tree[node] = mergeNodes(tree[2 * node], tree[2 * node + 1]);
    }

public:
    SegmentTree(const string& str) {
        s = str;
        n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void updateChar(int idx, char c) {
        update(1, 0, n - 1, idx, c);
    }

    int getMax() {
        return tree[1].max_len;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        SegmentTree st(s);
        vector<int> result;
        result.reserve(queryIndices.size());
        
        for (int i = 0; i < queryIndices.size(); ++i) {
            st.updateChar(queryIndices[i], queryCharacters[i]);
            result.push_back(st.getMax());
        }
        
        return result;
    }
};