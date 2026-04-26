/********************************************************************************************************\
 * FILE: linked_list.h                                                                                  *
 * AUTHOR: Michael Kamau                                                                                *
 *                                                                                                      *
 * PURPOSE:                                                                                             *
 * This header implements a generic singly linked list in C.                                            *
 * It provides dynamic storage for arbitrary data items by copying the data into the list nodes.        *
 * The list maintains pointers to both the head and tail nodes, enabling efficient append (push_back)   *
 * operations and traversal from the front.                                                             *
 *                                                                                                      *
 * USAGE:                                                                                               *
 * - Create a new list using `linked_list()`.                                                           *
 * - Add elements at the back using `push_back(list, data, size)`.                                      *
 * - Remove elements from the front or back using `LinkedListPopFront()` or `pop_back()`.                        *
 * - Access elements by index with `get_at_index(list, index)` (O(n) operation).                        *
 * - Check the number of elements with `len_of_list(list)`.                                             *
 * - Clear all elements and ACHIOR_LABS_FREE memory using `clear_list(&list)`.                                      *
 * EXAMPLE:                                                                                             *
 * LinkedList *self = linked_list();                                                                    *
 * int value = 42;                                                                                      *
 * push_back(list, &value, sizeof(int));                                                                *
 * u64 n = len_of_list(list);                                                                        *
 * LinkedListPopFront(list);                                                                                     *
 * clear_list(&list);                                                                                   *
\********************************************************************************************************/



/********************************************************************************************************\                                                                                                      *
 * NOTE :                                                                                               *
 * - The list OWNS THE DATA: all `ACHIOR_LABS_MALLOC`ed memory in nodes is ACHIOR_LABS_FREEd when elements are popped           *
 *   or when the list is cleared.                                                                       *
 * - `LinkedListPopFront()` and `pop_back()` ACHIOR_LABS_FREE both the node and its data; they DO NOT RETURN DATA.           *
 * - Indexing is zero-based; attmpting to get an index >= len_of_list(list) returns NULL.              *
 * - This implementation is singly linked; pop_back is O(n).                                            *
 *                                                                                                      *
\********************************************************************************************************/


#include "Include/List.h"


/**
 * 
 * This funciton creates a new empty linked list.
 *
 * Returns:
 *   A pointer to a dynamically allocated LinkedList.
 *   Caller is responsible for ACHIOR_LABS_FREEing it using clear_list().
 */

bool LinkedListNew(struct LinkedList *self,struct BumpAllocator *bump)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return false;
    }


    self->head = NULL;
    self->tail = NULL;
    self->len  = 0;
    self->bump = bump;

    return true;
}

/**
 * This function appends a new element to the end of the list.
 *
 * Parameters:
 *   - list -> pointer to the LinkedList
 *   - data -> pointer to the data to copy into the node
 *   - size -> size of the data in bytes
 *
 * Returns:
 *   true if the insertion succeeded, false on allocation failure or null list.
 *
 * Notes:
 *   The list makes a copy of the data, so the caller retains ownership of the original.
 */



bool LinkedListPushBack(struct LinkedList *self, void *data)
{
    struct Node *newNode = NULL;

    if(ACHIOR_LABS_NULL(self) || ACHIOR_LABS_NULL(data))
    {
        ACHIOR_LABS_RETURN_DEFER(exit_failure);
    }

    newNode = (struct Node *)ACHIOR_LABS_ARENA_ALLOC(self->bump,struct Node,1);
    if(ACHIOR_LABS_NULL(newNode))
    {
        ACHIOR_LABS_RETURN_DEFER(exit_failure);
    }


    newNode->data = data;
    if(ACHIOR_LABS_NULL(newNode->data))
    {
        ACHIOR_LABS_RETURN_DEFER(exit_failure_data_alloc);
    }


    //ACHIOR_LABS_MEMCPY(newNode->data,data,size);

    if(ACHIOR_LABS_LESS_EQUAL(self->len,0))
    {
        self->head = newNode;
        self->tail = newNode;
        ACHIOR_LABS_RETURN_DEFER(exit_success);
    }

    self->tail->next = newNode;
    self->tail       = newNode;
    newNode->next    = NULL;

    ACHIOR_LABS_RETURN_DEFER(exit_success);



exit_failure_data_alloc:
    //ACHIOR_LABS_FREE(newNode);

exit_failure:
    return false;

exit_success:
    self->len++;
    return true;
}


