%option noyywrap
%option never-interactive
%option caseless

%x CHAR
%x STRING
%x VERBATIM_STRING
%x STRIPSOFF_STRING

DEC_INT_PTTRN \-?[0-9]+(_[0-9]+)*
BIN_INT_PTTRN \-?0b[01]+(_[01]+)*
OCT_INT_PTTRN \-?0c[0-7]+(_[0-7]+)*
HEX_INT_PTTRN \-?0x[0-9a-f]+(_[0-9a-f]+)*

INVALID_VALUE_TOKEN \-?[0-9]+\w+

%{
    #include <ctype.h>
    #include <limits.h>
    #include <string.h>

    #include "utilities/char_utilities.h"
    #include "utilities/chararray_utilities.h"

    #include "parser.h"

    enum LexerErrorCode {
        NO_ERROR,
        GENERAL_ERROR,

        INVALID_CHAR_CODE
    };

    unsigned int debug_cursorLineIndex       = 0;
    unsigned int debug_cursorColumnIndex     = 0;

    void debug_moveCursorToNextLine() {
        debug_cursorLineIndex++;
        debug_cursorColumnIndex = 0;
    }

    void debug_moveCursorToNextCharacter(int word_length) {
        debug_cursorColumnIndex += word_length;
    }

    unsigned int error_cursorLineIndex;
    unsigned int error_cursorColumnIndex;
%}

%%

%{
    // Lexer error tools
    enum LexerErrorCode lexerErrorCode = NO_ERROR;
    char lexerErrorBuffer[1024];

    int lexerErrorValue;

    int oldCursorLineIndex         = 0;
    int oldCursorColumnIndex     = 0;

    // Read buffers
    CharArray* read_charArray;

    // Constraints
    unsigned int minCharCode = 0;
    unsigned int maxCharCode = 127;
%}

true   { debug_moveCursorToNextCharacter(yyleng); yylval.liter_boolean_field = 1; return LITER_BOOLEAN; }
false  { debug_moveCursorToNextCharacter(yyleng); yylval.liter_boolean_field = 0; return LITER_BOOLEAN; }

{DEC_INT_PTTRN} { debug_moveCursorToNextCharacter(yyleng); yylval.liter_integer_field = getDecIntFromStringWithDecInt_eiffel(yytext); return LITER_INTEGER; }
{BIN_INT_PTTRN} { debug_moveCursorToNextCharacter(yyleng); yylval.liter_integer_field = getDecIntFromStringWithBinInt_eiffel(yytext); return LITER_INTEGER; }
{OCT_INT_PTTRN} { debug_moveCursorToNextCharacter(yyleng); yylval.liter_integer_field = getDecIntFromStringWithOctInt_eiffel(yytext); return LITER_INTEGER; }
{HEX_INT_PTTRN} { debug_moveCursorToNextCharacter(yyleng); yylval.liter_integer_field = getDecIntFromStringWithHexInt_eiffel(yytext); return LITER_INTEGER; }

{INVALID_VALUE_TOKEN} { printf("[ LEXICAL ERROR :: Invalid value token \"%s\" in line: %d ]\n", yytext, debug_cursorLineIndex+1); debug_moveCursorToNextCharacter(yyleng); }

\' {
    read_charArray = chaarcreate();
    BEGIN(CHAR);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextCharacter(yyleng);
}

\" {
    read_charArray = chaarcreate();
    BEGIN(STRING);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextCharacter(yyleng);
}

\"\{[ \t]*\n {
    read_charArray = chaarcreate();
    BEGIN(VERBATIM_STRING);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextLine();
}

\"\[[ \t]*\n {
    read_charArray = chaarcreate();
    BEGIN(STRIPSOFF_STRING);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextLine();
}

<VERBATIM_STRING,STRIPSOFF_STRING,STRING,CHAR>[^\'\"\%\n']+     {
                                                                    chaarcat_str(read_charArray, yytext, strlen(yytext));
                                                                    debug_moveCursorToNextCharacter(yyleng);
                                                                }

