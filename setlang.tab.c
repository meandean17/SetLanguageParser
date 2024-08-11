
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "setlang.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "symbol_table.h"

    extern int yylex();
    extern int yylineno;
    extern char* yytext;
    void yyerror(const char *s);
    FILE* yyin;
    FILE* yyout;

    void yyerror(const char* s);
    int yydebug = 1; //enable debugging

    SymbolType current_type;

    //Function to generate unique labels
    int label_count = 0;
    char* new_label() {
        char* label = malloc(20);
        snprintf(label, 20, "L%d", label_count++);
        return label;
    }

    //function to check if an expression is a string
    int is_string(const char* expr) {
        return expr[0] == '"' && expr[strlen(expr) - 1] == '"';
    }

    //function to get expression type
    SymbolType get_expression_type(const char* expr) {
        if (strncmp(expr, "set_", 4) == 0) {
            return TYPE_SET;
        } else if (strncmp(expr, "collection_", 11) == 0) {
            return TYPE_COLLECTION;
        } else if (expr[0] >= '0' && expr[0] <= '9') {
            return TYPE_INT;
        } else {
            Symbol* sym = lookup_symbol(expr);
            if (sym != NULL) {
                return sym->type;
            }
        }
        return TYPE_INT;
    }


/* Line 189 of yacc.c  */
#line 123 "setlang.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     STRING = 259,
     IDENTIFIER = 260,
     INT = 261,
     STR = 262,
     SET = 263,
     COLLECTION = 264,
     IF = 265,
     ELSE = 266,
     WHILE = 267,
     FOR = 268,
     INPUT = 269,
     OUTPUT = 270,
     LBRACKET = 271,
     RBRACKET = 272,
     LBRACE = 273,
     RBRACE = 274,
     LPAREN = 275,
     RPAREN = 276,
     COMMA = 277,
     SIZE = 278,
     SEMICOLON = 279,
     COLON = 280,
     PLUS = 281,
     MINUS = 282,
     MULTIPLY = 283,
     DIVIDE = 284,
     AND = 285,
     ASSIGN = 286,
     EQUAL = 287,
     LESS = 288,
     GREATER = 289,
     LESS_EQUAL = 290,
     GREATER_EQUAL = 291,
     NOT = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 50 "setlang.y"

    int ival;
    char *sval;
    char *code;



