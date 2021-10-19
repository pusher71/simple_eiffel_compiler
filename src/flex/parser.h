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
     DATATYPE_BOOLEAN = 261,
     DATATYPE_CHARACTER = 262,
     DATATYPE_INTEGER_8 = 263,
     DATATYPE_INTEGER_16 = 264,
     DATATYPE_INTEGER_32 = 265,
     DATATYPE_INTEGER_64 = 266,
     DATATYPE_NATURAL_8 = 267,
     DATATYPE_NATURAL_16 = 268,
     DATATYPE_NATURAL_32 = 269,
     DATATYPE_NATURAL_64 = 270,
     DATATYPE_STRING = 271,
     LITER_BOOLEAN = 272,
     LITER_INTEGER = 273,
     LITER_CHAR = 274,
     LITER_STRING = 275,
     INHERIT = 276,
     RENAME = 277,
     UNDEFINE = 278,
     REDEFINE = 279,
     SELECT = 280,
     AS = 281,
     CREATE = 282,
     FEATURE = 283,
     LOCAL = 284,
     DO = 285,
     CURRENT = 286,
     RESULT = 287,
     PRECURSOR = 288
   };
#endif
/* Tokens.  */
#define ID 258
#define CLASS 259
#define END 260
#define DATATYPE_BOOLEAN 261
#define DATATYPE_CHARACTER 262
#define DATATYPE_INTEGER_8 263
#define DATATYPE_INTEGER_16 264
#define DATATYPE_INTEGER_32 265
#define DATATYPE_INTEGER_64 266
#define DATATYPE_NATURAL_8 267
#define DATATYPE_NATURAL_16 268
#define DATATYPE_NATURAL_32 269
#define DATATYPE_NATURAL_64 270
#define DATATYPE_STRING 271
#define LITER_BOOLEAN 272
#define LITER_INTEGER 273
#define LITER_CHAR 274
#define LITER_STRING 275
#define INHERIT 276
#define RENAME 277
#define UNDEFINE 278
#define REDEFINE 279
#define SELECT 280
#define AS 281
#define CREATE 282
#define FEATURE 283
#define LOCAL 284
#define DO 285
#define CURRENT 286
#define RESULT 287
#define PRECURSOR 288




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
    struct inheritance_block_strct* inheritance_block_field;

    struct parent_seq_strct*    parent_seq_field;
    struct parent_strct*        parent_field;
    struct parent_info_strct*   parent_info_field;
    struct rename_seq_strct*    rename_seq_field;

    // Creators block
    struct creators_block_strct*            creators_block_field;
    struct nonempty_creators_block_strct*   nonempty_creators_block_field;

    // Features block
    struct features_block_strct*                features_block_field;
    struct nonempty_features_block_strct*       nonempty_features_block_field;

    struct feature_decl_seq_strct*              feature_decl_seq_field;
    struct nonempty_feature_decl_seq_strct*     nonempty_feature_decl_seq_field;
    struct feature_decl_strct*                  feature_decl_field;

    struct ids_with_type_seq_strct*             ids_with_type_seq_field;
    struct nonempty_ids_with_type_seq_strct*    nonempty_ids_with_type_seq_field;
    struct ids_with_type_strct*                 ids_with_type_field;
    struct type_strct* type_field;

    struct routine_decl_body_strct* routine_decl_body_field;

    /* Constants */
    short				liter_boolean_field;
    long int 			liter_integer_field;
    char				liter_char_field;
    CharArray* 			liter_string_field;

    char*  				id_field;
}
/* Line 1529 of yacc.c.  */
#line 161 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/flex/parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

