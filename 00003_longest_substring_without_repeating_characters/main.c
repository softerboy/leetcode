#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void solve();
int lengthOfLongestSubstring(char *s);

void reset_hashtable(int hashtable[], int len) {
  for (int i = 0; i < len; ++i)
    hashtable[i] = 0;
}

void solve() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  fscanf(file, "%d", &num_test_cases);
  char buff[64];
  int answer, result;
  for (int i = 0; i < num_test_cases; ++i) {
    fscanf(file, "%s", buff);
    fscanf(file, "%d", &answer);
    result = lengthOfLongestSubstring(buff);
    if (answer == result)
      printf("Test case %d PASSED\n", i + 1);
    else {
      printf("Test case %d FAILED\n", i + 1);
      printf("  Output %d, Expected %d\n", result, answer);
    }
  }

  fclose(file);
}

int lengthOfLongestSubstring(char *s) {
  int hashtable[256] = {0};
  int curr, max = 0, i, j, k;
  for (i = 0; s[i] != '\0'; i++) {
    curr = 0;
    for (j = i; s[j] != '\0' && hashtable[s[j]] < 1; ++j) {
      hashtable[s[j]]++;
      curr++;
    }

    // reset only busy hashtable cells
    for (k = i; k < j; ++k) {
      hashtable[s[k]] = 0;
    }

    if (curr > max)
      max = curr;
  }

  return max;
}

int main() {
  solve();
  return 0;
}
