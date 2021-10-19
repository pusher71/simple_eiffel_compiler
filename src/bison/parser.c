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




/* Copy the first part of user declarations.  */
#line 3 "src/bison/bison.y"

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
/* Line 193 of yacc.c.  */
#line 224 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/bison/parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 237 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/bison/parser.c"

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
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNRULES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,     2,     2,    34,     2,    39,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    35,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    16,    17,    19,
      20,    22,    24,    27,    34,    35,    38,    41,    45,    47,
      51,    60,    67,    74,    79,    86,    91,    96,    99,   106,
     111,   116,   119,   124,   127,   130,   134,   140,   141,   143,
     146,   150,   151,   153,   156,   160,   161,   163,   166,   170,
     174,   179,   182,   190,   196,   197,   199,   202,   206,   210,
     216,   221,   222,   225,   228,   232,   235,   243,   245,   247,
     252,   256,   263,   267,   271,   277,   279,   284,   289,   297,
     301,   308,   315,   325,   327,   332,   336,   343,   344,   346,
     348,   352,   354,   358,   360,   362,   364,   366,   368,   370,
     372,   374,   376,   378,   380,   382,   384,   386,   388
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    -1,    49,    -1,    44,    49,    -1,
       3,    -1,    45,    34,     3,    -1,    -1,    35,    -1,    -1,
      48,    -1,    35,    -1,    48,    35,    -1,     4,     3,    50,
      55,    57,     5,    -1,    -1,    21,    51,    -1,    52,    46,
      -1,    51,    52,    46,    -1,     3,    -1,     3,    53,     5,
      -1,    22,    54,    23,    45,    24,    45,    25,    45,    -1,
      23,    45,    24,    45,    25,    45,    -1,    22,    54,    24,
      45,    25,    45,    -1,    24,    45,    25,    45,    -1,    22,
      54,    23,    45,    25,    45,    -1,    23,    45,    25,    45,
      -1,    22,    54,    25,    45,    -1,    25,    45,    -1,    22,
      54,    23,    45,    24,    45,    -1,    23,    45,    24,    45,
      -1,    22,    54,    24,    45,    -1,    24,    45,    -1,    22,
      54,    23,    45,    -1,    23,    45,    -1,    22,    54,    -1,
       3,    26,     3,    -1,    54,    34,     3,    26,     3,    -1,
      -1,    56,    -1,    27,    45,    -1,    56,    27,    45,    -1,
      -1,    58,    -1,    28,    59,    -1,    58,    28,    59,    -1,
      -1,    60,    -1,    61,    47,    -1,    60,    61,    47,    -1,
      45,    36,    74,    -1,    45,    36,    74,    65,    -1,    45,
      65,    -1,    45,    37,    62,    38,    36,    74,    65,    -1,
      45,    37,    62,    38,    65,    -1,    -1,    63,    -1,    64,
      46,    -1,    63,    64,    46,    -1,    45,    36,    74,    -1,
      66,    30,    47,    67,     5,    -1,    66,    30,    47,     5,
      -1,    -1,    29,    62,    -1,    68,    47,    -1,    67,    68,
      47,    -1,    27,     3,    -1,    27,     3,    39,     3,    37,
      71,    38,    -1,    69,    -1,     3,    -1,     3,    37,    71,
      38,    -1,     3,    39,    70,    -1,     3,    37,    71,    38,
      39,    70,    -1,    31,    39,    70,    -1,    32,    39,    70,
      -1,    37,    73,    38,    39,    70,    -1,    33,    -1,    33,
      37,    71,    38,    -1,    33,    40,     3,    41,    -1,    33,
      40,     3,    41,    37,    71,    38,    -1,    33,    39,    70,
      -1,    33,    37,    71,    38,    39,    70,    -1,    33,    40,
       3,    41,    39,    70,    -1,    33,    40,     3,    41,    37,
      71,    38,    39,    70,    -1,     3,    -1,     3,    37,    71,
      38,    -1,    70,    39,     3,    -1,    70,    39,     3,    37,
      71,    38,    -1,    -1,    72,    -1,    73,    -1,    72,    34,
      73,    -1,    69,    -1,    37,    73,    38,    -1,    17,    -1,
      18,    -1,    19,    -1,    20,    -1,     3,    -1,     6,    -1,
       7,    -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,
      12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   151,   151,   154,   155,   159,   160,   163,   164,   167,
     168,   171,   172,   176,   180,   181,   184,   185,   188,   189,
     192,   193,   194,   195,   197,   198,   199,   200,   202,   203,
     204,   205,   207,   208,   209,   212,   213,   217,   218,   221,
     222,   226,   227,   230,   231,   234,   235,   238,   239,   242,
     243,   244,   245,   246,   249,   250,   253,   254,   257,   260,
     261,   264,   265,   268,   269,   273,   274,   275,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   295,   296,   297,   298,   301,   302,   305,
     306,   309,   310,   311,   312,   313,   314,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CLASS", "END", "DATATYPE_BOOLEAN",
  "DATATYPE_CHARACTER", "DATATYPE_INTEGER_8", "DATATYPE_INTEGER_16",
  "DATATYPE_INTEGER_32", "DATATYPE_INTEGER_64", "DATATYPE_NATURAL_8",
  "DATATYPE_NATURAL_16", "DATATYPE_NATURAL_32", "DATATYPE_NATURAL_64",
  "DATATYPE_STRING", "LITER_BOOLEAN", "LITER_INTEGER", "LITER_CHAR",
  "LITER_STRING", "INHERIT", "RENAME", "UNDEFINE", "REDEFINE", "SELECT",
  "AS", "CREATE", "FEATURE", "LOCAL", "DO", "CURRENT", "RESULT",
  "PRECURSOR", "','", "';'", "':'", "'('", "')'", "'.'", "'{'", "'}'",
  "$accept", "program", "class_decl_seq", "identifiers_comma_seq",
  "opt_semicolon", "opt_semicolon_seq", "nonempty_opt_semicolon_seq",
  "class_decl", "inheritance_block", "parent_seq", "parent", "parent_info",
  "rename_seq", "creators_block", "nonempty_creators_block",
  "features_block", "nonempty_features_block", "feature_decl_seq",
  "nonempty_feature_decl_seq", "feature_decl", "ids_with_type_seq",
  "nonempty_ids_with_type_seq", "ids_with_type", "routine_decl_body",
  "local_decl", "instruction_seq", "instruction", "call", "call_sub_seq",
  "argument_seq", "nonempty_argument_seq", "expr", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    44,    59,    58,    40,    41,    46,
     123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    48,    48,    49,    50,    50,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    61,    62,    62,    63,    63,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    73,    73,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     3,     0,     1,     0,
       1,     1,     2,     6,     0,     2,     2,     3,     1,     3,
       8,     6,     6,     4,     6,     4,     4,     2,     6,     4,
       4,     2,     4,     2,     2,     3,     5,     0,     1,     2,
       3,     0,     1,     2,     3,     0,     1,     2,     3,     3,
       4,     2,     7,     5,     0,     1,     2,     3,     3,     5,
       4,     0,     2,     2,     3,     2,     7,     1,     1,     4,
       3,     6,     3,     3,     5,     1,     4,     4,     7,     3,
       6,     6,     9,     1,     4,     3,     6,     0,     1,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,    14,     1,     4,     0,    37,
      18,    15,     7,     0,    41,    38,     0,     0,     0,     0,
       0,     7,     8,    16,     5,    39,    45,     0,    42,     0,
       0,    34,    33,    31,    27,    19,    17,     0,    61,    43,
      46,     9,    13,    45,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     6,    54,     0,    54,    51,     0,     9,
      11,    47,    10,    44,    35,    32,    30,    26,     0,    29,
      25,    23,     0,    62,    55,     7,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,    49,     0,
       9,    48,    12,     0,     0,     0,     0,     0,     0,     7,
      56,    50,    61,     0,    28,    24,    22,    36,    21,    58,
      57,     0,    53,    68,    60,     0,     0,     0,    75,     0,
       0,     9,    67,     0,    61,    87,     0,    65,     0,     0,
      87,     0,     0,    93,    94,    95,    96,     0,    91,     0,
      59,     9,    63,    20,    52,     0,    88,    89,    83,    70,
       0,    72,    73,     0,    79,     0,     0,     0,    64,    69,
       0,    87,     0,     0,    76,    77,    92,     0,     0,    90,
       0,    85,    87,     0,    87,     0,    74,    71,    84,    87,
       0,    80,     0,    81,     0,    66,    78,    86,     0,    82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    38,    23,    61,    62,     4,     9,    11,
      12,    20,    31,    14,    15,    27,    28,    39,    40,    41,
      73,    74,    75,    57,    58,   120,   121,   138,   149,   145,
     146,   147,    88
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -121
static const yytype_int16 yypact[] =
{
      13,    26,    23,    13,  -121,    25,  -121,  -121,    63,    68,
     109,    63,    64,   101,    77,    79,   105,   101,   101,   101,
     106,    64,  -121,  -121,  -121,    78,   101,   111,    90,   101,
     110,     2,   -12,   -10,    78,  -121,  -121,   136,    57,  -121,
     101,   107,  -121,   101,    78,   137,   101,   101,   101,   138,
     101,   101,   101,  -121,   101,   114,   101,  -121,   113,   107,
    -121,  -121,   112,  -121,  -121,     6,    20,    78,   118,    40,
      78,    78,    43,  -121,   101,    64,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,    22,   108,
     107,  -121,  -121,   101,   101,   101,   142,   101,   114,    64,
    -121,  -121,    60,    70,    44,    78,    78,  -121,    78,  -121,
    -121,   114,  -121,    53,  -121,   145,   115,   116,    98,    39,
      82,   107,  -121,   101,   120,    39,   147,   117,   147,   147,
      39,   147,   148,  -121,  -121,  -121,  -121,    39,  -121,   119,
    -121,   107,  -121,    78,  -121,   121,   124,  -121,   123,   122,
     149,   122,   122,   125,   122,   126,   127,   129,  -121,   130,
      39,    39,   150,   133,   132,    61,   129,   147,   147,  -121,
     128,   135,    39,   147,    39,   147,   122,   122,  -121,    39,
     139,   122,   140,   122,   141,  -121,   134,  -121,   147,   122
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,  -121,   -13,   -11,   -58,  -121,   159,  -121,  -121,
     153,  -121,  -121,  -121,  -121,  -121,  -121,   131,  -121,   143,
     144,  -121,   102,   -74,  -121,  -121,    55,  -101,  -120,  -112,
    -121,  -116,   -91
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -62
static const yytype_int16 yytable[] =
{
      25,    91,   122,   139,    32,    33,    34,   109,   151,   152,
      36,   154,    50,    51,   101,    52,    44,     1,   153,   122,
     124,   156,    37,     6,    37,    46,    47,    48,   112,     5,
      93,    94,   103,    65,    66,    67,    49,    69,    70,    71,
      37,    72,   113,    72,   169,    95,     8,   176,   177,   170,
     144,    54,   -61,   181,    37,   183,   133,   134,   135,   136,
     180,    72,   182,   142,   100,    97,    10,   184,   189,   123,
     116,   117,   118,   113,    37,   114,   137,    37,    37,    98,
     104,   105,   106,   158,   108,   113,    54,   140,   110,    54,
     125,    37,   126,    55,    56,    13,   111,   115,   174,    22,
     175,   116,   117,   118,    24,    26,    29,   119,    30,   115,
     143,    35,    37,   116,   117,   118,    42,    76,    43,   119,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    16,    17,    18,    19,   130,    45,   131,   132,    53,
      64,    68,    60,    90,    96,   107,   102,    92,   127,    54,
     148,   155,   163,   171,   128,   129,   150,   157,   160,   159,
     161,   162,     7,   164,    21,   166,   178,   165,   167,   168,
     172,   173,   179,   188,    63,   141,    99,   185,   186,   187,
       0,     0,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89
};

static const yytype_int16 yycheck[] =
{
      13,    59,   103,   119,    17,    18,    19,    98,   128,   129,
      21,   131,    24,    25,    88,    25,    29,     4,   130,   120,
     111,   137,    34,     0,    34,    23,    24,    25,   102,     3,
      24,    25,    90,    46,    47,    48,    34,    50,    51,    52,
      34,    54,     3,    56,   160,    25,    21,   167,   168,   161,
     124,    29,    30,   173,    34,   175,    17,    18,    19,    20,
     172,    74,   174,   121,    75,    25,     3,   179,   188,    25,
      31,    32,    33,     3,    34,     5,    37,    34,    34,    36,
      93,    94,    95,   141,    97,     3,    29,     5,    99,    29,
      37,    34,    39,    36,    37,    27,    36,    27,    37,    35,
      39,    31,    32,    33,     3,    28,    27,    37,     3,    27,
     123,     5,    34,    31,    32,    33,     5,     3,    28,    37,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    22,    23,    24,    25,    37,    26,    39,    40,     3,
       3,     3,    35,    30,    26,     3,    38,    35,     3,    29,
       3,     3,     3,     3,    39,    39,    39,    38,    34,    38,
      37,    39,     3,    38,    11,    38,    38,    41,    39,    39,
      37,    39,    37,    39,    43,   120,    74,    38,    38,    38,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    43,    44,    49,     3,     0,    49,    21,    50,
       3,    51,    52,    27,    55,    56,    22,    23,    24,    25,
      53,    52,    35,    46,     3,    45,    28,    57,    58,    27,
       3,    54,    45,    45,    45,     5,    46,    34,    45,    59,
      60,    61,     5,    28,    45,    26,    23,    24,    25,    34,
      24,    25,    25,     3,    29,    36,    37,    65,    66,    61,
      35,    47,    48,    59,     3,    45,    45,    45,     3,    45,
      45,    45,    45,    62,    63,    64,     3,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    74,    62,
      30,    47,    35,    24,    25,    25,    26,    25,    36,    64,
      46,    65,    38,    47,    45,    45,    45,     3,    45,    74,
      46,    36,    65,     3,     5,    27,    31,    32,    33,    37,
      67,    68,    69,    25,    74,    37,    39,     3,    39,    39,
      37,    39,    40,    17,    18,    19,    20,    37,    69,    73,
       5,    68,    47,    45,    65,    71,    72,    73,     3,    70,
      39,    70,    70,    71,    70,     3,    73,    38,    47,    38,
      34,    37,    39,     3,    38,    41,    38,    39,    39,    73,
      71,     3,    37,    39,    37,    39,    70,    70,    38,    37,
      71,    70,    71,    70,    71,    38,    38,    38,    39,    70
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
#line 151 "src/bison/bison.y"
    { (yyval.program_field) = create_program(curr_node_index++, (yyvsp[(1) - (1)].class_decl_seq_field)); tree_root = (yyval.program_field); ;}
    break;

  case 3:
#line 154 "src/bison/bison.y"
    { (yyval.class_decl_seq_field) = create_class_decl_seq(curr_node_index++, (yyvsp[(1) - (1)].class_decl_field)); ;}
    break;

  case 4:
#line 155 "src/bison/bison.y"
    { (yyval.class_decl_seq_field) = append_class_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].class_decl_seq_field), (yyvsp[(2) - (2)].class_decl_field)); ;}
    break;

  case 5:
#line 159 "src/bison/bison.y"
    { (yyval.identifiers_comma_seq_field) = create_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (1)].id_field)); ;}
    break;

  case 6:
#line 160 "src/bison/bison.y"
    { (yyval.identifiers_comma_seq_field) = append_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 13:
#line 176 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(3) - (6)].inheritance_block_field), (yyvsp[(4) - (6)].creators_block_field), (yyvsp[(5) - (6)].features_block_field)); ;}
    break;

  case 14:
#line 180 "src/bison/bison.y"
    { (yyval.inheritance_block_field) = NULL; ;}
    break;

  case 15:
#line 181 "src/bison/bison.y"
    { (yyval.inheritance_block_field) = create_inheritance_block(curr_node_index++, (yyvsp[(2) - (2)].parent_seq_field)); ;}
    break;

  case 16:
#line 184 "src/bison/bison.y"
    { (yyval.parent_seq_field) = create_parent_seq(curr_node_index++, (yyvsp[(1) - (2)].parent_field)); ;}
    break;

  case 17:
#line 185 "src/bison/bison.y"
    { (yyval.parent_seq_field) = append_parent_seq(curr_node_index++, (yyvsp[(1) - (3)].parent_seq_field), (yyvsp[(2) - (3)].parent_field)); ;}
    break;

  case 18:
#line 188 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (1)].id_field), NULL); ;}
    break;

  case 19:
#line 189 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(2) - (3)].parent_info_field)); ;}
    break;

  case 20:
#line 192 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (8)].rename_seq_field), (yyvsp[(4) - (8)].identifiers_comma_seq_field), (yyvsp[(6) - (8)].identifiers_comma_seq_field), (yyvsp[(8) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 21:
#line 193 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, (yyvsp[(2) - (6)].identifiers_comma_seq_field), (yyvsp[(4) - (6)].identifiers_comma_seq_field), (yyvsp[(6) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 22:
#line 194 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (6)].rename_seq_field), NULL, (yyvsp[(4) - (6)].identifiers_comma_seq_field), (yyvsp[(6) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 23:
#line 195 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, NULL, (yyvsp[(2) - (4)].identifiers_comma_seq_field), (yyvsp[(4) - (4)].identifiers_comma_seq_field)); ;}
    break;

  case 24:
#line 197 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (6)].rename_seq_field), (yyvsp[(4) - (6)].identifiers_comma_seq_field), NULL, (yyvsp[(6) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 25:
#line 198 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, (yyvsp[(2) - (4)].identifiers_comma_seq_field), NULL, (yyvsp[(4) - (4)].identifiers_comma_seq_field)); ;}
    break;

  case 26:
#line 199 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (4)].rename_seq_field), NULL, NULL, (yyvsp[(4) - (4)].identifiers_comma_seq_field)); ;}
    break;

  case 27:
#line 200 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, NULL, NULL, (yyvsp[(2) - (2)].identifiers_comma_seq_field)); ;}
    break;

  case 28:
#line 202 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (6)].rename_seq_field), (yyvsp[(4) - (6)].identifiers_comma_seq_field), (yyvsp[(6) - (6)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 29:
#line 203 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, (yyvsp[(2) - (4)].identifiers_comma_seq_field), (yyvsp[(4) - (4)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 30:
#line 204 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (4)].rename_seq_field), NULL, (yyvsp[(4) - (4)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 31:
#line 205 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, NULL, (yyvsp[(2) - (2)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 32:
#line 207 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (4)].rename_seq_field), (yyvsp[(4) - (4)].identifiers_comma_seq_field), NULL, NULL); ;}
    break;

  case 33:
#line 208 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, NULL, (yyvsp[(2) - (2)].identifiers_comma_seq_field), NULL, NULL); ;}
    break;

  case 34:
#line 209 "src/bison/bison.y"
    { (yyval.parent_info_field) = create_parent_info(curr_node_index++, (yyvsp[(2) - (2)].rename_seq_field), NULL, NULL, NULL); ;}
    break;

  case 35:
#line 212 "src/bison/bison.y"
    { (yyval.rename_seq_field) = create_rename_seq(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 36:
#line 213 "src/bison/bison.y"
    { (yyval.rename_seq_field) = append_rename_seq(curr_node_index++, (yyvsp[(1) - (5)].rename_seq_field), (yyvsp[(3) - (5)].id_field), (yyvsp[(5) - (5)].id_field)); ;}
    break;

  case 37:
#line 217 "src/bison/bison.y"
    { (yyval.creators_block_field) = NULL; ;}
    break;

  case 38:
#line 218 "src/bison/bison.y"
    { (yyval.creators_block_field) = create_creators_block(curr_node_index++, (yyvsp[(1) - (1)].nonempty_creators_block_field)); ;}
    break;

  case 39:
#line 221 "src/bison/bison.y"
    { (yyval.nonempty_creators_block_field) = create_nonempty_creators_block(curr_node_index++, (yyvsp[(2) - (2)].identifiers_comma_seq_field)); ;}
    break;

  case 40:
#line 222 "src/bison/bison.y"
    { (yyval.nonempty_creators_block_field) = append_nonempty_creators_block(curr_node_index++, (yyvsp[(1) - (3)].nonempty_creators_block_field), (yyvsp[(3) - (3)].identifiers_comma_seq_field)); ;}
    break;

  case 41:
#line 226 "src/bison/bison.y"
    { (yyval.features_block_field) = NULL; ;}
    break;

  case 42:
#line 227 "src/bison/bison.y"
    { (yyval.features_block_field) = create_features_block(curr_node_index++, (yyvsp[(1) - (1)].nonempty_features_block_field)); ;}
    break;

  case 43:
#line 230 "src/bison/bison.y"
    { (yyval.nonempty_features_block_field) = create_nonempty_features_block(curr_node_index++, (yyvsp[(2) - (2)].feature_decl_seq_field)); ;}
    break;

  case 44:
#line 231 "src/bison/bison.y"
    { (yyval.nonempty_features_block_field) = append_nonempty_features_block(curr_node_index++, (yyvsp[(1) - (3)].nonempty_features_block_field), (yyvsp[(3) - (3)].feature_decl_seq_field)); ;}
    break;

  case 45:
#line 234 "src/bison/bison.y"
    { (yyval.feature_decl_seq_field) = NULL; ;}
    break;

  case 46:
#line 235 "src/bison/bison.y"
    { (yyval.feature_decl_seq_field) = create_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (1)].nonempty_feature_decl_seq_field)); ;}
    break;

  case 47:
