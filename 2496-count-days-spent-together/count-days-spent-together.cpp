class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        auto toDayOfYear = [&](const string& date) -> int {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));
            int total = day;
            for (int m = 0; m < month - 1; m++) {
                total += daysInMonth[m];
            }
            return total;
        };

        int aliceStart = toDayOfYear(arriveAlice);
        int aliceEnd = toDayOfYear(leaveAlice);
        int bobStart = toDayOfYear(arriveBob);
        int bobEnd = toDayOfYear(leaveBob);

        int start = max(aliceStart, bobStart);
        int end = min(aliceEnd, bobEnd);

        return max(0, end - start + 1);
    }
};