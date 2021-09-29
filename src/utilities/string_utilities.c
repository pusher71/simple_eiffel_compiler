#include "string_utilities.h"
#include "char_utilities.h"

#include <string.h>

int appendCharToStr(const char* src_string, char* dest_string, char chr) {
    if (src_string != dest_string) {
        strcpy(dest_string, src_string);
    }

    int dest_string_length = strlen(dest_string);
    dest_string[dest_string_length]     = chr;
    dest_string[dest_string_length + 1] = 0;
}

unsigned int getFirstWordFromStr(const char* src_string, char* dest_string, const char* delimiters) {
    int resultShift = 0;

    dest_string[0] = 0;

    for (int i=0; i<strlen(src_string) && !doesStrContainChar(delimiters, src_string[i]); i++) {
        resultShift++;
        appendCharToStr(dest_string, dest_string, src_string[i]);
    }

    if (src_string[resultShift] != '\0' && doesStrContainChar(delimiters, src_string[resultShift])) {
        appendCharToStr(dest_string, dest_string, src_string[resultShift]);
        resultShift++;
    }

    return resultShift;
}
