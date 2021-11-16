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
     DATATYPE_INTEGER_8 = 269,
     DATATYPE_INTEGER_16 = 270,
     DATATYPE_INTEGER_32 = 271,
     DATATYPE_INTEGER_64 = 272,
     DATATYPE_NATURAL_8 = 273,
     DATATYPE_NATURAL_16 = 274,
     DATATYPE_NATURAL_32 = 275,
     DATATYPE_NATURAL_64 = 276,
     DATATYPE_STRING = 277,
     DATATYPE_ARRAY = 278,
     ASSIGNMENT = 279,
     XOR = 280,
     OR = 281,
     AND = 282,
     NOTEQUAL = 283,
     GREAT_EQUAL = 284,
     LESS_EQUAL = 285,
     INTEGER_DIVISION = 286,
     NOT = 287,
     UMINUS = 288,
     LITER_BOOLEAN = 289,
     LITER_INTEGER = 290,
     LITER_CHAR = 291,
     LITER_STRING = 292,
     INHERIT = 293,
     RENAME = 294,
     UNDEFINE = 295,
     REDEFINE = 296,
     SELECT = 297,
     AS = 298,
     CREATE = 299,
     FEATURE = 300,
     LOCAL = 301,
     DO = 302,
     CURRENT = 303,
     RESULT = 304,
     PRECURSOR = 305
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
#define DATATYPE_INTEGER_8 269
#define DATATYPE_INTEGER_16 270
#define DATATYPE_INTEGER_32 271
#define DATATYPE_INTEGER_64 272
#define DATATYPE_NATURAL_8 273
#define DATATYPE_NATURAL_16 274
#define DATATYPE_NATURAL_32 275
#define DATATYPE_NATURAL_64 276
#define DATATYPE_STRING 277
#define DATATYPE_ARRAY 278
#define ASSIGNMENT 279
#define XOR 280
#define OR 281
#define AND 282
#define NOTEQUAL 283
#define GREAT_EQUAL 284
#define LESS_EQUAL 285
#define INTEGER_DIVISION 286
#define NOT 287
#define UMINUS 288
#define LITER_BOOLEAN 289
#define LITER_INTEGER 290
#define LITER_CHAR 291
#define LITER_STRING 292
#define INHERIT 293
#define RENAME 294
#define UNDEFINE 295
#define REDEFINE 296
#define SELECT 297
#define AS 298
#define CREATE 299
#define FEATURE 300
#define LOCAL 301
#define DO 302
#define CURRENT 303
#define RESULT 304
#define PRECURSOR 305




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
#line 256 "bison.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 269 "bison.tab.c"

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
#define YYLAST   1182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNRULES -- Number of states.  */
#define YYNSTATES  317

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    63,    36,    34,    60,    35,    41,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    61,
      28,    30,    29,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    65,     2,     2,     2,     2,
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
      25,    26,    27,    31,    32,    33,    37,    38,    39,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59
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
     398,   401,   406,   414,   418,   426,   436,   444,   446,   448,
     452,   457,   461,   467,   474,   478,   484,   491,   497,   505,
     514,   516,   520,   525,   530,   537,   545,   547,   551,   555,
     557,   559,   561,   563,   565,   569,   576,   580,   584,   588,
     592,   596,   599,   603,   607,   611,   615,   619,   623,   627,
     631,   635,   638,   640,   642,   644,   646,   648,   650,   652,
     654,   656,   658,   660,   662
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      73,     0,    -1,     3,    -1,    69,    60,     3,    -1,    -1,
      61,    -1,    -1,    72,    -1,    61,    -1,    72,    61,    -1,
      74,    -1,    75,    -1,    74,    75,    -1,     4,     3,    76,
      79,    80,     5,    -1,     4,     3,    76,    79,     5,    -1,
       4,     3,    76,    80,     5,    -1,     4,     3,    76,     5,
      -1,     4,     3,    79,    80,     5,    -1,     4,     3,    79,
       5,    -1,     4,     3,    80,     5,    -1,     4,     3,     5,
      -1,    47,    77,    70,    -1,    76,    77,    70,    -1,     3,
      48,    78,    49,    69,    50,    69,    51,    69,     5,    -1,
       3,    49,    69,    50,    69,    51,    69,     5,    -1,     3,
      48,    78,    50,    69,    51,    69,     5,    -1,     3,    50,
      69,    51,    69,     5,    -1,     3,    48,    78,    49,    69,
      51,    69,     5,    -1,     3,    49,    69,    51,    69,     5,
      -1,     3,    48,    78,    51,    69,     5,    -1,     3,    51,
      69,     5,    -1,     3,    48,    78,    49,    69,    50,    69,
       5,    -1,     3,    49,    69,    50,    69,     5,    -1,     3,
      48,    78,    50,    69,     5,    -1,     3,    50,    69,     5,
      -1,     3,    48,    78,    49,    69,     5,    -1,     3,    49,
      69,     5,    -1,     3,    48,    78,     5,    -1,     3,    -1,
       3,    52,     3,    -1,    78,    60,     3,    52,     3,    -1,
      53,    69,    -1,    79,    53,    69,    -1,    54,    81,    -1,
      80,    54,    81,    -1,    82,    71,    -1,    81,    82,    71,
      -1,    69,    62,    89,    -1,    69,    56,    84,     5,    -1,
      69,    55,    56,    84,     5,    -1,    69,    55,    83,    56,
      84,     5,    -1,    69,    42,    63,    56,    84,     5,    -1,
      69,    42,    63,    55,    56,    84,     5,    -1,    69,    42,
      63,    55,    83,    56,    84,     5,    -1,    69,    62,    89,
      56,    84,     5,    -1,    69,    62,    89,    55,    56,    84,
       5,    -1,    69,    62,    89,    55,    83,    56,    84,     5,
      -1,    69,    42,    63,    62,    89,    56,    84,     5,    -1,
      69,    42,    63,    62,    89,    55,    56,    84,     5,    -1,
      69,    42,    63,    62,    89,    55,    83,    56,    84,     5,
      -1,    69,    42,    83,    63,    56,    84,     5,    -1,    69,
      42,    83,    63,    55,    56,    84,     5,    -1,    69,    42,
      83,    63,    55,    83,    56,    84,     5,    -1,    69,    42,
      83,    63,    62,    89,    56,    84,     5,    -1,    69,    42,
      83,    63,    62,    89,    55,    56,    84,     5,    -1,    69,
      42,    83,    63,    62,    89,    55,    83,    56,    84,     5,
      -1,    69,    62,    89,    70,    -1,    83,    69,    62,    89,
      70,    -1,    71,    -1,    84,    85,    71,    -1,    53,     3,
      -1,    53,     3,    41,     3,    -1,    53,     3,    41,     3,
      42,    87,    63,    -1,     3,    24,    88,    -1,     6,    42,
      88,    63,     7,    84,     5,    -1,     6,    42,    88,    63,
       7,    84,     8,    84,     5,    -1,     9,    84,    10,    88,
      11,    84,     5,    -1,    88,    -1,     3,    -1,     3,    42,
      63,    -1,     3,    42,    87,    63,    -1,    57,    41,     3,
      -1,    57,    41,     3,    42,    63,    -1,    57,    41,     3,
      42,    87,    63,    -1,    58,    41,     3,    -1,    58,    41,
       3,    42,    63,    -1,    58,    41,     3,    42,    87,    63,
      -1,    42,    88,    63,    41,     3,    -1,    42,    88,    63,
      41,     3,    42,    63,    -1,    42,    88,    63,    41,     3,
      42,    87,    63,    -1,    59,    -1,    59,    42,    63,    -1,
      59,    42,    87,    63,    -1,    59,    64,     3,    65,    -1,
      59,    64,     3,    65,    42,    63,    -1,    59,    64,     3,
      65,    42,    87,    63,    -1,    88,    -1,    87,    60,    88,
      -1,    42,    88,    63,    -1,    43,    -1,    44,    -1,    45,
      -1,    46,    -1,    86,    -1,    88,    41,     3,    -1,    88,
      41,     3,    42,    87,    63,    -1,    88,    40,    88,    -1,
      88,    34,    88,    -1,    88,    35,    88,    -1,    88,    36,
      88,    -1,    88,    37,    88,    -1,    35,    88,    -1,    88,
      28,    88,    -1,    88,    29,    88,    -1,    88,    33,    88,
      -1,    88,    32,    88,    -1,    88,    30,    88,    -1,    88,
      31,    88,    -1,    88,    27,    88,    -1,    88,    26,    88,
      -1,    88,    25,    88,    -1,    38,    88,    -1,     3,    -1,
      12,    -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
      22,    -1,    23,    66,    89,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   168,   171,   172,   175,   176,   179,   180,
     184,   187,   188,   192,   193,   194,   195,   197,   198,   199,
     200,   204,   205,   208,   209,   210,   211,   213,   214,   215,
     216,   218,   219,   220,   221,   223,   224,   225,   226,   229,
     230,   234,   235,   239,   240,   243,   244,   247,   249,   250,
     251,   253,   254,   255,   257,   258,   259,   261,   262,   263,
     265,   266,   267,   269,   270,   271,   274,   275,   278,   279,
     282,   283,   284,   286,   288,   289,   290,   292,   295,   296,
     297,   299,   300,   301,   303,   304,   305,   307,   308,   309,
     311,   312,   313,   314,   315,   316,   319,   320,   323,   324,
     325,   326,   327,   329,   330,   331,   332,   334,   335,   336,
     337,   338,   340,   341,   342,   343,   344,   345,   347,   348,
     349,   350,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CLASS", "END", "IF", "THEN",
  "ELSE", "FROM", "UNTIL", "LOOP", "DATATYPE_BOOLEAN",
  "DATATYPE_CHARACTER", "DATATYPE_INTEGER_8", "DATATYPE_INTEGER_16",
  "DATATYPE_INTEGER_32", "DATATYPE_INTEGER_64", "DATATYPE_NATURAL_8",
  "DATATYPE_NATURAL_16", "DATATYPE_NATURAL_32", "DATATYPE_NATURAL_64",
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
  "instruction_seq", "instruction", "call", "argument_seq", "expr", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    60,    62,
      61,   283,   284,   285,    43,    45,    42,   286,   287,   288,
      64,    46,    40,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
      44,    59,    58,    41,   123,   125,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    71,    71,    72,    72,
      73,    74,    74,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89
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
       2,     4,     7,     3,     7,     9,     7,     1,     1,     3,
       4,     3,     5,     6,     3,     5,     6,     5,     7,     8,
       1,     3,     4,     4,     6,     7,     1,     3,     3,     1,
       1,     1,     1,     1,     3,     6,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4
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
       0,     0,     6,     0,    68,     0,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,     0,    47,
      46,     9,    13,     0,    37,     0,     0,     0,     0,    36,
       0,     0,    34,     0,    30,     0,     6,     0,     0,     0,
       0,     0,     6,    78,    48,     0,     6,     0,     0,     0,
      99,   100,   101,   102,     0,     0,     0,    90,     6,   103,
      77,     0,     0,     6,    39,     0,     0,     0,     0,     0,
       0,     0,     6,     0,     0,     0,     4,     0,     6,     0,
       0,    49,     0,     0,     0,     0,     0,    78,   111,   121,
       0,    70,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,    35,     0,     0,    33,
       0,    29,     0,    32,     0,    28,    26,     0,     6,    51,
       0,     6,    66,     6,     0,     0,     0,     4,    50,    73,
      79,     0,    96,     0,     0,    98,     0,    81,    84,    91,
       0,     0,   120,   119,   118,   112,   113,   116,   117,   115,
     114,   107,   108,   109,   110,   106,   104,   134,     0,     6,
      54,     0,     0,     0,    40,     0,    52,     0,     6,     0,
       0,     0,     6,    60,     0,     6,    67,     0,    80,     0,
       0,     0,    71,     0,     0,    92,    93,     0,    55,     0,
      31,     0,    27,    25,    24,    53,     0,     6,    57,    61,
       0,     6,     0,     0,    97,     6,     6,    87,     0,    82,
       0,    85,     0,     0,     0,    56,     0,    58,     0,    62,
       0,     6,    63,     0,     0,     0,     0,    83,    86,    94,
       0,   105,    23,    59,    64,     0,    74,     6,    76,    88,
       0,    72,    95,    65,     0,    89,    75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    60,    36,    64,    45,     2,     3,     4,    12,    16,
      54,    13,    14,    20,    21,    61,    65,   118,   119,   201,
     120,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -151
