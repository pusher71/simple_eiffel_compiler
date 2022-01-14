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
     CONSOLEIO = 267,
     DATATYPE_BOOLEAN = 268,
     DATATYPE_CHARACTER = 269,
     DATATYPE_INTEGER = 270,
     DATATYPE_NATURAL = 271,
     DATATYPE_STRING = 272,
     DATATYPE_ARRAY = 273,
     ASSIGNMENT = 274,
     XOR = 275,
     OR = 276,
     AND = 277,
     NOTEQUAL = 278,
     GREAT_EQUAL = 279,
     LESS_EQUAL = 280,
     MOD_DIVISION = 281,
     INTEGER_DIVISION = 282,
     NOT = 283,
     UMINUS = 284,
     LITER_BOOLEAN = 285,
     LITER_INTEGER = 286,
     LITER_CHAR = 287,
     LITER_STRING = 288,
     LITER_VOID = 289,
     INHERIT = 290,
     RENAME = 291,
     UNDEFINE = 292,
     REDEFINE = 293,
     SELECT = 294,
     AS = 295,
     CREATE = 296,
     FEATURE = 297,
     LOCAL = 298,
     DO = 299,
     CURRENT = 300,
     RESULT = 301,
     PRECURSOR = 302
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
#define CONSOLEIO 267
#define DATATYPE_BOOLEAN 268
#define DATATYPE_CHARACTER 269
#define DATATYPE_INTEGER 270
#define DATATYPE_NATURAL 271
#define DATATYPE_STRING 272
#define DATATYPE_ARRAY 273
#define ASSIGNMENT 274
#define XOR 275
#define OR 276
#define AND 277
#define NOTEQUAL 278
#define GREAT_EQUAL 279
#define LESS_EQUAL 280
#define MOD_DIVISION 281
#define INTEGER_DIVISION 282
#define NOT 283
#define UMINUS 284
#define LITER_BOOLEAN 285
#define LITER_INTEGER 286
#define LITER_CHAR 287
#define LITER_STRING 288
#define LITER_VOID 289
#define INHERIT 290
#define RENAME 291
#define UNDEFINE 292
#define REDEFINE 293
#define SELECT 294
#define AS 295
#define CREATE 296
#define FEATURE 297
#define LOCAL 298
#define DO 299
#define CURRENT 300
#define RESULT 301
#define PRECURSOR 302




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
    long long   liter_integer_field;
    char        liter_char_field;
    CharArray*  liter_string_field;

    char*       id_field;
}
/* Line 193 of yacc.c.  */
#line 248 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/bison/parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 261 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/bison/parser.c"

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
#define YYLAST   974

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNRULES -- Number of states.  */
#define YYNSTATES  282

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    60,    31,    29,    57,    30,    37,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    58,
      23,    25,    24,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,    64,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    26,    27,
      28,    32,    33,    34,    35,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    10,    12,    13,    15,    17,
      20,    22,    24,    27,    35,    42,    49,    55,    61,    66,
      71,    75,    78,    82,    91,    98,   105,   110,   117,   122,
     127,   129,   133,   139,   142,   146,   149,   153,   156,   160,
     164,   169,   175,   182,   189,   197,   206,   213,   221,   230,
     239,   249,   260,   268,   277,   287,   297,   308,   320,   325,
     331,   333,   335,   337,   339,   341,   343,   348,   350,   354,
     357,   362,   369,   377,   381,   389,   399,   407,   409,   411,
     415,   417,   419,   421,   423,   425,   429,   431,   433,   437,
     442,   444,   448,   453,   458,   465,   473,   477,   483,   490,
     495,   502,   511,   521,   525,   529,   533,   537,   541,   545,
     548,   552,   556,   560,   564,   568,   572,   576,   580,   584
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,     3,    -1,    66,    57,     3,    -1,    -1,
      58,    -1,    -1,    69,    -1,    58,    -1,    69,    58,    -1,
      71,    -1,    72,    -1,    71,    72,    -1,     4,     3,    44,
      73,    76,    77,     5,    -1,     4,     3,    44,    73,    76,
       5,    -1,     4,     3,    44,    73,    77,     5,    -1,     4,
       3,    44,    73,     5,    -1,     4,     3,    76,    77,     5,
      -1,     4,     3,    76,     5,    -1,     4,     3,    77,     5,
      -1,     4,     3,     5,    -1,    74,    67,    -1,    73,    74,
      67,    -1,     3,    45,    75,    47,    66,    48,    66,     5,
      -1,     3,    47,    66,    48,    66,     5,    -1,     3,    45,
      75,    48,    66,     5,    -1,     3,    48,    66,     5,    -1,
       3,    45,    75,    47,    66,     5,    -1,     3,    47,    66,
       5,    -1,     3,    45,    75,     5,    -1,     3,    -1,     3,
      49,     3,    -1,    75,    57,     3,    49,     3,    -1,    50,
      66,    -1,    76,    50,    66,    -1,    51,    78,    -1,    77,
      51,    78,    -1,    79,    68,    -1,    78,    79,    68,    -1,
      66,    59,    81,    -1,    66,    53,    82,     5,    -1,    66,
      52,    53,    82,     5,    -1,    66,    52,    80,    53,    82,
       5,    -1,    66,    38,    60,    53,    82,     5,    -1,    66,
      38,    60,    52,    53,    82,     5,    -1,    66,    38,    60,
      52,    80,    53,    82,     5,    -1,    66,    59,    81,    53,
      82,     5,    -1,    66,    59,    81,    52,    53,    82,     5,
      -1,    66,    59,    81,    52,    80,    53,    82,     5,    -1,
      66,    38,    60,    59,    81,    53,    82,     5,    -1,    66,
      38,    60,    59,    81,    52,    53,    82,     5,    -1,    66,
      38,    60,    59,    81,    52,    80,    53,    82,     5,    -1,
      66,    38,    80,    60,    53,    82,     5,    -1,    66,    38,
      80,    60,    52,    53,    82,     5,    -1,    66,    38,    80,
      60,    52,    80,    53,    82,     5,    -1,    66,    38,    80,
      60,    59,    81,    53,    82,     5,    -1,    66,    38,    80,
      60,    59,    81,    52,    53,    82,     5,    -1,    66,    38,
      80,    60,    59,    81,    52,    80,    53,    82,     5,    -1,
      66,    59,    81,    67,    -1,    80,    66,    59,    81,    67,
      -1,     3,    -1,    13,    -1,    14,    -1,    15,    -1,    16,
      -1,    17,    -1,    18,    61,    81,    62,    -1,    68,    -1,
      82,    83,    68,    -1,    50,     3,    -1,    50,     3,    37,
       3,    -1,    50,     3,    37,     3,    38,    60,    -1,    50,
       3,    37,     3,    38,    84,    60,    -1,     3,    19,    85,
      -1,     6,    38,    85,    60,     7,    82,     5,    -1,     6,
      38,    85,    60,     7,    82,     8,    82,     5,    -1,     9,
      82,    10,    85,    11,    82,     5,    -1,    85,    -1,    85,
      -1,    84,    57,    85,    -1,    39,    -1,    40,    -1,    41,
      -1,    42,    -1,    43,    -1,    38,    85,    60,    -1,    54,
      -1,     3,    -1,     3,    38,    60,    -1,     3,    38,    84,
      60,    -1,    56,    -1,    56,    38,    60,    -1,    56,    38,
      84,    60,    -1,    56,    63,     3,    64,    -1,    56,    63,
       3,    64,    38,    60,    -1,    56,    63,     3,    64,    38,
      84,    60,    -1,    85,    37,     3,    -1,    85,    37,     3,
      38,    60,    -1,    85,    37,     3,    38,    84,    60,    -1,
      50,    63,    81,    64,    -1,    50,    63,    81,    64,    37,
       3,    -1,    50,    63,    81,    64,    37,     3,    38,    60,
      -1,    50,    63,    81,    64,    37,     3,    38,    84,    60,
      -1,    85,    36,    85,    -1,    85,    29,    85,    -1,    85,
      30,    85,    -1,    85,    31,    85,    -1,    85,    33,    85,
      -1,    85,    32,    85,    -1,    30,    85,    -1,    85,    23,
      85,    -1,    85,    24,    85,    -1,    85,    28,    85,    -1,
      85,    27,    85,    -1,    85,    25,    85,    -1,    85,    26,
      85,    -1,    85,    22,    85,    -1,    85,    21,    85,    -1,
      85,    20,    85,    -1,    34,    85,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   161,   161,   162,   165,   166,   169,   170,   173,   174,
     178,   181,   182,   186,   187,   188,   189,   191,   192,   193,
     194,   198,   199,   202,   203,   204,   205,   207,   208,   209,
     210,   213,   214,   218,   219,   223,   224,   227,   228,   231,
     233,   234,   235,   237,   238,   239,   241,   242,   243,   245,
     246,   247,   249,   250,   251,   253,   254,   255,   258,   259,
     262,   263,   264,   265,   266,   267,   268,   271,   272,   275,
     276,   277,   278,   280,   282,   283,   284,   286,   289,   290,
     293,   294,   295,   296,   297,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   314,
     315,   316,   317,   319,   320,   321,   322,   323,   324,   325,
     327,   328,   329,   330,   331,   332,   334,   335,   336,   337
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CLASS", "END", "IF", "THEN",
  "ELSE", "FROM", "UNTIL", "LOOP", "CONSOLEIO", "DATATYPE_BOOLEAN",
  "DATATYPE_CHARACTER", "DATATYPE_INTEGER", "DATATYPE_NATURAL",
  "DATATYPE_STRING", "DATATYPE_ARRAY", "ASSIGNMENT", "XOR", "OR", "AND",
  "'<'", "'>'", "'='", "NOTEQUAL", "GREAT_EQUAL", "LESS_EQUAL", "'+'",
  "'-'", "'*'", "MOD_DIVISION", "INTEGER_DIVISION", "NOT", "UMINUS", "'@'",
  "'.'", "'('", "LITER_BOOLEAN", "LITER_INTEGER", "LITER_CHAR",
  "LITER_STRING", "LITER_VOID", "INHERIT", "RENAME", "UNDEFINE",
  "REDEFINE", "SELECT", "AS", "CREATE", "FEATURE", "LOCAL", "DO",
  "CURRENT", "RESULT", "PRECURSOR", "','", "';'", "':'", "')'", "'['",
  "']'", "'{'", "'}'", "$accept", "identifiers_comma_seq", "opt_semicolon",
  "opt_semicolon_seq", "nonempty_opt_semicolon_seq", "program",
  "class_decl_seq", "class_decl", "parent_seq", "parent", "rename_seq",
  "creators_seq", "features_seq", "feature_decl_seq", "feature_decl",
  "ids_with_type_seq", "type", "instruction_seq", "instruction",
  "argument_seq", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    60,    62,    61,   278,   279,   280,    43,
      45,    42,   281,   282,   283,   284,    64,    46,    40,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,    44,    59,    58,
      41,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     0,     1,     0,     1,     1,     2,
       1,     1,     2,     7,     6,     6,     5,     5,     4,     4,
       3,     2,     3,     8,     6,     6,     4,     6,     4,     4,
       1,     3,     5,     2,     3,     2,     3,     2,     3,     3,
       4,     5,     6,     6,     7,     8,     6,     7,     8,     8,
       9,    10,     7,     8,     9,     9,    10,    11,     4,     5,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     2,
       4,     6,     7,     3,     7,     9,     7,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     3,     4,
       1,     3,     4,     4,     6,     7,     3,     5,     6,     4,
       6,     8,     9,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    10,    11,     0,     1,    12,    20,     0,
       0,     0,     0,     0,    30,     0,     4,     2,    33,     0,
      35,     6,    18,     0,     0,    19,     0,     0,     0,     0,
      16,     4,     0,     0,     5,    21,     0,     0,     0,     6,
       0,     6,     8,    37,     7,    34,    17,    36,     0,     0,
       0,     0,    22,    14,     0,    15,     3,     0,     0,     0,
       6,     0,    67,     0,    60,    61,    62,    63,    64,    65,
       0,    39,    38,     9,     0,    29,     0,     0,     0,    28,
       0,    26,    13,     0,     6,     0,     0,     0,     0,     0,
       6,    87,    40,     0,     6,     0,     0,     0,    80,    81,
      82,    83,    84,     0,    86,    90,     6,    77,     0,     0,
       6,    31,     0,     0,     0,     0,     6,     0,     0,     0,
       4,     0,     6,     0,     0,    41,     0,     0,     0,     0,
       0,    87,     0,   109,   119,     0,    69,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       0,    27,     0,    25,     0,    24,     0,     6,    43,     0,
       6,    58,     6,     0,     0,     0,     4,    42,    73,    88,
       0,    78,     0,     0,    85,     0,     0,    91,     0,     0,
     118,   117,   116,   110,   111,   114,   115,   113,   112,   104,
     105,   106,   108,   107,   103,    96,    66,     0,     6,    46,
       0,    32,    44,     0,     6,     0,     0,     0,     6,    52,
       0,     6,    59,     0,    89,     0,     0,    70,    99,    92,
      93,     0,    47,     0,    23,    45,     0,     6,    49,    53,
       0,     6,     0,     0,    79,     6,     6,     0,     0,     0,
      97,     0,    48,    50,     0,    54,     0,     6,    55,     0,
       0,    71,     0,   100,    94,     0,    98,    51,    56,     0,
      74,     6,    76,    72,     0,    95,    57,     0,   101,     0,
      75,   102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    58,    35,    62,    44,     2,     3,     4,    15,    16,
      49,    12,    13,    20,    21,    59,    71,    63,   106,   180,
     107
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -127
static const yytype_int16 yypact[] =
{
      20,    49,    39,    20,  -127,   107,  -127,  -127,  -127,   111,
     114,   114,   127,    36,   -20,   135,    71,  -127,    93,   304,
     114,    98,  -127,   114,   104,  -127,   114,   173,   114,   114,
    -127,    71,   130,   121,  -127,  -127,   179,     5,    26,    98,
     878,    98,  -127,  -127,   110,    93,  -127,   114,   145,     6,
       0,     4,  -127,  -127,   138,  -127,  -127,    75,   228,    11,
      98,    28,  -127,   349,  -127,  -127,  -127,  -127,  -127,  -127,
     153,    72,  -127,  -127,   220,  -127,   114,   114,   224,  -127,
     114,  -127,  -127,    29,    98,   878,   878,    94,   229,   372,
      98,   103,  -127,   190,    98,   792,   792,   792,  -127,  -127,
    -127,  -127,  -127,     1,  -127,   -17,    98,   906,   878,    30,
      98,  -127,     2,    15,   182,    17,    98,    31,   391,    92,
      71,    55,    98,   878,   878,  -127,   414,   792,   170,   792,
     433,   212,   191,   165,   165,   829,   216,   878,   195,   259,
    -127,   792,   792,   792,   792,   792,   792,   792,   792,   792,
     792,   792,   792,   792,   792,   792,   260,   211,    98,    57,
     456,  -127,   114,  -127,   273,  -127,   475,    98,  -127,    66,
      98,  -127,    98,    77,   498,   154,    71,  -127,   906,  -127,
      82,   906,   847,   792,  -127,   274,   225,  -127,   109,   232,
     922,   922,   937,   210,   210,   210,   210,   210,   210,   233,
     233,   165,   165,   165,   255,   261,  -127,   517,    98,  -127,
      21,  -127,  -127,   540,    98,   108,   559,   582,    98,  -127,
     112,    98,  -127,   792,  -127,   286,   888,   262,   271,  -127,
     272,   218,  -127,   601,  -127,  -127,   624,    98,  -127,  -127,
     643,    98,   117,   666,   906,    98,    98,   241,   306,   264,
    -127,   133,  -127,  -127,   685,  -127,   708,    98,  -127,   330,
     727,  -127,   139,   275,  -127,   158,  -127,  -127,  -127,   750,
    -127,    98,  -127,  -127,   287,  -127,  -127,   769,  -127,   159,
    -127,  -127
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,   -10,   -14,   -18,  -127,  -127,  -127,   308,  -127,   297,
    -127,   300,    23,   290,    -5,   -36,    51,   -54,  -127,  -126,
     -52
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      18,    19,    61,    43,   136,    79,    89,   161,    17,    81,
      19,    75,   188,    45,    17,    41,    19,    52,    50,    51,
     163,   138,   165,    72,     1,    27,   234,    28,    29,    17,
     118,    17,    17,    17,    17,    24,   126,    19,    33,     6,
     130,    25,    41,   133,   134,   135,   139,   117,    80,    88,
     162,    88,     5,    76,    77,    54,   160,    36,    17,    36,
      17,    36,   166,    78,   137,    57,   112,   113,   174,    17,
     115,    87,    36,   159,    36,   178,   181,   182,    36,    60,
      17,    90,   116,   158,   167,   173,   181,    26,   140,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   207,   251,   171,    88,   172,    46,
     208,    17,     8,   213,    14,    17,   216,    17,   217,   214,
      17,   262,   127,   265,   109,   110,    55,    83,    84,    34,
     218,   226,    22,   215,    85,    53,   119,   120,    14,   223,
      30,   128,   224,    82,   169,   170,   121,   122,   279,    88,
      36,     9,   210,   123,   233,    26,    42,    10,    11,   157,
     236,   237,   222,    88,   240,   241,   223,   243,    73,   229,
     257,   244,    26,   131,   175,   176,    48,    23,    11,   181,
      23,    11,    56,   254,   242,    10,    11,   256,   186,    26,
     223,   259,   260,   266,    74,   181,   223,   181,   131,   273,
      95,   155,   156,   269,    96,    88,   220,   221,    97,    98,
      99,   100,   101,   102,   108,   223,   223,   277,   275,   281,
     132,   131,   181,   111,   104,    95,   105,   114,   129,    96,
     179,   164,    88,    97,    98,    99,   100,   101,   102,   150,
     151,   152,   153,   154,   131,   132,   155,   156,    95,   104,
     128,   105,    96,   185,   137,   187,    97,    98,    99,   100,
     101,   102,   189,   205,   152,   153,   154,   131,   132,   155,
     156,    95,   104,   206,   105,    96,   211,   227,   250,    97,
      98,    99,   100,   101,   102,    36,    36,    86,   124,   228,
     131,   132,   156,   245,    95,   104,   230,   105,    96,   231,
     247,   261,    97,    98,    99,   100,   101,   102,   248,   263,
     249,     7,    31,   274,   132,    32,    47,    95,   104,     0,
     105,    96,     0,     0,   264,    97,    98,    99,   100,   101,
     102,     0,     0,    91,     0,   270,    93,   132,   271,    94,
       0,   104,    37,   105,     0,     0,     0,   278,     0,     0,
       0,     0,    91,     0,    92,    93,    38,    39,    94,     0,
      95,    36,     0,    40,    96,     0,     0,     0,    97,    98,
      99,   100,   101,   102,     0,    91,     0,   125,    93,    95,
     103,    94,     0,    96,   104,     0,   105,    97,    98,    99,
     100,   101,   102,     0,    91,     0,   168,    93,     0,   103,
      94,     0,    95,   104,     0,   105,    96,     0,     0,     0,
      97,    98,    99,   100,   101,   102,     0,    91,     0,   177,
      93,    95,   103,    94,     0,    96,   104,     0,   105,    97,
      98,    99,   100,   101,   102,     0,    91,     0,     0,    93,
       0,   103,    94,   183,    95,   104,     0,   105,    96,     0,
       0,     0,    97,    98,    99,   100,   101,   102,     0,    91,
       0,   209,    93,    95,   103,    94,     0,    96,   104,     0,
     105,    97,    98,    99,   100,   101,   102,     0,    91,     0,
     212,    93,     0,   103,    94,     0,    95,   104,     0,   105,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
       0,    91,     0,   219,    93,    95,   103,    94,     0,    96,
     104,     0,   105,    97,    98,    99,   100,   101,   102,     0,
      91,     0,   232,    93,     0,   103,    94,     0,    95,   104,
       0,   105,    96,     0,     0,     0,    97,    98,    99,   100,
     101,   102,     0,    91,     0,   235,    93,    95,   103,    94,
       0,    96,   104,     0,   105,    97,    98,    99,   100,   101,
     102,     0,    91,     0,   238,    93,     0,   103,    94,     0,
      95,   104,     0,   105,    96,     0,     0,     0,    97,    98,
      99,   100,   101,   102,     0,    91,     0,   239,    93,    95,
     103,    94,     0,    96,   104,     0,   105,    97,    98,    99,
     100,   101,   102,     0,    91,     0,   252,    93,     0,   103,
      94,     0,    95,   104,     0,   105,    96,     0,     0,     0,
      97,    98,    99,   100,   101,   102,     0,    91,     0,   253,
      93,    95,   103,    94,     0,    96,   104,     0,   105,    97,
      98,    99,   100,   101,   102,     0,    91,     0,   255,    93,
       0,   103,    94,     0,    95,   104,     0,   105,    96,     0,
       0,     0,    97,    98,    99,   100,   101,   102,     0,    91,
       0,   258,    93,    95,   103,    94,     0,    96,   104,     0,
     105,    97,    98,    99,   100,   101,   102,     0,    91,     0,
     267,    93,     0,   103,    94,     0,    95,   104,     0,   105,
      96,     0,     0,     0,    97,    98,    99,   100,   101,   102,
       0,    91,     0,   268,    93,    95,   103,    94,     0,    96,
     104,     0,   105,    97,    98,    99,   100,   101,   102,     0,
      91,     0,   272,    93,     0,   103,    94,     0,    95,   104,
       0,   105,    96,     0,     0,     0,    97,    98,    99,   100,
     101,   102,     0,    91,     0,   276,    93,    95,   103,    94,
       0,    96,   104,     0,   105,    97,    98,    99,   100,   101,
     102,     0,    91,     0,   280,    93,     0,   103,    94,     0,
      95,   104,     0,   105,    96,     0,     0,     0,    97,    98,
      99,   100,   101,   102,     0,   131,     0,     0,     0,    95,
     103,     0,     0,    96,   104,     0,   105,    97,    98,    99,
     100,   101,   102,     0,     0,     0,     0,     0,     0,   103,
       0,     0,    95,   104,     0,   105,    96,     0,     0,     0,
      97,    98,    99,   100,   101,   102,     0,     0,     0,     0,
       0,     0,   132,     0,     0,     0,   104,     0,   105,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,     0,     0,   155,   156,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,    64,     0,   155,   156,     0,     0,     0,     0,   184,
       0,    65,    66,    67,    68,    69,    70,     0,     0,   246,
       0,     0,     0,     0,     0,     0,     0,   225,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,     0,     0,   155,   156,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
       0,     0,   155,   156,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,     0,     0,   155,   156,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,     0,   155,   156
};

