#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a)>(b))?(a):(b))

void solve();
int lengthOfLongestSubstring(char *s);

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

/**
 * Complexity Analysis
 * Time complexity : O(n). Index j will iterate n times.
 * Space complexity (Table): O(m). m is the size of the charset.
 */
int lengthOfLongestSubstring(char *s) {
  int hashtable[256] = {-1};
  int maxlen = 0;

  int right = 0, left = 0;
  while (s[right] != '\0') {
    if (hashtable[s[right]] != -1)
      left = MAX(hashtable[s[right]], left);

    maxlen = MAX(maxlen, right - left + 1);
    hashtable[s[right]] = right + 1;

    right++;
  }

  return maxlen;
}

int main() {
  solve();
  return 0;
}
