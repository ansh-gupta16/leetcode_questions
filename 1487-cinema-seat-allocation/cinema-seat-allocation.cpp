class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rowMasks;
        rowMasks.reserve(reservedSeats.size() * 2);

        for (auto& rs : reservedSeats) {
            int r = rs[0], s = rs[1];
            if (s >= 2 && s <= 9) {
                int bit = 1 << (s - 2);
                rowMasks[r] |= bit;
            }
        }

        const int LEFT  = 0b00001111; // seats 2-5
        const int MID   = 0b00111100; // seats 4-7
        const int RIGHT = 0b11110000; // seats 6-9

        long long total = 2LL * (n - (int)rowMasks.size());

        for (auto& [row, mask] : rowMasks) {
            if ((mask & LEFT) == 0 && (mask & RIGHT) == 0) {
                total += 2;
            } else if ((mask & LEFT) == 0 || (mask & MID) == 0 || (mask & RIGHT) == 0) {
                total += 1;
            }
        }

        return (int)total;
    }
};