static const yytype_int16 yycheck[] =
{
      10,    11,    38,    21,     3,     5,    60,     5,     3,     5,
      20,     5,   138,    23,     3,    20,    26,    31,    28,    29,
       5,    38,     5,    41,     4,    45,     5,    47,    48,     3,
      84,     3,     3,     3,     3,    12,    90,    47,    15,     0,
      94,     5,    47,    95,    96,    97,    63,    83,    48,    59,
      48,    61,     3,    47,    48,    32,   110,    57,     3,    57,
       3,    57,   116,    57,    63,    60,    76,    77,   122,     3,
      80,    60,    57,   109,    57,   127,   128,   129,    57,    53,
       3,    53,    53,    53,    53,   121,   138,    51,   106,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   158,   231,   120,   117,    53,     5,
      53,     3,     5,   167,     3,     3,   170,     3,   172,    53,
       3,   247,    19,   249,    52,    53,     5,    52,    53,    58,
      53,   183,     5,   169,    59,     5,    85,    86,     3,    57,
       5,    38,    60,     5,    52,    53,    52,    53,   274,   159,
      57,    44,   162,    59,   208,    51,    58,    50,    51,   108,
     214,    53,   176,   173,   218,    53,    57,   221,    58,    60,
      53,   223,    51,     3,   123,   124,     3,    50,    51,   231,
      50,    51,     3,   237,   220,    50,    51,   241,   137,    51,
      57,   245,   246,    60,    49,   247,    57,   249,     3,    60,
      30,    36,    37,   257,    34,   215,    52,    53,    38,    39,
      40,    41,    42,    43,    61,    57,    57,   271,    60,    60,
      50,     3,   274,     3,    54,    30,    56,     3,    38,    34,
      60,    49,   242,    38,    39,    40,    41,    42,    43,    29,
      30,    31,    32,    33,     3,    50,    36,    37,    30,    54,
      38,    56,    34,    37,    63,    60,    38,    39,    40,    41,
      42,    43,     3,     3,    31,    32,    33,     3,    50,    36,
      37,    30,    54,    62,    56,    34,     3,     3,    60,    38,
      39,    40,    41,    42,    43,    57,    57,    59,    59,    64,
       3,    50,    37,     7,    30,    54,    64,    56,    34,    38,
      38,    60,    38,    39,    40,    41,    42,    43,    37,     3,
      38,     3,    15,    38,    50,    15,    26,    30,    54,    -1,
      56,    34,    -1,    -1,    60,    38,    39,    40,    41,    42,
      43,    -1,    -1,     3,    -1,     5,     6,    50,     8,     9,
      -1,    54,    38,    56,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,     3,    -1,     5,     6,    52,    53,     9,    -1,
      30,    57,    -1,    59,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    -1,     3,    -1,     5,     6,    30,
      50,     9,    -1,    34,    54,    -1,    56,    38,    39,    40,
      41,    42,    43,    -1,     3,    -1,     5,     6,    -1,    50,
       9,    -1,    30,    54,    -1,    56,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,     3,    -1,     5,
       6,    30,    50,     9,    -1,    34,    54,    -1,    56,    38,
      39,    40,    41,    42,    43,    -1,     3,    -1,    -1,     6,
      -1,    50,     9,    10,    30,    54,    -1,    56,    34,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,     3,
      -1,     5,     6,    30,    50,     9,    -1,    34,    54,    -1,
      56,    38,    39,    40,    41,    42,    43,    -1,     3,    -1,
       5,     6,    -1,    50,     9,    -1,    30,    54,    -1,    56,
      34,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,     3,    -1,     5,     6,    30,    50,     9,    -1,    34,
      54,    -1,    56,    38,    39,    40,    41,    42,    43,    -1,
       3,    -1,     5,     6,    -1,    50,     9,    -1,    30,    54,
      -1,    56,    34,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    -1,     3,    -1,     5,     6,    30,    50,     9,
      -1,    34,    54,    -1,    56,    38,    39,    40,    41,    42,
      43,    -1,     3,    -1,     5,     6,    -1,    50,     9,    -1,
      30,    54,    -1,    56,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    -1,     3,    -1,     5,     6,    30,
      50,     9,    -1,    34,    54,    -1,    56,    38,    39,    40,
      41,    42,    43,    -1,     3,    -1,     5,     6,    -1,    50,
       9,    -1,    30,    54,    -1,    56,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,     3,    -1,     5,
       6,    30,    50,     9,    -1,    34,    54,    -1,    56,    38,
      39,    40,    41,    42,    43,    -1,     3,    -1,     5,     6,
      -1,    50,     9,    -1,    30,    54,    -1,    56,    34,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,     3,
      -1,     5,     6,    30,    50,     9,    -1,    34,    54,    -1,
      56,    38,    39,    40,    41,    42,    43,    -1,     3,    -1,
       5,     6,    -1,    50,     9,    -1,    30,    54,    -1,    56,
      34,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      -1,     3,    -1,     5,     6,    30,    50,     9,    -1,    34,
      54,    -1,    56,    38,    39,    40,    41,    42,    43,    -1,
       3,    -1,     5,     6,    -1,    50,     9,    -1,    30,    54,
      -1,    56,    34,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    -1,     3,    -1,     5,     6,    30,    50,     9,
      -1,    34,    54,    -1,    56,    38,    39,    40,    41,    42,
      43,    -1,     3,    -1,     5,     6,    -1,    50,     9,    -1,
      30,    54,    -1,    56,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    -1,     3,    -1,    -1,    -1,    30,
      50,    -1,    -1,    34,    54,    -1,    56,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    30,    54,    -1,    56,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    54,    -1,    56,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    -1,    36,    37,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     3,    -1,    36,    37,    -1,    -1,    -1,    -1,    60,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    -1,    -1,    36,    37,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      -1,    -1,    36,    37,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    -1,    36,    37,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    70,    71,    72,     3,     0,    72,     5,    44,
      50,    51,    76,    77,     3,    73,    74,     3,    66,    66,
      78,    79,     5,    50,    77,     5,    51,    45,    47,    48,
       5,    74,    76,    77,    58,    67,    57,    38,    52,    53,
      59,    79,    58,    68,    69,    66,     5,    78,     3,    75,
      66,    66,    67,     5,    77,     5,     3,    60,    66,    80,
      53,    80,    68,    82,     3,    13,    14,    15,    16,    17,
      18,    81,    68,    58,    49,     5,    47,    48,    57,     5,
      48,     5,     5,    52,    53,    59,    59,    60,    66,    82,
      53,     3,     5,     6,     9,    30,    34,    38,    39,    40,
      41,    42,    43,    50,    54,    56,    83,    85,    61,    52,
      53,     3,    66,    66,     3,    66,    53,    80,    82,    81,
      81,    52,    53,    59,    59,     5,    82,    19,    38,    38,
      82,     3,    50,    85,    85,    85,     3,    63,    38,    63,
      68,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    36,    37,    81,    53,    80,
      82,     5,    48,     5,    49,     5,    82,    53,     5,    52,
      53,    67,    53,    80,    82,    81,    81,     5,    85,    60,
      84,    85,    85,    10,    60,    37,    81,    60,    84,     3,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,     3,    62,    82,    53,     5,
      66,     3,     5,    82,    53,    80,    82,    82,    53,     5,
      52,    53,    67,    57,    60,    60,    85,     3,    64,    60,
      64,    38,     5,    82,     5,     5,    82,    53,     5,     5,
      82,    53,    80,    82,    85,     7,    11,    38,    37,    38,
      60,    84,     5,     5,    82,     5,    82,    53,     5,    82,
      82,    60,    84,     3,    60,    84,    60,     5,     5,    82,
       5,     8,     5,    60,    38,    60,     5,    82,    60,    84,
       5,    60
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
#line 161 "src/bison/bison.y"
    { (yyval.identifiers_comma_seq_field) = create_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (1)].id_field)); ;}
    break;

  case 3:
