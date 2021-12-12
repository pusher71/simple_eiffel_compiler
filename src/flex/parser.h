/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     CLASS = 259,
     END = 260,
     IF = 261,
     THEN = 262,
     ELSE = 263,
     FROM = 264,
     UNTIL = 265,
     LOOP = 266,
     DATATYPE_BOOLEAN = 267,
     DATATYPE_CHARACTER = 268,
     DATATYPE_INTEGER = 269,
     DATATYPE_NATURAL = 270,
     DATATYPE_STRING = 271,
     DATATYPE_ARRAY = 272,
     ASSIGNMENT = 273,
     XOR = 274,
     OR = 275,
     AND = 276,
     NOTEQUAL = 277,
     GREAT_EQUAL = 278,
     LESS_EQUAL = 279,
     INTEGER_DIVISION = 280,
     NOT = 281,
     UMINUS = 282,
     LITER_BOOLEAN = 283,
     LITER_INTEGER = 284,
     LITER_CHAR = 285,
     LITER_STRING = 286,
     INHERIT = 287,
     RENAME = 288,
     UNDEFINE = 289,
     REDEFINE = 290,
     SELECT = 291,
     AS = 292,
     CREATE = 293,
     FEATURE = 294,
     LOCAL = 295,
     DO = 296,
     CURRENT = 297,
     RESULT = 298,
     PRECURSOR = 299
   };
#endif
/* Tokens.  */
#define ID 258
#define CLASS 259
#define END 260
#define IF 261
#define THEN 262
#define ELSE 263
#define FROM 264
#define UNTIL 265
#define LOOP 266
#define DATATYPE_BOOLEAN 267
#define DATATYPE_CHARACTER 268
#define DATATYPE_INTEGER 269
#define DATATYPE_NATURAL 270
#define DATATYPE_STRING 271
#define DATATYPE_ARRAY 272
#define ASSIGNMENT 273
#define XOR 274
#define OR 275
#define AND 276
#define NOTEQUAL 277
#define GREAT_EQUAL 278
#define LESS_EQUAL 279
#define INTEGER_DIVISION 280
#define NOT 281
#define UMINUS 282
#define LITER_BOOLEAN 283
#define LITER_INTEGER 284
#define LITER_CHAR 285
#define LITER_STRING 286
#define INHERIT 287
#define RENAME 288
#define UNDEFINE 289
#define REDEFINE 290
#define SELECT 291
#define AS 292
#define CREATE 293
#define FEATURE 294
#define LOCAL 295
#define DO 296
#define CURRENT 297
#define RESULT 298
#define PRECURSOR 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "src/bison/bison.y"
{
    /* Common */
    struct identifiers_comma_seq_strct* identifiers_comma_seq_field;

    /* Main */
    struct program_strct*           program_field;
    struct class_decl_seq_strct*    class_decl_seq_field;
    struct class_decl_strct*        class_decl_field;

    /* Class */
    // Inheritance block
    struct parent_seq_strct*    parent_seq_field;
    struct parent_strct*        parent_field;
    struct rename_seq_strct*    rename_seq_field;

    // Creators block
    struct creators_seq_strct*          creators_seq_field;

    // Features block
    struct features_seq_strct*          features_seq_field;
    struct feature_decl_seq_strct*      feature_decl_seq_field;
    struct feature_decl_strct*          feature_decl_field;

    struct ids_with_type_seq_strct*     ids_with_type_seq_field;
    struct type_strct*                  type_field;

    // ... Instruction
    struct instruction_seq_strct*   instruction_seq_field;
    struct instruction_strct*       instruction_field;

    struct argument_seq_strct*              argument_seq_field;
    struct expr_strct* expr_field;

    /* Constants */
    short       liter_boolean_field;
    long int    liter_integer_field;
    char        liter_char_field;
    CharArray*  liter_string_field;

    char*       id_field;
}
/* Line 1529 of yacc.c.  */
#line 179 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/flex/parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

