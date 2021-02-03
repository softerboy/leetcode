#include <stdio.h>
#include <stdlib.h>

void run_tests();
int searchInsert(int *nums, int numsSize, int target);

int main() {
  run_tests();
  return 0;
}

int searchInsert(int *nums, int numsSize, int target) {
  int low = 0, high = numsSize - 1, index;

  while (low <= high) {
    index = (high + low) / 2;
    if (nums[index] == target)
      return index;
    if (nums[index] < target)
      low = index + 1;
    else if (nums[index] > target)
      high = index - 1;
  }

  return low;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  fscanf(file, "%d", &num_test_cases);

  int arr[1000] = {0}, arr_len, target, answer, result, i, j;
  for (i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d", &arr_len);

    for (j = 0; j < arr_len; ++j)
      fscanf(file, "%d", &arr[j]);

    fscanf(file, "%d%d", &target, &answer);
    result = searchInsert(arr, j, target);
    if (result == answer)
      printf("Test case %d PASSED\n", i);
    else {
      printf("Test case %d FAILED\n", i);
      printf("   Output %d, Expected %d\n", result, answer);
    }
  }

  fclose(file);
}
