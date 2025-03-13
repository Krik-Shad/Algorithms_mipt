struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) return head; // проверка на 0 или 1 элемент в списке
    ListNode* new_head = new ListNode(0);
    new_head -> next = head;
    ListNode* next_ptr = new_head;
    int value = next_ptr->next->val;
    while (next_ptr->next && next_ptr->next->next) // проверяем, что элемент тут не последний
    {
        if (next_ptr->next->next->val == value)
        {
            while (next_ptr->next && next_ptr->next->val == value) //проходим либо до конца либо до первого не повторяющегося элемента
            {
                ListNode* temp = next_ptr->next; // создаём новый указатель, чтобы поместить туда удаляемое значение
                next_ptr->next = next_ptr->next->next;
                temp = nullptr; //"удалили" значение next_ptr->next
            }
            if (next_ptr->next) //если остановились потому, что нашли не повторяющееся число
            {
                value = next_ptr->next->val;
            }
        }
        else
        {
            next_ptr = next_ptr->next;
            value = next_ptr->next->val;
        }
    }
    return new_head->next;
    }