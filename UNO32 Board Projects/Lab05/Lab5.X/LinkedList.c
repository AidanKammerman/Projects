#include "LinkedList.h"
#include "BOARD.h"

#include <stdio.h>
#include <string.h>

/**
 * This function starts a new linked list. Given an allocated pointer to data it will return a
 * pointer for a malloc()ed ListItem struct. If malloc() fails for any reason, then this function
 * returns NULL otherwise it should return a pointer to this new list item. data can be NULL.
 *
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occured.
 */
ListItem *LinkedListNew(char *data) {
    ListItem *list = malloc(1 * sizeof (ListItem)); //Establishing new list item as first item of list
    list->previousItem = NULL; //Establishing that the previous and next items of the list are NULL
    list->nextItem = NULL;
    list->data = data;
    return list; //returns newly created item of the Linked List
}

/**
 * This function allocates a new ListItem containing data and inserts it into the list directly
 * after item. It rearranges the pointers of other elements in the list to make this happen. If
 * passed a NULL item, CreateAfter() should still create a new ListItem, just with no previousItem.
 * It returns NULL if it can't malloc() a new ListItem, otherwise it returns a pointer to the new
 * item. The data parameter is also allowed to be NULL.
 *
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 */
ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    ListItem *list = malloc(1 * sizeof (ListItem));
    if (item == NULL) { //NULL Checker in case the list argument given is invalid 
        return NULL;
    }
    if (item->nextItem == NULL) { //Checking if the item given as an argument is the tail of the list

        list->previousItem = item;
        list->nextItem = NULL;
        list->data = data;
        item->nextItem = list;

        return list;
    } else {
        //Connecting the newly established item to those surrounding it
        list->previousItem = item;
        list->nextItem = item->nextItem;
        list->data = data;
        item->nextItem = list;
        list->nextItem->previousItem = list;
        return list; //returning the newly created item in the list
    }
}

/**
 * This function will remove a list item from the linked list and free() the memory that the
 * ListItem struct was using. It doesn't, however, free() the data pointer and instead returns it
 * so that the calling code can manage it.  If passed a pointer to NULL, LinkedListRemove() should
 * return NULL to signal an error.
 *
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem *item) {

    if (item == NULL) { //NULL Checker in case the list argument given is invalid
        return NULL;
    } else {
        char *tempdata = item->data; //Setting data of item equal to a temporary placeholder

        if (item->previousItem) { //Checking if the item given is the head of the list
            item->previousItem->nextItem = item->nextItem;
        }
        if (item->nextItem) { //Checking if the item given is the tail of the list
            item->nextItem->previousItem = item->previousItem;
        }

        free(item);
        return tempdata;
    }
}

/**
 * This function returns the total size of the linked list. This means that even if it is passed a
 * ListItem that is not at the head of the list, it should still return the total number of
 * ListItems in the list. A NULL argument will result in 0 being returned.
 *
 * @param list An item in the list to be sized.
 * @return The number of ListItems in the list (0 if `list` was NULL).
 */
int LinkedListSize(ListItem *list) {
    if (list == NULL) { //NULL Checker in case the list argument given is invalid
        return 0;
    } else {
        list = LinkedListGetFirst(list); //We must count starting from the beginning of the list
        int count = 0;
        while (list != NULL) {
            count++;
            list = list->nextItem;
        }
        return count;
    }
}

/**
 * This function returns the head of a list given some element in the list. If it is passed NULL,
 * it will just return NULL. If given the head of the list it will just return the pointer to the
 * head anyways for consistency.
 *
 * @param list An element in a list.
 * @return A pointer to the first element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetFirst(ListItem *list) {
    if (list == NULL) { //NULL Checker in case the list argument given is invalid
        return NULL;
    } else {
        while (list->previousItem != NULL) { //loops until the list items previous item is NULL, indicating that we have reached the head of the list
            list = list->previousItem;
        }
        return list;
    }
}

/**
 * This function operates identically to LinkedListGetFirst(), but returns
 * the tail of a linked list.
 * 
 * @param list An element in a list.
 * @return A pointer to the last element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetLast(ListItem *list) {
    if (list == NULL) { //NULL Checker in case the list argument given is invalid
        return NULL;
    } else {
        while (list->nextItem != NULL) { //loops until the list items next item is NULL, indicating that we have reached the tail of the list
            list = list->nextItem;
        }
        return list;
    }
}

/**
 * LinkedListSwapData() switches the data pointers of the two provided ListItems. This is most
 * useful when trying to reorder ListItems but when you want to preserve their location. This
 * function should return STANDARD_ERROR if either arguments are NULL, otherwise it should return
 * SUCCESS. If one or both of the data pointers are NULL in the given ListItems, it still does
 * perform the swap and returns SUCCESS.
 *
 * @param firstItem One of the items whose data will be swapped.
 * @param secondItem Another item whose data will be swapped.
 * @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */
int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    if (firstItem == NULL || secondItem == NULL) { //NULL Checker in case the list arguments given are invalid
        return STANDARD_ERROR;
    } else {
        char *data = firstItem-> data; //Setting data entry of firstItem equal to a temporary placeholder 'data'
        firstItem->data = secondItem -> data;
        secondItem -> data = data; //commits placeholder 'data' to the data slot of the secondItem
        return SUCCESS;
    }
}

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem *list) {
    if (list == NULL) { //NULL Checker in case the list argument given is invalid
        return STANDARD_ERROR;
    } else {
        list = LinkedListGetFirst(list); //Must begin printing from the first entry of the list which is why this function must be called
        printf("[");
        while (list != NULL) {
            printf("%s", list->data);
            if (list->nextItem != NULL) {
                printf(", "); //Adds a comma and space after each entry until it reaches the last list entry
            }
            list = list->nextItem;
        }
        printf("]");
        return SUCCESS;
    }
}