/* Line 214 of yacc.c  */
#line 204 "setlang.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 216 "setlang.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   284

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    22,    24,    28,    31,    32,    37,    38,    43,    44,
      49,    50,    55,    57,    61,    66,    72,    80,    88,   100,
     106,   114,   119,   123,   125,   128,   130,   134,   136,   138,
     140,   144,   148,   152,   156,   160,   164,   166,   168,   171,
     175,   178,   182,   184,   188,   192,   196,   200,   204,   208,
     211,   213,   215,   217
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    41,    -1,    40,    41,    -1,
      42,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    18,    40,    19,    -1,    56,    24,
      -1,    -1,     6,    43,    47,    24,    -1,    -1,     7,    44,
      47,    24,    -1,    -1,     8,    45,    47,    24,    -1,    -1,
       9,    46,    47,    24,    -1,     5,    -1,    47,    22,     5,
      -1,     5,    31,    56,    24,    -1,    10,    20,    60,    21,
      41,    -1,    10,    20,    60,    21,    41,    11,    41,    -1,
      10,    20,    60,    21,    18,    40,    19,    -1,    10,    20,
      60,    21,    18,    40,    19,    11,    18,    40,    19,    -1,
      12,    20,    60,    21,    41,    -1,    13,    20,     5,    25,
      61,    21,    41,    -1,    14,    56,     5,    24,    -1,    15,
      54,    24,    -1,    55,    -1,    54,    55,    -1,    56,    -1,
      23,    56,    23,    -1,     3,    -1,     4,    -1,     5,    -1,
      56,    30,    56,    -1,    56,    26,    56,    -1,    56,    27,
      56,    -1,    56,    28,    56,    -1,    56,    29,    56,    -1,
      20,    56,    21,    -1,    57,    -1,    58,    -1,    16,    17,
      -1,    16,    59,    17,    -1,    18,    19,    -1,    18,    59,
      19,    -1,    56,    -1,    59,    22,    56,    -1,    56,    32,
      56,    -1,    56,    33,    56,    -1,    56,    34,    56,    -1,
      56,    35,    56,    -1,    56,    36,    56,    -1,    37,    60,
      -1,    57,    -1,    58,    -1,    56,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    88,    89,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   112,   112,   118,   118,   124,   124,
     149,   149,   176,   182,   192,   217,   225,   237,   245,   259,
     272,   293,   308,   344,   345,   353,   365,   449,   453,   454,
     460,   474,   494,   514,   520,   526,   531,   532,   535,   539,
     555,   556,   570,   574,   583,   589,   595,   601,   607,   613,
     618,   623,   628,   640
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "STRING", "IDENTIFIER", "INT",
  "STR", "SET", "COLLECTION", "IF", "ELSE", "WHILE", "FOR", "INPUT",
  "OUTPUT", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "COMMA", "SIZE", "SEMICOLON", "COLON", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "AND", "ASSIGN", "EQUAL", "LESS", "GREATER", "LESS_EQUAL",
  "GREATER_EQUAL", "NOT", "$accept", "program", "statement_list",
  "statement", "declaration", "$@1", "$@2", "$@3", "$@4",
  "identifier_list", "assignment", "if_statement", "while_statement",
  "for_statement", "input_statement", "output_statement", "output_list",
  "output_item", "expression", "set_expression", "collection_expression",
  "element_list", "condition", "set_or_collection", 0
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
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    43,    42,    44,    42,    45,    42,
      46,    42,    47,    47,    48,    49,    49,    49,    49,    50,
      51,    52,    53,    54,    54,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     3,     4,     5,     7,     7,    11,     5,
       7,     4,     3,     1,     2,     1,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     1,     2,     3,
       2,     3,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    37,    38,    39,    14,    16,    18,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     3,     5,
       6,     7,     8,     9,    10,    11,     0,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,    39,     0,     0,
       0,     0,    33,    35,    48,    52,     0,    50,     0,    52,
       0,     0,     1,     4,    13,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,    62,    46,    47,
       0,     0,     0,     0,     0,    32,    34,    49,     0,    12,
      51,    45,    41,    42,    43,    44,    40,    24,     0,    15,
      17,    19,    21,    59,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    36,    53,    23,    54,    55,    56,    57,
      58,     0,    25,    29,    63,     0,     0,     0,     0,    12,
      26,    30,     0,     0,     0,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    30,    31,    32,    33,    62,
      20,    21,    22,    23,    24,    25,    41,    42,    26,    27,
      28,    50,    70,   115
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -27
static const yytype_int16 yypact[] =
{
     179,   -27,   -27,   -15,   -27,   -27,   -27,   -27,    -5,    17,
      22,   223,    76,   215,   107,   223,    56,   179,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   242,   -27,   -27,   223,
      53,    53,    53,    53,    20,    20,    64,   -27,   218,    34,
     223,    50,   -27,   254,   -27,   254,    13,   -27,   125,   242,
       7,   235,   -27,   -27,   -27,   223,   223,   223,   223,   223,
     249,   -27,    43,    71,    81,   174,    20,   219,   -27,   -27,
      51,    61,    60,    62,    -9,   -27,   -27,   -27,   223,   -27,
     -27,   -27,   -26,   -26,   -27,   -27,    49,   -27,    93,   -27,
     -27,   -27,   -27,   -27,   223,   223,   223,   223,   223,   197,
     179,   101,   -27,   -27,   254,   -27,   254,   254,   254,   254,
     254,   107,    96,   -27,   -27,    97,   143,   179,   179,   113,
     -27,   -27,   118,   179,   161,   -27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -27,   -27,   -14,   -16,   -27,   -27,   -27,   -27,   -27,    14,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   119,    -7,   -25,
     -23,   129,   -22,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      48,    53,    57,    58,    39,    43,    45,    49,    51,    68,
      68,    69,    69,    71,   103,    34,    29,    55,    56,    57,
      58,    59,    60,     1,     2,    37,    80,    67,    67,    78,
      77,    45,    53,    74,    43,    78,    13,    35,    38,    73,
      15,    68,    36,    69,    93,    63,    64,    65,    82,    83,
      84,    85,    86,     1,     2,    37,    52,    66,    61,    67,
      55,    56,    57,    58,    59,    88,    13,    89,    38,    72,
      15,   104,    99,    40,    75,    55,    56,    57,    58,     1,
       2,    37,   100,   112,   113,   101,   102,   106,   107,   108,
     109,   110,    13,    88,    38,    90,    15,   116,   105,    40,
      53,   120,   121,    88,    49,    91,   114,   117,    53,   124,
       1,     2,     3,     4,     5,     6,     7,     8,   118,     9,
      10,    11,    12,    13,   122,    14,    47,    15,     1,     2,
       3,     4,     5,     6,     7,     8,   123,     9,    10,    11,
      12,    13,    46,    14,    79,    15,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     9,    10,    11,    12,    13,
      76,    14,   119,    15,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     9,    10,    11,    12,    13,     0,    14,
     125,    15,     1,     2,     3,     4,     5,     6,     7,     8,
       0,     9,    10,    11,    12,    13,    88,    14,    92,    15,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     9,
      10,    11,    12,    13,     0,   111,     0,    15,     1,     2,
      37,     1,     2,    37,     0,     0,     1,     2,    37,     0,
       0,    13,    44,    38,    13,    15,    38,    47,    15,    13,
       0,    38,     0,    15,     0,    55,    56,    57,    58,    59,
       0,    94,    95,    96,    97,    98,    81,     0,     0,     0,
       0,    55,    56,    57,    58,    59,    54,     0,    55,    56,
      57,    58,    59,    87,     0,    55,    56,    57,    58,    59,
      55,    56,    57,    58,    59
};

