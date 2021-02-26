#include <stdio.h>
#include <stdlib.h>

void run_tests();
int fib(int n);

int main() {
  run_tests();
  return 0;
}

int fib(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;

  int prev = 0, next = 1, new_fib, k = 2;

  while (k <= n) {
    new_fib = prev + next;
    prev = next;
    next = new_fib;
    k++;
  }

  return new_fib;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, input, expected, output;
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d%d", &input, &expected);
    output = fib(input);
    if (expected == output)
      printf("Test case %d PASSED\n", i);
    else
      printf("Test case %d FAILED\n  Output %d, Expected %d", i, output, expected);
  }

  fclose(file);
}
