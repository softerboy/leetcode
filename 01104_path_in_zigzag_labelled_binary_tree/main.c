#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void run_tests();
int find_row(int label);
int find_label(int index);
int find_label_index(int label);
int *pathInZigZagTree(int label, int *returnSize);
int is_arrays_equal(int *arr1, int *arr2, int len);

int main() {
  run_tests();
  return 0;
}

/**
 * Time Complexity: O(log(label))
 *     We need loop each time to find
 *     index of parent label
 *
 * Space Complexity: O(log(label))
 *     We need extra space for holding items in
 *     result path array in a tree
 */
int *pathInZigZagTree(int label, int *returnSize) {
  // return array size is same as label row number
  int row = find_row(label);
  *returnSize = row;
  int *result = malloc(row * sizeof (int));

  result[--row] = label;
  int parentIndex = find_label_index(label);

  while (parentIndex != 1) {
    parentIndex /= 2;
    result[--row] = find_label(parentIndex);
  }
  printf("\n");

  return result;
}

// return the row of given label in a tree
int find_row(int label) {
  int row = 1;

  while ((1 << row) <= label)
    row++;

  return row;
}

// return the index of label in a
// array representation of the tree
int find_label_index(int label) {
  int row = find_row(label);

  if (row % 2 == 0)
    return 3 * (1 << (row - 1)) - label - 1;

  return label;
}

// return the label in index position
int find_label(int index) {
  // same as find_label_index, but we
  // send index as argument instead label
  return find_label_index(index);
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, label;
  fscanf(file, "%d", &num_test_cases);

  int *result, resultSize;
  int answer[100], answerSize;

  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d%d", &label, &answerSize);
    for (int j = 0; j < answerSize; ++j)
      fscanf(file, "%d", (answer + j));

    result = pathInZigZagTree(label, &resultSize);

    if (resultSize != answerSize) {
      printf("Test case %d FAILED, length don't equal\n", i);
      printf("   Output %d, Expected %d\n", resultSize, answerSize);
    } else if (!is_arrays_equal(result, answer, resultSize)) {
      printf("Test case %d FAILED, items don't match\n", i);
    } else {
      printf("Test case %d PASSED\n", i);
    }

    free(result);
  }

  fclose(file);
}

int is_arrays_equal(int *arr1, int *arr2, int len) {
  for (int i = 0; i < len; ++i) {
    if (arr1[i] != arr2[i]) return 0;
  }

  return 1;
}
