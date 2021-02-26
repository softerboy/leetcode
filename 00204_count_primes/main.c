#include <stdio.h>
#include <stdlib.h>

void run_tests();
int countPrimes(int n);

int main() {
  run_tests();
  return 0;
}

int countPrimes(int n) {
  char *primes = calloc(n, sizeof(char));

  for (int i = 2; i * i < n; ++i)
    if (!primes[i])
      for (int j = i * i; j < n; j += i)
        primes[j] = '1';

  int count = 0;
  for (int i = 2; i < n; ++i)
    if (!primes[i])
      ++count;

  free(primes);
  return count;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, input, answer, output;
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d%d", &input, &answer);
    output = countPrimes(input);
    if (output == answer)
      printf("Test case %d PASSED\n", i);
    else
      printf("Test case %d FAILED\n   Output %d, Expected %d\n", i, output, answer);
  }

  fclose(file);
}
