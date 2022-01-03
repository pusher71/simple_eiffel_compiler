#include <string.h>
#include <stdlib.h>
#include "char_utilities.h"

int doesStrContainChar(const char* str, char chr) {
    int result = 0;

    int strLength = strlen(str);
    for (int i=0; i<strLength; i++) {
        if (chr == str[i]) {
            result = 1;
            break;
        }
    }

    return result;
}

void removeExclCharsFromStr(const char* inputStr, const char* exclChars, char* outputStr) {
    outputStr[0] = 0;

    int strLength = strlen(inputStr);
    int currIndex = 0;

    for (int i=0; i<strLength; i++) {
        if ( !doesStrContainChar(exclChars, inputStr[i]) ) {
            outputStr[currIndex] = inputStr[i];
            currIndex++;
        }
    }
    outputStr[currIndex] = 0;
}

long long getDecIntFromStringWithDecInt_eiffel(const char* decIntStr) {
    char buffer[1000];
    removeExclCharsFromStr(decIntStr, "_", buffer);

    return atoll(buffer);
}

long long getDecIntFromStringWithBinInt_eiffel(const char* binIntStr) {
    char buffer[1000];
    removeExclCharsFromStr(binIntStr, "_", buffer);

    char buffer_1[1000] = "\0";

    if (buffer[0] == '-') {
        strcpy(buffer_1, "-");
        strcat(buffer_1, buffer + 3);
    }
    else {
        strcpy(buffer_1, buffer + 2);
    }

    return strtoll(buffer_1, NULL, 2);
}

long long getDecIntFromStringWithOctInt_eiffel(const char* octIntStr) {
    char buffer[1000];
    removeExclCharsFromStr(octIntStr, "_", buffer);

    char buffer_1[1000] = "\0";

    if (buffer[0] == '-') {
        strcpy(buffer_1, "-");
        strcat(buffer_1, buffer + 3);
    }
    else {
        strcpy(buffer_1, buffer + 2);
    }

    return strtoll(buffer_1, NULL, 8);
}

long long getDecIntFromStringWithHexInt_eiffel(const char* hexIntStr) {
    char buffer[1000];
    removeExclCharsFromStr(hexIntStr, "_", buffer);

    char buffer_1[1000] = "\0";

    if (buffer[0] == '-') {
        strcpy(buffer_1, "-");
        strcat(buffer_1, buffer + 3);
    }
    else {
        strcpy(buffer_1, buffer + 2);
    }

    return strtoll(buffer_1, NULL, 16);
}
