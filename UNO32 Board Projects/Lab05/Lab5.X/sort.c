
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"


// **** Declare any function prototypes here ***
ListItem *CreateUnsortedList(void); //this function has been written for you
ListItem *SelectionSort(ListItem* list);
ListItem *InsertionSort(ListItem* list);

/* Students should not need to modify main! */
int main(void) {
    BOARD_Init();

    printf("\n\nWelcome to 1760640's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem* listToSort;

    //Do a timing test 
    printf("\nStarting stopwatch for selection sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = SelectionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);


    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = InsertionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    BOARD_End();
    while (1);
    return 0;
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list) {
    //YOUR CODE GOES HERE!
    ListItem *S;
    ListItem *FU;
    FU = LinkedListGetFirst(list);
    while (FU != LinkedListGetLast(list)) {
        S = FU->nextItem;
        while (S != NULL) {
            if (strcmp(FU->data, S->data) > 0) {
                LinkedListSwapData(FU, S);
            }
            S = S->nextItem;
        }
        FU = FU->nextItem;
    }
    return list;
}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list) {
    //YOUR CODE GOES HERE!
    ListItem *FS;
    ListItem *LU;
    ListItem *S;
    FS = LinkedListGetLast(list);
    while (FS != LinkedListGetFirst(list)) {
        LU = FS->previousItem;
        if (strcmp(FS->data, LU->data) > 0) {
            FS = LU;
        } else {
            S = FS;
            while (S != LinkedListGetLast(list)) {
                if (strcmp(S->nextItem->data, LU->data) > 0) {
                    break;
                } else {
                    S = S->nextItem;
                }
            }
            LinkedListRemove(LU);
            LinkedListCreateAfter(S, LU->data);
        }
    }
    return list;
}

/* CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
    char* wordList[] = {
        "decide", "toothpaste", "lowly", "robin", "reign", "crowd",
        "pies", "reduce", "tendency", "surround", "finger", "rake",
        "alleged", "hug", "nest", "punishment", "eggnog", "side",
        "beef", "exuberant", "sort", "scream", "zip", "hair",
        "ragged", "damage", "thought", "jump", "frequent", "substance",
        "head", "step", "faithful", "sidewalk", "pig", "raspy",
        "juggle", "shut", "maddening", "rock", "telephone", "selective",
        NULL
    };
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};


    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if (tail == NULL) {
            printf("ERROR:  Heap full! Please increase heap size.\n");
            FATAL_ERROR();
        }
    }
    return head;
}
// </editor-fold>
