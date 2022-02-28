// K McCarthy 2022

#include <iostream>

// https://leetcode.com/problems/reverse-linked-list/
// Given the head of a singly linked list, reverse the list, and return the reversed list.
// Constraints: The number of nodes in the list is the range[0, 5000] and - 5000 <= Node.val <= 5000

// Definition for singly - linked list from leetcode
// ergo not a representation of how I would write this struct
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* ReverseList(ListNode* head) {
	// no need to sort a list of 0 or 1
	if (head == NULL || head->next == NULL)
		return head;
	// head of the list has no parent, so NULL
	ListNode* parent = NULL;
	// set current node to the head
	ListNode* current = head;
	while (current != NULL) {
		// temporarily hold onto the child node's pointer
		ListNode* child = current->next;
		// set the current node to point to its parent
		current->next = parent;
		// make the current node the new parent
		parent = current;
		// make the current node the previously stored child node
		current = child;
	}
	// loop ends when current is NULL, so parent holds the new head node
	return parent;
}

void TestReverseList() {
	// Test list
	ListNode c(5);
	ListNode b(2, &c);
	ListNode a(1, &b);
	ListNode* node = ReverseList(&a);
	while (node != NULL) {
		std::cout << node->val << " ";
		node = node->next;
	}
	std::cout << std::endl;
}