#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#ifndef EXPERIMENT
#define EXPERIMENT 1
#endif

// Recursive function (DFS-based)
bool dfs(const char* s, const char* p, int i, int j) {
    int s_len = strlen(s);
    int p_len = strlen(p);

    // If both s and p are exhausted, return true
    if (i >= s_len && j >= p_len) return true;

    // If pattern is exhausted but string is not, return false
    if (j >= p_len) return false;

    // Check if current characters match (or p[j] is '.')
    bool match = (i < s_len) && (s[i] == p[j] || p[j] == '.');

    // Handle '*' in pattern
    if (j + 1 < p_len && p[j + 1] == '*') {
        return (dfs(s, p, i, j + 2)) ||  // Don't use '*'
               (match && dfs(s, p, i + 1, j)); // Use '*' (match one more character)
    }

    // If characters match, proceed to next character in both s and p
    if (match) return dfs(s, p, i + 1, j + 1);

    return false;
}

// Wrapper function for regex matching
bool isMatch(const char* s, const char* p) {
    return dfs(s, p, 0, 0);
}

// Generate a random string of lowercase letters
void generateRandomString(char* str, int length) {
    for (int i = 0; i < length; i++) {
        str[i] = 'a' + rand() % 26;  // Random lowercase letter
    }
    str[length] = '\0';
}

// Generate a random pattern including '*', '.' and letters
void generateRandomPattern(char* pattern, int length) {
    for (int i = 0; i < length; i++) {
        int r = rand() % 4;
        if (r == 0) pattern[i] = '.';   // 25% chance for '.'
        else if (r == 1 && i > 0) {     // 25% chance for '*' (ensuring valid placement)
            pattern[i] = '*';
        } else pattern[i] = 'a' + rand() % 26; // 50% chance for letters
    }
    pattern[length] = '\0';
}

// Main function
int main(int argc, char** argv) {
#if EXPERIMENT == 0
    // **Normal Mode: Run Test Cases**
    printf("Test 1: %d\n", isMatch("aa", "a"));        // Expected: 0 (false)
    printf("Test 2: %d\n", isMatch("aa", "a*"));       // Expected: 1 (true)
    printf("Test 3: %d\n", isMatch("ab", ".*"));       // Expected: 1 (true)
    printf("Test 4: %d\n", isMatch("mississippi", "mis*is*p*.")); // Expected: 0 (false)
    printf("Test 5: %d\n", isMatch("aaa", "a*a"));    // Expected: 1 (true)
    printf("Test 6: %d\n", isMatch("aaaaaaaaaaaaaaaaaaa", "a*a*a*a*a*a*a*a*a*b"));    // Expected: 0 (true)
#else
    if (argc != 2) {
        printf("One argument expected: ./lowSolution1.c 1000\n");
        return 1;
    }
    // Convert the argument of the program into an integer
    const int size = atoi(argv[1]);
    // **Benchmark Mode: Measure Execution Time for n*n Calls**
    srand(time(NULL)); // Seed randomness
    clock_t start, end;
    double total_time;

    // Get the time before we start
    start = clock();

    // Perform the isMatch
    char s[size], p[size];
    generateRandomString(s, rand() % (size - 1) + 1);
    generateRandomPattern(p, rand() % (size - 1) + 1);
    isMatch(s, p);

    // Get the time after we are done
    end = clock();
    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken for %dx%d matches: %.6f seconds\n", size, size, total_time);

#endif

    return 0;
}
