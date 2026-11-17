#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "roomManip.h"
#include "stringManip.h"

// builds a linked list for east/west of random rooms of size dungeonSize
Room *createDungeon(Room *roomArray, int arraySize, int dungeonSize) {
    if (roomArray == NULL || arraySize <= 0 || dungeonSize <= 0) {
        return NULL;
    }

    Room *head = NULL;
    Room *prev = NULL;

    for (int i = 0; i < dungeonSize; i++) {
        // pick a random room from the array and create a copy of it
        int randIndex = rand() % arraySize;
        Room *newRoom = roomCreate(&roomArray[randIndex]);

        if (head == NULL) {
            head = newRoom;
        } else {
            // link east and west
            prev->east = newRoom;
            newRoom->west = prev;
        }
        prev = newRoom;
    }

    return head;
}

// loops through the dungeon linked list printing each room's code and name
void printDungeon(Room *startRoom) {
    Room *current = startRoom;
    while (current != NULL) {
        printf("Room %s: %s\n", current->code, current->name);
        current = current>east;
    }
}
// walks through the dungeon linked list and frees every room node
void deleteDungeon(Room *startRoom) {
    Room *current = startRoom;
    while (current != NULL) {
        Room *nextRoom = current->east;
        free(current);
        current = nextRoom;
    }
}