#line 238 "src/bison/bison.y"
    { (yyval.nonempty_feature_decl_seq_field) = create_nonempty_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].feature_decl_field)); ;}
    break;

  case 48:
#line 239 "src/bison/bison.y"
    { (yyval.nonempty_feature_decl_seq_field) = append_nonempty_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (3)].nonempty_feature_decl_seq_field), (yyvsp[(2) - (3)].feature_decl_field)); ;}
    break;

  case 49:
#line 242 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].type_field), NULL, NULL); ;}
    break;

  case 50:
#line 243 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), (yyvsp[(3) - (4)].type_field), NULL, (yyvsp[(4) - (4)].routine_decl_body_field)); ;}
    break;

  case 51:
#line 244 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (2)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(2) - (2)].routine_decl_body_field)); ;}
    break;

  case 52:
#line 245 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), (yyvsp[(6) - (7)].type_field), (yyvsp[(3) - (7)].ids_with_type_seq_field), (yyvsp[(7) - (7)].routine_decl_body_field)); ;}
    break;

  case 53:
#line 246 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (5)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (5)].ids_with_type_seq_field), (yyvsp[(5) - (5)].routine_decl_body_field)); ;}
    break;

  case 54:
#line 249 "src/bison/bison.y"
    { (yyval.ids_with_type_seq_field) = NULL; ;}
    break;

  case 55:
#line 250 "src/bison/bison.y"
    { (yyval.ids_with_type_seq_field) = create_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (1)].nonempty_ids_with_type_seq_field)); ;}
    break;

  case 56:
#line 253 "src/bison/bison.y"
    { (yyval.nonempty_ids_with_type_seq_field) = create_nonempty_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (2)].ids_with_type_field)); ;}
    break;

  case 57:
#line 254 "src/bison/bison.y"
    { (yyval.nonempty_ids_with_type_seq_field) = append_nonempty_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (3)].nonempty_ids_with_type_seq_field), (yyvsp[(2) - (3)].ids_with_type_field)); ;}
    break;

  case 58:
#line 257 "src/bison/bison.y"
    { (yyval.ids_with_type_field) = create_ids_with_type(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].type_field)); ;}
    break;

  case 59:
#line 260 "src/bison/bison.y"
    { (yyval.routine_decl_body_field) = create_routine_decl_body(curr_node_index++); ;}
    break;

  case 60:
#line 261 "src/bison/bison.y"
    { (yyval.routine_decl_body_field) = create_routine_decl_body(curr_node_index++); ;}
    break;

  case 97:
#line 318 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_user_defined, (yyvsp[(1) - (1)].id_field)); ;}
    break;

  case 98:
#line 319 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_boolean, NULL); ;}
    break;

  case 99:
#line 320 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_character, NULL); ;}
    break;

  case 100:
#line 321 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_8,  NULL); ;}
    break;

  case 101:
#line 322 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_16, NULL); ;}
    break;

  case 102:
#line 323 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_32, NULL); ;}
    break;

  case 103:
#line 324 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_64, NULL); ;}
    break;

  case 104:
#line 325 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_8,  NULL); ;}
    break;

  case 105:
#line 326 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_16, NULL); ;}
    break;

  case 106:
#line 327 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_32, NULL); ;}
    break;

  case 107:
#line 328 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_64, NULL); ;}
    break;

  case 108:
#line 329 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_string, NULL); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1941 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/bison/parser.c"
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


#line 332 "src/bison/bison.y"


