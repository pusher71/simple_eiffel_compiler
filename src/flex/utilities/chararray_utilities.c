#include "chararray_utilities.h"
#include <stdio.h>
#include <stdlib.h>

struct CharArray {
    short isInitialized;	/*! Sign indicating that char array is initialized for work */

    char* beginPtr;			/*! Beginning of char array */
    unsigned int length;	/*! Length of char array */
};

CharArray* chaarcreate() {
    CharArray* result = (CharArray*)malloc(sizeof(CharArray));
    result->isInitialized = 1;
    result->length = 0;

    return result;
}

int chaardestroy(CharArray* char_array) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Destroy char array that isn\'t initialized ]\n");
        return 1;
    }

    // Free memory that is used by char array
    chaarclr(char_array);

    char_array->isInitialized = 0;
    free(char_array);

    return 0;
}

unsigned int chaarlen(const CharArray* char_array) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Get length of char array that isn\'t initialized ]\n");
        return -1;
    }

    // Get length of char array
    return char_array->length;
}

char chaargetchr(const CharArray* char_array, unsigned int char_index) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Get character of char array that isn\'t initialized ]\n");
        return -1;
    }

    // Get character of char array at given position
    if (char_index >= 0 && char_index <= char_array->length-1) 	{ return char_array->beginPtr[char_index]; }
    else 														{ return -1; }
}

int chaarclr(CharArray* char_array) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Clear data of char array that isn\'t initialized ]\n");
        return 1;
    }

    // Clear data of char array if char array isn't empty
    if (char_array->length != 0) {
        free(char_array->beginPtr);
        char_array->length = 0;
    }

    return 0;
}

int chaarcpy(CharArray* dest_chararray, const CharArray* src_chararray) {
    // Set error if char arrays aren't initialized
    int errorCode = 0;
    if (!dest_chararray->isInitialized) { errorCode = 1; printf("[ CHAR ARRAY ERROR :: Destination char array isn\'t initialized ]\n"); }
    if (!src_chararray->isInitialized) 	{ errorCode = 1; printf("[ CHAR ARRAY ERROR :: Source char array isn\'t initialized ]\n"); }

    if (errorCode != 0) { return 1; }

    // Clear char array
    chaarclr(dest_chararray);

    // Copy data from source char array to destination char array
    dest_chararray->beginPtr = (char*)malloc(src_chararray->length * sizeof(char));
    for (int i=0; i<src_chararray->length; i++) {
        dest_chararray->beginPtr[i] = src_chararray->beginPtr[i];
    }

    dest_chararray->length = src_chararray->length;

    return 0;
}

int chaarcpy_str(CharArray* dest_chararray, const char* src_string, unsigned src_string_length) {
    // Set error if char array isn't initialized
    if (!dest_chararray->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Copy string data to char array that isn\'t initialized ]\n");
        return 1;
    }

    // Clear char array
    chaarclr(dest_chararray);

    // Copy data from input string to char array
    dest_chararray->beginPtr = (char*)malloc(src_string_length * sizeof(char));
    for (int i=0; i<src_string_length; i++) {
        dest_chararray->beginPtr[i] = src_string[i];
    }

    dest_chararray->length = src_string_length;

    return 0;
}

int chaardel(CharArray* char_array, unsigned int start_char_index, unsigned int chars_count) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Delete data of char array that isn\'t initialized ]\n");
        return 1;
    }

    // Extract all non-deleted characters of char array ...
    CharArray* buffer = chaarcreate();

    // ... Extract first part of char array before deleted characters
    for (int i=0; i<start_char_index && i<char_array->length; i++) {
        chaaraddchr(buffer, char_array->beginPtr[i]);
    }

    // ... Extract second part of char array after deleted characters
    for (int i=start_char_index + chars_count; i<char_array->length; i++) {
        chaaraddchr(buffer, char_array->beginPtr[i]);
    }

    // Replace char array characters with extracted characters
    unsigned int deletedCharsCount = char_array->length - buffer->length;

    chaarcpy(char_array, buffer);
    chaardestroy(buffer);

    return deletedCharsCount;
}