static const yytype_int16 yypact[] =
{
      17,    28,    12,    17,  -151,   146,  -151,  -151,  -151,    36,
      41,    41,   103,   109,   153,    -2,    -5,  -151,    61,   188,
      41,    71,  -151,    -5,   219,   221,  -151,    41,   223,  -151,
      41,   152,    41,    41,    41,  -151,  -151,   183,     3,   113,
      71,   464,    71,  -151,  -151,   181,  -151,  -151,   228,  -151,
      61,  -151,    41,   197,    14,    10,    27,     8,  -151,   -19,
      76,     4,    71,   115,  -151,   415,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,   204,    87,
    -151,  -151,  -151,   280,  -151,    41,    41,    41,   281,  -151,
      41,    41,  -151,    41,  -151,   116,    71,   464,   464,    79,
     216,   460,    71,   -13,  -151,   248,    71,   145,   145,   145,
    -151,  -151,  -151,  -151,   295,   267,   272,   -34,    71,  -151,
    1112,   464,   117,    71,  -151,    22,    33,     9,   262,    80,
      11,    30,    71,   119,   485,   110,    -5,   121,    71,   464,
     464,  -151,   530,   145,    54,   145,   557,   276,   198,   198,
     521,   278,   317,   319,   222,   321,  -151,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   322,   259,    71,   122,   588,  -151,    41,    41,  -151,
      41,  -151,   324,  -151,    41,  -151,  -151,   615,    71,  -151,
     123,    71,  -151,    71,   136,   646,   256,    -5,  -151,  1112,
    -151,   -35,  1112,  1056,   145,   287,   328,   291,   292,  -151,
      67,   277,  1127,  1127,  1141,   218,   218,   218,   218,   218,
     218,   200,   200,   198,   198,   300,   301,  -151,   673,    71,
    -151,    86,    35,    45,  -151,    49,  -151,   704,    71,   149,
     731,   762,    71,  -151,   178,    71,  -151,   145,  -151,   337,
    1095,   342,   304,   258,   294,  -151,   306,   145,  -151,   789,
    -151,    41,  -151,  -151,  -151,  -151,   820,    71,  -151,  -151,
     847,    71,   179,   878,  1112,    71,    71,   308,   145,  -151,
      90,  -151,   211,   320,   226,  -151,    50,  -151,   905,  -151,
     936,    71,  -151,   390,   963,   346,   231,  -151,  -151,  -151,
     232,  -151,  -151,  -151,  -151,   994,  -151,    71,  -151,  -151,
     247,  -151,  -151,  -151,  1021,  -151,  -151
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,   -10,   -21,   -16,  -151,  -151,  -151,   351,  -151,   344,
    -151,   347,    21,   330,   -11,   -36,   -44,  -151,  -151,  -150,
      52,   148
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      18,    19,    46,    63,   210,    44,    17,    17,   154,    42,
      19,   143,     6,    94,   181,    89,   185,    50,   101,    84,
      19,     1,    55,    56,    57,   247,    80,   176,   248,   144,
     155,     5,    92,    25,    28,   186,    95,    96,   179,    15,
     262,    42,    19,    97,    17,    48,    31,    32,    33,    34,
     263,   100,   134,   100,   264,   302,    35,   147,   142,   133,
      90,    91,   146,    85,    86,    87,    59,    99,    37,    37,
      37,    37,   177,   178,    88,   125,   126,   127,    93,   175,
     129,   130,    37,   131,   180,   183,   174,    37,   187,   107,
      37,   260,   108,    37,   195,    37,   109,   110,   111,   112,
     113,   194,   156,   280,   282,    37,    15,   284,    22,    37,
      37,   115,   116,   117,    26,   192,    17,   200,    17,    17,
      17,    37,    17,   100,    17,    17,    17,   247,   296,   228,
     255,   184,    43,   300,   137,   138,    37,   261,    98,    17,
      37,   139,   122,   123,   237,   310,    37,   240,   147,   241,
     247,     8,    17,   297,   239,    53,    10,    11,    29,   148,
     149,   150,    27,    11,   100,   190,   191,   231,   232,    62,
     233,   102,   132,   173,   235,   188,   246,   193,   229,   238,
     107,    17,    17,   108,   100,   259,    58,   109,   110,   111,
     112,   113,   242,     9,   266,   199,   202,   203,   270,    10,
      11,   273,   115,   116,   117,   267,   202,    30,   272,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   288,    47,   147,    49,   290,    51,   100,
      38,   293,   294,    82,   271,   291,   168,   169,   170,   171,
     170,   171,    81,    39,    40,   135,   136,   305,    37,    83,
      41,   286,   166,   167,   168,   169,   250,   107,   170,   171,
     108,   147,   100,   314,   109,   110,   111,   112,   113,   172,
     121,   247,    27,    11,   298,    30,    37,    30,   140,   115,
     116,   117,    30,   124,   128,   209,   247,   196,   197,   301,
     145,   247,   247,   107,   311,   312,   108,   147,   151,   274,
     109,   110,   111,   112,   113,   202,   202,   247,   152,   202,
     315,   244,   245,   153,   182,   115,   116,   117,   144,   206,
     207,   279,   208,   147,   211,   226,   227,   234,   251,   107,
     202,   252,   108,   253,   254,   202,   109,   110,   111,   112,
     113,   171,   256,   257,   275,   277,   278,   202,   283,   147,
     295,   115,   116,   117,     7,   107,    23,   281,   108,    24,
      52,     0,   109,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
       0,   107,     0,   299,   108,     0,     0,     0,   109,   110,
     111,   112,   113,   103,     0,   306,   105,     0,   307,   106,
       0,     0,     0,   115,   116,   117,     0,     0,     0,   309,
       0,     0,     0,     0,     0,     0,     0,     0,   103,     0,
     104,   105,     0,     0,   106,   107,     0,     0,   108,     0,
       0,     0,   109,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,   114,     0,     0,     0,   115,   116,   117,
     107,     0,     0,   108,     0,     0,     0,   109,   110,   111,
     112,   113,     0,   103,     0,   141,   105,    66,   114,   106,
       0,     0,   115,   116,   117,     0,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,   103,     0,
     189,   105,     0,     0,   106,   107,     0,     0,   108,     0,
       0,     0,   109,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,   114,     0,     0,     0,   115,   116,   117,
     107,     0,     0,   108,     0,     0,     0,   109,   110,   111,
     112,   113,     0,   103,     0,   198,   105,     0,   114,   106,
       0,     0,   115,   116,   117,     0,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,     0,
     103,   170,   171,   105,     0,   107,   106,   204,   108,     0,
       0,     0,   109,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,   114,   205,     0,     0,   115,   116,   117,
       0,   103,   107,   230,   105,   108,     0,   106,     0,   109,
     110,   111,   112,   113,     0,     0,     0,     0,     0,     0,
     114,     0,     0,     0,   115,   116,   117,     0,   103,     0,
     236,   105,     0,   107,   106,     0,   108,     0,     0,     0,
     109,   110,   111,   112,   113,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,   115,   116,   117,     0,   103,
     107,   243,   105,   108,     0,   106,     0,   109,   110,   111,
     112,   113,     0,     0,     0,     0,     0,     0,   114,     0,
       0,     0,   115,   116,   117,     0,   103,     0,   258,   105,
       0,   107,   106,     0,   108,     0,     0,     0,   109,   110,
     111,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,   116,   117,     0,   103,   107,   265,
     105,   108,     0,   106,     0,   109,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
     115,   116,   117,     0,   103,     0,   268,   105,     0,   107,
     106,     0,   108,     0,     0,     0,   109,   110,   111,   112,
     113,     0,     0,     0,     0,     0,     0,   114,     0,     0,
       0,   115,   116,   117,     0,   103,   107,   269,   105,   108,
       0,   106,     0,   109,   110,   111,   112,   113,     0,     0,
       0,     0,     0,     0,   114,     0,     0,     0,   115,   116,
     117,     0,   103,     0,   285,   105,     0,   107,   106,     0,
     108,     0,     0,     0,   109,   110,   111,   112,   113,     0,
       0,     0,     0,     0,     0,   114,     0,     0,     0,   115,
     116,   117,     0,   103,   107,   287,   105,   108,     0,   106,
       0,   109,   110,   111,   112,   113,     0,     0,     0,     0,
       0,     0,   114,     0,     0,     0,   115,   116,   117,     0,
     103,     0,   289,   105,     0,   107,   106,     0,   108,     0,
       0,     0,   109,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,   114,     0,     0,     0,   115,   116,   117,
       0,   103,   107,   292,   105,   108,     0,   106,     0,   109,
     110,   111,   112,   113,     0,     0,     0,     0,     0,     0,
     114,     0,     0,     0,   115,   116,   117,     0,   103,     0,
     303,   105,     0,   107,   106,     0,   108,     0,     0,     0,
     109,   110,   111,   112,   113,     0,     0,     0,     0,     0,
       0,   114,     0,     0,     0,   115,   116,   117,     0,   103,
     107,   304,   105,   108,     0,   106,     0,   109,   110,   111,
     112,   113,     0,     0,     0,     0,     0,     0,   114,     0,
       0,     0,   115,   116,   117,     0,   103,     0,   308,   105,
       0,   107,   106,     0,   108,     0,     0,     0,   109,   110,
     111,   112,   113,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,   115,   116,   117,     0,   103,   107,   313,
     105,   108,     0,   106,     0,   109,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,   114,     0,     0,     0,
     115,   116,   117,     0,   103,     0,   316,   105,     0,   107,
     106,     0,   108,     0,     0,     0,   109,   110,   111,   112,
     113,     0,     0,     0,     0,     0,     0,   114,     0,     0,
       0,   115,   116,   117,     0,     0,   107,     0,     0,   108,
       0,     0,     0,   109,   110,   111,   112,   113,     0,     0,
       0,     0,     0,     0,   114,     0,     0,     0,   115,   116,
     117,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,     0,     0,   170,   171,     0,     0,
       0,     0,     0,     0,     0,     0,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   249,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,     0,     0,   170,   171,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
       0,     0,   170,   171,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,     0,     0,   170,   171,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,     0,
       0,   170,   171
};