<VERBATIM_STRING,STRIPSOFF_STRING>[\"\'\%\n]+                   {
                                                                    chaarcat_str(read_charArray, yytext, strlen(yytext));

                                                                    for (int i=0; i<strlen(yytext); i++) {
                                                                        if (yytext[i] == '\n')     { debug_moveCursorToNextLine(); }
                                                                        else                     { debug_moveCursorToNextCharacter(1); }
                                                                    }
                                                                }

<STRING>\'+                                                     {
                                                                    chaarcat_str(read_charArray, yytext, strlen(yytext));
                                                                    debug_moveCursorToNextCharacter(yyleng);
                                                                }

<CHAR>\"+                                                       {
                                                                    chaarcat_str(read_charArray, yytext, strlen(yytext));
                                                                    debug_moveCursorToNextCharacter(yyleng);
                                                                }

<STRING,CHAR>\%A {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "@", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%B {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\10", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%C {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "^", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%D {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "$", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%F {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\14", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%H {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\10", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%L {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "~", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%N {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\n", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%Q {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "`", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%R {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\15", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%S {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "#", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%T {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\t", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%U {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "\0", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%V {
    if (isupper(yytext[1])) {
        chaarcat_str(read_charArray, "|", 1);
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%%  { chaarcat_str(read_charArray, "%", 1); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\' { chaarcat_str(read_charArray, "\'", 1); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\" { chaarcat_str(read_charArray, "\"", 1); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\( { chaarcat_str(read_charArray, "[", 1); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\) { chaarcat_str(read_charArray, "]", 1); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\< { chaarcat_str(read_charArray, "{", 1); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\> { chaarcat_str(read_charArray, "}", 1); debug_moveCursorToNextCharacter(yyleng); }

<STRING,CHAR>\%\/{DEC_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithDecInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)       { chaaraddchr(read_charArray, charCode); }
    else                                                        { lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%\/{BIN_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithBinInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)       { chaaraddchr(read_charArray, charCode); }
    else                                                        { lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%\/{OCT_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithOctInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)       { chaaraddchr(read_charArray, charCode); }
    else                                                        { lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%\/{HEX_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithHexInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)       { chaaraddchr(read_charArray, charCode); }
    else                                                        { lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<CHAR>%[^\'\n] {
    printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    lexerErrorCode = GENERAL_ERROR;

    debug_moveCursorToNextCharacter(yyleng);
}

<CHAR>%\/[^\'\n]*\/ {
    printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    lexerErrorCode = GENERAL_ERROR;

    debug_moveCursorToNextCharacter(yyleng);
}

<CHAR>\n {
    printf("[ LEXICAL ERROR :: No matching \' bracket for bracket at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    lexerErrorCode = NO_ERROR;

    BEGIN(INITIAL);
    chaardestroy(read_charArray);

    debug_moveCursorToNextLine();
}

<CHAR><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching \' bracket for bracket at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    lexerErrorCode = NO_ERROR;

    BEGIN(INITIAL);
    chaardestroy(read_charArray);
}

<CHAR>\' {
    if (lexerErrorCode == NO_ERROR) {
        if (chaarlen(read_charArray) == 1) {
            yylval.liter_char_field = chaargetchr(read_charArray, 0);
            chaardestroy(read_charArray);

            debug_moveCursorToNextCharacter(yyleng);
            BEGIN(INITIAL);

            return LITER_CHAR;
        }
        else if (chaarlen(read_charArray) > 1) {
            printf("[ LEXICAL ERROR :: More than one character are placed in single brackets \'");
            chaarprint(read_charArray, CHAAR__STANDARD_PRINT);
            printf("\' at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
        }
        else if (chaarlen(read_charArray) == 0) {
            printf("[ LEXICAL ERROR :: Empty character \'\' at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
        }
    }
    else {
        if (lexerErrorCode == INVALID_CHAR_CODE) {
            printf("[ LEXICAL ERROR :: Invalid character code (%d) at (line: %d, column = %d) ]\n", lexerErrorValue, error_cursorLineIndex+1, error_cursorColumnIndex+1);
        }

        lexerErrorCode = NO_ERROR;
    }

    chaardestroy(read_charArray);

    debug_moveCursorToNextCharacter(yyleng);
    BEGIN(INITIAL);
}

<STRING>%[ \t\n]+% {
    for (int i=0; i<strlen(yytext); i++) {
        if (yytext[i] == '\n')     { debug_moveCursorToNextLine(); }
        else                     { debug_moveCursorToNextCharacter(1); }
    }
}

<STRING>%[^\"\n] {
    printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' in string at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    lexerErrorCode = GENERAL_ERROR;

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING>%\/[^\"\n]*\/ {
    printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' in string at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    lexerErrorCode = GENERAL_ERROR;

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING>[^\"\n] {
    printf("[ LEXICAL ERROR :: Unknown character \"%s\" in string at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    lexerErrorCode = GENERAL_ERROR;

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING>\n {
    printf("[ LEXICAL ERROR :: No matching \" bracket at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);

    BEGIN(INITIAL);
    chaardestroy(read_charArray);

    debug_moveCursorToNextLine();
}

<STRING><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching \" bracket at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);

    BEGIN(INITIAL);
    chaardestroy(read_charArray);
}

<STRING>\" {
    if (lexerErrorCode == NO_ERROR) {
        yylval.liter_string_field = read_charArray;

        debug_moveCursorToNextCharacter(yyleng-1);
        BEGIN(INITIAL);

        return LITER_STRING;
    }
    else {
        lexerErrorCode = NO_ERROR;
    }

    chaardestroy(read_charArray);

    debug_moveCursorToNextCharacter(yyleng);
    BEGIN(INITIAL);
}

<VERBATIM_STRING>^[ \t]*\}\" {
    int lastCharPos = chaarlen(read_charArray) - 1;
    if (chaargetchr(read_charArray, lastCharPos) == '\n') {
        chaardel(read_charArray, lastCharPos, 1);
    }

    yylval.liter_string_field = read_charArray;
    return LITER_STRING;

    debug_moveCursorToNextCharacter(yyleng-1);
    BEGIN(INITIAL);
}

<VERBATIM_STRING>^[ \t]*[^ \t\n]+[ \t]*\}\" {
    printf("[ LEXICAL ERROR :: No matching <}\"> bracket for verbatim string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);

    BEGIN(INITIAL);
    chaardestroy(read_charArray);

    for (int i=0; i<strlen(yytext); i++) {
        if (yytext[i] == '\n')     { debug_moveCursorToNextLine(); }
        else                     { debug_moveCursorToNextCharacter(1); }
    }
}

<VERBATIM_STRING><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching <}\"> bracket for verbatim string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);

    BEGIN(INITIAL);
    chaardestroy(read_charArray);
}

\}\" {
    printf("[ LEXICAL ERROR :: Invalid closing bracket <}\"> for verbatim string at (line: %d, column = %d) ]\n", debug_cursorLineIndex+1, debug_cursorColumnIndex+1);

    debug_moveCursorToNextCharacter(yyleng);
}

<STRIPSOFF_STRING>^[ \t]*\]\" {
    int lastCharPos = chaarlen(read_charArray) - 1;
    if (chaargetchr(read_charArray, lastCharPos) == '\n') {
        chaardel(read_charArray, lastCharPos, 1);
    }

    // Define number of first space characters to delete in each line of stripsoff string
    unsigned int firstChrsToDeleteCount = (chaargetchr(read_charArray, chaarlen(read_charArray)-1) != '\n' ? UINT_MAX : 0);

    int currIndex = 0;
    do {
        // Get each line of char array beginning from the first line
        CharArray* currLine = chaarcreate();

        for (;currIndex < chaarlen(read_charArray) && chaargetchr(read_charArray, currIndex) != '\n'; currIndex++) {
            chaaraddchr(currLine, chaargetchr(read_charArray, currIndex));
        }
        currIndex++;

        // Check if gotten line is empty
        int isLineEmpty = 1;
        for (int i=0; i<chaarlen(currLine) && isLineEmpty; i++) {
            char currChar = chaargetchr(currLine, i);
            if (currChar != ' ' && currChar != '\t') { isLineEmpty = 0; }
        }

        // Count number of spaces placed in the beginning of gotten line
        unsigned int firstNonSpaceIndex = 0;
        for (;firstNonSpaceIndex < chaarlen(currLine) && chaargetchr(currLine, firstNonSpaceIndex) == ' '; firstNonSpaceIndex++);

        // Redefine current number of first spaces to delete
        if (isLineEmpty)                                         { firstChrsToDeleteCount = 0; }
        else if (firstChrsToDeleteCount > firstNonSpaceIndex)     { firstChrsToDeleteCount = firstNonSpaceIndex; }

        chaardestroy(currLine);

    } while(currIndex < chaarlen(read_charArray) && firstChrsToDeleteCount != 0);

    // Get result stripsoff string without defined first space characters in each line
    CharArray* result = chaarcreate();

    currIndex = 0;
    do {
        CharArray* currLine = chaarcreate();

        for (;currIndex < chaarlen(read_charArray) && chaargetchr(read_charArray, currIndex) != '\n'; currIndex++) {
            chaaraddchr(currLine, chaargetchr(read_charArray, currIndex));
        }

        if (chaargetchr(read_charArray, currIndex) == '\n') { chaaraddchr(currLine, '\n'); }
        currIndex++;

        chaardel(currLine, 0, firstChrsToDeleteCount);
        chaarcat(result, currLine);
    } while(currIndex < chaarlen(read_charArray));

    // Print result
    yylval.liter_string_field = result;
    chaardestroy(read_charArray);

    return LITER_STRING;

    debug_moveCursorToNextCharacter(yyleng-1);
    BEGIN(INITIAL);
}

<STRIPSOFF_STRING>^[ \t]*[^ \t\n]+[ \t]*\]\" {
    printf("[ LEXICAL ERROR :: No matching <]\"> bracket for strips-off string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);

    BEGIN(INITIAL);
    chaardestroy(read_charArray);

    for (int i=0; i<strlen(yytext); i++) {
        if (yytext[i] == '\n')     { debug_moveCursorToNextLine(); }
        else                     { debug_moveCursorToNextCharacter(1); }
    }
}

<STRIPSOFF_STRING><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching <]\"> bracket for strips-off string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);

    BEGIN(INITIAL);
    chaardestroy(read_charArray);
}

\]\" {
    printf("[ LEXICAL ERROR :: Invalid closing bracket <]\"> for strips-off string at (line: %d, column = %d) ]\n", debug_cursorLineIndex+1, debug_cursorColumnIndex+1);

    debug_moveCursorToNextCharacter(yyleng);
}

class           { debug_moveCursorToNextCharacter(yyleng); return CLASS; }
create          { debug_moveCursorToNextCharacter(yyleng); return CREATE; }
do              { debug_moveCursorToNextCharacter(yyleng); return DO; }
end             { debug_moveCursorToNextCharacter(yyleng); return END; }
feature         { debug_moveCursorToNextCharacter(yyleng); return FEATURE; }
inherit         { debug_moveCursorToNextCharacter(yyleng); return INHERIT; }
rename          { debug_moveCursorToNextCharacter(yyleng); return RENAME; }
as              { debug_moveCursorToNextCharacter(yyleng); return AS; }
undefine        { debug_moveCursorToNextCharacter(yyleng); return UNDEFINE; }
redefine        { debug_moveCursorToNextCharacter(yyleng); return REDEFINE; }
select          { debug_moveCursorToNextCharacter(yyleng); return SELECT; }
local           { debug_moveCursorToNextCharacter(yyleng); return LOCAL; }
result          { debug_moveCursorToNextCharacter(yyleng); return RESULT; }
current         { debug_moveCursorToNextCharacter(yyleng); return CURRENT; }
void            { debug_moveCursorToNextCharacter(yyleng); }

if              { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
then            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
else            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
elseif          { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
inspect         { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
when            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
loop            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
from            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
until           { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
variant         { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }

boolean         { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_BOOLEAN; }
character       { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_CHARACTER; }
integer_8       { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_INTEGER_8; }
integer_16      { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_INTEGER_16; }
integer_32      { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_INTEGER_32; }
integer_64      { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_INTEGER_64; }
natural_8       { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_NATURAL_8; }
natural_16      { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_NATURAL_16; }
natural_32      { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_NATURAL_32; }
natural_64      { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_NATURAL_64; }
string          { debug_moveCursorToNextCharacter(yyleng); return DATATYPE_STRING; }

"+"     { printf("<OPERATOR: PLUS>\n"); debug_moveCursorToNextCharacter(yyleng); }
"-"     { printf("<OPERATOR: MINUS>\n"); debug_moveCursorToNextCharacter(yyleng); }
"*"     { printf("<OPERATOR: MULT>\n"); debug_moveCursorToNextCharacter(yyleng); }
"//"    { printf("<OPERATOR: INTEGER DIVISION>\n"); debug_moveCursorToNextCharacter(yyleng); }
"\\"    { printf("<OPERATOR: FRACTIONAL DIVISION>\n"); debug_moveCursorToNextCharacter(yyleng); }

"="     { printf("<OPERATOR: EQUALITY>\n"); debug_moveCursorToNextCharacter(yyleng); }
"/="    { printf("<OPERATOR: INEQUALITY>\n"); debug_moveCursorToNextCharacter(yyleng); }
">"     { printf("<OPERATOR: MORE>\n"); debug_moveCursorToNextCharacter(yyleng); }
"<"     { printf("<OPERATOR: LESS>\n"); debug_moveCursorToNextCharacter(yyleng); }
">="    { printf("<OPERATOR: MORE OR EQUAL>\n"); debug_moveCursorToNextCharacter(yyleng); }
"<="    { printf("<OPERATOR: LESS OR EQUAL>\n"); debug_moveCursorToNextCharacter(yyleng); }

":="    { printf("<OPERATOR: ASSIGN>\n"); debug_moveCursorToNextCharacter(yyleng); }

and     { printf("<OPERATOR: AND>\n"); debug_moveCursorToNextCharacter(yyleng); }
or      { printf("<OPERATOR: OR>\n"); debug_moveCursorToNextCharacter(yyleng); }
not     { printf("<OPERATOR: NOT>\n"); debug_moveCursorToNextCharacter(yyleng); }
xor     { printf("<OPERATOR: XOR>\n"); debug_moveCursorToNextCharacter(yyleng); }

"." { debug_moveCursorToNextCharacter(yyleng); return '.'; }
";" { debug_moveCursorToNextCharacter(yyleng); return ';'; }
"[" { debug_moveCursorToNextCharacter(yyleng); return '['; }
"]" { debug_moveCursorToNextCharacter(yyleng); return ']'; }

[_a-zA-Z]+[_a-zA-Z0-9]* {
    char* id_name = (char*)malloc(yyleng+1);
    strcpy(id_name, yytext);

    yylval.id_field = id_name;

    debug_moveCursorToNextCharacter(yyleng);
    return ID;
}

"," { debug_moveCursorToNextCharacter(yyleng); return ','; }
":" { debug_moveCursorToNextCharacter(yyleng); return ':'; }
"(" { debug_moveCursorToNextCharacter(yyleng); return '('; }
")" { debug_moveCursorToNextCharacter(yyleng); return ')'; }
"{" { debug_moveCursorToNextCharacter(yyleng); return '{'; }
"}" { debug_moveCursorToNextCharacter(yyleng); return '}'; }

\n { debug_moveCursorToNextLine(); }

\-\-.* { debug_moveCursorToNextCharacter(yyleng); }
[ \t]+ { debug_moveCursorToNextCharacter(yyleng); }

. {
    printf("[ LEXICAL ERROR :: Unknown token \"%s\" at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    debug_moveCursorToNextCharacter(yyleng);
}

%%
