/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 3 "bison.y"

    #include <stdio.h>

    #include "tree_nodes.h"
    #include "tree_creators.h"
    #include "../flex/utilities/chararray_utilities.h"

    extern int yylex();
    void yyerror(const char* s) {
        fprintf(stderr, "%s\n", s);
    }

    struct program_strct* tree_root = NULL;
    unsigned int curr_node_index = 0;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "bison.y"
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

    struct call_strct*                      call_field;
    struct argument_seq_strct*              argument_seq_field;

    struct expr_strct* expr_field;

    /* Constants */
    short       liter_boolean_field;
    long int    liter_integer_field;
    char        liter_char_field;
    CharArray*  liter_string_field;

    char*       id_field;
}
/* Line 193 of yacc.c.  */
#line 244 "bison.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 257 "bison.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1165

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  303

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    57,    30,    28,    54,    29,    35,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    55,
      22,    24,    23,     2,    34,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    25,    26,    27,
      31,    32,    33,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    10,    12,    13,    15,    17,
      20,    22,    24,    27,    34,    40,    46,    51,    57,    62,
      67,    71,    75,    79,    90,    99,   108,   115,   124,   131,
     138,   143,   152,   159,   166,   171,   178,   183,   188,   190,
     194,   200,   203,   207,   210,   214,   217,   221,   225,   230,
     236,   243,   250,   258,   267,   274,   282,   291,   300,   310,
     321,   329,   338,   348,   358,   369,   381,   386,   392,   394,
     398,   401,   406,   413,   421,   425,   433,   443,   451,   453,
     455,   459,   461,   463,   465,   467,   471,   473,   475,   479,
     484,   486,   490,   495,   500,   507,   515,   519,   525,   532,
     537,   544,   553,   563,   567,   571,   575,   579,   583,   586,
     590,   594,   598,   602,   606,   610,   614,   618,   622,   625,
     627,   629,   631,   633,   635,   637
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,     3,    -1,    63,    54,     3,    -1,    -1,
      55,    -1,    -1,    66,    -1,    55,    -1,    66,    55,    -1,
      68,    -1,    69,    -1,    68,    69,    -1,     4,     3,    70,
      73,    74,     5,    -1,     4,     3,    70,    73,     5,    -1,
       4,     3,    70,    74,     5,    -1,     4,     3,    70,     5,
      -1,     4,     3,    73,    74,     5,    -1,     4,     3,    73,
       5,    -1,     4,     3,    74,     5,    -1,     4,     3,     5,
      -1,    41,    71,    64,    -1,    70,    71,    64,    -1,     3,
      42,    72,    43,    63,    44,    63,    45,    63,     5,    -1,
       3,    43,    63,    44,    63,    45,    63,     5,    -1,     3,
      42,    72,    44,    63,    45,    63,     5,    -1,     3,    44,
      63,    45,    63,     5,    -1,     3,    42,    72,    43,    63,
      45,    63,     5,    -1,     3,    43,    63,    45,    63,     5,
      -1,     3,    42,    72,    45,    63,     5,    -1,     3,    45,
      63,     5,    -1,     3,    42,    72,    43,    63,    44,    63,
       5,    -1,     3,    43,    63,    44,    63,     5,    -1,     3,
      42,    72,    44,    63,     5,    -1,     3,    44,    63,     5,
      -1,     3,    42,    72,    43,    63,     5,    -1,     3,    43,
      63,     5,    -1,     3,    42,    72,     5,    -1,     3,    -1,
       3,    46,     3,    -1,    72,    54,     3,    46,     3,    -1,
      47,    63,    -1,    73,    47,    63,    -1,    48,    75,    -1,
      74,    48,    75,    -1,    76,    65,    -1,    75,    76,    65,
      -1,    63,    56,    82,    -1,    63,    50,    78,     5,    -1,
      63,    49,    50,    78,     5,    -1,    63,    49,    77,    50,
      78,     5,    -1,    63,    36,    57,    50,    78,     5,    -1,
      63,    36,    57,    49,    50,    78,     5,    -1,    63,    36,
      57,    49,    77,    50,    78,     5,    -1,    63,    56,    82,
      50,    78,     5,    -1,    63,    56,    82,    49,    50,    78,
       5,    -1,    63,    56,    82,    49,    77,    50,    78,     5,
      -1,    63,    36,    57,    56,    82,    50,    78,     5,    -1,
      63,    36,    57,    56,    82,    49,    50,    78,     5,    -1,
      63,    36,    57,    56,    82,    49,    77,    50,    78,     5,
      -1,    63,    36,    77,    57,    50,    78,     5,    -1,    63,
      36,    77,    57,    49,    50,    78,     5,    -1,    63,    36,
      77,    57,    49,    77,    50,    78,     5,    -1,    63,    36,
      77,    57,    56,    82,    50,    78,     5,    -1,    63,    36,
      77,    57,    56,    82,    49,    50,    78,     5,    -1,    63,
      36,    77,    57,    56,    82,    49,    77,    50,    78,     5,
      -1,    63,    56,    82,    64,    -1,    77,    63,    56,    82,
      64,    -1,    65,    -1,    78,    79,    65,    -1,    47,     3,
      -1,    47,     3,    35,     3,    -1,    47,     3,    35,     3,
      36,    57,    -1,    47,     3,    35,     3,    36,    80,    57,
      -1,     3,    18,    81,    -1,     6,    36,    81,    57,     7,
      78,     5,    -1,     6,    36,    81,    57,     7,    78,     8,
      78,     5,    -1,     9,    78,    10,    81,    11,    78,     5,
      -1,    81,    -1,    81,    -1,    80,    54,    81,    -1,    37,
      -1,    38,    -1,    39,    -1,    40,    -1,    36,    81,    57,
      -1,    51,    -1,     3,    -1,     3,    36,    57,    -1,     3,
      36,    80,    57,    -1,    53,    -1,    53,    36,    57,    -1,
      53,    36,    80,    57,    -1,    53,    58,     3,    59,    -1,
      53,    58,     3,    59,    36,    57,    -1,    53,    58,     3,
      59,    36,    80,    57,    -1,    81,    35,     3,    -1,    81,
      35,     3,    36,    57,    -1,    81,    35,     3,    36,    80,
      57,    -1,    47,    58,     3,    59,    -1,    47,    58,     3,
      59,    35,     3,    -1,    47,    58,     3,    59,    35,     3,
      36,    57,    -1,    47,    58,     3,    59,    35,     3,    36,
      80,    57,    -1,    81,    34,    81,    -1,    81,    28,    81,
      -1,    81,    29,    81,    -1,    81,    30,    81,    -1,    81,
      31,    81,    -1,    29,    81,    -1,    81,    22,    81,    -1,
      81,    23,    81,    -1,    81,    27,    81,    -1,    81,    26,
      81,    -1,    81,    24,    81,    -1,    81,    25,    81,    -1,
      81,    21,    81,    -1,    81,    20,    81,    -1,    81,    19,
      81,    -1,    32,    81,    -1,     3,    -1,    12,    -1,    13,
      -1,    14,    -1,    15,    -1,    16,    -1,    17,    60,    82,
      61,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   160,   160,   161,   164,   165,   168,   169,   172,   173,
     177,   180,   181,   185,   186,   187,   188,   190,   191,   192,
     193,   197,   198,   201,   202,   203,   204,   206,   207,   208,
     209,   211,   212,   213,   214,   216,   217,   218,   219,   222,
     223,   227,   228,   232,   233,   236,   237,   240,   242,   243,
     244,   246,   247,   248,   250,   251,   252,   254,   255,   256,
     258,   259,   260,   262,   263,   264,   267,   268,   271,   272,
     275,   276,   277,   278,   280,   282,   283,   284,   286,   289,
     290,   293,   294,   295,   296,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   313,
     314,   315,   316,   318,   319,   320,   321,   322,   323,   325,
     326,   327,   328,   329,   330,   332,   333,   334,   335,   339,
     340,   341,   342,   343,   344,   345
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CLASS", "END", "IF", "THEN",
  "ELSE", "FROM", "UNTIL", "LOOP", "DATATYPE_BOOLEAN",
  "DATATYPE_CHARACTER", "DATATYPE_INTEGER", "DATATYPE_NATURAL",
  "DATATYPE_STRING", "DATATYPE_ARRAY", "ASSIGNMENT", "XOR", "OR", "AND",
  "'<'", "'>'", "'='", "NOTEQUAL", "GREAT_EQUAL", "LESS_EQUAL", "'+'",
  "'-'", "'*'", "INTEGER_DIVISION", "NOT", "UMINUS", "'@'", "'.'", "'('",
  "LITER_BOOLEAN", "LITER_INTEGER", "LITER_CHAR", "LITER_STRING",
  "INHERIT", "RENAME", "UNDEFINE", "REDEFINE", "SELECT", "AS", "CREATE",
  "FEATURE", "LOCAL", "DO", "CURRENT", "RESULT", "PRECURSOR", "','", "';'",
  "':'", "')'", "'{'", "'}'", "'['", "']'", "$accept",
  "identifiers_comma_seq", "opt_semicolon", "opt_semicolon_seq",
  "nonempty_opt_semicolon_seq", "program", "class_decl_seq", "class_decl",
  "parent_seq", "parent", "rename_seq", "creators_seq", "features_seq",
  "feature_decl_seq", "feature_decl", "ids_with_type_seq",
  "instruction_seq", "instruction", "argument_seq", "expr", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    60,    62,    61,   277,   278,   279,    43,    45,
      42,   280,   281,   282,    64,    46,    40,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,    44,    59,    58,    41,   123,   125,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      67,    68,    68,    69,    69,    69,    69,    69,    69,    69,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    82,
      82,    82,    82,    82,    82,    82
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     0,     1,     0,     1,     1,     2,
       1,     1,     2,     6,     5,     5,     4,     5,     4,     4,
       3,     3,     3,    10,     8,     8,     6,     8,     6,     6,
       4,     8,     6,     6,     4,     6,     4,     4,     1,     3,
       5,     2,     3,     2,     3,     2,     3,     3,     4,     5,
       6,     6,     7,     8,     6,     7,     8,     8,     9,    10,
       7,     8,     9,     9,    10,    11,     4,     5,     1,     3,
       2,     4,     6,     7,     3,     7,     9,     7,     1,     1,
       3,     1,     1,     1,     1,     3,     1,     1,     3,     4,
       1,     3,     4,     4,     6,     7,     3,     5,     6,     4,
       6,     8,     9,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    10,    11,     0,     1,    12,    20,     0,
       0,     0,     0,     0,     0,    38,     4,     2,    41,     0,
      43,     6,    16,     4,     0,     0,    18,     0,     0,    19,
       0,     0,     0,     0,     0,     5,    21,     0,     0,     0,
       6,     0,     6,     8,    45,     7,    22,    14,     0,    15,
      42,    17,    44,     0,     0,     0,     0,     0,     3,     0,
       0,     0,     6,     0,    68,     0,   119,   120,   121,   122,
     123,   124,     0,    47,    46,     9,    13,     0,    37,     0,
       0,     0,     0,    36,     0,     0,    34,     0,    30,     0,
       6,     0,     0,     0,     0,     0,     6,    87,    48,     0,
       6,     0,     0,     0,    81,    82,    83,    84,     0,    86,
      90,     6,    78,     0,     0,     6,    39,     0,     0,     0,
       0,     0,     0,     0,     6,     0,     0,     0,     4,     0,
       6,     0,     0,    49,     0,     0,     0,     0,     0,    87,
       0,   108,   118,     0,    70,     0,     0,     0,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     0,     0,    35,     0,
       0,    33,     0,    29,     0,    32,     0,    28,    26,     0,
       6,    51,     0,     6,    66,     6,     0,     0,     0,     4,
      50,    74,    88,     0,    79,     0,     0,    85,     0,     0,
      91,     0,     0,   117,   116,   115,   109,   110,   113,   114,
     112,   111,   104,   105,   106,   107,   103,    96,   125,     0,
       6,    54,     0,     0,     0,    40,     0,    52,     0,     6,
       0,     0,     0,     6,    60,     0,     6,    67,     0,    89,
       0,     0,    71,    99,    92,    93,     0,    55,     0,    31,
       0,    27,    25,    24,    53,     0,     6,    57,    61,     0,
       6,     0,     0,    80,     6,     6,     0,     0,     0,    97,
       0,    56,     0,    58,     0,    62,     0,     6,    63,     0,
       0,    72,     0,   100,    94,     0,    98,    23,    59,    64,
       0,    75,     6,    77,    73,     0,    95,    65,     0,   101,
       0,    76,   102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    60,    36,    64,    45,     2,     3,     4,    12,    16,
      54,    13,    14,    20,    21,    61,    65,   111,   193,   112,
      73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
      17,    12,    32,    17,  -144,   201,  -144,  -144,  -144,    47,
      88,    88,   176,   212,    24,   366,    71,  -144,    93,   287,
      88,   129,  -144,    71,   216,   119,  -144,    88,   224,  -144,
      88,   148,    88,    88,    88,  -144,  -144,   152,     5,     4,
     129,   390,   129,  -144,  -144,   163,  -144,  -144,   225,  -144,
      93,  -144,    88,   169,    13,    54,    39,    11,  -144,   -19,
     -28,     6,   129,    10,  -144,   347,  -144,  -144,  -144,  -144,
    -144,  -144,   185,   158,  -144,  -144,  -144,   250,  -144,    88,
      88,    88,   252,  -144,    88,    88,  -144,    88,  -144,    63,
     129,   390,   390,    86,   -16,   386,   129,   198,  -144,   234,
     129,  1007,  1007,  1007,  -144,  -144,  -144,  -144,     3,  -144,
     -24,   129,  1101,   390,   107,   129,  -144,    99,    96,    14,
     243,   100,    22,    28,   129,   108,   411,   228,    71,   125,
     129,   390,   390,  -144,   450,  1007,    49,  1007,   475,   266,
     221,   258,   258,  1042,   269,   291,    80,   304,  -144,  1007,
    1007,  1007,  1007,  1007,  1007,  1007,  1007,  1007,  1007,  1007,
    1007,  1007,  1007,   305,   248,   129,   127,   514,  -144,    88,
      88,  -144,    88,  -144,   310,  -144,    88,  -144,  -144,   539,
     129,  -144,   160,   129,  -144,   129,   161,   578,   251,    71,
    -144,  1101,  -144,    92,  1101,  1059,  1007,  -144,   312,   265,
    -144,   165,   267,  1116,  1116,  1130,   336,   336,   336,   336,
     336,   336,   314,   314,   258,   258,   299,   281,  -144,   603,
     129,  -144,   116,    36,    38,  -144,    43,  -144,   642,   129,
     162,   667,   706,   129,  -144,   177,   129,  -144,  1007,  -144,
     331,  1084,   306,   311,  -144,   319,   199,  -144,   731,  -144,
      88,  -144,  -144,  -144,  -144,   770,   129,  -144,  -144,   795,
     129,   197,   834,  1101,   129,   129,   229,   337,   259,  -144,
     200,  -144,   117,  -144,   859,  -144,   898,   129,  -144,   322,
     923,  -144,   217,   321,  -144,   227,  -144,  -144,  -144,  -144,
     962,  -144,   129,  -144,  -144,   282,  -144,  -144,   987,  -144,
     233,  -144,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,   -10,   -21,   -17,  -144,  -144,  -144,   344,  -144,   351,
    -144,   356,    23,   342,    -6,   -34,   -51,  -144,  -143,    37,
     112
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      18,    19,    46,   201,    44,    63,   144,    17,    17,    17,
      19,    95,   146,    17,    42,     5,    88,    50,    78,   173,
      19,     1,    55,    56,    57,    74,    37,   177,    92,    29,
      89,    90,     6,   178,   147,    25,    28,    91,    37,   126,
     132,   251,    19,   252,    86,   134,    42,    48,   253,   138,
      15,    94,   139,    94,    62,   125,    79,    80,    81,    83,
      96,   145,    59,    93,   167,    37,    17,    82,    37,   117,
     118,   119,    30,   179,   121,   122,    37,   123,   101,   187,
     166,   102,    37,   139,    87,   103,   104,   105,   106,   107,
      37,    17,    37,    37,   148,   186,   140,    37,    84,    85,
     109,   171,   110,   270,   168,   175,   192,   184,    37,   101,
      17,    17,   102,   124,   219,    94,   103,   104,   105,   106,
     107,   249,   287,   282,    49,   285,    35,   140,    17,   228,
      17,   109,   231,   110,   232,   129,   130,   200,   141,   142,
     143,   172,   131,   169,   170,   176,   238,    37,   230,   239,
      37,    53,   300,    37,    37,    58,    94,   165,   180,   222,
     223,   250,   224,    17,    17,    17,   226,    30,   237,   248,
      37,    37,   191,   194,   195,   185,    94,   220,   255,    15,
      17,    22,   259,   194,    43,   262,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
      17,   261,   139,   127,   128,   274,     8,   114,   115,   276,
     229,   233,   256,   279,   280,    77,   135,    26,    75,   238,
      94,    47,   244,    10,    11,   164,   290,   260,   101,    51,
      76,   102,   139,   241,   136,   103,   104,   105,   106,   107,
     272,   298,     9,   188,   189,   113,   140,   277,    10,    11,
     109,    94,   110,   116,   238,   120,   269,   286,   101,    27,
      11,   102,   139,    27,    11,   103,   104,   105,   106,   107,
     137,   238,    30,    30,   294,   263,   140,   182,   183,   145,
     109,   238,   110,   194,   296,   139,   281,   238,   101,   174,
     302,   102,   162,   163,   199,   103,   104,   105,   106,   107,
     235,   236,   136,   194,   198,   194,   140,   202,   217,   218,
     109,   101,   110,   225,   102,   242,   284,   246,   103,   104,
     105,   106,   107,    38,   243,    97,   245,   291,    99,   140,
     292,   100,   194,   109,   163,   110,    39,    40,   264,   299,
     283,    37,   266,    41,   160,   161,   267,     7,   162,   163,
      97,   101,    98,    99,   102,   268,   100,   295,   103,   104,
     105,   106,   107,    23,   158,   159,   160,   161,    24,   108,
     162,   163,    52,   109,     0,   110,   101,     0,     0,   102,
       0,     0,     0,   103,   104,   105,   106,   107,     0,    97,
       0,   133,    99,    66,   108,   100,     0,     0,   109,     0,
     110,     0,    67,    68,    69,    70,    71,    72,    31,    32,
      33,    34,     0,     0,    97,   101,   181,    99,   102,     0,
     100,     0,   103,   104,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,     0,     0,   109,     0,   110,
     101,     0,     0,   102,     0,     0,     0,   103,   104,   105,
     106,   107,     0,    97,     0,   190,    99,     0,   108,   100,
       0,     0,   109,     0,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,   101,
       0,    99,   102,     0,   100,   196,   103,   104,   105,   106,
     107,     0,     0,     0,     0,     0,     0,   108,     0,     0,
       0,   109,     0,   110,   101,     0,     0,   102,     0,     0,
       0,   103,   104,   105,   106,   107,     0,    97,     0,   221,
      99,     0,   108,   100,     0,     0,   109,     0,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,   101,   227,    99,   102,     0,   100,     0,
     103,   104,   105,   106,   107,     0,     0,     0,     0,     0,
       0,   108,     0,     0,     0,   109,     0,   110,   101,     0,
       0,   102,     0,     0,     0,   103,   104,   105,   106,   107,
       0,    97,     0,   234,    99,     0,   108,   100,     0,     0,
     109,     0,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,   101,   247,    99,
     102,     0,   100,     0,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,   108,     0,     0,     0,   109,
       0,   110,   101,     0,     0,   102,     0,     0,     0,   103,
     104,   105,   106,   107,     0,    97,     0,   254,    99,     0,
     108,   100,     0,     0,   109,     0,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,   101,   257,    99,   102,     0,   100,     0,   103,   104,
     105,   106,   107,     0,     0,     0,     0,     0,     0,   108,
       0,     0,     0,   109,     0,   110,   101,     0,     0,   102,
       0,     0,     0,   103,   104,   105,   106,   107,     0,    97,
       0,   258,    99,     0,   108,   100,     0,     0,   109,     0,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    97,   101,   271,    99,   102,     0,
     100,     0,   103,   104,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,     0,     0,   109,     0,   110,
     101,     0,     0,   102,     0,     0,     0,   103,   104,   105,
     106,   107,     0,    97,     0,   273,    99,     0,   108,   100,
       0,     0,   109,     0,   110,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,   101,
     275,    99,   102,     0,   100,     0,   103,   104,   105,   106,
     107,     0,     0,     0,     0,     0,     0,   108,     0,     0,
       0,   109,     0,   110,   101,     0,     0,   102,     0,     0,
       0,   103,   104,   105,   106,   107,     0,    97,     0,   278,
      99,     0,   108,   100,     0,     0,   109,     0,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,   101,   288,    99,   102,     0,   100,     0,
     103,   104,   105,   106,   107,     0,     0,     0,     0,     0,
       0,   108,     0,     0,     0,   109,     0,   110,   101,     0,
       0,   102,     0,     0,     0,   103,   104,   105,   106,   107,
       0,    97,     0,   289,    99,     0,   108,   100,     0,     0,
     109,     0,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,   101,   293,    99,
     102,     0,   100,     0,   103,   104,   105,   106,   107,     0,
       0,     0,     0,     0,     0,   108,     0,     0,     0,   109,
       0,   110,   101,     0,     0,   102,     0,     0,     0,   103,
     104,   105,   106,   107,     0,    97,     0,   297,    99,     0,
     108,   100,     0,     0,   109,     0,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,   101,   301,    99,   102,     0,   100,     0,   103,   104,
     105,   106,   107,     0,     0,     0,     0,     0,     0,   108,
     139,     0,     0,   109,     0,   110,   101,     0,     0,   102,
       0,     0,     0,   103,   104,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   101,     0,   109,   102,
     110,     0,     0,   103,   104,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   140,     0,     0,     0,   109,     0,
     110,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,     0,     0,   162,   163,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,     0,     0,   162,   163,   265,     0,     0,     0,   197,
       0,     0,     0,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   240,     0,   162,   163,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,     0,     0,   162,   163,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,     0,     0,
     162,   163,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,     0,     0,   162,   163
};

