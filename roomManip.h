#ifndef ROOM_MANIP_H
#define ROOM_MANIP_H

// define the Room struct to hold dungeon room data and directional links
typedef struct Room {
    char code[10];
    char name[1000];
    char desc[1000];
    struct Room *north;
    struct Room *east;
    struct Room *south;
    struct Room *west;
} Room;

// takes a pointer to a room and returns a dynamically allocated copy of that room
Room* roomCreate(Room *sourceRoom);

// reads rooms from fileName into a dynamic array and stores the count in roomCount
Room* readRoomFile(char *fileName, int *roomCount);

#endif