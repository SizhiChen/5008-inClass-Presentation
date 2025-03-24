#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    int m = strlen(s), n = strlen(p);
    bool dp[m + 1][n + 1];

    memset(dp, false, sizeof(dp));
    dp[0][0] = true;

    for (int j = 2; j <= n; j++) {
        if (p[j - 1] == '*')
            dp[0][j] = dp[0][j - 2];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // directly match or match with "."
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } 
            // matchs using "*"
            else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    dp[i][j] |= dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];
}

// 测试代码
int main() {
    printf("Test 1: %d\n", isMatch("aa", "a"));       // 0 (false)
    printf("Test 2: %d\n", isMatch("aa", "a*"));      // 1 (true)
    printf("Test 3: %d\n", isMatch("ab", ".*"));      // 1 (true)
    printf("Test 4: %d\n", isMatch("mississippi", "mis*is*p*.")); // 0 (false)
    printf("Test 5: %d\n", isMatch("aaa", "a*a"));   // 1 (true)
    return 0;
}
