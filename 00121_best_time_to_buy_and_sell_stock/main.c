#include <stdio.h>
#include <stdlib.h>

void run_tests();
int maxProfit(int* prices, int pricesSize);

int main() {
  run_tests();
  return 0;
}

int maxProfit(int* prices, int pricesSize) {
  int profit = 0;
  int buy = prices[0];

  for (int i = 1; i < pricesSize; ++i) {
    // stock just begins reducing here
    if (prices[i] <= buy)
      buy = prices[i];
    else {
      // stock begin growth here
      profit += prices[i] - buy;
      buy = prices[i];
    }
  }

  return profit;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, input_len, *input, output, answer;
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d", &input_len);
    input = malloc(input_len * sizeof (int));
    for (int j = 0; j < input_len; ++j)
      fscanf(file, "%d", &input[j]);
    fscanf(file, "%d", &answer);

    output = maxProfit(input, input_len);
    if (output == answer)
      printf("Test case %d PASSED\n", i);
    else
      printf("Test case %d FAILED\n  Output %d, Expected %d\n", i, output, answer);

    free(input);
  }

  fclose(file);
}
