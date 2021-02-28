#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_tests();
void reverseString(char* s, int sSize);

int main() {
  run_tests();
  return 0;
}

void reverseString(char* s, int sSize) {
  int left = 0, right = sSize - 1;
  while (left < right) {
    char temp = s[left];
    s[left++] = s[right];
    s[right--] = temp;
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
    reverseString(input, strlen(input));
    if (strcmp(input, output) == 0)
      printf("Test case %d PASSED\n", i);
    else
      printf("Test case %d FAILED\n  Output %s, Expected %s\n", i, input, output);
  }

  fclose(file);
}
