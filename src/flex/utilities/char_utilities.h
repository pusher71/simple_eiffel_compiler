#pragma once

/* Check if string contains given character
 * \param[in] str               input string
 * \param[in] chr               input character
 * \return result of checking
 */
int doesStrContainChar(const char* str, char chr);

/* Remove excluding characters from string
 * \param[in] inputStr          input string
 * \param[in] exclChars         excluding character
 * \return string without excluding characters
 */
void removeExclCharsFromStr(const char* inputStr, const char* exclChars, char* outputStr);

/* Convert string with decimal integer to decimal integer value
 * \param[in] decIntStr         string with decimal integer
 * \return decimal integer value
 */
long long getDecIntFromStringWithDecInt_eiffel(const char* decIntStr);

/* Convert string with binary integer to binary decimal value
 * \param[in] binIntStr         string with binary integer
 * \return decimal integer value
 */
long long getDecIntFromStringWithBinInt_eiffel(const char* binIntStr);

/* Convert string with octal integer to octal decimal value
 * \param[in] octIntStr         string with octal integer
 * \return decimal integer value
 */
long long getDecIntFromStringWithOctInt_eiffel(const char* octIntStr);

/* Convert string with hexadecimal integer to decimal integer value
 * \param[in] hexIntStr         string with hexadecimal integer
 * \return decimal integer value
 */
long long getDecIntFromStringWithHexInt_eiffel(const char* hexIntStr);
