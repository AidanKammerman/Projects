/* 
 * File:   part1.c
 * Author: Aidan Kammerman (akammerm@ucsc.edu)
 *
 * Created on April 7, 2021, 2:35 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//Class specific libraries
#include "BOARD.h"


// User libraries

int main(void) {
    BOARD_Init();
    unsigned char vals[] = {rand(), rand(), rand(), rand(), rand()};
    int valsToBeSorted[] = {vals[0], vals[1], vals[2], vals[3], vals[4]};

    // Sort the array in place.

    // 5 recorded values of valsToBeSorted from the last run: [15, 135, 138, 151, 251]
    
    int i, j;
    for (i = 0; i < 5; i++) {
        int aTemp = valsToBeSorted[i];
        for (j = i - 1; j >= 0; j--) {
            if (valsToBeSorted[j] <= aTemp)
                break;
            valsToBeSorted[j + 1] = valsToBeSorted[j];
        }
        valsToBeSorted [j + 1] = aTemp;
    }

    // Print out the array
    printf("[");
    for (i = 0; i < 4; i++) {
        printf("%d, ", valsToBeSorted[i]);
    }
    printf("%d]\n", valsToBeSorted[i]);

    /*
     * Returning from main() is bad form in embedded environments. So we
     * sit and spin.
     */
    BOARD_End();
    while (1);
}