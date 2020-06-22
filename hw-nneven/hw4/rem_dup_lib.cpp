#include "rem_dup_lib.h"

// Deletes consecutive equal values from the list
void removeConsecutive(Item* head)
{
	if (head == nullptr) return;
	else {
		if (head->next != nullptr)
		{
			if (head->val == head->next->val)
			{
				Item* temp = head->next;
				head->next = head->next->next;
				delete temp;
				removeConsecutive(head);
			} else {
				removeConsecutive(head->next);
			}
		}
	}
}

// Makes a copy of the items in the head1 and head2 lists
// concatenating the new head2 items to the end of the
// new head1 list items.
Item* concatenate(Item* head1, Item* head2)
{
	if (head1 == nullptr && head2 == nullptr) return nullptr;
	if (head1 != nullptr)
	{
		return new Item(head1->val, concatenate(head1->next, head2));
	} else if (head2 != nullptr) {
		return new Item(head2->val, concatenate(head1, head2->next));
	}
	return nullptr;
}