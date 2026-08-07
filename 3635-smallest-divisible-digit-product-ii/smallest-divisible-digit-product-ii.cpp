#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    static void get_factors(int d, int &c2, int &c3, int &c5, int &c7) {
        c2 = c3 = c5 = c7 = 0;
        if (d == 2) c2 = 1;
        else if (d == 3) c3 = 1;
        else if (d == 4) c2 = 2;
        else if (d == 5) c5 = 1;
        else if (d == 6) { c2 = 1; c3 = 1; }
        else if (d == 7) c7 = 1;
        else if (d == 8) c2 = 3;
        else if (d == 9) c3 = 2;
    }

public:
    string smallestNumber(string num, long long t) {
        // DP table for minimum digits needed to gather powers of 2 and 3
        static int dp[60][40];
        static bool initialized = false;
        if (!initialized) {
            for (int i = 0; i < 60; ++i) {
                for (int j = 0; j < 40; ++j) {
                    dp[i][j] = 1e9; // initialize with infinity equivalent
                }
            }
            dp[0][0] = 0;
            int moves[6][2] = {{1,0}, {0,1}, {2,0}, {1,1}, {3,0}, {0,2}}; // prime factors for {2,3,4,6,8,9}
            
            for (int r2 = 0; r2 < 60; ++r2) {
                for (int r3 = 0; r3 < 40; ++r3) {
                    if (r2 == 0 && r3 == 0) continue;
                    int res = 1e9;
                    for (auto& m : moves) {
                        int f2 = m[0], f3 = m[1];
                        if (r2 == 0 && f2 > 0 && f3 == 0) continue;
                        if (r3 == 0 && f3 > 0 && f2 == 0) continue;
                        
                        int nr2 = max(0, r2 - f2);
                        int nr3 = max(0, r3 - f3);
                        if (nr2 == r2 && nr3 == r3) continue;
                        
                        res = min(res, 1 + dp[nr2][nr3]);
                    }
                    dp[r2][r3] = res;
                }
            }
            initialized = true;
        }

        // Step 1: Factorize t
        int req2 = 0, req3 = 0, req5 = 0, req7 = 0;
        long long temp = t;
        while (temp % 2 == 0) { req2++; temp /= 2; }
        while (temp % 3 == 0) { req3++; temp /= 3; }
        while (temp % 5 == 0) { req5++; temp /= 5; }
        while (temp % 7 == 0) { req7++; temp /= 7; }
        
        // If t has prime factors other than 2, 3, 5, 7, no digit product can ever be divisible by t.
        if (temp > 1) return "-1";
        
        int n = num.length();
        vector<int> p2(n + 1, 0), p3(n + 1, 0), p5(n + 1, 0), p7(n + 1, 0);
        int first_zero = n;
        
        // Accumulate prefix factors for num up to the first '0'
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
            int c2, c3, c5, c7;
            get_factors(num[i] - '0', c2, c3, c5, c7);
            p2[i + 1] = p2[i] + c2;
            p3[i + 1] = p3[i] + c3;
            p5[i + 1] = p5[i] + c5;
            p7[i + 1] = p7[i] + c7;
        }
        
        // Step 2: Check if `num` is already fully valid
        if (first_zero == n && p2[n] >= req2 && p3[n] >= req3 && p5[n] >= req5 && p7[n] >= req7) {
            return num;
        }
        
        // Helper lambda to construct the smallest valid suffix
        auto build = [&](string pref_str, int curr2, int curr3, int curr5, int curr7, int total_len) -> string {
            string ans = pref_str;
            ans.reserve(total_len);
            int rem_len = total_len - ans.length();
            
            for (int i = 0; i < rem_len; ++i) {
                for (int c = 1; c <= 9; ++c) {
                    int fc2, fc3, fc5, fc7;
                    get_factors(c, fc2, fc3, fc5, fc7);
                    
                    int r2 = max(0, req2 - curr2 - fc2);
                    int r3 = max(0, req3 - curr3 - fc3);
                    int r5 = max(0, req5 - curr5 - fc5);
                    int r7 = max(0, req7 - curr7 - fc7);
                    
                    if (r5 + r7 + dp[r2][r3] <= (rem_len - 1 - i)) {
                        ans += (char)('0' + c);
                        curr2 += fc2; curr3 += fc3; curr5 += fc5; curr7 += fc7;
                        break;
                    }
                }
            }
            return ans;
        };
        
        // Step 3: Find optimal divergence point retaining maximum prefix
        for (int i = min(n - 1, first_zero); i >= 0; --i) {
            int start_d = num[i] - '0' + 1;
            for (int d = start_d; d <= 9; ++d) {
                int f2, f3, f5, f7;
                get_factors(d, f2, f3, f5, f7);
                
                int r2 = max(0, req2 - p2[i] - f2);
                int r3 = max(0, req3 - p3[i] - f3);
                int r5 = max(0, req5 - p5[i] - f5);
                int r7 = max(0, req7 - p7[i] - f7);
                
                // If the required digits to fulfill factors fits into the rest of the string
                if (r5 + r7 + dp[r2][r3] <= n - 1 - i) {
                    return build(num.substr(0, i) + to_string(d), p2[i] + f2, p3[i] + f3, p5[i] + f5, p7[i] + f7, n);
                }
            }
        }
        
        // Step 4: No same-length substitution works, extend length 
        int min_required_len = req5 + req7 + dp[req2][req3];
        int m = max(n + 1, min_required_len);
        
        return build("", 0, 0, 0, 0, m);
    }
};