#include <stdio.h>
#include <stdlib.h>

void run_tests();
int removeDuplicates(int *nums, int numsSize);

int main() {
  run_tests();
  return 0;
}

int removeDuplicates(int *nums, int numsSize) {
  int i = 0, j = 0, max = -1001;

  for (i = 0; i < numsSize; ++i) {
    if (nums[i] > max) {
      max = nums[i];
      nums[j++] = max;
    }
  }

  return j;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(-1);
  }

  int num_test_cases;
  fscanf(file, "%d", &num_test_cases);

  int inputSize, input[20], answerSize, answer[20], result;

  for (int i = 0; i < num_test_cases; ++i) {
    fscanf(file, "%d", &inputSize);
    for (int j = 0; j < inputSize; ++j)
      fscanf(file, "%d", &input[j]);

    fscanf(file, "%d", &answerSize);
    for (int j = 0; j < answerSize; ++j)
      fscanf(file, "%d", &answer[j]);

    result = removeDuplicates(input, inputSize);
    if (result != answerSize) {
      printf("Test case %d FAILED\n", i);
      printf("  Output %d, Expected %d\n", result, answerSize);
    } else {
      for (int j = 0; j < result; ++j) {
        if (answer[j] != input[j]) {
          printf("Test case %d FAILED\n", i);
          printf("  Elements not equal, Output %d, Expected %d\n", input[j], answer[j]);
          return;
        }
      }

      printf("Test case %d PASSED\n", i);
    }
  }

  fclose(file);
}