static const yytype_int16 yycheck[] =
{
      10,    11,    23,    39,   154,    21,     3,     3,    42,    20,
      20,    24,     0,     5,     5,     5,     5,    27,    62,     5,
      30,     4,    32,    33,    34,    60,    42,     5,    63,    42,
      64,     3,     5,    12,    13,     5,    55,    56,     5,     3,
       5,    52,    52,    62,     3,    24,    48,    49,    50,    51,
       5,    61,    96,    63,     5,     5,    61,     3,   102,    95,
      50,    51,   106,    49,    50,    51,    63,    63,    60,    60,
      60,    60,    50,    51,    60,    85,    86,    87,    51,   123,
      90,    91,    60,    93,    51,     5,   122,    60,   132,    35,
      60,     5,    38,    60,   138,    60,    42,    43,    44,    45,
      46,   137,   118,   253,   254,    60,     3,   257,     5,    60,
      60,    57,    58,    59,     5,   136,     3,    63,     3,     3,
       3,    60,     3,   133,     3,     3,     3,    60,   278,   173,
      63,    51,    61,   283,    55,    56,    60,    51,    62,     3,
      60,    62,    55,    56,   188,   295,    60,   191,     3,   193,
      60,     5,     3,    63,   190,     3,    53,    54,     5,   107,
     108,   109,    53,    54,   174,    55,    56,   177,   178,    56,
     180,    56,    56,    56,   184,    56,   197,    56,    56,    56,
      35,     3,     3,    38,   194,   229,     3,    42,    43,    44,
      45,    46,    56,    47,   238,   143,   144,   145,   242,    53,
      54,   245,    57,    58,    59,    56,   154,    54,   244,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   267,     5,     3,     5,   271,     5,   239,
      42,   275,   276,     5,    56,    56,    36,    37,    40,    41,
      40,    41,    61,    55,    56,    97,    98,   291,    60,    52,
      62,   261,    34,    35,    36,    37,   204,    35,    40,    41,
      38,     3,   272,   307,    42,    43,    44,    45,    46,   121,
      66,    60,    53,    54,    63,    54,    60,    54,    62,    57,
      58,    59,    54,     3,     3,    63,    60,   139,   140,    63,
      42,    60,    60,    35,    63,    63,    38,     3,     3,   247,
      42,    43,    44,    45,    46,   253,   254,    60,    41,   257,
      63,    55,    56,    41,    52,    57,    58,    59,    42,    41,
       3,    63,     3,     3,     3,     3,    67,     3,    41,    35,
     278,     3,    38,    42,    42,   283,    42,    43,    44,    45,
      46,    41,    65,    42,     7,     3,    42,   295,    42,     3,
      42,    57,    58,    59,     3,    35,    12,    63,    38,    12,
      30,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      -1,    35,    -1,    63,    38,    -1,    -1,    -1,    42,    43,
      44,    45,    46,     3,    -1,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    57,    58,    59,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,     6,    -1,    -1,     9,    35,    -1,    -1,    38,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    57,    58,    59,
      35,    -1,    -1,    38,    -1,    -1,    -1,    42,    43,    44,
      45,    46,    -1,     3,    -1,     5,     6,     3,    53,     9,
      -1,    -1,    57,    58,    59,    -1,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     3,    -1,
       5,     6,    -1,    -1,     9,    35,    -1,    -1,    38,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    57,    58,    59,
      35,    -1,    -1,    38,    -1,    -1,    -1,    42,    43,    44,
      45,    46,    -1,     3,    -1,     5,     6,    -1,    53,     9,
      -1,    -1,    57,    58,    59,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
       3,    40,    41,     6,    -1,    35,     9,    10,    38,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    63,    -1,    -1,    57,    58,    59,
      -1,     3,    35,     5,     6,    38,    -1,     9,    -1,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    57,    58,    59,    -1,     3,    -1,
       5,     6,    -1,    35,     9,    -1,    38,    -1,    -1,    -1,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    57,    58,    59,    -1,     3,
      35,     5,     6,    38,    -1,     9,    -1,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    57,    58,    59,    -1,     3,    -1,     5,     6,
      -1,    35,     9,    -1,    38,    -1,    -1,    -1,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    57,    58,    59,    -1,     3,    35,     5,
       6,    38,    -1,     9,    -1,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      57,    58,    59,    -1,     3,    -1,     5,     6,    -1,    35,
       9,    -1,    38,    -1,    -1,    -1,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    57,    58,    59,    -1,     3,    35,     5,     6,    38,
      -1,     9,    -1,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    57,    58,
      59,    -1,     3,    -1,     5,     6,    -1,    35,     9,    -1,
      38,    -1,    -1,    -1,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    57,
      58,    59,    -1,     3,    35,     5,     6,    38,    -1,     9,
      -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,    58,    59,    -1,
       3,    -1,     5,     6,    -1,    35,     9,    -1,    38,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    57,    58,    59,
      -1,     3,    35,     5,     6,    38,    -1,     9,    -1,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    57,    58,    59,    -1,     3,    -1,
       5,     6,    -1,    35,     9,    -1,    38,    -1,    -1,    -1,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    57,    58,    59,    -1,     3,
      35,     5,     6,    38,    -1,     9,    -1,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    57,    58,    59,    -1,     3,    -1,     5,     6,
      -1,    35,     9,    -1,    38,    -1,    -1,    -1,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    57,    58,    59,    -1,     3,    35,     5,
       6,    38,    -1,     9,    -1,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      57,    58,    59,    -1,     3,    -1,     5,     6,    -1,    35,
       9,    -1,    38,    -1,    -1,    -1,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    57,    58,    59,    -1,    -1,    35,    -1,    -1,    38,
      -1,    -1,    -1,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    57,    58,
      59,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    40,    41,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    40,    41,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    40,    41,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    73,    74,    75,     3,     0,    75,     5,    47,
      53,    54,    76,    79,    80,     3,    77,     3,    69,    69,
      81,    82,     5,    77,    79,    80,     5,    53,    80,     5,
      54,    48,    49,    50,    51,    61,    70,    60,    42,    55,
      56,    62,    82,    61,    71,    72,    70,     5,    80,     5,
      69,     5,    81,     3,    78,    69,    69,    69,     3,    63,
      69,    83,    56,    83,    71,    84,     3,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    89,
      71,    61,     5,    52,     5,    49,    50,    51,    60,     5,
      50,    51,     5,    51,     5,    55,    56,    62,    62,    63,
      69,    84,    56,     3,     5,     6,     9,    35,    38,    42,
      43,    44,    45,    46,    53,    57,    58,    59,    85,    86,
      88,    66,    55,    56,     3,    69,    69,    69,     3,    69,
      69,    69,    56,    83,    84,    89,    89,    55,    56,    62,
      62,     5,    84,    24,    42,    42,    84,     3,    88,    88,
      88,     3,    41,    41,    42,    64,    71,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      40,    41,    89,    56,    83,    84,     5,    50,    51,     5,
      51,     5,    52,     5,    51,     5,     5,    84,    56,     5,
      55,    56,    70,    56,    83,    84,    89,    89,     5,    88,
      63,    87,    88,    88,    10,    63,    41,     3,     3,    63,
      87,     3,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,     3,    67,    84,    56,
       5,    69,    69,    69,     3,    69,     5,    84,    56,    83,
      84,    84,    56,     5,    55,    56,    70,    60,    63,    63,
      88,    41,     3,    42,    42,    63,    65,    42,     5,    84,
       5,    51,     5,     5,     5,     5,    84,    56,     5,     5,
      84,    56,    83,    84,    88,     7,    11,     3,    42,    63,
      87,    63,    87,    42,    87,     5,    69,     5,    84,     5,
      84,    56,     5,    84,    84,    42,    87,    63,    63,    63,
      87,    63,     5,     5,     5,    84,     5,     8,     5,    63,
      87,    63,    63,     5,    84,    63,     5
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
#line 167 "bison.y"
    { (yyval.identifiers_comma_seq_field) = create_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (1)].id_field)); ;}
    break;

  case 3:
