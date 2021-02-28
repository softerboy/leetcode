#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_VOWEL(ch) (strchr("aeuioAEUIO", (ch)) ? 1 : 0)

void run_tests();
void reverseVowels(char *s);

int main() {
  run_tests();
  return 0;
}

void reverseVowels(char *s) {
  int left = 0, right = strlen(s) - 1;
  while (left < right) {
    while (left < right && !IS_VOWEL(s[left]))
      left++;
    while (left < right && !IS_VOWEL(s[right]))
      right--;

    if (left < right) {
      char temp = s[left];
      s[left++] = s[right];
      s[right--] = temp;
    }
  }
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  char input[30], output[30];
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%s%s", input, output);
    reverseVowels(input);
    if (strcmp(input, output) == 0)
      printf("Test case %d PASSED\n", i);
    else
      printf("Test case %d FAILED\n  Output %s, Expected %s\n", i, input, output);
  }

  fclose(file);
}
