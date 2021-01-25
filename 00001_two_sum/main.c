#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

typedef struct node {
  int key;
  int value;
  struct node *next;
} node;

int hash(int key);
int absolute(int value);
node *new_node(int key, int value);
node *find(node *hashtable[], int key);
void solve(int *nums, int numSize, int target);
void insert(node *hashtable[], int key, int value);
int *twoSum(int *nums, int numsSize, int target, int *returnSize);

int main() {
  int nums1[] = {2, 7, 11, 15}, numSize1 = 4, target1 = 9;
  int nums2[] = {3, 2, 4}, numSize2 = 3, target2 = 6;
  int nums3[] = {3, 3}, numSize3 = 2, target3 = 6;

  solve(nums1, numSize1, target1);
  solve(nums2, numSize2, target2);
  solve(nums3, numSize3, target3);

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

void solve(int *nums, int numSize, int target) {
  int returnSize = 0;
  int *res = twoSum(nums, numSize, target, &returnSize);

  for (int i = 0; i < returnSize; ++i) {
    printf("%d ", res[i]);
  }
  printf("\n");

  free(res);
}