#line 168 "bison.y"
    { (yyval.identifiers_comma_seq_field) = append_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 10:
#line 184 "bison.y"
    { (yyval.program_field) = create_program(curr_node_index++, (yyvsp[(1) - (1)].class_decl_seq_field)); tree_root = (yyval.program_field); ;}
    break;

  case 11:
#line 187 "bison.y"
    { (yyval.class_decl_seq_field) = create_class_decl_seq(curr_node_index++, (yyvsp[(1) - (1)].class_decl_field)); ;}
    break;

  case 12:
#line 188 "bison.y"
    { (yyval.class_decl_seq_field) = append_class_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].class_decl_seq_field), (yyvsp[(2) - (2)].class_decl_field)); ;}
    break;

  case 13:
#line 192 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(3) - (6)].parent_seq_field), (yyvsp[(4) - (6)].creators_seq_field), (yyvsp[(5) - (6)].features_seq_field)); ;}
    break;

  case 14:
#line 193 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), (yyvsp[(3) - (5)].parent_seq_field), (yyvsp[(4) - (5)].creators_seq_field), NULL); ;}
    break;

  case 15:
#line 194 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), (yyvsp[(3) - (5)].parent_seq_field), NULL, (yyvsp[(4) - (5)].features_seq_field)); ;}
    break;

  case 16:
#line 195 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), (yyvsp[(3) - (4)].parent_seq_field), NULL, NULL); ;}
    break;

  case 17:
#line 197 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), NULL, (yyvsp[(3) - (5)].creators_seq_field), (yyvsp[(4) - (5)].features_seq_field)); ;}
    break;

  case 18:
#line 198 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), NULL, (yyvsp[(3) - (4)].creators_seq_field), NULL); ;}
    break;

  case 19:
#line 199 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), NULL, NULL, (yyvsp[(3) - (4)].features_seq_field)); ;}
    break;

  case 20:
#line 200 "bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (3)].id_field), NULL, NULL, NULL); ;}
    break;

  case 21:
#line 204 "bison.y"
    { (yyval.parent_seq_field) = create_parent_seq(curr_node_index++, (yyvsp[(2) - (3)].parent_field)); ;}
    break;

  case 22:
#line 205 "bison.y"
    { (yyval.parent_seq_field) = append_parent_seq(curr_node_index++, (yyvsp[(1) - (3)].parent_seq_field), (yyvsp[(2) - (3)].parent_field)); ;}
    break;

  case 23:
#line 208 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (10)].id_field), (yyvsp[(3) - (10)].rename_seq_field), (yyvsp[(5) - (10)].identifiers_comma_seq_field), (yyvsp[(7) - (10)].identifiers_comma_seq_field), (yyvsp[(9) - (10)].identifiers_comma_seq_field)); ;}
    break;

  case 24:
