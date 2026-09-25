class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int pos = 0;
        set<string> result = parseConcat(expression, pos);
        return vector<string>(result.begin(), result.end());
    }

private:
    // Parses a sequence of concatenated factors until ',' or '}' or end of string
    set<string> parseConcat(const string& s, int& pos) {
        vector<set<string>> factors;
        while (pos < (int)s.size() && s[pos] != ',' && s[pos] != '}') {
            factors.push_back(parseFactor(s, pos));
        }
        
        // Cartesian product concatenation of all factors
        set<string> result;
        result.insert("");
        for (auto& factorSet : factors) {
            set<string> newResult;
            for (const string& prefix : result) {
                for (const string& suffix : factorSet) {
                    newResult.insert(prefix + suffix);
                }
            }
            result = newResult;
        }
        return result;
    }

    // Parses either a {..,..} union group or a run of literal letters
    set<string> parseFactor(const string& s, int& pos) {
        if (s[pos] == '{') {
            pos++; // consume '{'
            set<string> result;
            while (true) {
                set<string> sub = parseConcat(s, pos);
                result.insert(sub.begin(), sub.end());
                if (pos < (int)s.size() && s[pos] == ',') {
                    pos++; // consume ','
                    continue;
                }
                break;
            }
            pos++; // consume '}'
            return result;
        } else {
            // consecutive lowercase letters form a single literal word
            int start = pos;
            while (pos < (int)s.size() && islower(s[pos])) {
                pos++;
            }
            return {s.substr(start, pos - start)};
        }
    }
};