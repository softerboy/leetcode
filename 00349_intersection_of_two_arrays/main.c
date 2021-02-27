#include <stdio.h>
#include <stdlib.h>

void run_tests();
int is_arrays_equal(int *arr1, int *arr2, int len);
void read_into_array(int *arr, int len, FILE *file);
int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize);

int main() {
  run_tests();
  return 0;
}

int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize) {
  int freq_table[30] = {0};
  int size = nums1Size > nums2Size ? nums1Size : nums2Size;
  int *result = malloc(size * sizeof(int));

  for (int i = 0; i < nums1Size; ++i)
    freq_table[nums1[i]]++;

  int count = 0;
  for (int i = 0; i < nums2Size; ++i) {
    if (freq_table[nums2[i]] != 0) {
      freq_table[nums2[i]] = 0;
      result[count++] = nums2[i];
    }
  }

  *returnSize = count;
  return result;
}

int is_arrays_equal(int *arr1, int *arr2, int len) {
  // assume array elements is less than 30
  int count[30] = {0};

  for (int i = 0; i < len; ++i)
    count[arr1[i]]++;

  for (int i = 0; i < len; ++i)
    count[arr2[i]]--;

  for (int i = 0; i < len; ++i)
    if (count[i] != 0) return 0;

  return 1;
}

void read_into_array(int *arr, int len, FILE *file) {
  for (int i = 0; i < len; ++i)
    fscanf(file, "%d", &arr[i]);
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases;
  int input_len1, input1[30];
  int input_len2, input2[30];
  int expected_len, expected[30], output_len, *output;

  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d", &input_len1);
    read_into_array(input1, input_len1, file);
    fscanf(file, "%d", &input_len2);
    read_into_array(input2, input_len2, file);
    fscanf(file, "%d", &expected_len);
    read_into_array(expected, expected_len, file);

    output = intersect(input1, input_len1, input2, input_len2, &output_len);
    if (output_len != expected_len) {
      printf("Test case %d FAILED, sizes doesn't match\n", i);
      printf("  Output size %d, Expected size %d\n", output_len, expected_len);
    } else {
      if (is_arrays_equal(output, expected, output_len)) {
        printf("Test case %d PASSED\n", i);
      } else {
        printf("Test case %d FAILED, items don't match\n", i);
      }
    }

    free(output);
  }

  fclose(file);
}