static const yytype_int16 yycheck[] =
{
      10,    11,    23,   146,    21,    39,     3,     3,     3,     3,
      20,    62,    36,     3,    20,     3,     5,    27,     5,     5,
      30,     4,    32,    33,    34,    42,    54,     5,    56,     5,
      49,    50,     0,     5,    58,    12,    13,    56,    54,    90,
      56,     5,    52,     5,     5,    96,    52,    24,     5,   100,
       3,    61,     3,    63,    50,    89,    43,    44,    45,     5,
      50,    58,    57,    57,   115,    54,     3,    54,    54,    79,
      80,    81,    48,   124,    84,    85,    54,    87,    29,   130,
     114,    32,    54,     3,    45,    36,    37,    38,    39,    40,
      54,     3,    54,    54,   111,   129,    47,    54,    44,    45,
      51,     5,    53,   246,     5,     5,    57,   128,    54,    29,
       3,     3,    32,    50,   165,   125,    36,    37,    38,    39,
      40,     5,     5,   266,     5,   268,    55,    47,     3,   180,
       3,    51,   183,    53,   185,    49,    50,    57,   101,   102,
     103,    45,    56,    44,    45,    45,    54,    54,   182,    57,
      54,     3,   295,    54,    54,     3,   166,    50,    50,   169,
     170,    45,   172,     3,     3,     3,   176,    48,   189,   220,
      54,    54,   135,   136,   137,    50,   186,    50,   229,     3,
       3,     5,   233,   146,    55,   236,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
       3,   235,     3,    91,    92,   256,     5,    49,    50,   260,
      50,    50,    50,   264,   265,    46,    18,     5,    55,    54,
     230,     5,    57,    47,    48,   113,   277,    50,    29,     5,
       5,    32,     3,   196,    36,    36,    37,    38,    39,    40,
     250,   292,    41,   131,   132,    60,    47,    50,    47,    48,
      51,   261,    53,     3,    54,     3,    57,    57,    29,    47,
      48,    32,     3,    47,    48,    36,    37,    38,    39,    40,
      36,    54,    48,    48,    57,   238,    47,    49,    50,    58,
      51,    54,    53,   246,    57,     3,    57,    54,    29,    46,
      57,    32,    34,    35,     3,    36,    37,    38,    39,    40,
      49,    50,    36,   266,    35,   268,    47,     3,     3,    61,
      51,    29,    53,     3,    32,     3,    57,    36,    36,    37,
      38,    39,    40,    36,    59,     3,    59,     5,     6,    47,
       8,     9,   295,    51,    35,    53,    49,    50,     7,    57,
       3,    54,    36,    56,    30,    31,    35,     3,    34,    35,
       3,    29,     5,     6,    32,    36,     9,    36,    36,    37,
      38,    39,    40,    12,    28,    29,    30,    31,    12,    47,
      34,    35,    30,    51,    -1,    53,    29,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    -1,     3,
      -1,     5,     6,     3,    47,     9,    -1,    -1,    51,    -1,
      53,    -1,    12,    13,    14,    15,    16,    17,    42,    43,
      44,    45,    -1,    -1,     3,    29,     5,     6,    32,    -1,
       9,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    -1,    53,
      29,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    -1,     3,    -1,     5,     6,    -1,    47,     9,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    29,
      -1,     6,    32,    -1,     9,    10,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    -1,    53,    29,    -1,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    -1,     3,    -1,     5,
       6,    -1,    47,     9,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    29,     5,     6,    32,    -1,     9,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    53,    29,    -1,
      -1,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      -1,     3,    -1,     5,     6,    -1,    47,     9,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    29,     5,     6,
      32,    -1,     9,    -1,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,
      -1,    53,    29,    -1,    -1,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    -1,     3,    -1,     5,     6,    -1,
      47,     9,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    29,     5,     6,    32,    -1,     9,    -1,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    51,    -1,    53,    29,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    -1,     3,
      -1,     5,     6,    -1,    47,     9,    -1,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    29,     5,     6,    32,    -1,
       9,    -1,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    -1,    53,
      29,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    -1,     3,    -1,     5,     6,    -1,    47,     9,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    29,
       5,     6,    32,    -1,     9,    -1,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    51,    -1,    53,    29,    -1,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    -1,     3,    -1,     5,
       6,    -1,    47,     9,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    29,     5,     6,    32,    -1,     9,    -1,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    53,    29,    -1,
      -1,    32,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      -1,     3,    -1,     5,     6,    -1,    47,     9,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    29,     5,     6,
      32,    -1,     9,    -1,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,
      -1,    53,    29,    -1,    -1,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    40,    -1,     3,    -1,     5,     6,    -1,
      47,     9,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    29,     5,     6,    32,    -1,     9,    -1,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,
       3,    -1,    -1,    51,    -1,    53,    29,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    29,    -1,    51,    32,
      53,    -1,    -1,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    51,    -1,
      53,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    11,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    57,    -1,    34,    35,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    67,    68,    69,     3,     0,    69,     5,    41,
      47,    48,    70,    73,    74,     3,    71,     3,    63,    63,
      75,    76,     5,    71,    73,    74,     5,    47,    74,     5,
      48,    42,    43,    44,    45,    55,    64,    54,    36,    49,
      50,    56,    76,    55,    65,    66,    64,     5,    74,     5,
      63,     5,    75,     3,    72,    63,    63,    63,     3,    57,
      63,    77,    50,    77,    65,    78,     3,    12,    13,    14,
      15,    16,    17,    82,    65,    55,     5,    46,     5,    43,
      44,    45,    54,     5,    44,    45,     5,    45,     5,    49,
      50,    56,    56,    57,    63,    78,    50,     3,     5,     6,
       9,    29,    32,    36,    37,    38,    39,    40,    47,    51,
      53,    79,    81,    60,    49,    50,     3,    63,    63,    63,
       3,    63,    63,    63,    50,    77,    78,    82,    82,    49,
      50,    56,    56,     5,    78,    18,    36,    36,    78,     3,
      47,    81,    81,    81,     3,    58,    36,    58,    65,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    34,    35,    82,    50,    77,    78,     5,    44,
      45,     5,    45,     5,    46,     5,    45,     5,     5,    78,
      50,     5,    49,    50,    64,    50,    77,    78,    82,    82,
       5,    81,    57,    80,    81,    81,    10,    57,    35,     3,
      57,    80,     3,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,     3,    61,    78,
      50,     5,    63,    63,    63,     3,    63,     5,    78,    50,
      77,    78,    78,    50,     5,    49,    50,    64,    54,    57,
      57,    81,     3,    59,    57,    59,    36,     5,    78,     5,
      45,     5,     5,     5,     5,    78,    50,     5,     5,    78,
      50,    77,    78,    81,     7,    11,    36,    35,    36,    57,
      80,     5,    63,     5,    78,     5,    78,    50,     5,    78,
      78,    57,    80,     3,    57,    80,    57,     5,     5,     5,
      78,     5,     8,     5,    57,    36,    57,     5,    78,    57,
      80,     5,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 160 "bison.y"
    { (yyval.identifiers_comma_seq_field) = create_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (1)].id_field)); ;}
    break;

  case 3:
#line 161 "bison.y"
    { (yyval.identifiers_comma_seq_field) = append_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 10:
#line 177 "bison.y"
    { (yyval.program_field) = create_program(curr_node_index++, (yyvsp[(1) - (1)].class_decl_seq_field)); tree_root = (yyval.program_field); ;}
    break;

  case 11:
#line 180 "bison.y"
    { (yyval.class_decl_seq_field) = create_class_decl_seq(curr_node_index++, (yyvsp[(1) - (1)].class_decl_field)); ;}
    break;

  case 12:
#line 181 "bison.y"
    { (yyval.class_decl_seq_field) = append_class_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].class_decl_seq_field), (yyvsp[(2) - (2)].class_decl_field)); ;}
    break;

  case 13:
#line 185 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(3) - (6)].parent_seq_field), (yyvsp[(4) - (6)].creators_seq_field), (yyvsp[(5) - (6)].features_seq_field)); ;}
    break;

  case 14:
#line 186 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), (yyvsp[(3) - (5)].parent_seq_field), (yyvsp[(4) - (5)].creators_seq_field), NULL); ;}
    break;

  case 15:
#line 187 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), (yyvsp[(3) - (5)].parent_seq_field), NULL, (yyvsp[(4) - (5)].features_seq_field)); ;}
    break;

  case 16:
#line 188 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), (yyvsp[(3) - (4)].parent_seq_field), NULL, NULL); ;}
    break;

  case 17:
#line 190 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), NULL, (yyvsp[(3) - (5)].creators_seq_field), (yyvsp[(4) - (5)].features_seq_field)); ;}
    break;

  case 18:
#line 191 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), NULL, (yyvsp[(3) - (4)].creators_seq_field), NULL); ;}
    break;

  case 19:
#line 192 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), NULL, NULL, (yyvsp[(3) - (4)].features_seq_field)); ;}
    break;

  case 20:
#line 193 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (3)].id_field), NULL, NULL, NULL); ;}
    break;

  case 21:
#line 197 "bison.y"
    { (yyval.parent_seq_field) = create_parent_seq(curr_node_index++, (yyvsp[(2) - (3)].parent_field)); ;}
    break;

  case 22:
#line 198 "bison.y"
    { (yyval.parent_seq_field) = append_parent_seq(curr_node_index++, (yyvsp[(1) - (3)].parent_seq_field), (yyvsp[(2) - (3)].parent_field)); ;}
    break;

  case 23:
#line 201 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (10)].id_field), (yyvsp[(3) - (10)].rename_seq_field), (yyvsp[(5) - (10)].identifiers_comma_seq_field), (yyvsp[(7) - (10)].identifiers_comma_seq_field), (yyvsp[(9) - (10)].identifiers_comma_seq_field)); ;}
    break;

  case 24:
