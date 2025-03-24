#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#ifndef EXPERIMENT
#define EXPERIMENT 0
#endif

void generateRandomString(char* str, int length);
void generateRandomPattern(char* pattern, int length);

int** allocateMemo(int m, int n);
void freeMemo(int** memo, int m);

// Dynamic Programming Approach for Regex Matching
bool isMatch(char* s, char* p) {
    int m = strlen(s), n = strlen(p);

    // Allocate memory dynamically based on input size
    // int** memo = allocateMemo(m, n);
    bool memo[m + 1][n + 1];

    // Initialize memoization table with 0 (false)
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            memo[i][j] = 0;
        }
    }
    memo[0][0] = true;

    for (int j = 2; j <= n; j++) {
        if (p[j - 1] == '*') {
            memo[0][j] = memo[0][j - 2];
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // Direct match or match with "."
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                memo[i][j] = memo[i - 1][j - 1];
            } 
            // Matching using "*"
            else if (p[j - 1] == '*') {
                memo[i][j] = memo[i][j - 2];
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    memo[i][j] |= memo[i - 1][j];
                }
            }
        }
    }

    // Store result before freeing memory
    bool result = memo[m][n];

    // Free allocated memory
    // freeMemo(memo, m);

    return result;
}

// Test cases
int main(int argc, char** argv) {
#if EXPERIMENT == 0
    // Test cases
    printf("Test 1: %d\n", isMatch("aa", "a"));        // Expected: 0 (false)
    printf("Test 2: %d\n", isMatch("aa", "a*"));       // Expected: 1 (true)
    printf("Test 3: %d\n", isMatch("ab", ".*"));       // Expected: 1 (true)
    printf("Test 4: %d\n", isMatch("mississippi", "mis*is*p*.")); // Expected: 0 (false)
    printf("Test 5: %d\n", isMatch("aaa", "a*a"));    // Expected: 1 (true)
#else
    if (argc != 2) {
        printf("One argument expected: ./solution2.c 1000\n");
        return 1;
    }
    // Convert the argument of the program into an integer
    const int size = atoi(argv[1]);
    // Performance testing for n*n matches
    srand(time(NULL)); // Seed for randomness
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

// Allocate memory for memoization table dynamically
int** allocateMemo(int m, int n) {
    int** memo = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        memo[i] = (int*)malloc((n + 1) * sizeof(int));
    }
    return memo;
}

// Free allocated memory
void freeMemo(int** memo, int m) {
    for (int i = 0; i <= m; i++) {
        free(memo[i]);
    }
    free(memo);
}