#line 162 "src/bison/bison.y"
    { (yyval.identifiers_comma_seq_field) = append_identifiers_comma_seq(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 10:
#line 178 "src/bison/bison.y"
    { (yyval.program_field) = create_program(curr_node_index++, (yyvsp[(1) - (1)].class_decl_seq_field)); tree_root = (yyval.program_field); ;}
    break;

  case 11:
#line 181 "src/bison/bison.y"
    { (yyval.class_decl_seq_field) = create_class_decl_seq(curr_node_index++, (yyvsp[(1) - (1)].class_decl_field)); ;}
    break;

  case 12:
#line 182 "src/bison/bison.y"
    { (yyval.class_decl_seq_field) = append_class_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].class_decl_seq_field), (yyvsp[(2) - (2)].class_decl_field)); ;}
    break;

  case 13:
#line 186 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (7)].id_field), (yyvsp[(4) - (7)].parent_seq_field), (yyvsp[(5) - (7)].creators_seq_field), (yyvsp[(6) - (7)].features_seq_field)); ;}
    break;

  case 14:
#line 187 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(4) - (6)].parent_seq_field), (yyvsp[(5) - (6)].creators_seq_field), NULL); ;}
    break;

  case 15:
#line 188 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(4) - (6)].parent_seq_field), NULL, (yyvsp[(5) - (6)].features_seq_field)); ;}
    break;

  case 16:
#line 189 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), (yyvsp[(4) - (5)].parent_seq_field), NULL, NULL); ;}
    break;

  case 17:
#line 191 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (5)].id_field), NULL, (yyvsp[(3) - (5)].creators_seq_field), (yyvsp[(4) - (5)].features_seq_field)); ;}
    break;

  case 18:
#line 192 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), NULL, (yyvsp[(3) - (4)].creators_seq_field), NULL); ;}
    break;

  case 19:
#line 193 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (4)].id_field), NULL, NULL, (yyvsp[(3) - (4)].features_seq_field)); ;}
    break;

  case 20:
#line 194 "src/bison/bison.y"
    { (yyval.class_decl_field) = create_class_decl(curr_node_index++, (yyvsp[(2) - (3)].id_field), NULL, NULL, NULL); ;}
    break;

  case 21:
#line 198 "src/bison/bison.y"
    { (yyval.parent_seq_field) = create_parent_seq(curr_node_index++, (yyvsp[(1) - (2)].parent_field)); ;}
    break;

  case 22:
#line 199 "src/bison/bison.y"
    { (yyval.parent_seq_field) = append_parent_seq(curr_node_index++, (yyvsp[(1) - (3)].parent_seq_field), (yyvsp[(2) - (3)].parent_field)); ;}
    break;

  case 23:
#line 202 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (8)].id_field), (yyvsp[(3) - (8)].rename_seq_field), (yyvsp[(5) - (8)].identifiers_comma_seq_field), (yyvsp[(7) - (8)].identifiers_comma_seq_field)); ;}
    break;

  case 24:
#line 203 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), NULL, (yyvsp[(3) - (6)].identifiers_comma_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 25:
#line 204 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), NULL, (yyvsp[(5) - (6)].identifiers_comma_seq_field)); ;}
    break;

  case 26:
#line 205 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field)); ;}
    break;

  case 27:
#line 207 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (6)].id_field), (yyvsp[(3) - (6)].rename_seq_field), (yyvsp[(5) - (6)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 28:
#line 208 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), NULL, (yyvsp[(3) - (4)].identifiers_comma_seq_field), NULL); ;}
    break;

  case 29:
#line 209 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (4)].id_field), (yyvsp[(3) - (4)].rename_seq_field), NULL, NULL); ;}
    break;

  case 30:
#line 210 "src/bison/bison.y"
    { (yyval.parent_field) = create_parent(curr_node_index++, (yyvsp[(1) - (1)].id_field), NULL, NULL, NULL); ;}
    break;

  case 31:
#line 213 "src/bison/bison.y"
    { (yyval.rename_seq_field) = create_rename_seq(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].id_field)); ;}
    break;

  case 32:
