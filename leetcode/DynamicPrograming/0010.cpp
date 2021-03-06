#include <string>
#include <gtest/gtest.h>

class Solution {
public:
    bool isMatch(std::string s, std::string p);
};

bool Solution::isMatch(std::string s, std::string p) {
    p = ' ' + p;
    s = ' ' + s;
    const int m = p.length();
    const int n = s.length();
    bool dp[m][n];
    dp[0][0] = true;

    for (int i = 1; i < m; i++) {
        dp[i][0] = p[i] == '*' && dp[i-2][0];

        for (int j = 1; j < n; j++) {
            if (p[i] == '.' || p[i] == s[j]) 
                dp[i][j] = dp[i-1][j-1];
            else if (p[i] == '*')
                dp[i][j] = dp[i-2][j] || (dp[i][j-1] && (p[i-1] == '.' || p[i-1] == s[j]));
        }
    }
    return dp[m-1][n-1];
}

TEST(TestIsMatchSuite, TestIsMatch) {
    Solution solution = Solution();
    ASSERT_FALSE(solution.isMatch("aa", "a"));
    ASSERT_TRUE(solution.isMatch("aa", "a*"));
    ASSERT_TRUE(solution.isMatch("ab", ".*"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}