#line 209 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), NULL, (yyvsp[(3) - (8)].identifiers_comma_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 25:
#line 210 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), NULL, (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 26:
#line 211 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 27:
#line 213 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), NULL, (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 28:
#line 214 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 29:
#line 215 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), NULL, NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 30:
#line 216 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, NULL, NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field)); ;}
    break;

  case 31:
#line 218 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 32:
#line 219 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 33:
#line 220 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 34:
#line 221 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 35:
#line 223 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL, NULL); ;}
    break;

  case 36:
#line 224 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field), NULL, NULL); ;}
    break;

  case 37:
#line 225 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), (yyvsp[(3) - (4)].rename_seq_field), NULL, NULL, NULL); ;}
    break;

  case 38:
#line 226 "bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (1)].id_field), NULL, NULL, NULL, NULL); ;}
    break;

  case 39:
#line 229 "bison.y"
    { (yyval.rename_seq_field) = create_rename_seq(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 40:
#line 230 "bison.y"
    { (yyval.rename_seq_field) = append_rename_seq(curr_node_index++, (yyvsp[(1) - (5)].rename_seq_field), (yyvsp[(3) - (5)].id_field), (yyvsp[(5) - (5)].id_field)); ;}
    break;

  case 41:
#line 234 "bison.y"
    { (yyval.creators_seq_field) = create_creators_seq(curr_node_index++, (yyvsp[(2) - (2)].identifiers_comma_seq_field)); ;}
    break;

  case 42:
#line 235 "bison.y"
    { (yyval.creators_seq_field) = append_creators_seq(curr_node_index++, (yyvsp[(1) - (3)].creators_seq_field), (yyvsp[(3) - (3)].identifiers_comma_seq_field)); ;}
    break;

  case 43:
#line 239 "bison.y"
    { (yyval.features_seq_field) = create_features_seq(curr_node_index++, (yyvsp[(2) - (2)].feature_decl_seq_field)); ;}
    break;

  case 44:
#line 240 "bison.y"
    { (yyval.features_seq_field) = append_features_seq(curr_node_index++, (yyvsp[(1) - (3)].features_seq_field), (yyvsp[(3) - (3)].feature_decl_seq_field)); ;}
    break;

  case 45:
#line 243 "bison.y"
    { (yyval.feature_decl_seq_field) = create_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].feature_decl_field)); ;}
    break;

  case 46:
