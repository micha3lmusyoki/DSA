#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *detectCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    struct ListNode *slow = head;
    struct ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            break;
        }
    }
    if (fast == NULL || fast->next == NULL) {
        return NULL;
    }
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

int main() {
    struct ListNode *head1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    head1->val = 1;
    head1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head1->next->val = 2;
    head1->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head1->next->next->val = 3;
    head1->next->next->next = NULL;

    struct ListNode *result1 = detectCycle(head1);
    printf("Test Case 1 (No Cycle): %s\n", result1 ? "Cycle Found" : "No Cycle");

    struct ListNode *head2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    head2->val = 1;
    head2->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head2->next->val = 2;
    head2->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head2->next->next->val = 3;
    head2->next->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    head2->next->next->next->val = 4;
    head2->next->next->next->next = head2->next;

    struct ListNode *result2 = detectCycle(head2);
    printf("Test Case 2 (Cycle Exists): Entry at node %d\n", result2->val);

    free(head1->next->next);
    free(head1->next);
    free(head1);

    return 0;
}
