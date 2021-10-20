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
     DATATYPE_INTEGER_32 = 261,
     LITER_BOOLEAN = 262,
     LITER_INTEGER = 263,
     LITER_CHAR = 264,
     LITER_STRING = 265,
     INHERIT = 266,
     RENAME = 267,
     UNDEFINE = 268,
     REDEFINE = 269,
     SELECT = 270,
     AS = 271,
     CREATE = 272,
     FEATURE = 273,
     LOCAL = 274,
     DO = 275,
     CURRENT = 276,
     RESULT = 277,
     PRECURSOR = 278
   };
#endif
/* Tokens.  */
#define ID 258
#define CLASS 259
#define END 260
#define DATATYPE_INTEGER_32 261
#define LITER_BOOLEAN 262
#define LITER_INTEGER 263
#define LITER_CHAR 264
#define LITER_STRING 265
#define INHERIT 266
#define RENAME 267
#define UNDEFINE 268
#define REDEFINE 269
#define SELECT 270
#define AS 271
#define CREATE 272
#define FEATURE 273
#define LOCAL 274
#define DO 275
#define CURRENT 276
#define RESULT 277
#define PRECURSOR 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "bison.y"
{
    /* Main */
    struct program_strct*           program_field;
    struct class_decl_seq_strct*    class_decl_seq_field;
    struct class_decl_strct*        class_decl_field;

    /* Class */
    struct inheritance_block_strct* inheritance_block_field;
    struct creators_block_strct*    creators_block_field;
    struct features_block_strct*    features_block_field;

    /* Constants */
    short				liter_boolean_field;
    long int 			liter_integer_field;
    char				liter_char_field;
    CharArray* 			liter_string_field;

    char*  				id_field;
}
/* Line 1529 of yacc.c.  */
#line 115 "bison.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

