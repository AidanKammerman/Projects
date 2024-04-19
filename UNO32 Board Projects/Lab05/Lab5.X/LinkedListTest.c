/* 
 * File:   LinkedListTest.c
 * Author: Aidan Kammerman, 1760640
 *
 * Created on May 4th, 2021, 6:32 PM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"

int main(void) {
    BOARD_Init();

    int n = 0; //establishing counter which increases by one for each passed test
    int size = 0; //establishing integer to record size of a given list

    //TESTS FOR LinkedListNew FUNCTION
    ListItem *pointer = LinkedListNew("Apple");
    if (strcmp(pointer->data, "Apple") == 0) {
        n += 1;
    }
    pointer = LinkedListNew("Banana");
    if (strcmp(pointer->data, "Banana") == 0) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListNew function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListCreateAfter FUNCTION
    pointer = LinkedListNew("Apple");
    ListItem *test = LinkedListCreateAfter(pointer, "Tomato");
    if (strcmp(pointer->nextItem->data, "Tomato") == 0) {
        n += 1;
    }
    LinkedListCreateAfter(test, "Avocado");
    if (strcmp(test->nextItem->data, "Avocado") == 0) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListCreateAfter function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListRemove FUNCTION
    pointer = LinkedListNew("Pear");
    char *deleted_entry = LinkedListRemove(pointer);
    if (strcmp(deleted_entry, "Pear") == 0) {
        n += 1;
    }
    pointer = LinkedListNew("Guava");
    deleted_entry = LinkedListRemove(pointer);
    if (strcmp(deleted_entry, "Guava") == 0) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListRemove function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListSize FUNCTION
    pointer = LinkedListNew("Car");
    ListItem *seconditem = LinkedListCreateAfter(pointer, "Motorcycle");

    size = LinkedListSize(seconditem);

    if (size == 2) {
        n += 1;
    }
    ListItem *thirditem = LinkedListCreateAfter(pointer, "Plane");

    size = LinkedListSize(thirditem);

    if (size == 3) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListSize function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListGetFirst FUNCTION
    pointer = LinkedListNew("Car");
    seconditem = LinkedListCreateAfter(pointer, "Motorcycle");
    thirditem = LinkedListCreateAfter(pointer, "Plane");

    ListItem *first = LinkedListGetFirst(thirditem);
    if (strcmp(first->data, "Car") == 0) {
        n += 1;
    }
    ListItem *fourthitem = LinkedListCreateAfter(pointer, "Tank");
    first = LinkedListGetFirst(fourthitem);
    if (strcmp(first->data, "Car") == 0) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListGetFirst function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListGetLast FUNCTION
    pointer = LinkedListNew("Car");
    seconditem = LinkedListCreateAfter(pointer, "Motorcycle");
    thirditem = LinkedListCreateAfter(seconditem, "Plane");

    ListItem *last = LinkedListGetLast(pointer);
    if (strcmp(last->data, "Plane") == 0) {
        n += 1;
    }
    fourthitem = LinkedListCreateAfter(thirditem, "Tank");
    last = LinkedListGetLast(pointer);
    if (strcmp(last->data, "Tank") == 0) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListGetLast function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListSwapData FUNCTION
    pointer = LinkedListNew("Car");
    seconditem = LinkedListCreateAfter(pointer, "Motorcycle");
    thirditem = LinkedListCreateAfter(seconditem, "Plane");
    LinkedListSwapData(seconditem, thirditem);
    last = LinkedListGetLast(pointer);
    if (strcmp(last->data, "Motorcycle") == 0) {
        n += 1;
    }
    fourthitem = LinkedListCreateAfter(thirditem, "Tank");
    LinkedListSwapData(seconditem, fourthitem);
    last = LinkedListGetLast(pointer);
    if (strcmp(last->data, "Plane") == 0) {
        n += 1;
    }
    printf("%d/2 tests passed for LinkedListSwapData function.\n", n);
    n = 0; // resetting n for later usage


    //TESTS FOR LinkedListPrint FUNCTION
    pointer = LinkedListNew("Car");
    seconditem = LinkedListCreateAfter(pointer, "Motorcycle");
    thirditem = LinkedListCreateAfter(seconditem, "Plane");

    printf("\nOutput of LinkedListPrint Test 1: ");
    LinkedListPrint(thirditem);

    printf("\nExpected Output: [Car, Motorcycle, Plane]");

    pointer = LinkedListNew("Apple");
    seconditem = LinkedListCreateAfter(pointer, "Banana");
    thirditem = LinkedListCreateAfter(seconditem, "Strawberry");

    printf("\n\nOutput of LinkedListPrint Test 2: ");
    LinkedListPrint(seconditem);

    printf("\nExpected Output: [Apple, Banana, Strawberry]");



    BOARD_End();
    while (1);
    return 0;
}
