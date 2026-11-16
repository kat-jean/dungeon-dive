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

// pretty much copied from hw4 files ... with a few changes to make it work for this

// reads the room list file and returns a pointer to the start of the Room array
Room* readRoomFile(char *fileName, int *roomCount) {
    // open the file passed in the argument in read mode
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        *roomCount = 0;
        return NULL;
    }

    // set up variables for an array of Room structs
    int capacity = 5;
    int count = 0;

    // allocate the initial memory for 5 rooms
    Room *rooms = malloc(capacity * sizeof(Room));

    char sep[] = ":";
    char buffer[5000];

    // read the file line by line using strtok...
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // skip empty lines in the file
        if (buffer[0] == '\n') {
            continue;
        }

        // create a copy of the line because strtok modifies strings in-place
        char buffer_copy[5000];
        strcpy(buffer_copy, buffer);

        // split the line into a key and value ("room name" & its actual name)
        char *key = strtok(buffer_copy, sep);
        char *value = strtok(NULL, sep);

        // check if both the key and value were found and clean the extra whitespace
        if (key != NULL && value != NULL) {
            char *cleaned_value = str_trim(value);

            // if the key is "Room Name", store it in the current room slot...
            // and resize the array if the current capacity limit is reached
            if (strcmp(key, "Room Name") == 0) {
                if (count >= capacity) {
                    capacity *= 2;
                    Room *temp = realloc(rooms, capacity * sizeof(Room));
                    rooms = temp;
                }
                strncpy(rooms[count].name, cleaned_value, sizeof(rooms[count].name) - 1);
                rooms[count].name[sizeof(rooms[count].name) - 1] = '\0';
            }
            // if the key is "Room Code", store it in the current room slot...
            else if (strcmp(key, "Room Code") == 0) {
                strncpy(rooms[count].code, cleaned_value, sizeof(rooms[count].code) - 1);
                rooms[count].code[sizeof(rooms[count].code) - 1] = '\0';
            }
            // if the key is "Room Description", store it, initialize pointers, and increment room count
            else if (strcmp(key, "Room Description") == 0) {
                strncpy(rooms[count].desc, cleaned_value, sizeof(rooms[count].desc) - 1);
                rooms[count].desc[sizeof(rooms[count].desc) - 1] = '\0';
                rooms[count].north = NULL;
                rooms[count].east = NULL;
                rooms[count].south = NULL;
                rooms[count].west = NULL;
                count++;
            }

            // free the memory dynamically allocated by the str_trim function
            free(cleaned_value);
        }
    }

    // close the file stream once all lines have been processed
    fclose(fp);

    // store the final room count in the pointer passed in and return the array
    *roomCount = count;
    return rooms;
}