#line 244 "bison.y"
    { (yyval.feature_decl_seq_field) = append_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (3)].feature_decl_seq_field), (yyvsp[(2) - (3)].feature_decl_field)); ;}
    break;

  case 47:
#line 247 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].type_field), NULL, NULL, NULL); ;}
    break;

  case 48:
#line 249 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(3) - (4)].instruction_seq_field)); ;}
    break;

  case 49:
#line 250 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (5)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(4) - (5)].instruction_seq_field)); ;}
    break;

  case 50:
#line 251 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(3) - (6)].ids_with_type_seq_field), (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 51:
#line 253 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 52:
#line 254 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 53:
#line 255 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(5) - (8)].ids_with_type_seq_field), (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 54:
#line 257 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), (yyvsp[(3) - (6)].type_field), NULL, NULL, (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 55:
#line 258 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), (yyvsp[(3) - (7)].type_field), NULL, NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 56:
#line 259 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), (yyvsp[(3) - (8)].type_field), NULL, (yyvsp[(5) - (8)].ids_with_type_seq_field), (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 57:
#line 261 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), (yyvsp[(5) - (8)].type_field), NULL, NULL, (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 58:
#line 262 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), (yyvsp[(5) - (9)].type_field), NULL, NULL, (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 59:
#line 263 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (10)].identifiers_comma_seq_field), (yyvsp[(5) - (10)].type_field), NULL, (yyvsp[(7) - (10)].ids_with_type_seq_field), (yyvsp[(9) - (10)].instruction_seq_field)); ;}
    break;

  case 60:
#line 265 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (7)].ids_with_type_seq_field), NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 61:
#line 266 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (8)].ids_with_type_seq_field), NULL, (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 62:
#line 267 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (9)].ids_with_type_seq_field), (yyvsp[(6) - (9)].ids_with_type_seq_field), (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 63:
#line 269 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), (yyvsp[(6) - (9)].type_field), (yyvsp[(3) - (9)].ids_with_type_seq_field), NULL, (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 64:
#line 270 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (10)].identifiers_comma_seq_field), (yyvsp[(6) - (10)].type_field), (yyvsp[(3) - (10)].ids_with_type_seq_field), NULL, (yyvsp[(9) - (10)].instruction_seq_field)); ;}
    break;

  case 65:
#line 271 "bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (11)].identifiers_comma_seq_field), (yyvsp[(6) - (11)].type_field), (yyvsp[(3) - (11)].ids_with_type_seq_field), (yyvsp[(8) - (11)].ids_with_type_seq_field), (yyvsp[(10) - (11)].instruction_seq_field)); ;}
    break;

  case 66:
#line 274 "bison.y"
    { (yyval.ids_with_type_seq_field) = create_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), (yyvsp[(3) - (4)].type_field)); ;}
    break;

  case 67:
#line 275 "bison.y"
    { (yyval.ids_with_type_seq_field) = append_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (5)].ids_with_type_seq_field), (yyvsp[(2) - (5)].identifiers_comma_seq_field), (yyvsp[(4) - (5)].type_field)); ;}
    break;

  case 68:
#line 278 "bison.y"
    { (yyval.instruction_seq_field) = create_instruction_seq(curr_node_index++, NULL); ;}
    break;

  case 69:
#line 279 "bison.y"
    { (yyval.instruction_seq_field) = append_instruction_seq(curr_node_index++, (yyvsp[(1) - (3)].instruction_seq_field), (yyvsp[(2) - (3)].instruction_field)); ;}
    break;

  case 70:
#line 282 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (2)].id_field), NULL, NULL); ;}
    break;

  case 71:
#line 283 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (4)].id_field), (yyvsp[(4) - (4)].id_field), NULL); ;}
    break;

  case 72:
#line 284 "bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (7)].id_field), (yyvsp[(4) - (7)].id_field), (yyvsp[(6) - (7)].argument_seq_field)); ;}
    break;

  case 73:
