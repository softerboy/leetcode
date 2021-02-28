#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

void run_tests();
struct ListNode *find_cycle(struct ListNode *head);
struct ListNode *read_into_llist(FILE *file, int len_1, struct ListNode **tail);
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB);

int main() {
  run_tests();
  return 0;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
  // find tail of head A
  struct ListNode *tail = headA, *ref = NULL;
  while (tail != NULL && tail->next != NULL)
    tail = tail->next;

  // save tail reference
  ref = tail;
  // link A's tail with A's head
  if (tail) tail->next = headA;

  // apply Floyd's cycle detection algorithm on B
  struct ListNode *cycle = find_cycle(headB);
  if (cycle) {
    // cycle detected
    // find cycle start node
    struct ListNode *start = headB;
    while (start != cycle) {
      start = start->next;
      cycle = cycle->next;
    }
    // restore A's state by removing tail link from A's head
    if (ref) ref->next = NULL;
    return start;
  }

  // restore A's state by removing tail link from A's head
  if (ref) ref->next = NULL;

  return NULL;
}

struct ListNode *find_cycle(struct ListNode *head) {
  struct ListNode *hare = head;
  struct ListNode *tortoise = head;

  while (hare && tortoise && tortoise->next) {
    hare = hare->next;
    tortoise = tortoise->next->next;
    if (tortoise == hare)
      return tortoise;
  }

  return NULL;
}

void run_tests() {
  FILE *file = fopen("test.txt", "r");
  if (!file) {
    fprintf(stderr, "fopen error\n");
    exit(1);
  }

  int num_test_cases, len_1, len_2, len_3, output;
  struct ListNode *headA = NULL, *headB = NULL, *headC = NULL;
  struct ListNode *tailA = NULL, *tailB = NULL, *tailC = NULL;
  fscanf(file, "%d", &num_test_cases);
  for (int i = 1; i <= num_test_cases; ++i) {
    fscanf(file, "%d", &len_1);
    headA = read_into_llist(file, len_1, &tailA);
    fscanf(file, "%d", &len_2);
    headB = read_into_llist(file, len_2, &tailB);
    fscanf(file, "%d", &len_3);
    headC = read_into_llist(file, len_3, &tailC);
    if (tailA) tailA->next = headC;
    if (tailB) tailB->next = headC;

    fscanf(file, "%d", &output);
    struct ListNode *found = getIntersectionNode(headA, headB);
    if (found) {
      if (found->val == output)
        printf("Test case %d PASSED\n", i);
      else
        printf("Test case %d FAILED\n  Output %d, Expected %d\n", i, found->val, output);
    } else if (output != 0) {
      printf("Test case %d FAILED\n  Output NULL, Expected %d node\n", i, output);
    } else {
      printf("Test case %d PASSED\n", i);
    }
  }

  fclose(file);
}

struct ListNode *read_into_llist(FILE *file, int len_1, struct ListNode **tail) {
  struct ListNode *head = NULL;
  *tail = head;

  struct ListNode *node = NULL;
  for (int i = 0; i < len_1; ++i) {
    node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    fscanf(file, "%d", &(node->val));

    if (head == NULL)
      head = *tail = node;
    else {
      (*tail)->next = node;
      *tail = node;
    }
  }

  return head;
}
