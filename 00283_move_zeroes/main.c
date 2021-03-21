#include <stdio.h>
#include <stdlib.h>

void run_tests();
void moveZeroes(int* nums, int numsSize);
int *read_array(FILE *file, int *out_len);
int is_array_equal(int *arr1, int len1, int *arr2, int len2);

int main() {
  run_tests();
  return 0;
}

void moveZeroes(int* nums, int numsSize) {
  int k = 0,  i;

  for (i = 0; i < numsSize; ++i)
    if (nums[i] != 0)
      nums[k++] = nums[i];

  for (i = k; i < numsSize; ++i)
    nums[i] = 0;
}

int is_array_equal(int *arr1, int len1, int *arr2, int len2) {
  if (len1 != len2)
    return 1; // sizes not equal

  for (int i = 0; i < len1; ++i)
    if (arr1[i] != arr2[i])
      return 2; // contents not equal

  return 0; // contents are equal
}

int *read_array(FILE *file, int *out_len) {
  fscanf(file, "%d", out_len);
  int *arr = malloc(*out_len * sizeof (int));
  for (int i = 0; i < *out_len; ++i)
    fscanf(file, "%d", &arr[i]);
  return arr;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  int in_len, *in;
  int ans_len, *ans;
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    in = read_array(file, &in_len);
    ans = read_array(file, &ans_len);
    moveZeroes(in, in_len);
    int res = is_array_equal(in, in_len, ans, ans_len);
    if (res == 0)
      printf("Test case %d PASSED\n", i);
    else if (res == 1)
      printf("Test case %d FAILED\n   Sizes not equal\n", i);
    else
      printf("Test case %d FAILED\n   Contents not equal\n", i);

    free(in);
    free(ans);
  }

  fclose(file);
}
