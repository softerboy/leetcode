#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

void solve();
void clear(struct ListNode *node);
struct ListNode *create_node(int val);
struct ListNode *add(int val1, int val2, int *carry);
struct ListNode *push_back(struct ListNode *tail, struct ListNode *node);
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2);

int main() {
  solve();
  return 0;
}

struct ListNode *create_node(int val) {
  struct ListNode *n = malloc(sizeof(struct ListNode));
  n->val = val;
  n->next = NULL;
  return n;
}

struct ListNode *add(int val1, int val2, int *carry) {
  int sum = val1 + val2 + *carry;
  struct ListNode *n = NULL;
  if (sum >= 10) {
    n = create_node(sum % 10);
    *carry = sum / 10;
  } else {
    n = create_node(sum);
    *carry = 0;
  }

  return n;
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
  struct ListNode *sentinel = create_node(-1);

  int carry = 0;
  struct ListNode *tail = sentinel;
  while (l1 || l2) {
    if (l1 && l2) {
      struct ListNode *new_node = add(l1->val, l2->val, &carry);
      tail = push_back(tail, new_node);
      l1 = l1->next;
      l2 = l2->next;
    } else if (l1) {
      struct ListNode *new_node = add(l1->val, 0, &carry);
      tail = push_back(tail, new_node);
      l1 = l1->next;
    } else {
      struct ListNode *new_node = add(l2->val, 0, &carry);
      tail = push_back(tail, new_node);
      l2 = l2->next;
    }
  }

  if (carry) {
    struct ListNode *new_node = create_node(carry);
    push_back(tail, new_node);
  }

  return sentinel->next;
}

struct ListNode *push_back(struct ListNode *tail, struct ListNode *node) {
  tail->next = node;
  tail = node;
  return tail;
}

void clear(struct ListNode *node) {
  while (node) {
    struct ListNode* temp = node;
    node = node->next;
    free(temp);
  }
}

void solve() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_cases, n1, n2, n3, val;
  fscanf(file, "%d", &num_cases);

  for (int i = 1; i <= num_cases ; ++i) {

    struct ListNode *sentiel1 = create_node(-1);
    struct ListNode *sentiel2 = create_node(-1);
    struct ListNode *tail1 = sentiel1, *tail2 = sentiel2;
    struct ListNode *new_node;

    fscanf(file, "%d%d%d", &n1, &n2, &n3);
    for (int j = 0; j < n1; ++j) {
      fscanf(file, "%d", &val);
      new_node = create_node(val);
      tail1->next = new_node;
      tail1 = new_node;
    }

    for (int j = 0; j < n2; ++j) {
      fscanf(file, "%d", &val);
      new_node = create_node(val);
      tail2->next = new_node;
      tail2 = new_node;
    }

    struct ListNode *res = addTwoNumbers(sentiel1->next, sentiel2->next);
    struct ListNode *head = res;
    for (int j = 0; j < n3; ++j) {
      fscanf(file, "%d", &val);
      assert(head->val == val);
      head = head->next;
    }

    clear(sentiel1);
    clear(sentiel2);
    clear(res);

    printf("Test case %d PASSED\n", i);
  }

  fclose(file);
}