#line 286 "bison.y"
    { (yyval.instruction_field) = create_assign_instruction(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 74:
#line 288 "bison.y"
    { (yyval.instruction_field) = create_if_instruction(curr_node_index++, (yyvsp[(3) - (7)].expr_field), (yyvsp[(6) - (7)].instruction_seq_field), NULL); ;}
    break;

  case 75:
#line 289 "bison.y"
    { (yyval.instruction_field) = create_if_instruction(curr_node_index++, (yyvsp[(3) - (9)].expr_field), (yyvsp[(6) - (9)].instruction_seq_field), (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 76:
#line 290 "bison.y"
    { (yyval.instruction_field) = create_loop_instruction(curr_node_index++, (yyvsp[(2) - (7)].instruction_seq_field), (yyvsp[(4) - (7)].expr_field), (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 77:
#line 292 "bison.y"
    { (yyval.instruction_field) = create_instruction_as_expr(curr_node_index++, (yyvsp[(1) - (1)].expr_field)); ;}
    break;

  case 78:
#line 295 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_method_or_var, (yyvsp[(1) - (1)].id_field), NULL, NULL); ;}
    break;

  case 79:
#line 296 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_method, (yyvsp[(1) - (3)].id_field), NULL, NULL); ;}
    break;

  case 80:
#line 297 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_method, (yyvsp[(1) - (4)].id_field), (yyvsp[(3) - (4)].argument_seq_field), NULL); ;}
    break;

  case 81:
#line 299 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_current, (yyvsp[(3) - (3)].id_field), NULL, NULL); ;}
    break;

  case 82:
#line 300 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_current, (yyvsp[(3) - (5)].id_field), NULL, NULL); ;}
    break;

  case 83:
#line 301 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_current, (yyvsp[(3) - (6)].id_field), (yyvsp[(5) - (6)].argument_seq_field), NULL); ;}
    break;

  case 84:
#line 303 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_result, (yyvsp[(3) - (3)].id_field), NULL, NULL); ;}
    break;

  case 85:
#line 304 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_result, (yyvsp[(3) - (5)].id_field), NULL, NULL); ;}
    break;

  case 86:
#line 305 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_result, (yyvsp[(3) - (6)].id_field), (yyvsp[(5) - (6)].argument_seq_field), NULL); ;}
    break;

  case 87:
#line 307 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_parenthesized_expr, (yyvsp[(5) - (5)].id_field), NULL, (yyvsp[(2) - (5)].expr_field)); ;}
    break;

  case 88:
#line 308 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_parenthesized_expr, (yyvsp[(5) - (7)].id_field), NULL, (yyvsp[(2) - (7)].expr_field)); ;}
    break;

  case 89:
#line 309 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_parenthesized_expr, (yyvsp[(5) - (8)].id_field), (yyvsp[(7) - (8)].argument_seq_field), (yyvsp[(2) - (8)].expr_field)); ;}
    break;

  case 90:
#line 311 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_precursor, NULL, NULL, NULL); ;}
    break;

  case 91:
#line 312 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_precursor, NULL, NULL, NULL); ;}
    break;

  case 92:
#line 313 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_precursor, NULL, (yyvsp[(3) - (4)].argument_seq_field), NULL); ;}
    break;

  case 93:
#line 314 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_precursor, (yyvsp[(3) - (4)].id_field), NULL, NULL); ;}
    break;

  case 94:
#line 315 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_precursor, (yyvsp[(3) - (6)].id_field), NULL, NULL); ;}
    break;

  case 95:
#line 316 "bison.y"
    { (yyval.call_field) = create_call(curr_node_index++, call_precursor, (yyvsp[(3) - (7)].id_field), (yyvsp[(6) - (7)].argument_seq_field), NULL); ;}
    break;

  case 96:
#line 319 "bison.y"
    { (yyval.argument_seq_field) = create_argument_seq(curr_node_index++, (yyvsp[(1) - (1)].expr_field)); ;}
    break;

  case 97:
#line 320 "bison.y"
    { (yyval.argument_seq_field) = append_argument_seq(curr_node_index++, (yyvsp[(1) - (3)].argument_seq_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 98:
#line 323 "bison.y"
    { (yyval.expr_field) = (yyvsp[(2) - (3)].expr_field); ;}
    break;

  case 99:
#line 324 "bison.y"
    { (yyval.expr_field) = create_expr_liter_bool(curr_node_index++, (yyvsp[(1) - (1)].liter_boolean_field)); ;}
    break;

  case 100:
#line 325 "bison.y"
    { (yyval.expr_field) = create_expr_liter_int (curr_node_index++, (yyvsp[(1) - (1)].liter_integer_field)); ;}
    break;

  case 101:
#line 326 "bison.y"
    { (yyval.expr_field) = create_expr_liter_char(curr_node_index++, (yyvsp[(1) - (1)].liter_char_field)); ;}
    break;

  case 102:
#line 327 "bison.y"
    { (yyval.expr_field) = create_expr_liter_str (curr_node_index++, (yyvsp[(1) - (1)].liter_string_field)); ;}
    break;

  case 103:
#line 329 "bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, (yyvsp[(1) - (1)].call_field)); ;}
    break;

  case 104:
#line 330 "bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].id_field), NULL); ;}
    break;

  case 105:
#line 331 "bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (6)].expr_field), (yyvsp[(3) - (6)].id_field), (yyvsp[(5) - (6)].argument_seq_field)); ;}
    break;

  case 106:
#line 332 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_arrelem, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 107:
#line 334 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_plus, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 108:
#line 335 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_bminus, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 109:
#line 336 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_mul, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 110:
#line 337 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_idiv, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 111:
#line 338 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_uminus, NULL, (yyvsp[(2) - (2)].expr_field)); ;}
    break;

  case 112:
#line 340 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_less, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 113:
#line 341 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_great, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 114:
#line 342 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_less_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 115:
#line 343 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_great_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 116:
#line 344 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 117:
#line 345 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_notequal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 118:
#line 347 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_and, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 119:
#line 348 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_or, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 120:
#line 349 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_xor, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 121:
#line 350 "bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_not, NULL, (yyvsp[(2) - (2)].expr_field)); ;}
    break;

  case 122:
#line 354 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_user_defined, (yyvsp[(1) - (1)].id_field), NULL); ;}
    break;

  case 123:
#line 355 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_boolean, NULL, NULL); ;}
    break;

  case 124:
#line 356 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_character, NULL, NULL); ;}
    break;

  case 125:
#line 357 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_8,  NULL, NULL); ;}
    break;

  case 126:
#line 358 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_16, NULL, NULL); ;}
    break;

  case 127:
#line 359 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_32, NULL, NULL); ;}
    break;

  case 128:
#line 360 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer_64, NULL, NULL); ;}
    break;

  case 129:
#line 361 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_8,  NULL, NULL); ;}
    break;

  case 130:
#line 362 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_16, NULL, NULL); ;}
    break;

  case 131:
#line 363 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_32, NULL, NULL); ;}
    break;

  case 132:
#line 364 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural_64, NULL, NULL); ;}
    break;

  case 133:
#line 365 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_string, NULL, NULL); ;}
    break;

  case 134:
#line 366 "bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_array, NULL, (yyvsp[(3) - (4)].type_field)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2560 "bison.tab.c"
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


#line 369 "bison.y"