/**
 * This function removes the last element of the list.
 *
 * Parameters:
 *   - list -> pointer to the LinkedList
 *
 * Notes:
 *   - ACHIOR_LABS_FREEs both the node and the data it contains.
 *   - Does nothing if the list is empty or null.
 *   - After pop_back, self->tail and self->head are updated accordingly.
 */



bool LinkedListPopBack(struct LinkedList *self)
{
    struct Node * tmp   = NULL;
    struct Node *toPop  = NULL;

    if(ACHIOR_LABS_NULL(self))
    {
        ACHIOR_LABS_RETURN_DEFER(exit_failure);
    }

    if(ACHIOR_LABS_EQUAL(self->len,1))
    {
        ACHIOR_LABS_RETURN_DEFER(exit_success_head);
    }

    tmp = self->head;
    while(tmp->next != self->tail)
    {
        tmp = tmp->next;
    }

    ACHIOR_LABS_RETURN_DEFER(exit_success);


exit_failure:
    return false;

exit_success:
    toPop            = tmp->next;
    self->tail       = tmp;
    self->tail->next =  NULL;
    self->len--;

    //ACHIOR_LABS_FREE(toPop->data);
    //ACHIOR_LABS_FREE(toPop);

exit_success_head:
    self->len--;
    self->head = NULL;
    self->tail = NULL;
    //ACHIOR_LABS_FREE(self->head->data);
    //ACHIOR_LABS_FREE(self->head);
    return true;

}


/**
 * This function removes the first element of the list.
 *
 * Parameters:
 *   - list -> pointer to the LinkedList
 *
 * Notes:
 *   - ACHIOR_LABS_FREEs both the node and the data it contains.
 *   - Does nothing if the list is empty or null.
 *   - After LinkedListPopFront, self->head and self->tail are updated accordingly.
 */

bool LinkedListPopFront(struct LinkedList *self)
{
    struct Node *tmp = NULL;
    if(ACHIOR_LABS_NULL(self))
    {
        ACHIOR_LABS_RETURN_DEFER(exit_failure);
    }

    if(ACHIOR_LABS_EQUAL(self->len,1))
    {
        ACHIOR_LABS_RETURN_DEFER(pop_head);
    }


pop:
    tmp        = self->head;
    self->head = self->head->next;
    tmp->next  = NULL;
    self->len--;
    //ACHIOR_LABS_FREE(tmp->data);
    //ACHIOR_LABS_FREE(tmp);


pop_head:
    //ACHIOR_LABS_FREE(self->head->data);
    //ACHIOR_LABS_FREE(self->head);
    self->head = NULL;
    self->tail = NULL;
    self->len--;
    return true;

exit_failure:
    return false;
}


/**
 * This function retrieves the data pointer stored at a specific index.
 *
 * Parameters:
 *   - list -> pointer to the LinkedList
 *   - index  -> zero-based index of the element
 *
 * Returns:
 *   Pointer to the data at the given index, or NULL if index is out of bounds or list is null.
 *
 * Notes:
 *   - This operation is O(n) in a singly linked list.
 *   - Returned pointer is owned by the list; do not ACHIOR_LABS_FREE it.
 */

void *LinkedListAt(struct LinkedList *self, u64 index)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return NULL;
    }

    if(self->len <= index)
    {
        return NULL;
    }

    struct Node *tmp = self->head;

    for(u64 i = 0; i< index; i++)
    {
        tmp = tmp->next;
    }

    return tmp->data;
}


/**
 * This function returns the number of elements currently in the list.
 *
 * Parameters:
 *   - list -> pointer to the LinkedList
 *
 * Returns:
 *   Size of the list (number of nodes). Returns 0 if list is null.
 */

u64 LinkedListLength(struct LinkedList *self)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return 0;
    }

    return self->len;
}


/**
 * This function ACHIOR_LABS_FREEs all memory used by the list, including all nodes and their data.
 *
 * Parameters:
 *   - list -> pointer to a LinkedList* (pointer to the list pointer)
 *
 * Notes:
 *   - After this call, *self is set to NULL.
 *   - Safe to call on an already empty or null list.
 */

void LinkedListClearList(struct LinkedList **self)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return;
    }


    return;

    struct Node *node = (*self)->head;

    for(u64 i = 0; i < (*self)->len; i++)
    {
        struct Node *tmp = node->next;
        //ACHIOR_LABS_FREE(node->data);
        //ACHIOR_LABS_FREE(node);
        node = tmp;
    }

    //ACHIOR_LABS_FREE(*self);
    *self = NULL;
}