#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void run_tests();
int maxArea(int *height, int heightSize);

int main() {
  run_tests();
  return 0;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, height[10], heightSize, result, answer;
  fscanf(file, "%d", &num_test_cases);

  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d", &heightSize);
    for (int j = 0; j < heightSize; ++j)
      fscanf(file, "%d", &height[j]);

    fscanf(file, "%d", &answer);
    result = maxArea(height, heightSize);
    if (result == answer)
      printf("Test case %d PASSED\n", i);
    else {
      printf("Test case %d FAILED\n", i);
      printf("  Output %d, Expected %d\n", result, answer);
    }
  }

  fclose(file);
}

/**
 * Brute force
 *
 * Time Complexity: O(n ^ 2)
 *    Calculating area for all n * (n - 1) / 2 height pairs
 *
 * Space complexity: O(1)
 *    Constant extra space is used
 */

/*
int maxArea(int *height, int heightSize) {
  int max = height[0] < height[1] ? height[0] : height[1], area;
  for (int i = 0; i < heightSize - 1; ++i) {
    for (int j = i + 1; j < heightSize; ++j) {
      area = (height[i] < height[j] ? height[i] : height[j]) * (j - i);
      if (area > max) max = area;
    }
  }
  return max;
}
*/

/**
 * Time Complexity: O(n)
 *   Single pass
 *
 *  Space complexity: O(1)
 *    Constant space is used
 */
int maxArea(int *height, int heightSize) {
  int left = 0, right = heightSize - 1, area = 0;

  while (left < right) {
    area = MAX(area, MIN(height[left], height[right]) * (right - left));
    if (height[left] < height[right]) left++;
    else right--;
  }

  return area;
}
