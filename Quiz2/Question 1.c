#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }

    struct ListNode *slow = head;
    struct ListNode *fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        if (slow == fast) {
            return true;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    return false;
}

struct ListNode* newNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

int main() {
    struct ListNode *head1 = newNode(1);
    head1->next = newNode(2);
    head1->next->next = newNode(3);
    printf("Test Case 1 (No Cycle): %s\n", hasCycle(head1) ? "Cycle Found" : "No Cycle");

    struct ListNode *head2 = newNode(1);
    head2->next = newNode(2);
    head2->next->next = newNode(3);
    head2->next->next->next = head2;
    printf("Test Case 2 (Cycle Exists): %s\n", hasCycle(head2) ? "Cycle Found" : "No Cycle");

    free(head1->next->next);
    free(head1->next);
    free(head1);


    return 0;
}
