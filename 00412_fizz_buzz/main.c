#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_tests();
char **fizzBuzz(int n, int *returnSize);

int main() {
  run_tests();
  return 0;
}

char **fizzBuzz(int n, int *returnSize) {
  char **result = malloc(n * sizeof(char *));
  int i;
  for (i = 0; i < n; ++i)
    result[i] = malloc(11 * sizeof(char));

  for (i = 1; i <= n; ++i) {
    if (i % 15 == 0)
      sprintf(result[i - 1], "%s", "FizzBuzz");
    else if (i % 3 == 0)
      sprintf(result[i - 1], "%s", "Fizz");
    else if (i % 5 == 0)
      sprintf(result[i - 1], "%s", "Buzz");
    else
      sprintf(result[i - 1], "%d", i);
  }

  *returnSize = n;
  return result;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  char line[11], **result;
  int num_test_cases, n, result_size;
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d", &n);

    result = fizzBuzz(n, &result_size);
    if (result_size != n) {
      printf("Test case %d FAILED, sizes doesn't match\n", i);
    } else {
      int passed = 1;
      for (int j = 0; j < result_size; ++j) {
        fscanf(file, "%s", line);
        if (strcmp(line, result[j]) != 0) {
          printf("Test case %d FAILED, items doesn't match\n", i);
          passed = 0;
          break;
        }
      }

      if (passed) printf("Test case %d PASSED\n", i);
    }

    for (int j = 0; j < result_size; ++j)
      free(result[j]);

    free(result);
  }

  fclose(file);
}
