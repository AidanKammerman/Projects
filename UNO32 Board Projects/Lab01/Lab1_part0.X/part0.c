/* 
 * File:   part0.c
 * Author: Aidan Kammerman (akammerm@ucsc.edu)
 *
 * Created on April 6, 2021, 11:12 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * 
 */

int main(void) {
    BOARD_Init();
    printf("Hello World\n");

    BOARD_End(); // handles cleanup of the system
    while (1); // if embedded we should never exit.

}
