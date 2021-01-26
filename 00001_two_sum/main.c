#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 1000

typedef struct node {
  int key;
  int value;
  struct node *next;
} node;

void solve();
int hash(int key);
int absolute(int value);
node *new_node(int key, int value);
node *find(node *hashtable[], int key);
int array_has(int *array, int len, int val);
void insert(node *hashtable[], int key, int value);
int *twoSum(int *nums, int numsSize, int target, int *returnSize);

int main() {
  solve();

  return 0;
}

int absolute(int value) { return value >= 0 ? value : -value; }

int hash(int key) { return absolute(key) % SIZE; }

node *new_node(int key, int value) {
  node *n = malloc(sizeof(node));
  if (n == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  n->key = key;
  n->value = value;
  n->next = NULL;
  return n;
}

void insert(node *hashtable[], int key, int value) {
  int k = hash(key);
  if (hashtable[k] == NULL) {
    node *n = new_node(key, value);
    hashtable[k] = n;
  } else {
    node *n = new_node(key, value);
    node *last = hashtable[k];
    n->next = last;
    hashtable[k] = n;
  }
}

node *find(node *hashtable[], int key) {
  int k = hash(key);

  node *head = hashtable[k];
  while (head != NULL) {
    if (head->key == key)
      return head;
    head = head->next;
  }

  return NULL;
}

/**
*  Time complexity : O(n)
*  We traverse the list containing n elements only once.
*  Each look up in the table costs only O(1) time.
*
*  Space complexity : O(n)
*  The extra space required depends on the number of items
*  stored in the hash table, which stores at most n elements.
*/

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  node *hashtable[SIZE] = {NULL};

  for (int i = 0; i < numsSize; ++i) {
    int complement = target - nums[i];
    node *found = find(hashtable, complement);

    if (found && found->value != i) {
      int *result = malloc(2 * sizeof(int));
      result[0] = i;
      result[1] = found->value;
      *returnSize = 2;
      return result;
    }

    insert(hashtable, nums[i], i);
  }

  *returnSize = 0;
  return NULL;
}

void solve() {
  FILE *file = fopen("test.txt", "r");

  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int return_size, num_cases, nums_size, target, val;
  fscanf(file, "%d", &num_cases);

  for (int i = 0; i < num_cases; ++i) {
    fscanf(file, "%d%d", &nums_size, &target);
    int *nums = malloc(nums_size * sizeof(int));
    for (int j = 0; j < nums_size; ++j) {
      fscanf(file, "%d", &val);
      nums[j] = val;
    }

    int *res = twoSum(nums, nums_size, target, &return_size);
    for (int j = 0; j < return_size; ++j) {
      fscanf(file, "%d", &val);
      assert(array_has(res, return_size, val));
    }

    printf("Test case %d PASSED\n", i + 1);
    free(res);
  }
}

int array_has(int *array, int len, int val) {
  for (int i = 0; i < len; ++i) {
    if (array[i] == val) return 1;
  }

  return 0;
}
