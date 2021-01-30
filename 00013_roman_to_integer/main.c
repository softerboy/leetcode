#include <stdio.h>
#include <stdlib.h>

void solve();
int romanToInt(char *s);

int main() {
  solve();
  return 0;
}

/**
 * Time Complexity: O(n)
 *    We need to loop through each character in input string
 *
 *  Space Complexity: O(1)
 *    No extra space required
 */
int romanToInt(char * s) {
  int sum = 0;

  char prev;
  while (*s != '\0') {
    switch (*s) {
      case 'I':
        sum += 1;
        break;
      case 'V':
        sum += 5;
        if (prev == 'I')
          sum -= 2;
        break;
      case 'X':
        sum += 10;
        if (prev == 'I')
          sum -= 2;
        break;
      case 'L':
        sum += 50;
        if (prev == 'X')
          sum -= 20;
        break;
      case 'C':
        sum += 100;
        if (prev == 'X')
          sum -= 20;
        break;
      case 'D':
        sum += 500;
        if (prev == 'C')
          sum -= 200;
        break;
      case 'M':
        sum += 1000;
        if (prev == 'C')
          sum -= 200;
        break;
      default:
        break;
    }

    prev = *s;
    s++;
  }

  return sum;
}

void solve() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(-1);
  }

  int test_cases = 0, answer, result;
  char buff[15];
  fscanf(file, "%d", &test_cases);
  for (int i = 1; i <= test_cases; ++i) {
    fscanf(file, "%s%d", buff, &answer);
    result = romanToInt(buff);
    if (result == answer)
      printf("Test case %d PASSED\n", i);
    else {
      printf("Test case %d FAILED\n", i);
      printf("   Output %d, Expected %d\n", result, answer);
    }
  }

  fclose(file);
}
