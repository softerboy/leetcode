#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_tests();
char *longestPalindrome(char *s);

int main() {
  run_tests();
  return 0;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");

  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  char str[30] = {'\0'}, answer[30] = {'\0'};

  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%s%s", str, answer);
    char *result = longestPalindrome(str);

    if (strcmp(result, answer) == 0)
      printf("Test case %d PASSED\n", i);
    else {
      printf("Test case %d FAILED\n", i);
      printf("   Output %s, Expected %s\n", result, answer);
    }

    free(result);
  }

  fclose(file);
}

char *longestPalindrome(char *s) {
  int len = strlen(s);

  int **table = malloc(1000 * sizeof(int *));
  for (int i = 0; i < 1000; ++i)
    table[i] = malloc(1000 * sizeof(int));

  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      table[i][j] = 0;
    }
  }

  // all substrings of length 1 are palindromes
  for (int i = 0; i < len; ++i)
    table[i][i] = 1;

  int left = 0, right = 0;
  int found = 0;
  // check for length 2 substrings
  for (int i = 0; i < len - 1; ++i) {
    if (s[i] == s[i + 1]) {
      table[i][i + 1] = 1;
      if (found == 0) {
        left = i;
        right = i + 1;
        found = 1;
      }
    }
  }

  // Check for lengths greater than 2.
  // k is length of substring
  for (int k = 3; k <= len; ++k) {
    // Fix the starting index
    for (int i = 0; i < len - k + 1; ++i) {
      // Get the ending index of substring from
      // starting index i and length k
      int j = i + k - 1;

      // checking for sub-string from ith index to
      // jth index iff str[i+1] to str[j-1] is a
      // palindrome
      if (table[i + 1][j - 1] && s[i] == s[j]) {
        table[i][j] = 1;
        if (j - i > right - left) {
          left = i;
          right = j;
        }
      }
    }
  }

  for (int i = 0; i < 1000; ++i)
    free(table[i]);

  free(table);

  char *buff = malloc(1001 * sizeof(char));
  memcpy(buff, s + left, right - left + 1);
  buff[right - left + 1] = '\0';
  return buff;
}
