#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_tests();
char *countAndSay(int n);

int main() {
  run_tests();
  return 0;
}

char *countAndSay(int n) {
  if (n == 1) return "1";

  char *prev = malloc(4463 * sizeof(char));
  prev[0] = '1';
  prev[1] = '1';
  prev[2] = '\0';

  char next[4463] = {'\0'};

  for (int i = 3; i <= n; ++i) {
    int count = 0;
    char curr = prev[0];
    for (int j = 0; j <= strlen(prev); ++j) {
      if (curr == prev[j]) {
        count++;
      } else {
        // write count
        snprintf(next + strlen(next), 3, "%d%c", count, curr);
        curr = prev[j];
        // reset counter
        count = 1;
      }
    }
    // make new result as prev
    memcpy(prev, next, strlen(next));
    next[0] = '\0';
  }

  return prev;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  char answer[300] = {0}, *result;
  int num_test_cases, n;
  fscanf(file, "%d", &num_test_cases);

  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d%s", &n, answer);
    result = countAndSay(n);
    if (strcmp(result, answer) == 0) {
      printf("Test case %d PASSED\n", i);
    } else {
      printf("Test case %d FAILED\n", i);
      printf("   Output %s, Expected %s\n", result, answer);
    }
  }

  free(result);
  fclose(file);
}
