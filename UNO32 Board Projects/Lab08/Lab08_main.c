// Include libraries here
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Game.h"

//CSE013E Support Library
#include "UNIXBOARD.h"

// User libraries

//  Set any macros or preprocessor directives here
#define NORTH 'n'
#define EAST 'e'
#define SOUTH 's'
#define WEST 'w'
#define QUIT 'q'

//  Declare any data types here

char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
int roomExits = 0b0000;

//  Define any global or external variables here

//  Declare any function prototypes here

void displayRoom(void)
{
    system("clear");

    GameGetCurrentRoomTitle(title);
    printf("\n%s\n\n", title);

    GameGetCurrentRoomDescription(description);
    printf("%s\n\n", description);

    roomExits = GameGetCurrentRoomExits();

    if ((roomExits & GAME_ROOM_EXIT_NORTH_EXISTS) == GAME_ROOM_EXIT_NORTH_EXISTS)
    {
        printf("NORTH\n");
    }
    if ((roomExits & GAME_ROOM_EXIT_EAST_EXISTS) == GAME_ROOM_EXIT_EAST_EXISTS)
    {
        printf("EAST\n");
    }
    if ((roomExits & GAME_ROOM_EXIT_SOUTH_EXISTS) == GAME_ROOM_EXIT_SOUTH_EXISTS)
    {
        printf("SOUTH\n");
    }
    if ((roomExits & GAME_ROOM_EXIT_WEST_EXISTS) == GAME_ROOM_EXIT_WEST_EXISTS)
    {
        printf("WEST\n");
    }

    printf("\n");
}

int main()
{
    uint8_t dir = 0;
    uint8_t roomExits = 0;
    if (GameInit() == STANDARD_ERROR)
    {
        printf("Failed to Land Starting Room");
        FATAL_ERROR();
    }

    //function to display room

    displayRoom();

    while (TRUE)
    {
        dir = getchar();
        roomExits = GameGetCurrentRoomExits();

        switch (dir)
        {
        case NORTH:
            if (roomExits & GAME_ROOM_EXIT_NORTH_EXISTS)
            {
                if (GameGoNorth() != STANDARD_ERROR)
                {
                    //do something reference code does nothing
                }
                else
                {
                    FATAL_ERROR();
                }
            }
            break;

        case EAST:
            if (roomExits & GAME_ROOM_EXIT_EAST_EXISTS)
            {
                if (GameGoEast() != STANDARD_ERROR)
                {
                    //do something reference code does nothing
                }
                else
                {
                    FATAL_ERROR();
                }
            }
            break;

        case SOUTH:
            if (roomExits & GAME_ROOM_EXIT_SOUTH_EXISTS)
            {
                if (GameGoSouth() != STANDARD_ERROR)
                {
                    //do something reference code does nothing
                }
                else
                {
                    FATAL_ERROR();
                }
            }
            break;

        case WEST:
            if (roomExits & GAME_ROOM_EXIT_WEST_EXISTS)
            {
                if (GameGoWest() != STANDARD_ERROR)
                {
                    //do something reference code does nothing
                }
                else
                {
                    FATAL_ERROR();
                }
            }
            break;

        case QUIT:
            printf("Thank you for playing. Goodbye \n");
            exit(0);
            break;
        }

        //display room
        displayRoom();
        while (getchar() != '\n')
            ;
    }

    /** Your custom code goes below here **/

    /**/
}