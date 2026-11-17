#ifndef STRING_MANIP_H
#define STRING_MANIP_H

// removes the whitespace from each end of a string sent to it
char *str_trim(char *strToTrim);

// returns a pointer to the substring that begins at start and ends at end
char *str_cut(char *str, int start, int end);

#endif