#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#ifndef EXPERIMENT
#define EXPERIMENT 1
#endif

void generateRandomString(char* str, int length);
void generateRandomPattern(char* pattern, int length);
void allocateMemo(int max_len);
void freeMemo(int max_len);

int** memo;  // Dynamically allocated 2D array for memoization
int max_len = 21;  // Default value (previously `#define MAX_LEN 21`)

// Recursive function with memoization
bool dfs(const char* s, const char* p, int i, int j) {
    // If already computed, return the cached result
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    int s_len = strlen(s);
    int p_len = strlen(p);

    // Base case: if both strings are exhausted
    if (i >= s_len && j >= p_len) {
        memo[i][j] = true;
        return memo[i][j];
    }

    // If pattern exhausted but s still has characters
    if (j >= p_len) {
        memo[i][j] = false;
        return memo[i][j];
    }

    // Check if first character matches
    bool match = (i < s_len) && (s[i] == p[j] || p[j] == '.');

    // Handle '*'
    if (j + 1 < p_len && p[j + 1] == '*') {
        bool result = (dfs(s, p, i, j + 2) || (match && dfs(s, p, i + 1, j)));
        memo[i][j] = result;
        return memo[i][j];
    }

    // If no '*', move to the next character
    if (match) {
        bool result = dfs(s, p, i + 1, j + 1);
        memo[i][j] = result;
        return memo[i][j];
    }

    memo[i][j] = false;
    return memo[i][j];
}

bool isMatch(char* s, char* p) {
    // Allocate memory for memoization table
    allocateMemo(max_len);

    // Initialize memoization table with -1 (uncomputed)
    for (int i = 0; i < max_len; i++)
        for (int j = 0; j < max_len; j++)
            memo[i][j] = -1;

    bool result = dfs(s, p, 0, 0);

    // Free allocated memory
    freeMemo(max_len);

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
        printf("One argument expected: ./solution1.c 1000\n");
        return 1;
    }
    // Convert the argument of the program into an integer
    const int size = atoi(argv[1]);
    max_len = size;

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

// Allocate memory for memoization table dynamically based on `max_len`
void allocateMemo(int max_len) {
    memo = (int**)malloc(max_len * sizeof(int*));
    for (int i = 0; i < max_len; i++) {
        memo[i] = (int*)malloc(max_len * sizeof(int));
    }
}

// Free allocated memory
void freeMemo(int max_len) {
    for (int i = 0; i < max_len; i++) {
        free(memo[i]);
    }
    free(memo);
}
