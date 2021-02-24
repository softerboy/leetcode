#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_tests();
char *complexNumberMultiply(char *a, char *b);

int main() {
  run_tests();
  return 0;
}

/**
 * Time Complexity: O(1)
 *   Constant time required to parse string into real and imaginary parts
 * Space Complexity: O(1)
 *   Constant space required for return multiplication result
 */
char *complexNumberMultiply(char *a, char *b) {
  int re1, im1, re2, im2;

  // read real and imaginary parts of each
  // multiplication complex numbers
  sscanf(a, "%d+%di", &re1, &im1);
  sscanf(b, "%d+%di", &re2, &im2);

  char *output = malloc(16 * sizeof(char));
  // use the formula for calculating new real and imaginary parts
  // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
  sprintf(output, "%d+%di", re1 * re2 - im1 * im2, re1 * im2 + re2 * im1);
  return output;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  fscanf(file, "%d", &num_test_cases);

  char a[16], b[16], answer[16], *result;
  for (int i = 1; i < num_test_cases; ++i) {
    fscanf(file, "%s%s%s", a, b, answer);
    result = complexNumberMultiply(a, b);
    if (strcmp(answer, result))
      printf("Test case %d FAILED\n   Output %s, Expected %s\n", i, result, answer);
    else
      printf("Test case %d PASSED\n", i);

    free(result);
  }

  fclose(file);
}
