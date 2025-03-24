#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 21  // Given 1 <= s.length, p.length <= 20

int memo[MAX_LEN][MAX_LEN];  // -1: uncomputed, 0: false, 1: true

// Recursive function with memoization
bool dfs(const char* s, const char* p, int i, int j) {
    // If already computed, return the cached result
    if (memo[i][j] != -1) return memo[i][j];

    int s_len = strlen(s);
    int p_len = strlen(p);

    // Base case: if both strings are exhausted
    if (i >= s_len && j >= p_len) return memo[i][j] = true;

    // If pattern exhausted but s still has characters
    if (j >= p_len) return memo[i][j] = false;

    // Check if first character matches
    bool match = (i < s_len) && (s[i] == p[j] || p[j] == '.');

    // Handle '*'
    if (j + 1 < p_len && p[j + 1] == '*') {
        // Don't use '*' (skip p[j] and p[j+1]) OR use '*' (consume one matching character)
        return memo[i][j] = (dfs(s, p, i, j + 2) || (match && dfs(s, p, i + 1, j)));
    }

    // If no '*', move to the next character
    if (match) return memo[i][j] = dfs(s, p, i + 1, j + 1);

    return memo[i][j] = false;
}

bool isMatch(char* s, char* p) {
    // Initialize memoization table with -1 (uncomputed)
    for (int i = 0; i < MAX_LEN; i++)
        for (int j = 0; j < MAX_LEN; j++)
            memo[i][j] = -1;

    return dfs(s, p, 0, 0);
}

// Test cases
int main() {
    printf("Test 1: %d\n", isMatch("aa", "a"));        // Expected: 0 (false)
    printf("Test 2: %d\n", isMatch("aa", "a*"));       // Expected: 1 (true)
    printf("Test 3: %d\n", isMatch("ab", ".*"));       // Expected: 1 (true)
    printf("Test 4: %d\n", isMatch("mississippi", "mis*is*p*.")); // Expected: 0 (false)
    printf("Test 5: %d\n", isMatch("aaa", "a*a"));    // Expected: 1 (true)
    return 0;
}