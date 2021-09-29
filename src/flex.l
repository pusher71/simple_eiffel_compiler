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

    #include "utilities/char_utilities.h"
    #include "utilities/string_utilities.h"

    enum LexerErrorCode {
        NO_ERROR,
        GENERAL_ERROR,

        INVALID_CHAR_CODE
    };

    unsigned int debug_cursorLineIndex 		= 0;
    unsigned int debug_cursorColumnIndex 	= 0;

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

    int oldCursorLineIndex 		= 0;
    int oldCursorColumnIndex 	= 0;

    // Read buffers
    char read_string[1024];

    // Constraints
    unsigned int minCharCode = 0;
    unsigned int maxCharCode = 127;
%}

true   { printf("<BOOLEAN: %d>\n", 1); debug_moveCursorToNextCharacter(yyleng); }
false  { printf("<BOOLEAN: %d>\n", 0); debug_moveCursorToNextCharacter(yyleng); }

{DEC_INT_PTTRN} { printf("<DECIMAL INTEGER LITERAL: value = %ld; matched string = \"%s\">\n", getDecIntFromStringWithDecInt_eiffel(yytext), yytext); debug_moveCursorToNextCharacter(yyleng); }
{BIN_INT_PTTRN} { printf("<BINARY INTEGER LITERAL: value = %ld; matched string = \"%s\">\n", getDecIntFromStringWithBinInt_eiffel(yytext), yytext); debug_moveCursorToNextCharacter(yyleng); }
{OCT_INT_PTTRN} { printf("<OCTAL INTEGER LITERAL: value = %ld; matched string = \"%s\">\n", getDecIntFromStringWithOctInt_eiffel(yytext), yytext); debug_moveCursorToNextCharacter(yyleng); }
{HEX_INT_PTTRN} { printf("<HEXADECIMAL INTEGER LITERAL: value = %ld; matched string = \"%s\">\n", getDecIntFromStringWithHexInt_eiffel(yytext), yytext); debug_moveCursorToNextCharacter(yyleng); }

{INVALID_VALUE_TOKEN} { printf("[ LEXICAL ERROR :: Invalid value token \"%s\" in line: %d ]\n", yytext, debug_cursorLineIndex+1); debug_moveCursorToNextCharacter(yyleng); }

\' {
    read_string[0] = 0;
    BEGIN(CHAR);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextCharacter(yyleng);
}

\" {
    read_string[0] = 0;
    BEGIN(STRING);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextCharacter(yyleng);
}

\"\{[ \t]*\n {
    read_string[0] = 0;
    BEGIN(VERBATIM_STRING);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextLine();
}

\"\[[ \t]*\n {
    read_string[0] = 0;
    BEGIN(STRIPSOFF_STRING);

    error_cursorLineIndex = debug_cursorLineIndex;
    error_cursorColumnIndex = debug_cursorColumnIndex;
    debug_moveCursorToNextLine();
}

<VERBATIM_STRING,STRIPSOFF_STRING,STRING,CHAR>[^\'\"\%\n']+     {
                                                                    strcat(read_string, yytext);
                                                                    debug_moveCursorToNextCharacter(yyleng);
                                                                }

<VERBATIM_STRING,STRIPSOFF_STRING>[\"\'\%\n]+                   {
                                                                    strcat(read_string, yytext);

                                                                    for (int i=0; i<strlen(yytext); i++) {
                                                                        if (yytext[i] == '\n') 	{ debug_moveCursorToNextLine(); }
                                                                        else 					{ debug_moveCursorToNextCharacter(1); }
                                                                    }
                                                                }

<STRING>\'+                                                     { strcat(read_string, yytext); debug_moveCursorToNextCharacter(yyleng); }
<CHAR>\"+                                                       { strcat(read_string, yytext); debug_moveCursorToNextCharacter(yyleng); }