#line 214 "src/bison/bison.y"
    { (yyval.rename_seq_field) = append_rename_seq(curr_node_index++, (yyvsp[(1) - (5)].rename_seq_field), (yyvsp[(3) - (5)].id_field), (yyvsp[(5) - (5)].id_field)); ;}
    break;

  case 33:
#line 218 "src/bison/bison.y"
    { (yyval.creators_seq_field) = create_creators_seq(curr_node_index++, (yyvsp[(2) - (2)].identifiers_comma_seq_field)); ;}
    break;

  case 34:
#line 219 "src/bison/bison.y"
    { (yyval.creators_seq_field) = append_creators_seq(curr_node_index++, (yyvsp[(1) - (3)].creators_seq_field), (yyvsp[(3) - (3)].identifiers_comma_seq_field)); ;}
    break;

  case 35:
#line 223 "src/bison/bison.y"
    { (yyval.features_seq_field) = create_features_seq(curr_node_index++, (yyvsp[(2) - (2)].feature_decl_seq_field)); ;}
    break;

  case 36:
#line 224 "src/bison/bison.y"
    { (yyval.features_seq_field) = append_features_seq(curr_node_index++, (yyvsp[(1) - (3)].features_seq_field), (yyvsp[(3) - (3)].feature_decl_seq_field)); ;}
    break;

  case 37:
#line 227 "src/bison/bison.y"
    { (yyval.feature_decl_seq_field) = create_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (2)].feature_decl_field)); ;}
    break;

  case 38:
#line 228 "src/bison/bison.y"
    { (yyval.feature_decl_seq_field) = append_feature_decl_seq(curr_node_index++, (yyvsp[(1) - (3)].feature_decl_seq_field), (yyvsp[(2) - (3)].feature_decl_field)); ;}
    break;

  case 39:
#line 231 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (3)].identifiers_comma_seq_field), (yyvsp[(3) - (3)].type_field), NULL, NULL, NULL); ;}
    break;

  case 40:
#line 233 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(3) - (4)].instruction_seq_field)); ;}
    break;

  case 41:
#line 234 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (5)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(4) - (5)].instruction_seq_field)); ;}
    break;

  case 42:
#line 235 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(3) - (6)].ids_with_type_seq_field), (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 43:
#line 237 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 44:
#line 238 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), NULL, NULL, NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 45:
#line 239 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), NULL, NULL, (yyvsp[(5) - (8)].ids_with_type_seq_field), (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 46:
#line 241 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (6)].identifiers_comma_seq_field), (yyvsp[(3) - (6)].type_field), NULL, NULL, (yyvsp[(5) - (6)].instruction_seq_field)); ;}
    break;

  case 47:
#line 242 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), (yyvsp[(3) - (7)].type_field), NULL, NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 48:
#line 243 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), (yyvsp[(3) - (8)].type_field), NULL, (yyvsp[(5) - (8)].ids_with_type_seq_field), (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 49:
#line 245 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), (yyvsp[(5) - (8)].type_field), NULL, NULL, (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 50:
#line 246 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), (yyvsp[(5) - (9)].type_field), NULL, NULL, (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 51:
#line 247 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (10)].identifiers_comma_seq_field), (yyvsp[(5) - (10)].type_field), NULL, (yyvsp[(7) - (10)].ids_with_type_seq_field), (yyvsp[(9) - (10)].instruction_seq_field)); ;}
    break;

  case 52:
#line 249 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (7)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (7)].ids_with_type_seq_field), NULL, (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 53:
#line 250 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (8)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (8)].ids_with_type_seq_field), NULL, (yyvsp[(7) - (8)].instruction_seq_field)); ;}
    break;

  case 54:
#line 251 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), NULL, (yyvsp[(3) - (9)].ids_with_type_seq_field), (yyvsp[(6) - (9)].ids_with_type_seq_field), (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 55:
#line 253 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (9)].identifiers_comma_seq_field), (yyvsp[(6) - (9)].type_field), (yyvsp[(3) - (9)].ids_with_type_seq_field), NULL, (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 56:
#line 254 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (10)].identifiers_comma_seq_field), (yyvsp[(6) - (10)].type_field), (yyvsp[(3) - (10)].ids_with_type_seq_field), NULL, (yyvsp[(9) - (10)].instruction_seq_field)); ;}
    break;

  case 57:
#line 255 "src/bison/bison.y"
    { (yyval.feature_decl_field) = create_feature_decl(curr_node_index++, (yyvsp[(1) - (11)].identifiers_comma_seq_field), (yyvsp[(6) - (11)].type_field), (yyvsp[(3) - (11)].ids_with_type_seq_field), (yyvsp[(8) - (11)].ids_with_type_seq_field), (yyvsp[(10) - (11)].instruction_seq_field)); ;}
    break;

  case 58:
#line 258 "src/bison/bison.y"
    { (yyval.ids_with_type_seq_field) = create_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (4)].identifiers_comma_seq_field), (yyvsp[(3) - (4)].type_field)); ;}
    break;

  case 59:
#line 259 "src/bison/bison.y"
    { (yyval.ids_with_type_seq_field) = append_ids_with_type_seq(curr_node_index++, (yyvsp[(1) - (5)].ids_with_type_seq_field), (yyvsp[(2) - (5)].identifiers_comma_seq_field), (yyvsp[(4) - (5)].type_field)); ;}
    break;

  case 60:
#line 262 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_user_defined, (yyvsp[(1) - (1)].id_field), NULL); ;}
    break;

  case 61:
#line 263 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_boolean, "BOOLEAN", NULL); ;}
    break;

  case 62:
#line 264 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_character, "CHARACTER", NULL); ;}
    break;

  case 63:
#line 265 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_integer, "INTEGER", NULL); ;}
    break;

  case 64:
#line 266 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_natural, "NATURAL", NULL); ;}
    break;

  case 65:
#line 267 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_string, "STRING", NULL); ;}
    break;

  case 66:
#line 268 "src/bison/bison.y"
    { (yyval.type_field) = create_type(curr_node_index++, dtype_array, "ARRAY", (yyvsp[(3) - (4)].type_field)); ;}
    break;

  case 67:
#line 271 "src/bison/bison.y"
    { (yyval.instruction_seq_field) = create_instruction_seq(curr_node_index++, NULL); ;}
    break;

  case 68:
#line 272 "src/bison/bison.y"
    { (yyval.instruction_seq_field) = append_instruction_seq(curr_node_index++, (yyvsp[(1) - (3)].instruction_seq_field), (yyvsp[(2) - (3)].instruction_field)); ;}
    break;

  case 69:
#line 275 "src/bison/bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (2)].id_field), NULL, NULL); ;}
    break;

  case 70:
#line 276 "src/bison/bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (4)].id_field), (yyvsp[(4) - (4)].id_field), NULL); ;}
    break;

  case 71:
#line 277 "src/bison/bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (6)].id_field), (yyvsp[(4) - (6)].id_field), NULL); ;}
    break;

  case 72:
#line 278 "src/bison/bison.y"
    { (yyval.instruction_field) = create_create_instruction(curr_node_index++, (yyvsp[(2) - (7)].id_field), (yyvsp[(4) - (7)].id_field), (yyvsp[(6) - (7)].argument_seq_field)); ;}
    break;

  case 73:
