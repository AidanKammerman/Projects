/* 
 * File:   part3.c
 * Author: Aidan Kammerman (akammerm@ucsc.edu)
 *
 * Created on April 7, 2021, 3:31 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Oled.h"
#include "Ascii.h"
#include "OledDriver.h"
#include "BOARD.h"

/*
 * 
 */
int main(void) {
    BOARD_Init();
    OledInit();
    OledDrawString("Hello World!");
    OledUpdate();
    scanf(" ");

    //BOARD_End(); // handles cleanup of the system

    while (1); // if embedded we should never exit.
}


