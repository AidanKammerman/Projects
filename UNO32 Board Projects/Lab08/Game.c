#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int ItemsRequired = 1;
int descriptionLength;
int descriptionLength2;
int ItemsContainedLength;
int ItemsContainedLength2;
int SkippedDescriptionLength;
int CurrentRoomExits = 0b0000;

static struct
{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t north;
    uint8_t east;
    uint8_t south;
    uint8_t west;
} currentRoom = {};

int LoadRoom(uint16_t roomNumber)
{

    int incompleteItems = 0;
    int NecessaryItems = 0;
    int incompleteItems2 = 0;
    int NecessaryItems2 = 0;

    FILE *room;
    char roomFileName[50];

    sprintf(roomFileName, "RoomFiles/room%d.txt", roomNumber);

    if ((room = fopen(roomFileName, "rb")) == NULL)
    {
        return STANDARD_ERROR;
    }

    fgetc(room);
    fgetc(room);
    fgetc(room);

    int titleLength = fgetc(room);

    if (titleLength == EOF || titleLength == 0 || fgets(currentRoom.title, titleLength + 1, room) == NULL)
    {
        fclose(room);
        return STANDARD_ERROR;
    }

    currentRoom.title[titleLength] = '\0';

    int ItemReqLength = fgetc(room);

    for (int i = 0; i < ItemReqLength; i++)
    {
        if (FindInInventory(fgetc(room)) != SUCCESS)
        {
            NecessaryItems = 0;
            incompleteItems = 1;
        }
        else
        {
            NecessaryItems = 1;
        }
    }

    if (ItemReqLength == 0)
    {
        NecessaryItems = 1;
        incompleteItems = 0;
    }

    if ((NecessaryItems == ItemsRequired) && (incompleteItems == 0))
    {
        descriptionLength = fgetc(room);

        if (descriptionLength == EOF || descriptionLength == 0 || fgets(currentRoom.description, descriptionLength + 1, room) == NULL)
        {
            fclose(room);
            return STANDARD_ERROR;
        }

        currentRoom.description[descriptionLength] = '\0';

        ItemsContainedLength = fgetc(room);

        for (int j = 0; j < ItemsContainedLength; j++)
        {
            AddToInventory(fgetc(room));
        }

        currentRoom.north = fgetc(room);
        currentRoom.east = fgetc(room);
        currentRoom.south = fgetc(room);
        currentRoom.west = fgetc(room);
    }
    else
    {

        SkippedDescriptionLength = fgetc(room);

        for (int z = 0; z < SkippedDescriptionLength; z++)
        {
            fgetc(room);
        }

        ItemsContainedLength = fgetc(room);

        for (int j = 0; j < ItemsContainedLength; j++)
        {
            fgetc(room);
        }

        //skipping exits of first version if required items aren't in player inventory

        fgetc(room);
        fgetc(room);
        fgetc(room);
        fgetc(room);

        int ItemReqLength2 = fgetc(room);

        for (int b = 0; b < ItemReqLength2; b++)
        {
            if (FindInInventory(fgetc(room)) != SUCCESS)
            {
                NecessaryItems2 = 0;
                incompleteItems2 = 1;
            }
            else
            {
                NecessaryItems2 = 1;
            }
        }

        if (ItemReqLength2 == 0)
        {
            NecessaryItems2 = 1;
            incompleteItems2 = 0;
        }

        if ((NecessaryItems2 == ItemsRequired) && (incompleteItems2 == 0))
        {
            descriptionLength2 = fgetc(room);

            if (descriptionLength2 == EOF || descriptionLength2 == 0 || fgets(currentRoom.description, descriptionLength2 + 1, room) == NULL)
            {
                fclose(room);
                return STANDARD_ERROR;
            }

            currentRoom.description[descriptionLength2] = '\0';

            ItemsContainedLength = fgetc(room);

            for (int j = 0; j < ItemsContainedLength; j++)
            {
                AddToInventory(fgetc(room));
            }

            currentRoom.north = fgetc(room);
            currentRoom.east = fgetc(room);
            currentRoom.south = fgetc(room);
            currentRoom.west = fgetc(room);
        }
    }

    return SUCCESS;
}

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void)
{
    if (currentRoom.north != 0)
    {
        return LoadRoom(currentRoom.north);
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void)
{
    if (currentRoom.east != 0)
    {
        return LoadRoom(currentRoom.east);
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void)
{
    if (currentRoom.south != 0)
    {
        return LoadRoom(currentRoom.south);
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoWest(void)
{
    if (currentRoom.west != 0)
    {
        return LoadRoom(currentRoom.west);
    }
    return STANDARD_ERROR;
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void)
{
    return LoadRoom(STARTING_ROOM);
}

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title)
{
    strcpy(title, currentRoom.title);
    return strlen(currentRoom.title);
}

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc)
{
    strcpy(desc, currentRoom.description);
    return strlen(currentRoom.description);
}

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void)
{
    CurrentRoomExits = 0b0000;

    if (currentRoom.north != 0)
    {
        CurrentRoomExits = (CurrentRoomExits | GAME_ROOM_EXIT_NORTH_EXISTS);
    }
    if (currentRoom.east != 0)
    {
        CurrentRoomExits = (CurrentRoomExits | GAME_ROOM_EXIT_EAST_EXISTS);
    }
    if (currentRoom.south != 0)
    {
        CurrentRoomExits = (CurrentRoomExits | GAME_ROOM_EXIT_SOUTH_EXISTS);
    }
    if (currentRoom.west != 0)
    {
        CurrentRoomExits = (CurrentRoomExits | GAME_ROOM_EXIT_WEST_EXISTS);
    }

    return CurrentRoomExits;
}
