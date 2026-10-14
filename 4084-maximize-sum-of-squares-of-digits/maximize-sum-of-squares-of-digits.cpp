class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        long long maxPossible = 9LL * num;
        if (sum > maxPossible || sum < 1) return "";

        long long q = sum / 9;
        int r = sum % 9;

        // q nines, one digit of value r (if r > 0), rest zeros
        long long nonZeroCount = q + (r > 0 ? 1 : 0);
        long long zeroCount = (long long)num - nonZeroCount;

        string result;
        result.reserve(num);

        for (long long i = 0; i < q; i++) {
            result += '9';
        }
        if (r > 0) {
            result += char('0' + r);
        }
        for (long long i = 0; i < zeroCount; i++) {
            result += '0';
        }

        return result;
    }
};