#line 202 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), NULL, (yyvsp[(3) - (8)].identifiers_comma_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 25:
#line 203 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), NULL, (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 26:
#line 204 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 27:
#line 206 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), NULL, (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 28:
#line 207 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 29:
#line 208 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), NULL, NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 30:
#line 209 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, NULL, NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field)); ;}
    break;

  case 31:
#line 211 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 32:
#line 212 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 33:
#line 213 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 34:
#line 214 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 35:
#line 216 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL, NULL); ;}
    break;

  case 36:
#line 217 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field), NULL, NULL); ;}
    break;

  case 37:
#line 218 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), (yyvsp[(3) - (4)].rename_seq_field), NULL, NULL, NULL); ;}
    break;

  case 38:
#line 219 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (1)].id_field), NULL, NULL, NULL, NULL); ;}
    break;

  case 39:
#line 222 "bison.y"
    { (yyval.rename_seq_field) = create_rename_seq(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 40:
#line 223 "bison.y"
    { (yyval.rename_seq_field) = append_rename_seq(curr_node_index++, (yyvsp[(1) - (5)].rename_seq_field), (yyvsp[(3) - (5)].id_field), (yyvsp[(5) - (5)].id_field)); ;}
    break;

  case 41:
#line 227 "bison.y"
    { (yyval.creators_seq_field) = create_creators_seq(curr_node_index++, (yyvsp[(2) - (2)].identifiers_comma_seq_field)); ;}
    break;

  case 42:
#line 228 "bison.y"
    { (yyval.creators_seq_field) = append_creators_seq(curr_node_index++, (yyvsp[(1) - (3)].creators_seq_field), (yyvsp[(3) - (3)].identifiers_comma_seq_field)); ;}
    break;

  case 43:
#line 232 "bison.y"
    { (yyval.features_seq_field) = create_features_seq(curr_node_index++, (yyvsp[(2) - (2)].feature_decl_seq_field)); ;}
    break;

  case 44:
#line 233 "bison.y"
    { (yyval.features_seq_field) = append_features_seq(curr_node_index++, (yyvsp[(1) - (3)].features_seq_field), (yyvsp[(3) - (3)].feature_decl_seq_field)); ;}
    break;

  case 45:
#line 236 "bison.y"
    { (yyval.feature_decl_seq_field) = create_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].feature_decl_field)); ;}
    break;

  case 46:
