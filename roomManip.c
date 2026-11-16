#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "roomManip.h"
#include "stringManip.h"

// takes a pointer to a room and returns a copy of that room
Room* roomCreate(Room *sourceRoom) {
    if (sourceRoom == NULL) {
        return NULL;
    }

    // allocate memory for the new room copy
    Room *newRoom = malloc(sizeof(Room));
    if (newRoom == NULL) {
        return NULL;
    }

    // copy the room strings safely
    strncpy(newRoom->code, sourceRoom->code, sizeof(newRoom->code) - 1);
    newRoom->code[sizeof(newRoom->code) - 1] = '\0';

    strncpy(newRoom->name, sourceRoom->name, sizeof(newRoom->name) - 1);
    newRoom->name[sizeof(newRoom->name) - 1] = '\0';

    strncpy(newRoom->desc, sourceRoom->desc, sizeof(newRoom->desc) - 1);
    newRoom->desc[sizeof(newRoom->desc) - 1] = '\0';

    // initialize all 4 directional pointers to NULL
    newRoom->north = NULL;
    newRoom->east = NULL;
    newRoom->south = NULL;
    newRoom->west = NULL;

    return newRoom;
}