int chaarcat(CharArray* dest_chararray, const CharArray* src_chararray) {
    // Set error if char arrays aren't initialized
    int errorCode = 0;
    if (!dest_chararray->isInitialized) { errorCode = 1; printf("[ CHAR ARRAY ERROR :: Destination char array isn\'t initialized ]\n"); }
    if (!src_chararray->isInitialized) 	{ errorCode = 1; printf("[ CHAR ARRAY ERROR :: Source char array isn\'t initialized ]\n"); }

    if (errorCode != 0) { return 1; }

    // Allocate memory for new elements in destination char array
    unsigned int newCharArraySize = dest_chararray->length + src_chararray->length;

    if (dest_chararray->length == 0) 	{ dest_chararray->beginPtr = (char*)malloc(src_chararray->length * sizeof(char)); }
    else 								{ dest_chararray->beginPtr = (char*)realloc(dest_chararray->beginPtr, newCharArraySize * sizeof(char)); }

    // Append data from source char array to destination char array
    for (int i=0; i<src_chararray->length; i++) {
        dest_chararray->beginPtr[i + dest_chararray->length] = src_chararray->beginPtr[i];
    }

    dest_chararray->length = newCharArraySize;

    return 0;
}

int chaarcat_str(CharArray* dest_chararray, const char* src_string, unsigned src_string_length) {
    // Set error if char array isn't initialized
    if (!dest_chararray->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Copy string data to char array that isn\'t initialized ]\n");
        return 1;
    }

    // Convert string to char array
    CharArray* buffer = chaarcreate();
    chaarcpy_str(buffer, src_string, src_string_length);

    // Concat converted string data to data of char array
    int successCode = chaarcat(dest_chararray, buffer);
    chaardestroy(buffer);

    return successCode;
}

int chaaraddchr(CharArray* char_array, char chr) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Copy stringdata to char array that isn\'t initialized ]\n");
        return 1;
    }

    // Allocate memory for new element in char array
    if (char_array->length == 0) 	{ char_array->beginPtr = (char*)malloc(sizeof(char)); }
    else 							{ char_array->beginPtr = (char*)realloc(char_array->beginPtr, (char_array->length + 1) * sizeof(char)); }

    // Append new element to the allocated position in char array
    char_array->beginPtr[char_array->length] = chr;
    char_array->length++;

    return 0;
}

int chaarcmp(const CharArray* left_chararray, const CharArray* right_chararray) {
    // Set error if char arrays aren't initialized
    int errorCode = 0;
    if (!left_chararray->isInitialized) 	{ errorCode = 1; printf("[ CHAR ARRAY ERROR :: Left char array isn\'t initialized ]\n"); }
    if (!right_chararray->isInitialized) 	{ errorCode = 1; printf("[ CHAR ARRAY ERROR :: Right char array isn\'t initialized ]\n"); }

    if (errorCode != 0) { return 2; }

    // Compare char arrays
    if (left_chararray->length > right_chararray->length) 		{ return 1; }
    else if (left_chararray->length < right_chararray->length) 	{ return -1; }
    else {
        int currCharsCompareCode = 0;

        for (int i=0; i<left_chararray->length; i++) {
            if (left_chararray->beginPtr[i] > right_chararray->beginPtr[i]) 		{ currCharsCompareCode = 1; break; }
            else if (left_chararray->beginPtr[i] < right_chararray->beginPtr[i]) 	{ currCharsCompareCode = -1; break; }
        }

        return currCharsCompareCode;
    }

    return 0;
}

int chaarprint(const CharArray* char_array, enum CharArrayPrintMode mode) {
    // Set error if char array isn't initialized
    if (!char_array->isInitialized) {
        printf("[ CHAR ARRAY ERROR :: Print char array that isn\'t initialized ]\n");
        return 1;
    }

    // Print char array based on given print mode
    for (int i=0; i<char_array->length; i++) {
        if (mode == CHAAR__STANDARD_PRINT) 			{ printf("%c", char_array->beginPtr[i]); }			// Standard printing characters of char array
        else if (mode == CHAAR__HEX_CODES_PRINT) 	{ printf("%02x ", char_array->beginPtr[i]); }		// Printing hexadecimal codes of char array characters
        else 										{ return 1; }										// Set error if given print mode is invalid
    }

    // If hex codes of char array are printed remove last delimiter character
    if (mode == CHAAR__HEX_CODES_PRINT) { printf("\10"); }

    return 0;
}