#line 237 "bison.y"
    { (yyval.feature_decl_seq_field) = append_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (3)].feature_decl_seq_field), (yyvsp[(2) - (3)].feature_decl_field)); ;}
    break;

  case 47:
#line 240 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].type_field), NULL, NULL, NULL); ;}
    break;

  case 48:
#line 242 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(3) - (4)].instruction_seq_field)); ;}
    break;

  case 49:
#line 243 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (5)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(4) - (5)].instruction_seq_field)); ;}
    break;

  case 50:
#line 244 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(3) - (6)].ids_with_type_seq_field), (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 51:
#line 246 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 52:
#line 247 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 53:
#line 248 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(5) - (8)].ids_with_type_seq_field), (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 54:
#line 250 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), (yyvsp[(3) - (6)].type_field), NULL, NULL, (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 55:
#line 251 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), (yyvsp[(3) - (7)].type_field), NULL, NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 56:
#line 252 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), (yyvsp[(3) - (8)].type_field), NULL, (yyvsp[(5) - (8)].ids_with_type_seq_field), (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 57:
#line 254 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), (yyvsp[(5) - (8)].type_field), NULL, NULL, (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 58:
#line 255 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), (yyvsp[(5) - (9)].type_field), NULL, NULL, (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 59:
#line 256 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (10)].identifiers_comma_seq_field), (yyvsp[(5) - (10)].type_field), NULL, (yyvsp[(7) - (10)].ids_with_type_seq_field), (yyvsp[(9) - (10)].instruction_seq_field)); ;}
    break;

  case 60:
#line 258 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (7)].ids_with_type_seq_field), NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 61:
#line 259 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (8)].ids_with_type_seq_field), NULL, (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 62:
#line 260 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (9)].ids_with_type_seq_field), (yyvsp[(6) - (9)].ids_with_type_seq_field), (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 63:
#line 262 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), (yyvsp[(6) - (9)].type_field), (yyvsp[(3) - (9)].ids_with_type_seq_field), NULL, (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 64:
#line 263 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (10)].identifiers_comma_seq_field), (yyvsp[(6) - (10)].type_field), (yyvsp[(3) - (10)].ids_with_type_seq_field), NULL, (yyvsp[(9) - (10)].instruction_seq_field)); ;}
    break;

  case 65:
#line 264 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (11)].identifiers_comma_seq_field), (yyvsp[(6) - (11)].type_field), (yyvsp[(3) - (11)].ids_with_type_seq_field), (yyvsp[(8) - (11)].ids_with_type_seq_field), (yyvsp[(10) - (11)].instruction_seq_field)); ;}
    break;

  case 66:
#line 267 "bison.y"
    { (yyval.ids_with_type_seq_field) = create_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), (yyvsp[(3) - (4)].type_field)); ;}
    break;

  case 67:
#line 268 "bison.y"
    { (yyval.ids_with_type_seq_field) = append_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (5)].ids_with_type_seq_field), (yyvsp[(2) - (5)].identifiers_comma_seq_field), (yyvsp[(4) - (5)].type_field)); ;}
    break;

  case 68:
#line 271 "bison.y"
    { (yyval.instruction_seq_field) = create_instruction_seq(curr_node_index++, NULL); ;}
    break;

  case 69:
#line 272 "bison.y"
    { (yyval.instruction_seq_field) = append_instruction_seq(curr_node_index++, (yyvsp[(1) - (3)].instruction_seq_field), (yyvsp[(2) - (3)].instruction_field)); ;}
    break;

  case 70:
#line 275 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (2)].id_field), NULL, NULL); ;}
    break;

  case 71:
#line 276 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (4)].id_field), (yyvsp[(4) - (4)].id_field), NULL); ;}
    break;

  case 72:
#line 277 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(4) - (6)].id_field), NULL); ;}
    break;

  case 73:
#line 278 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (7)].id_field), (yyvsp[(4) - (7)].id_field), (yyvsp[(6) - (7)].argument_seq_field)); ;}
    break;

  case 74:
#line 280 "bison.y"
    { (yyval.instruction_field) = create_assign_instruction(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 75:
#line 282 "bison.y"
    { (yyval.instruction_field) = create_if_instruction(curr_node_index++, (yyvsp[(3) - (7)].expr_field), (yyvsp[(6) - (7)].instruction_seq_field), NULL); ;}
    break;

  case 76:
#line 283 "bison.y"
    { (yyval.instruction_field) = create_if_instruction(curr_node_index++, (yyvsp[(3) - (9)].expr_field), (yyvsp[(6) - (9)].instruction_seq_field), (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 77:
#line 284 "bison.y"
    { (yyval.instruction_field) = create_loop_instruction(curr_node_index++, (yyvsp[(2) - (7)].instruction_seq_field), (yyvsp[(4) - (7)].expr_field), (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 78:
#line 286 "bison.y"
    { (yyval.instruction_field) = create_instruction_as_expr(curr_node_index++, (yyvsp[(1) - (1)].expr_field)); ;}
    break;

  case 79:
#line 289 "bison.y"
    { (yyval.argument_seq_field) = create_argument_seq(curr_node_index++, (yyvsp[(1) - (1)].expr_field)); ;}
    break;

  case 80:
#line 290 "bison.y"
    { (yyval.argument_seq_field) = append_argument_seq(curr_node_index++, (yyvsp[(1) - (3)].argument_seq_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 81:
#line 293 "bison.y"
    { (yyval.expr_field) = create_expr_liter_bool(curr_node_index++, (yyvsp[(1) - (1)].liter_boolean_field)); ;}
    break;

  case 82:
#line 294 "bison.y"
    { (yyval.expr_field) = create_expr_liter_int (curr_node_index++, (yyvsp[(1) - (1)].liter_integer_field)); ;}
    break;

  case 83:
#line 295 "bison.y"
    { (yyval.expr_field) = create_expr_liter_char(curr_node_index++, (yyvsp[(1) - (1)].liter_char_field)); ;}
    break;

  case 84:
#line 296 "bison.y"
    { (yyval.expr_field) = create_expr_liter_str (curr_node_index++, (yyvsp[(1) - (1)].liter_string_field)); ;}
    break;

  case 85:
#line 298 "bison.y"
    { (yyval.expr_field) = (yyvsp[(2) - (3)].expr_field); ;}
    break;

  case 86:
#line 299 "bison.y"
    { (yyval.expr_field) = create_expr_current(curr_node_index++, NULL); ;}
    break;

  case 87:
#line 300 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, (yyvsp[(1) - (1)].id_field)); ;}
    break;

  case 88:
#line 301 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_method, (yyvsp[(1) - (3)].id_field), NULL, NULL); ;}
    break;

  case 89:
#line 302 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_method, (yyvsp[(1) - (4)].id_field), (yyvsp[(3) - (4)].argument_seq_field), NULL); ;}
    break;

  case 90:
#line 303 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_precursor, NULL, NULL, NULL); ;}
    break;

  case 91:
#line 304 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_precursor, NULL, NULL, NULL); ;}
    break;

  case 92:
#line 305 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_precursor, NULL, (yyvsp[(3) - (4)].argument_seq_field), NULL); ;}
    break;

  case 93:
#line 306 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_precursor, (yyvsp[(3) - (4)].id_field), NULL, NULL); ;}
    break;

  case 94:
#line 307 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_precursor, (yyvsp[(3) - (6)].id_field), NULL, NULL); ;}
    break;

  case 95:
#line 308 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, call_precursor, (yyvsp[(3) - (7)].id_field), (yyvsp[(6) - (7)].argument_seq_field), NULL); ;}
    break;

  case 96:
#line 309 "bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].id_field), NULL); ;}
    break;

  case 97:
#line 310 "bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (5)].expr_field), (yyvsp[(3) - (5)].id_field), NULL); ;}
    break;

  case 98:
#line 311 "bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (6)].expr_field), (yyvsp[(3) - (6)].id_field), (yyvsp[(5) - (6)].argument_seq_field)); ;}
    break;

  case 99:
#line 313 "bison.y"
    { (yyval.expr_field) = NULL; ;}
    break;

  case 100:
#line 314 "bison.y"
    { (yyval.expr_field) = NULL; ;}
    break;

  case 101:
#line 315 "bison.y"
    { (yyval.expr_field) = NULL; ;}
    break;

  case 102:
#line 316 "bison.y"
    { (yyval.expr_field) = NULL; ;}
    break;

  case 103:
#line 318 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_arrelem, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 104:
#line 319 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_plus, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 105:
#line 320 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_bminus, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 106:
#line 321 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_mul, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 107:
#line 322 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_idiv, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 108:
#line 323 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_uminus, NULL, (yyvsp[(2) - (2)].expr_field)); ;}
    break;

  case 109:
#line 325 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_less, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 110:
#line 326 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_great, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 111:
#line 327 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_less_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 112:
#line 328 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_great_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 113:
#line 329 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 114:
#line 330 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_notequal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 115:
#line 332 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_and, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 116:
#line 333 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_or, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 117:
#line 334 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_xor, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 118:
#line 335 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_not, NULL, (yyvsp[(2) - (2)].expr_field)); ;}
    break;

  case 119:
#line 339 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_user_defined, (yyvsp[(1) - (1)].id_field), NULL); ;}
    break;

  case 120:
#line 340 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_boolean, NULL, NULL); ;}
    break;

  case 121:
#line 341 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_character, NULL, NULL); ;}
    break;

  case 122:
#line 342 "bison.y"
    { (yyval.type_field) = NULL; ;}
    break;

  case 123:
#line 343 "bison.y"
    { (yyval.type_field) = NULL; ;}
    break;

  case 124:
#line 344 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_string, NULL, NULL); ;}
    break;

  case 125:
#line 345 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_array, NULL, (yyvsp[(3) - (4)].type_field)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2487 "bison.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 348 "bison.y"


