#pragma once

/* Append character to string
 * \param[in]   src_string          source string
 * \param[out]  dest_string         destination string
 * \param[in]   chr                 character that will be appended
 */
int appendCharToStr(const char* src_string, char* dest_string, char chr);

/* Get first word (can be EMPTY) from given string
 * \param[in]   src_string          source string
 * \param[out]  dest_string         destination string
 * \param[in]   chr                 delimiters
 * \return shift to next word index
 */
unsigned int getFirstWordFromStr(const char* src_string, char* dest_string, const char* delimiters);