<STRING,CHAR>\%A {
    if (isupper(yytext[1])) {
        strcat(read_string, "@");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%B {
    if (isupper(yytext[1])) {
        strcat(read_string, "\10");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%C {
    if (isupper(yytext[1])) {
        strcat(read_string, "^");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%D {
    if (isupper(yytext[1])) {
        strcat(read_string, "$");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%F {
    if (isupper(yytext[1])) {
        strcat(read_string, "\14");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%H {
    if (isupper(yytext[1])) {
        strcat(read_string, "\\");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%L {
    if (isupper(yytext[1])) {
        strcat(read_string, "~");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%N {
    if (isupper(yytext[1])) {
        strcat(read_string, "\n");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%Q {
    if (isupper(yytext[1])) {
        strcat(read_string, "`");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%R {
    if (isupper(yytext[1])) {
        strcat(read_string, "\15");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%S {
    if (isupper(yytext[1])) {
        strcat(read_string, "#");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%T {
    if (isupper(yytext[1])) {
        strcat(read_string, "\t");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%U {
    if (isupper(yytext[1])) {
        strcat(read_string, "\0");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%V {
    if (isupper(yytext[1])) {
        strcat(read_string, "|");
    }
    else {
        printf("[ LEXICAL ERROR :: Unknown escape sequence \'%s\' at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
        lexerErrorCode = GENERAL_ERROR;
    }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%% { strcat(read_string, "%"); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\' { strcat(read_string, "\'"); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\" { strcat(read_string, "\""); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\( { strcat(read_string, "["); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\) { strcat(read_string, "]"); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\< { strcat(read_string, "{"); debug_moveCursorToNextCharacter(yyleng); }
<STRING,CHAR>\%\> { strcat(read_string, "}"); debug_moveCursorToNextCharacter(yyleng); }

<STRING,CHAR>\%\/{DEC_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithDecInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)   	{ appendCharToStr(read_string, read_string, charCode); }
    else                                    					{ lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%\/{BIN_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithBinInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)   	{ appendCharToStr(read_string, read_string, charCode); }
    else                                    					{ lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%\/{OCT_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithOctInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)   	{ appendCharToStr(read_string, read_string, charCode); }
    else                                    					{ lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING,CHAR>\%\/{HEX_INT_PTTRN}\/ {
    char buffer[1024];
    strcpy(buffer, yytext+2);
    buffer[strlen(buffer)-1] = 0;

    short charCode = getDecIntFromStringWithHexInt_eiffel(buffer);

    if (charCode >= minCharCode && charCode <= maxCharCode)   	{ appendCharToStr(read_string, read_string, charCode); }
    else                                    					{ lexerErrorValue = charCode; lexerErrorCode = INVALID_CHAR_CODE; }

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
    debug_moveCursorToNextLine();
}

<CHAR><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching \' bracket for bracket at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    lexerErrorCode = NO_ERROR;

    BEGIN(INITIAL);
}

<CHAR>\' {
    if (lexerErrorCode == NO_ERROR) {
        if (strlen(read_string) == 1) {
            printf("<CHAR LITERAL: value = \'%c\'; char code = %d>\n", read_string[0], (int)read_string[0]);
        }
        else if (strlen(read_string) > 1) {
            printf("[ LEXICAL ERROR :: More than one character are placed in single brackets \'%s\' at (line: %d, column = %d) ]\n", read_string, error_cursorLineIndex+1, error_cursorColumnIndex+1);
        }
        else if (strlen(read_string) == 0) {
            printf("[ LEXICAL ERROR :: Empty character \'\' at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
        }
    }
    else {
        if (lexerErrorCode == INVALID_CHAR_CODE) {
            printf("[ LEXICAL ERROR :: Invalid character code (%d) at (line: %d, column = %d) ]\n", lexerErrorValue, error_cursorLineIndex+1, error_cursorColumnIndex+1);
        }

        lexerErrorCode = NO_ERROR;
    }

    BEGIN(INITIAL);

    debug_moveCursorToNextCharacter(yyleng);
}

<STRING>%[ \t\n]+% {
    for (int i=0; i<strlen(yytext); i++) {
        if (yytext[i] == '\n') 	{ debug_moveCursorToNextLine(); }
        else 					{ debug_moveCursorToNextCharacter(1); }
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

    debug_moveCursorToNextLine();
}

<STRING><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching \" bracket at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    BEGIN(INITIAL);
}

<STRING>\" {
    if (lexerErrorCode == NO_ERROR) {
        printf("<STRING LITERAL: value = \"%s\">\n", read_string);
    }
    else {
        lexerErrorCode = NO_ERROR;
    }

    BEGIN(INITIAL);

    debug_moveCursorToNextCharacter(yyleng);
}

<VERBATIM_STRING>^[ \t]*\}\" {
    int readString_length = strlen(read_string);
    if (read_string[readString_length-1] == '\n') {
        read_string[readString_length-1] = 0;
    }

    printf("<STRING LITERAL: value = \"%s\">\n", read_string);
    BEGIN(INITIAL);

    debug_moveCursorToNextCharacter(yyleng-1);
}

<VERBATIM_STRING>^[ \t]*[^ \t\n]+[ \t]*\}\" {
    printf("[ LEXICAL ERROR :: No matching <}\"> bracket for verbatim string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    BEGIN(INITIAL);

    for (int i=0; i<strlen(yytext); i++) {
        if (yytext[i] == '\n') 	{ debug_moveCursorToNextLine(); }
        else 					{ debug_moveCursorToNextCharacter(1); }
    }
}

<VERBATIM_STRING><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching <}\"> bracket for verbatim string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    BEGIN(INITIAL);
}

\}\" {
    printf("[ LEXICAL ERROR :: Invalid closing bracket <}\"> for verbatim string at (line: %d, column = %d) ]\n", debug_cursorLineIndex+1, debug_cursorColumnIndex+1);

    debug_moveCursorToNextCharacter(yyleng);
}

<STRIPSOFF_STRING>^[ \t]*\]\" {
    char buffer_word[1024];

    int readString_length = strlen(read_string);
    if (read_string[readString_length-1] == '\n') {
        read_string[readString_length-1] = 0;
    }

    // Define number of first space characters to delete in strings in each line
    int spaceChrsCountToDelete = (read_string[strlen(read_string)-1] != '\n' ? INT_MAX : 0);
    int curr_spaceChrsCountToDelete = 0;

    int currShift = 0;
    do {
        currShift += getFirstWordFromStr(read_string + currShift, buffer_word, "\n");

        curr_spaceChrsCountToDelete = 0;
        for (int i=0; i<strlen(buffer_word) && buffer_word[i] == ' '; i++) {
            curr_spaceChrsCountToDelete++;
        }

        if (buffer_word[0] == '\0') {
            printf("GOT HERE\n");
            curr_spaceChrsCountToDelete = -1;
            spaceChrsCountToDelete = 0;
        }
        else if (spaceChrsCountToDelete > curr_spaceChrsCountToDelete) {
            spaceChrsCountToDelete = curr_spaceChrsCountToDelete;
        }

    } while(read_string[currShift] != '\0' && curr_spaceChrsCountToDelete != -1);

    // Delete defined first space characters in strings in each line
    char buffer_result[1024] = "\0";

    currShift = 0;
    do {
        currShift += getFirstWordFromStr(read_string + currShift, buffer_word, "\n");
        strcat(buffer_result, buffer_word + spaceChrsCountToDelete);
    } while(read_string[currShift] != '\0');

    printf("<STRING LITERAL: value = \"%s\">\n", buffer_result);
    BEGIN(INITIAL);

    debug_moveCursorToNextCharacter(yyleng-1);
}

<STRIPSOFF_STRING>^[ \t]*[^ \t\n]+[ \t]*\]\" {
    printf("[ LEXICAL ERROR :: No matching <]\"> bracket for strips-off string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    BEGIN(INITIAL);

    for (int i=0; i<strlen(yytext); i++) {
        if (yytext[i] == '\n') 	{ debug_moveCursorToNextLine(); }
        else 					{ debug_moveCursorToNextCharacter(1); }
    }
}

<STRIPSOFF_STRING><<EOF>> {
    printf("[ LEXICAL ERROR :: No matching <]\"> bracket for strips-off string at (line: %d, column = %d) ]\n", error_cursorLineIndex+1, error_cursorColumnIndex+1);
    BEGIN(INITIAL);
}

\]\" {
    printf("[ LEXICAL ERROR :: Invalid closing bracket <]\"> for strips-off string at (line: %d, column = %d) ]\n", debug_cursorLineIndex+1, debug_cursorColumnIndex+1);

    debug_moveCursorToNextCharacter(yyleng);
}

if              { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
then            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
else            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
elseif	        { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
inspect         { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
when		    { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
loop            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
from            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
until		    { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }

alias			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
attribute	    { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
class			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
create			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
deferred		{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
do				{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
end		    	{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
ensure			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
expanded		{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
export			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
feature	    	{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
inherit		    { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
invariant		{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
local			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
note			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
require	    	{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
result			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
retry			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
variant	    	{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
void			{ printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }

detachable          { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
separate            { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
comparable          { printf("<KEYWORD: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }

boolean             { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
character           { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
integer_8           { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
integer_16          { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
integer_32          { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
integer_64          { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
natural_8           { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
natural_16          { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
natural_32          { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
natural_64          { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }
string              { printf("<DATA TYPE: %s>\n", yytext); debug_moveCursorToNextCharacter(yyleng); }

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

"." { printf("<OPERATOR: DOT>\n"); debug_moveCursorToNextCharacter(yyleng); }
";" { printf("<OPERATOR: SEMICOLON>\n"); debug_moveCursorToNextCharacter(yyleng); }
"[" { printf("<OPERATOR: LEFT SQUARE BRACKET>\n"); debug_moveCursorToNextCharacter(yyleng); }
"]" { printf("<OPERATOR: RIGHT SQUARE BRACKET>\n"); debug_moveCursorToNextCharacter(yyleng); }

[_a-zA-Z]+\w* { printf("<IDENTIFIER: \"%s\">\n", yytext); debug_moveCursorToNextCharacter(yyleng); }

"," { printf("<SYNTAX SIGN: COMMA>\n"); debug_moveCursorToNextCharacter(yyleng); }
":" { printf("<SYNTAX SIGN: COLON>\n"); }
"(" { printf("<SYNTAX SIGN: LEFT ROUND BRACKET>\n"); debug_moveCursorToNextCharacter(yyleng); }
")" { printf("<SYNTAX SIGN: RIGHT ROUND BRACKET>\n"); debug_moveCursorToNextCharacter(yyleng); }
"{" { printf("<SYNTAX SIGN: LEFT CURLY BRACKET>\n"); debug_moveCursorToNextCharacter(yyleng); }
"}" { printf("<SYNTAX SIGN: RIGHT CURLY BRACKET>\n"); debug_moveCursorToNextCharacter(yyleng); }

\n { debug_moveCursorToNextLine(); }

\-\-.* { debug_moveCursorToNextCharacter(yyleng); }
[ \t]+ { debug_moveCursorToNextCharacter(yyleng); }

. {
    printf("[ LEXICAL ERROR :: Unknown token \"%s\" at (line: %d, column = %d) ]\n", yytext, debug_cursorLineIndex+1, debug_cursorColumnIndex+1);
    debug_moveCursorToNextCharacter(yyleng);
}

%%
