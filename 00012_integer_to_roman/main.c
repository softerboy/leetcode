#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve();
char *intToRoman(int num);

int main() {
  solve();
  return 0;
}

/**
 * Time Complexity: O([num / 1000] + 12 + 1)
 *    We need count 1000's and plus
 *    possible 888 number case, which is equal to
 *    DCCCLXXXVIII in roman, i.e. additional 12 character
 *    plus null terminator
 *
 *  Space Complexity: O([num / 1000] + 12 + 1)
 *    Room for each character in roman number plus null terminator
 */
char *intToRoman(int num) {
  // max possible roman number length for
  // problem constraints corresponds to
  // MMMDCCCLXXXVIII (3333 in decimal)
  // i.e. 12 characters long

  // DON'T forget about null terminator
  char *roman = malloc(17 * sizeof(char));

  int i = 0;
  while (num >= 1000) {
    roman[i++] = 'M';
    num -= 1000;
  }

  if (num >= 900) {
    roman[i++] = 'C';
    roman[i++] = 'M';
    num -= 900;
  } else if (num >= 500) {
    roman[i++] = 'D';
    num -= 500;

    while (num >= 100) {
      roman[i++] = 'C';
      num -= 100;
    }
  } else if (num >= 400) {
    roman[i++] = 'C';
    roman[i++] = 'D';
    num -= 400;
  } else {
    while (num >= 100) {
      roman[i++] = 'C';
      num -= 100;
    }
  }

  if (num >= 90) {
    roman[i++] = 'X';
    roman[i++] = 'C';
    num -= 90;
  } else if (num >= 50) {
    roman[i++] = 'L';
    num -= 50;
    while (num >= 10) {
      roman[i++] = 'X';
      num -= 10;
    }
  } else if (num >= 40) {
    roman[i++] = 'X';
    roman[i++] = 'L';
    num -= 40;
  } else {
    while (num >= 10) {
      roman[i++] = 'X';
      num -= 10;
    }
  }

  if (num == 9) {
    roman[i++] = 'I';
    roman[i++] = 'X';
  } else if (num >= 5) {
    roman[i++] = 'V';
    num -= 5;
    while (num >= 1) {
      roman[i++] = 'I';
      num -= 1;
    }
  } else if (num >= 4) {
    roman[i++] = 'I';
    roman[i++] = 'V';
  } else {
    while (num >= 1) {
      roman[i++] = 'I';
      num -= 1;
    }
  }

  roman[i] = '\0';

  return roman;
}

void solve() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(-1);
  }

  int num_cases, decimal;
  char answer[30];
  fscanf(file, "%d", &num_cases);
  for (int i = 1; i <= num_cases; ++i) {
    fscanf(file, "%d%s", &decimal, answer);
    char *result = intToRoman(decimal);
    if (strcmp(result, answer) == 0)
      printf("Test case %d PASSED\n", i);
    else {
      printf("Test case %d FAILED\n", i);
      printf("   Output %s, Expected %s", result, answer);
    }
    free(result);
  }
  fclose(file);
}
