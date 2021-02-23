#include <stdio.h>
#include <stdlib.h>

#define WORD_LEN 100

void run_tests();
char **create_matrix(int r, int c);
void print_arr(char **arr, int len);
void free_matrix(char **matrix, int r);
char **commonChars(char **A, int ASize, int *returnSize);
int is_arrays_equal(char **first, char **second, int len);

int main() {
  run_tests();
  return 0;
}

/**
 * Time Complexity: O(n)
 *   n - all characters count in input array
 *
 *  Space Complexity: O(26 * MAX_WORD_LENGTH)
 *    We need extra memory to save each character in each word
 */
char **commonChars(char **A, int ASize, int *returnSize) {
  int table[WORD_LEN][26] = {0};

  // allocate memory for output string array
  char **result = malloc(WORD_LEN * sizeof(char *));
  for (int i = 0; i < WORD_LEN; ++i)
    // room for each character and null terminator
    result[i] = malloc(2 * sizeof(char));

  // count each character count in each word
  for (int i = 0; i < ASize; ++i)
    for (int j = 0; A[i][j]; ++j)
      table[i][A[i][j] - 'a']++;

  int count = 0;
  // for each lowercase character
  for (int i = 0; i < 26; ++i) {
    int c = 0;
    int min = WORD_LEN + 1;
    for (int j = 0; j < ASize; ++j) {
      if (table[j][i] > 0) {
        // if character count greater than zero
        // we increment `c`, so, if character occurs
        // in each word, after ending in this inner
        // cycle, `c` should be equal to WORDs length i.e. ASize
        ++c;
        if (table[j][i] < min)
          min = table[j][i];
      }
    }

    if (c == ASize && min != WORD_LEN + 1) {
      for (int j = 0; j < min; ++j) {
        result[count][0] = (char) (i + 'a');
        result[count][1] = '\0';
        ++count;
      }
    }
  }

  *returnSize = count;
  return result;
}

void free_matrix(char **matrix, int r) {
  for (int i = 0; i < r; ++i)
    free(matrix[i]);

  free(matrix);
}

char **create_matrix(int r, int c) {
  char **matrix = malloc(r * sizeof(char *));
  for (int i = 0; i < r; ++i)
    matrix[i] = malloc(c * sizeof(char));

  return matrix;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, in_len, out_len, result_len;
  char **result;

  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    char **input_arr = create_matrix(10, 10);
    char **output_arr = create_matrix(10, 10);

    fscanf(file, "%d", &in_len);
    for (int j = 0; j < in_len; ++j)
      fscanf(file, "%s", input_arr[j]);

    fscanf(file, "%d", &out_len);
    for (int j = 0; j < out_len; ++j)
      fscanf(file, "%s", output_arr[j]);

    result = commonChars(input_arr, in_len, &result_len);
    if (result_len != out_len) {
      printf("Test case %d FAILED, sizes doesn't match\n", i);
      printf("  Output size %d, Expected size %d\n", result_len, out_len);
      printf("  Output array: ");
      print_arr(result, result_len);
      printf("\n  Expected array: ");
      print_arr(output_arr, out_len);
      printf("\n");
    } else if (is_arrays_equal(output_arr, result, result_len)) {
      printf("Test case %d PASSED\n", i);
    } else {
      printf("Test case %d FAILED, items doesn't match\n", i);
      printf("   Output: ");
      print_arr(result, result_len);
      printf("\n");
      printf("   Expected: ");
      print_arr(output_arr, out_len);
      printf("\n");
    }

    // free result array
    free_matrix(input_arr, in_len);
    free_matrix(output_arr, out_len);
    free_matrix(result, result_len);
  }

  fclose(file);
}

int is_arrays_equal(char **first, char **second, int len) {
  int table[26] = {0};

  for (int i = 0; i < len; ++i)
    for (int j = 0; first[i][j]; ++j)
      table[first[i][j] - 'a']++;

  for (int i = 0; i < len; ++i)
    for (int j = 0; second[i][j]; ++j)
      table[second[i][j] - 'a']--;

  for (int i = 0; i < 26; ++i)
    if (table[i] != 0) return 0;

  return 1;
}

void print_arr(char **arr, int len) {
  for (int i = 0; i < len; ++i)
    printf("%s ", arr[i]);
}

