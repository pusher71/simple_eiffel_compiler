#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ===============================================================
// #
// #   CHAR ARRAY STRUCT ...
// #
// ===============================================================
/**
 * @brief Char Array struct
 */
typedef struct CharArray CharArray;

// ==================================================
// # ... CREATING
// ==================================================
/**
 * @brief Create char array
 * @return char array allocated on the heap
 */
CharArray* chaarcreate();

/**
 * @brief Destroy char array
 * @return success code (0 - success, 1 - error)
 */
int chaardestroy(CharArray* char_array);

// ==================================================
// # ... GETTING ATTRIBUTES
// ==================================================
/**
 * @brief Get length of char array
 * @param[in] char_array				input char array
 * @return length of char array (-1 - invalid char array)
 */
unsigned int chaarlen(const CharArray* char_array);

/**
 * @brief Get character of char array at given index
 * @param char_array					input char array
 * @param char_index					index of character
 * @return gotten character ('-1' - if error has occurred)
 */
char chaargetchr(const CharArray* char_array, unsigned int char_index);

// ==================================================
// # ... CONTRACT
// ==================================================
// --------------------------------------------------
// | Contract with clearing char array data
// --------------------------------------------------
/**
 * @brief Clear data of char array
 * @param[in] 	char_array				input char array
 * @return success code (0 - success, 1 - error)
 */
int chaarclr(CharArray* char_array);

/**
 * @brief Copy data of source char array to destination char array
 * @param[out] 	dest_chararray			destination char array
 * @param[in] 	src_chararray     		source char array
 * @return success code (0 - success, 1 - error)
 */
int chaarcpy(CharArray* dest_chararray, const CharArray* src_chararray);

/**
 * @brief Copy data of source string to destination char array
 * @param[out] 	dest_chararray			destination char array
 * @param[in]   src_string				source string
 * @param[in]   src_string_length		length of source string
 * @return success code (0 - success, 1 - error)
 */
int chaarcpy_str(CharArray* dest_chararray, const char* src_string, unsigned src_string_length);

/**
 * @brief Delete elements in char array
 * @param[in, out] 	char_array			input char array
 * @param[in] 		start_char_index	index of character in char array from which deleting will be performed
 * @param[in] 		chars_count			count of characters to delete
 * @return count of characters that were deleted
 */
int chaardel(CharArray* char_array, unsigned int start_char_index, unsigned int chars_count);

// --------------------------------------------------
// | Contract without clearing char array data
// --------------------------------------------------
/**
 * @brief Concat data of source char array to data of destination char array
 * @param[in, out] 	dest_chararray		destination char array
 * @param[in] 		src_chararray     	source char array
 * @return success code (0 - success, 1 - error)
 */
int chaarcat(CharArray* dest_chararray, const CharArray* src_chararray);

/**
 * @brief Concat data of source string to data of destination char array
 * @param[out] 	dest_chararray			destination char array
 * @param[in]   src_string				source string
 * @param[in]   src_string_length		length of source string
 * @return success code (0 - success, 1 - error)
 */
int chaarcat_str(CharArray* out_char_array, const char* input_str, unsigned str_length);

/**
 * @brief Append char to the end of char array
 * @param[in, out] 	char_array			char array
 * @param[in] 		chr					input char
 * @return success code (0 - success, 1 - error)
 */
int chaaraddchr(CharArray* char_array, char chr);

// ==================================================
// # ... COMPARING
// ==================================================
/**
 * @brief Compare two char arrays
 * @param[in] left_chararray			left char array
 * @param[in] right_chararray			right char array
 * @return result of comparing (0 - equal; 1 - left is more; -1 - right is more; 2 - invalid input data)
 */
int chaarcmp(const CharArray* left_chararray, const CharArray* right_chararray);

// ==================================================
// # ... ADDITIONAL
// ==================================================
/**
 * @brief Enumeration of char array print modes
 */
enum CharArrayPrintMode {
    CHAAR__STANDARD_PRINT,		/*! Standard printing characters of char array */
    CHAAR__HEX_CODES_PRINT		/*! Printing hexadecimal codes of char array characters */
};

/**
 * @brief Print data of char array to the console
 * @param[in] char_array				input char array
 * @param[in] mode						mode of printing char array
 * @return success code (0 - success, 1 - error)
 */
int chaarprint(const CharArray* char_array, enum CharArrayPrintMode mode);

#ifdef __cplusplus
}
#endif