#line 280 "src/bison/bison.y"
    { (yyval.instruction_field) = create_assign_instruction(curr_node_index++, (yyvsp[(1) - (3)].id_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 74:
#line 282 "src/bison/bison.y"
    { (yyval.instruction_field) = create_if_instruction(curr_node_index++, (yyvsp[(3) - (7)].expr_field), (yyvsp[(6) - (7)].instruction_seq_field), NULL); ;}
    break;

  case 75:
#line 283 "src/bison/bison.y"
    { (yyval.instruction_field) = create_if_instruction(curr_node_index++, (yyvsp[(3) - (9)].expr_field), (yyvsp[(6) - (9)].instruction_seq_field), (yyvsp[(8) - (9)].instruction_seq_field)); ;}
    break;

  case 76:
#line 284 "src/bison/bison.y"
    { (yyval.instruction_field) = create_loop_instruction(curr_node_index++, (yyvsp[(2) - (7)].instruction_seq_field), (yyvsp[(4) - (7)].expr_field), (yyvsp[(6) - (7)].instruction_seq_field)); ;}
    break;

  case 77:
#line 286 "src/bison/bison.y"
    { (yyval.instruction_field) = create_instruction_as_expr(curr_node_index++, (yyvsp[(1) - (1)].expr_field)); ;}
    break;

  case 78:
#line 289 "src/bison/bison.y"
    { (yyval.argument_seq_field) = create_argument_seq(curr_node_index++, (yyvsp[(1) - (1)].expr_field)); ;}
    break;

  case 79:
#line 290 "src/bison/bison.y"
    { (yyval.argument_seq_field) = append_argument_seq(curr_node_index++, (yyvsp[(1) - (3)].argument_seq_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 80:
#line 293 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_liter_bool(curr_node_index++, (yyvsp[(1) - (1)].liter_boolean_field)); ;}
    break;

  case 81:
#line 294 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_liter_int (curr_node_index++, (yyvsp[(1) - (1)].liter_integer_field)); ;}
    break;

  case 82:
#line 295 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_liter_char(curr_node_index++, (yyvsp[(1) - (1)].liter_char_field)); ;}
    break;

  case 83:
#line 296 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_liter_str (curr_node_index++, (yyvsp[(1) - (1)].liter_string_field)); ;}
    break;

  case 84:
#line 297 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_liter_void(curr_node_index++); ;}
    break;

  case 85:
#line 299 "src/bison/bison.y"
    { (yyval.expr_field) = (yyvsp[(2) - (3)].expr_field); (yyval.expr_field)->is_parenthesized = 1; ;}
    break;

  case 86:
#line 300 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_current(curr_node_index++); ;}
    break;

  case 87:
#line 301 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, expr_call_selffeature, (yyvsp[(1) - (1)].id_field), NULL, 1); ;}
    break;

  case 88:
#line 302 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, expr_call_selffeature, (yyvsp[(1) - (3)].id_field), NULL, 0); ;}
    break;

  case 89:
#line 303 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_call(curr_node_index++, expr_call_selffeature, (yyvsp[(1) - (4)].id_field), (yyvsp[(3) - (4)].argument_seq_field), 0); ;}
    break;

  case 90:
#line 304 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_precursorcall(curr_node_index++, NULL, NULL); ;}
    break;

  case 91:
#line 305 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_precursorcall(curr_node_index++, NULL, NULL); ;}
    break;

  case 92:
#line 306 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_precursorcall(curr_node_index++, NULL, NULL); ;}
    break;

  case 93:
#line 307 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_precursorcall(curr_node_index++, (yyvsp[(3) - (4)].id_field), NULL); ;}
    break;

  case 94:
#line 308 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_precursorcall(curr_node_index++, (yyvsp[(3) - (6)].id_field), NULL); ;}
    break;

  case 95:
#line 309 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_precursorcall(curr_node_index++, (yyvsp[(3) - (7)].id_field), (yyvsp[(6) - (7)].argument_seq_field)); ;}
    break;

  case 96:
#line 310 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].id_field), NULL, 1); ;}
    break;

  case 97:
#line 311 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (5)].expr_field), (yyvsp[(3) - (5)].id_field), NULL, 0); ;}
    break;

  case 98:
#line 312 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_subcall(curr_node_index++, (yyvsp[(1) - (6)].expr_field), (yyvsp[(3) - (6)].id_field), (yyvsp[(5) - (6)].argument_seq_field), 0); ;}
    break;

  case 99:
#line 314 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_creation(curr_node_index++, (yyvsp[(3) - (4)].type_field), NULL, NULL); ;}
    break;

  case 100:
#line 315 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_creation(curr_node_index++, (yyvsp[(3) - (6)].type_field), (yyvsp[(6) - (6)].id_field), NULL); ;}
    break;

  case 101:
#line 316 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_creation(curr_node_index++, (yyvsp[(3) - (8)].type_field), (yyvsp[(6) - (8)].id_field), NULL); ;}
    break;

  case 102:
#line 317 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_creation(curr_node_index++, (yyvsp[(3) - (9)].type_field), (yyvsp[(6) - (9)].id_field), (yyvsp[(8) - (9)].argument_seq_field)); ;}
    break;

  case 103:
#line 319 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_arrelem, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 104:
#line 320 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_plus, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 105:
#line 321 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_bminus, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 106:
#line 322 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_mul, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 107:
#line 323 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_idiv, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 108:
#line 324 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_mod, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 109:
#line 325 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_uminus, NULL, (yyvsp[(2) - (2)].expr_field)); ;}
    break;

  case 110:
#line 327 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_less, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 111:
#line 328 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_great, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 112:
#line 329 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_less_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 113:
#line 330 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_great_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 114:
#line 331 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_equal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 115:
#line 332 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_notequal, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 116:
#line 334 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_and, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 117:
#line 335 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_or, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 118:
#line 336 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_xor, (yyvsp[(1) - (3)].expr_field), (yyvsp[(3) - (3)].expr_field)); ;}
    break;

  case 119:
#line 337 "src/bison/bison.y"
    { (yyval.expr_field) = create_expr_operation(curr_node_index++, expr_not, NULL, (yyvsp[(2) - (2)].expr_field)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2409 "/Users/alekseiyakimov/Documents/GitHub/simple_eiffel_compiler/src/bison/parser.c"
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


#line 340 "src/bison/bison.y"


