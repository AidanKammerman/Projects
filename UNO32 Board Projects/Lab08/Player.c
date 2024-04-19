#include "UNIXBOARD.h"
#include "Player.h"
#include <stdint.h>

//#define INVENTORY_SIZE 4

static uint8_t inventory[INVENTORY_SIZE] = {0};
/*
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item){
    for (int i = 0; i < INVENTORY_SIZE; i++){
        if (item == inventory[i]){
            return STANDARD_ERROR;
        }
    }
    for (int i = 0; i < INVENTORY_SIZE; i++){
        if (inventory[i] == 0){
            inventory[i] = item;
            return SUCCESS;
            break;
        }
    }
    return STANDARD_ERROR;
}

/*
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item){
if (0 <= item && item <= 255){
    for (int i = 0; i < INVENTORY_SIZE; i++){
        if (item == inventory[i]){
            return SUCCESS;
            }
        }
    }
    return STANDARD_ERROR;
}