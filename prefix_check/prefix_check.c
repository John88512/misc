#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @file prefix_check.c
 * @brief Checks if input string starts with one of predefined prefix groups
 * @author Embedded Systems Engineer
 * @date 2026-01-08
 */

/**
 * @brief Checks if the first up to 12 characters of input string match any allowed prefix group
 * 
 * Validates input string against predefined prefix groups: "ABC", "DEF", "HIJK", "LMNOPQ".
 * Examines only first 12 characters maximum. Returns match status with error handling.
 * 
 * @param str Pointer to null-terminated input string to check
 * @return 1 if prefix matches any allowed group
 * @return 0 if no prefix match found
 * @return -1 if input error (NULL pointer or non-printable characters in first 12 chars)
 */
int check_string_prefix(const char *str) {
    /* Step 1: Validate input pointer - NULL input is error condition */
    if (!str) {
        return -1;
    }

    /* Step 2: Check first 12 characters for non-printable chars (32-126 ASCII range required) */
    /* Non-printable characters indicate corrupted/invalid input */
    for (int i = 0; i < 12 && str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] > 126) {
            return -1;  /* Error: Invalid character found */
        }
    }

    /* Step 3: Define allowed prefix patterns in array for easy maintenance */
    const char *prefixes[] = {"QEY", "QEM", "QED", "QEH"};
    size_t num_prefixes = sizeof(prefixes) / sizeof(prefixes[0]);  /* Calculate array size */

    /* Step 4: Compare input string prefix against each allowed pattern */
    for (size_t i = 0; i < num_prefixes; i++) {
        size_t len = strlen(prefixes[i]);  /* Get length of current prefix pattern */
        
        /* Use strncmp to compare exact prefix length - allows longer strings with matching prefix */
        if (strncmp(str, prefixes[i], len) == 0) {
            return 1;  /* Match found - success */
        }
    }

    /* Step 5: No matches found */
    return 0;
}

/**
 * @brief Test harness for check_string_prefix function
 * 
 * Comprehensive test suite covering:
 * - Exact prefix matches
 * - Partial prefix matches (shorter input)
 * - Longer strings with valid prefix
 * - Non-matching strings
 * - Edge cases (empty string, NULL, invalid chars)
 * 
 * @return 0 on successful test execution
 */
int main() {
    /* Test case array - covers all expected behaviors and edge conditions */
    const char *test_cases[] = {
        "QVFW2",         /* command without checksum -> 0 */
        "QPIGS",         /* command without checksum -> 0 */
        "QEY2011",       /* Exact prefix + extra chars -> 1 */
        "QEM202510",     /* Exact prefix + extra chars -> 1 */
        "XYZabc",        /* No match -> 0 */
        "QED20250908",   /* Exact prefix + extra chars -> 1 */
        "QE",            /* Partial DEF prefix -> 0 */
        "",              /* Empty string -> 0 */
        "QEH2025032315", /* Exact prefix + extra chars -> 1 */
        NULL,            /* NULL pointer -> -1 */
        "ABC\njunk",     /* Non-printable char -> -1 */
        "QEYOPQRSTUV"    /* 12 chars, valid prefix -> 1 */
    };
    
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    /* Print header for test results */
    printf("Testing check_string_prefix function:\n");
    printf("=====================================\n");

    /* Execute each test case and display results */
    for (size_t i = 0; i < num_tests; i++) {
        int result = check_string_prefix(test_cases[i]);
        printf("Test %2zu: \"%s\" -> %d\n", 
               i + 1, 
               test_cases[i] ? test_cases[i] : "NULL", 
               result);
    }

    printf("=====================================\n");
    printf("All tests completed.\n");

    return 0;  /* Success - tests executed without runtime errors */
}