static const yytype_int8 yycheck[] =
{
      14,    17,    28,    29,    11,    12,    13,    14,    15,    34,
      35,    34,    35,    35,    23,    20,    31,    26,    27,    28,
      29,    30,    29,     3,     4,     5,    19,    34,    35,    22,
      17,    38,    48,    40,    41,    22,    16,    20,    18,     5,
      20,    66,    20,    66,    66,    31,    32,    33,    55,    56,
      57,    58,    59,     3,     4,     5,     0,    37,     5,    66,
      26,    27,    28,    29,    30,    22,    16,    24,    18,     5,
      20,    78,    21,    23,    24,    26,    27,    28,    29,     3,
       4,     5,    21,    99,   100,    25,    24,    94,    95,    96,
      97,    98,    16,    22,    18,    24,    20,   111,     5,    23,
     116,   117,   118,    22,   111,    24,     5,    11,   124,   123,
       3,     4,     5,     6,     7,     8,     9,    10,    21,    12,
      13,    14,    15,    16,    11,    18,    19,    20,     3,     4,
       5,     6,     7,     8,     9,    10,    18,    12,    13,    14,
      15,    16,    13,    18,    19,    20,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    12,    13,    14,    15,    16,
      41,    18,    19,    20,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    12,    13,    14,    15,    16,    -1,    18,
      19,    20,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    12,    13,    14,    15,    16,    22,    18,    24,    20,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    14,    15,    16,    -1,    18,    -1,    20,     3,     4,
       5,     3,     4,     5,    -1,    -1,     3,     4,     5,    -1,
      -1,    16,    17,    18,    16,    20,    18,    19,    20,    16,
      -1,    18,    -1,    20,    -1,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    21,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    24,    -1,    26,    27,
      28,    29,    30,    24,    -1,    26,    27,    28,    29,    30,
      26,    27,    28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    12,
      13,    14,    15,    16,    18,    20,    39,    40,    41,    42,
      48,    49,    50,    51,    52,    53,    56,    57,    58,    31,
      43,    44,    45,    46,    20,    20,    20,     5,    18,    56,
      23,    54,    55,    56,    17,    56,    59,    19,    40,    56,
      59,    56,     0,    41,    24,    26,    27,    28,    29,    30,
      56,     5,    47,    47,    47,    47,    37,    56,    57,    58,
      60,    60,     5,     5,    56,    24,    55,    17,    22,    19,
      19,    21,    56,    56,    56,    56,    56,    24,    22,    24,
      24,    24,    24,    60,    32,    33,    34,    35,    36,    21,
      21,    25,    24,    23,    56,     5,    56,    56,    56,    56,
      56,    18,    41,    41,     5,    61,    40,    11,    21,    19,
      41,    41,    11,    18,    40,    19
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 82 "setlang.y"
    { 
        printf("Completed parsing program\n");
        fprintf(yyout, "%s", (yyvsp[(1) - (1)].code));
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 88 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 89 "setlang.y"
    {
                    (yyval.code) = malloc(strlen((yyvsp[(1) - (2)].code)) + strlen((yyvsp[(2) - (2)].code)) + 2);
                    sprintf((yyval.code), "%s\n%s", (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code));
                    free((yyvsp[(1) - (2)].code));
                    free((yyvsp[(2) - (2)].code));
                ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 97 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 98 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 99 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 100 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 101 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 102 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 103 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 105 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (2)].code)) + 3);
                sprintf((yyval.code), "%s;", (yyvsp[(1) - (2)].code));
                free((yyvsp[(1) - (2)].code));
            ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 112 "setlang.y"
    { current_type = TYPE_INT; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 112 "setlang.y"
    {
                printf("Declaring INT: %s\n", (yyvsp[(3) - (4)].code));  // Debug print
                (yyval.code) = malloc(strlen((yyvsp[(3) - (4)].code)) + 7);
                sprintf((yyval.code), "int %s;", (yyvsp[(3) - (4)].code));
                free((yyvsp[(3) - (4)].code));
            ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 118 "setlang.y"
    { current_type = TYPE_STR; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 118 "setlang.y"
    {
                printf("Declaring STR: %s\n", (yyvsp[(3) - (4)].code));  // Debug print
                (yyval.code) = malloc(strlen((yyvsp[(3) - (4)].code)) + 15);
                sprintf((yyval.code), "char* %s = NULL;", (yyvsp[(3) - (4)].code));
                free((yyvsp[(3) - (4)].code));
            ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 124 "setlang.y"
    { current_type = TYPE_SET; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 124 "setlang.y"
    {
                printf("Declaring SET: %s\n", (yyvsp[(3) - (4)].code));  // Debug print
                char* temp = strdup((yyvsp[(3) - (4)].code));
                char* token = strtok(temp, ",");
                (yyval.code) = malloc(1);
                (yyval.code)[0] = '\0';
                while (token != NULL) {
                    char* trimmed = token;
                    while (*trimmed == ' ') trimmed++; // trim leading spaces
                    char* end = trimmed + strlen(trimmed) - 1;
                    while (end > trimmed && *end == ' ') end--; // trim trailing spaces
                    *(end + 1) = '\0';

                    char* new_decl = malloc(strlen(trimmed) + 30);
                    sprintf(new_decl, "set_t* %s = set_new();\n", trimmed);

                    (yyval.code) = realloc((yyval.code), strlen((yyval.code)) + strlen(new_decl) + 1);
                    strcat((yyval.code), new_decl);

                    free(new_decl);
                    token = strtok(NULL, ",");
                }
                free(temp);
                free((yyvsp[(3) - (4)].code));
            ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 149 "setlang.y"
    { current_type = TYPE_COLLECTION; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 149 "setlang.y"
    {
                printf("Declaring COLLECTION: %s\n", (yyvsp[(3) - (4)].code));  // Debug print
                char* temp = strdup((yyvsp[(3) - (4)].code));
                char* token = strtok(temp, ",");
                (yyval.code) = malloc(1);
                (yyval.code)[0] = '\0';
                while (token != NULL) {
                    char* trimmed = token;
                    while (*trimmed == ' ') trimmed++; // trim leading spaces
                    char* end = trimmed + strlen(trimmed) - 1;
                    while (end > trimmed && *end == ' ') end--; // trim trailing spaces
                    *(end + 1) = '\0';

                    char* new_decl = malloc(strlen(trimmed) + 30);
                    sprintf(new_decl, "collection_t* %s = collection_new();\n", trimmed);

                    (yyval.code) = realloc((yyval.code), strlen((yyval.code)) + strlen(new_decl) + 1);
                    strcat((yyval.code), new_decl);

                    free(new_decl);
                    token = strtok(NULL, ",");
                }
                free(temp);
                free((yyvsp[(3) - (4)].code));
            ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 176 "setlang.y"
    {
                    if (!insert_symbol((yyvsp[(1) - (1)].sval), current_type)) {
                        yyerror("Symbol already defined");
                    }
                    (yyval.code) = strdup((yyvsp[(1) - (1)].sval));
                ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 182 "setlang.y"
    {
                    if (!insert_symbol((yyvsp[(3) - (3)].sval), current_type)) {
                        yyerror("Symbol already defined");
                    }
                    (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].sval)) + 3);
                    sprintf((yyval.code), "%s, %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].sval));
                    free((yyvsp[(1) - (3)].code));
                ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 192 "setlang.y"
    {
                printf("Debug: Assigning to: %s\n", (yyvsp[(1) - (4)].sval));  // Debug print
                printf("Expression: %s\n", (yyvsp[(3) - (4)].code));  // Debug print
                Symbol* sym = lookup_symbol((yyvsp[(1) - (4)].sval));
                if (sym == NULL) {
                    yyerror("Undefined variable");
                } else {
                    SymbolType type = get_expression_type((yyvsp[(3) - (4)].code));
                    if(strncmp((yyvsp[(3) - (4)].code), "set_add", 7) == 0 || strncmp((yyvsp[(3) - (4)].code), "set_remove", 10) == 0) {
                        // for set_add and set_remove, dont assign result
                        (yyval.code) = malloc(strlen((yyvsp[(3) - (4)].code)) + 2);
                        sprintf((yyval.code), "%s;", (yyvsp[(3) - (4)].code));
                    } else if (sym->type == TYPE_SET && type == TYPE_SET) {
                        (yyval.code) = malloc(strlen((yyvsp[(1) - (4)].sval)) + strlen((yyvsp[(3) - (4)].code)) + 50);
                        sprintf((yyval.code), "set_free(%s);\n%s = %s;", (yyvsp[(1) - (4)].sval), (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].code));
                    } else {
                        (yyval.code) = malloc(strlen((yyvsp[(1) - (4)].sval)) + strlen((yyvsp[(3) - (4)].code)) + 5);
                        sprintf((yyval.code), "%s = %s;", (yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].code));
                    }
                }
                free((yyvsp[(1) - (4)].sval));
                free((yyvsp[(3) - (4)].code));
            ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 217 "setlang.y"
    {
                char* label = new_label();
                (yyval.code) = malloc(strlen((yyvsp[(3) - (5)].code)) + strlen((yyvsp[(5) - (5)].code)) + strlen(label) + 50);
                sprintf((yyval.code), "if (!(%s)) goto %s;\n%s\n%s:", (yyvsp[(3) - (5)].code), label, (yyvsp[(5) - (5)].code), label);
                free((yyvsp[(3) - (5)].code));
                free((yyvsp[(5) - (5)].code));
                free(label);
            ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 225 "setlang.y"
    {
                char* else_label = new_label();
                char* end_label = new_label();
                (yyval.code) = malloc(strlen((yyvsp[(3) - (7)].code)) + strlen((yyvsp[(5) - (7)].code)) + strlen((yyvsp[(7) - (7)].code)) + strlen(else_label) + strlen(end_label) + 100);
                sprintf((yyval.code), "if (!(%s)) goto %s;\n%s\ngoto %s;\n%s:\n%s\n%s",
                        (yyvsp[(3) - (7)].code), else_label, (yyvsp[(5) - (7)].code), end_label, else_label, (yyvsp[(7) - (7)].code), end_label);
                free((yyvsp[(3) - (7)].code));
                free((yyvsp[(5) - (7)].code));
                free((yyvsp[(7) - (7)].code));
                free(else_label);
                free(end_label);
            ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 237 "setlang.y"
    {
                char* label = new_label();
                (yyval.code) = malloc(strlen((yyvsp[(3) - (7)].code)) + strlen((yyvsp[(6) - (7)].code)) + strlen(label) + 50);
                sprintf((yyval.code), "if (!(%s)) goto %s;\n{\n%s\n}\n%s:", (yyvsp[(3) - (7)].code), label, (yyvsp[(6) - (7)].code), label);
                free((yyvsp[(3) - (7)].code));
                free((yyvsp[(6) - (7)].code));
                free(label);
            ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 245 "setlang.y"
    {
                char *else_label = new_label();
                char *end_label = new_label();
                (yyval.code) = malloc(strlen((yyvsp[(3) - (11)].code)) + strlen((yyvsp[(6) - (11)].code)) + strlen((yyvsp[(10) - (11)].code)) + strlen(else_label) + strlen(end_label) + 100);
                sprintf((yyval.code), "if (!(%s)) goto %s;\n{\n%s\n}\ngoto %s;\n%s:\n{\n%s\n}\n%s:", 
                        (yyvsp[(3) - (11)].code), else_label, (yyvsp[(6) - (11)].code), end_label, else_label, (yyvsp[(10) - (11)].code), end_label);
                free((yyvsp[(3) - (11)].code));
                free((yyvsp[(6) - (11)].code));
                free((yyvsp[(10) - (11)].code));
                free(else_label);
                free(end_label);
            ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 259 "setlang.y"
    {
                    char* start_label = new_label();
                    char* end_label = new_label();
                    (yyval.code) = malloc(strlen((yyvsp[(3) - (5)].code)) + strlen((yyvsp[(5) - (5)].code)) + strlen(start_label) + strlen(end_label) + 100);
                    sprintf((yyval.code), "%s:\nif (!%s) goto %s;\n%s\ngoto %s;\n%s:", 
                            start_label, (yyvsp[(3) - (5)].code), end_label, (yyvsp[(5) - (5)].code), start_label, end_label);
                    free((yyvsp[(3) - (5)].code));
                    free((yyvsp[(5) - (5)].code));
                    free(start_label);
                    free(end_label);
                ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 272 "setlang.y"
    {
                    char* start_label = new_label();
                    char* end_label = new_label();
                    (yyval.code) = malloc(strlen((yyvsp[(3) - (7)].sval)) + strlen((yyvsp[(5) - (7)].code)) + strlen((yyvsp[(7) - (7)].code)) + strlen(start_label) + strlen(end_label) + 200);
                    sprintf((yyval.code), "{\n iterator_t it = iterator_new(%s);\n"
                                " %s:\n"
                                " if (!iterator_has_next(&it)) goto %s;\n"
                                " %s = iterator_next(&it);\n"
                                " %s\n"
                                " goto %s;\n"
                                " %s:\n"
                                " iterator_free(&it);\n"
                                "}\n",
                            (yyvsp[(5) - (7)].code), start_label, end_label, (yyvsp[(3) - (7)].sval), (yyvsp[(7) - (7)].code), start_label, end_label);
                    free((yyvsp[(5) - (7)].code));
                    free((yyvsp[(7) - (7)].code));
                    free(start_label);
                    free(end_label);
                ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 293 "setlang.y"
    {
                Symbol* sym = lookup_symbol((yyvsp[(3) - (4)].sval));
                if (sym == NULL) {
                    yyerror("Undefined variable");
                }
                (yyval.code) = malloc(strlen((yyvsp[(2) - (4)].code)) + strlen((yyvsp[(3) - (4)].sval)) + 100);
                sprintf((yyval.code), "printf(%s);\n"
                            "if (scanf(\"%%d\", &%s) != 1) {\n"
                            "   fprintf(stderr, \"Invalid input\\n\");\n"
                            "   exit(1);\n"
                            "}\n", (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].sval));
                free((yyvsp[(2) - (4)].code));
                ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 308 "setlang.y"
    {
                    (yyval.code) = malloc(strlen((yyvsp[(2) - (3)].code)) + 100);
                    strcpy((yyval.code), "");
                    char *token = strtok((yyvsp[(2) - (3)].code), ";");
                    while (token != NULL) {
                        char *temp = malloc(strlen(token) + 100);
                        if (token[0] == '"') { // String literal
                            sprintf(temp, "printf(%s);\n", token);
                        } else if (strstr(token, "set_size") != NULL) { // Set size
                            char *set_name = strdup(token + 9); // skip "set_size("
                            set_name[strlen(set_name) - 1] = '\0'; // remove trailing ')'
                            sprintf(temp, "printf(\"%%d\", set_size(%s));\n", set_name);
                            free(set_name);
                        } else {
                            Symbol *sym = lookup_symbol(token);
                            if (sym == NULL) {
                                yyerror("Undefined variable");
                            } else if (sym->type == TYPE_INT) {
                                sprintf(temp, "printf(\"%%d\", %s);\n", token);
                            } else if (sym->type == TYPE_SET) {
                                sprintf(temp, "set_print(%s);\n", token);
                            } else if (sym->type == TYPE_COLLECTION) {
                                sprintf(temp, "collection_print(%s);\n", token);
                            } else {
                                yyerror("Unsupported type for output");
                            }
                        }
                        strcat((yyval.code), temp);
                        free(temp);
                        token = strtok(NULL, ";");
                    }
                    strcat((yyval.code), "printf(\"\\n\");\n");
                    free((yyvsp[(2) - (3)].code));
                ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 344 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 345 "setlang.y"
    {
            (yyval.code) = malloc(strlen((yyvsp[(1) - (2)].code)) + strlen((yyvsp[(2) - (2)].code)) + 2);
            sprintf((yyval.code), "%s;%s", (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code));
            free((yyvsp[(1) - (2)].code));
            free((yyvsp[(2) - (2)].code));
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 353 "setlang.y"
    {
                if (is_string((yyvsp[(1) - (1)].code))) {
                    (yyval.code) = (yyvsp[(1) - (1)].code);
                } else {
                    Symbol *sym = lookup_symbol((yyvsp[(1) - (1)].code));
                    if (sym && sym->type == TYPE_SET) {
                        (yyval.code) = strdup((yyvsp[(1) - (1)].code));
                    } else {
                        (yyval.code) = (yyvsp[(1) - (1)].code);
                    }
                }
            ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 365 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(2) - (3)].code)) + 30);
                sprintf((yyval.code), "set_size(%s)", (yyvsp[(2) - (3)].code));
                free((yyvsp[(2) - (3)].code));
            ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 449 "setlang.y"
    {
                (yyval.code) = malloc(20);
                sprintf((yyval.code), "%d", (yyvsp[(1) - (1)].ival));
            ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 453 "setlang.y"
    { (yyval.code) = strdup((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 454 "setlang.y"
    {
                if (lookup_symbol((yyvsp[(1) - (1)].sval)) == NULL) {
                    yyerror("Undefined variable");
                }
                (yyval.code) = strdup((yyvsp[(1) - (1)].sval));
            ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 460 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 30);
                SymbolType type1 = get_expression_type((yyvsp[(1) - (3)].code));
                SymbolType type2 = get_expression_type((yyvsp[(3) - (3)].code));
                if (type1 == TYPE_SET && type2 == TYPE_SET) {
                    sprintf((yyval.code), "set_intersection(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_COLLECTION) {
                    sprintf((yyval.code), "collection_intersection(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else {
                    yyerror("AND operation can only be applied to sets/collections");
                }
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 474 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 30);
                SymbolType type1 = get_expression_type((yyvsp[(1) - (3)].code));
                SymbolType type2 = get_expression_type((yyvsp[(3) - (3)].code));
                if (type1 == TYPE_SET && type2 == TYPE_SET) {
                    sprintf((yyval.code), "set_union(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_COLLECTION) {
                    sprintf((yyval.code), "collection_union(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_SET && type2 == TYPE_INT) {
                    sprintf((yyval.code), "set_add(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_STR) {
                    sprintf((yyval.code), "collection_add(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_INT && type2 == TYPE_INT) {
                    sprintf((yyval.code), "%s + %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else {
                    yyerror("PLUS operation not supported for these types");
                }
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 494 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 30);
                SymbolType type1 = get_expression_type((yyvsp[(1) - (3)].code));
                SymbolType type2 = get_expression_type((yyvsp[(3) - (3)].code));
                if (type1 == TYPE_SET && type2 == TYPE_SET) {
                    sprintf((yyval.code), "set_difference(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_COLLECTION) {
                    sprintf((yyval.code), "collection_difference(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_SET && type2 == TYPE_INT) {
                    sprintf((yyval.code), "set_remove(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_COLLECTION && type2 == TYPE_STR) {
                    sprintf((yyval.code), "collection_remove(%s, %s)", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else if (type1 == TYPE_INT && type2 == TYPE_INT) {
                    sprintf((yyval.code), "%s - %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                } else {
                    yyerror("MINUS operation not supported for these types");
                }
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 514 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 4);
                sprintf((yyval.code), "%s * %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 520 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 4);
                sprintf((yyval.code), "%s / %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 526 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(2) - (3)].code)) + 3);
                sprintf((yyval.code), "(%s)", (yyvsp[(2) - (3)].code));
                free((yyvsp[(2) - (3)].code));
            ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 531 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 532 "setlang.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 535 "setlang.y"
    { 
                    (yyval.code) = strdup("set_new()"); 
                    printf("Debug: Created empty set\n");
                ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 539 "setlang.y"
    {
                    printf("Debug: Set expression with elements\n");
                    char* temp = malloc(strlen((yyvsp[(2) - (3)].code)) + 50); // increased buffer size
                    int count = 1; // start with 1 for the first element
                    for (int i = 0; (yyvsp[(2) - (3)].code)[i] != '\0'; i++) {
                        if ((yyvsp[(2) - (3)].code)[i] == ',') { // count the number of commas
                            count++;
                        }
                    }
                    sprintf(temp, "set_from_array(%d, %s)", count, (yyvsp[(2) - (3)].code));
                    (yyval.code) = temp;
                    printf("Created set: %s\n", (yyval.code));
                    free((yyvsp[(2) - (3)].code));
                ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 555 "setlang.y"
    { (yyval.code) = strdup("collection_new()"); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 556 "setlang.y"
    {
                        char* temp = malloc(strlen((yyvsp[(2) - (3)].code)) + 50); // increased buffer size
                        int count = 1; // start with 1 for the first element
                        for (int i = 0; (yyvsp[(2) - (3)].code)[i] != '\0'; i++) {
                            if ((yyvsp[(2) - (3)].code)[i] == ',') { // count the number of commas
                                count++;
                            }
                        }
                        sprintf(temp, "collection_from_array(%d, %s)", count, (yyvsp[(2) - (3)].code));
                        (yyval.code) = temp;
                        free((yyvsp[(2) - (3)].code));
                    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 570 "setlang.y"
    { 
                printf("Debug: Element list with single expression\n");
                (yyval.code) = (yyvsp[(1) - (1)].code); 
            ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 574 "setlang.y"
    {
                printf("Debug: Element list with multiple expressions\n");
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 3);
                sprintf((yyval.code), "%s, %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 583 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 4);
                sprintf((yyval.code), "%s == %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 589 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 4);
                sprintf((yyval.code), "%s < %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 595 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 4);
                sprintf((yyval.code), "%s > %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 601 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 5);
                sprintf((yyval.code), "%s <= %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 607 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (3)].code)) + strlen((yyvsp[(3) - (3)].code)) + 5);
                sprintf((yyval.code), "%s >= %s", (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
                free((yyvsp[(1) - (3)].code));
                free((yyvsp[(3) - (3)].code));
            ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 613 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(2) - (2)].code)) + 3);
                sprintf((yyval.code), "!%s", (yyvsp[(2) - (2)].code));
                free((yyvsp[(2) - (2)].code));
            ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 618 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (1)].code)) + 10);
                sprintf((yyval.code), "!set_is_empty(%s)", (yyvsp[(1) - (1)].code));
                free((yyvsp[(1) - (1)].code));
            ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 623 "setlang.y"
    {
                (yyval.code) = malloc(strlen((yyvsp[(1) - (1)].code)) + 20);
                sprintf((yyval.code), "!collection_is_empty(%s)", (yyvsp[(1) - (1)].code));
                free((yyvsp[(1) - (1)].code));
            ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 628 "setlang.y"
    {
                Symbol* sym = lookup_symbol((yyvsp[(1) - (1)].code));
                if (sym && sym->type == lookup_symbol((yyvsp[(1) - (1)].code))) {
                    (yyval.code) = malloc(strlen((yyvsp[(1) - (1)].code)) + 20);
                    sprintf((yyval.code), "!set_is_empty(%s)", (yyvsp[(1) - (1)].code));
                } else {
                    (yyval.code) = strdup((yyvsp[(1) - (1)].code));
                }
                free((yyvsp[(1) - (1)].code));
            ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 640 "setlang.y"
    {
                    Symbol* sym = lookup_symbol((yyvsp[(1) - (1)].sval));
                    if (sym == NULL) {
                        yyerror("Undefined variable");
                    } else if (sym->type != TYPE_SET && sym->type != TYPE_COLLECTION) {
                        yyerror("Variable is not a set or collection");
                    }
                    (yyval.code) = strdup((yyvsp[(1) - (1)].sval));
                ;}
    break;



/* Line 1455 of yacc.c  */
#line 2373 "setlang.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 651 "setlang.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error on line %d: %s\n", yylineno, s);
    fprintf(stderr, "Near token: %s\n", yytext);
    exit(1); //Exit on error to avoid silent failures
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening input file");
        return 1;
    }
    
    yyout = fopen(argv[2], "w");
    if (!yyout) {
        perror("Error opening output file");
        return 1;
    }

    yyin = input;
    init_symbol_table();

    //Write necessary includes and function prototypes
    fprintf(yyout, "#include <stdio.h>\n");
    fprintf(yyout, "#include <stdlib.h>\n");
    fprintf(yyout, "#include \"setlang_runtime.h\"\n");
    fprintf(yyout, "int main() {\n");


    printf("Starting to parse...\n");
    int result = yyparse();
    printf("Parsing finished with result: %d.\n", result);
    fprintf(yyout, "// Cleanup\n");
    for (int i = 0; i < table_size; i++) {
        if (symbol_table[i] && symbol_table[i]->type == TYPE_SET) {
            fprintf(yyout, "set_free(%s);\n", symbol_table[i]->name);
        }
    }
    //Close main function
    fprintf(yyout, "return 0;\n}\n");

    free_symbol_table();
    
    if (result == 0) {
        printf("Parsing completed successfully.\n");
    } else {
        printf("Parsing failed.\n");
    }
    
    fclose(input);
    fclose(yyout);
    return result;
}

