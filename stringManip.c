#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// function from class... removes excess whitespace from a string
    char* trim(char *strToTrim){
    int strSize = strlen(strToTrim);

    char *endPtr = strToTrim + strSize - 1;
    while (isspace(*endPtr)){
        endPtr--; 
    }
    *(endPtr+1) = '\0';

    char *start = strToTrim;
    while (isspace(*start)){
        start++;
    }

    // allocate memory and copy string into storage spot
    char *finalVersion = malloc(sizeof(char) * (strlen(start) + 1));
    strcpy(finalVersion, start);
    return finalVersion;
}

// returns a newly allocated substring from index start to end 
char *str_cut(char *str, int start, int end){
    if (str == NULL || start < 0 || end < start){
        return NULL;
    }

    int len = strlen(str);
    if (start >= len){
        return NULL;
    }
    if (end >= len){
        end = len - 1;
    }

}