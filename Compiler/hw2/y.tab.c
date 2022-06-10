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
     VAR = 258,
     PACKAGE = 259,
     NEWLINE = 260,
     IDENT = 261,
     RETURN = 262,
     FUNC = 263,
     SEMICOLON = 264,
     COLON = 265,
     COMMA = 266,
     INT = 267,
     FLOAT = 268,
     BOOL = 269,
     STRING = 270,
     INC = 271,
     DEC = 272,
     GEQ = 273,
     LOR = 274,
     LAND = 275,
     EQL = 276,
     NEQ = 277,
     LSS = 278,
     LEQ = 279,
     GTR = 280,
     ASSIGN = 281,
     ADD_ASSIGN = 282,
     SUB_ASSIGN = 283,
     MUL_ASSIGN = 284,
     QUO_ASSIGN = 285,
     REM_ASSIGN = 286,
     IF = 287,
     ELSE = 288,
     FOR = 289,
     SWITCH = 290,
     CASE = 291,
     DEFAULT = 292,
     LBRACE = 293,
     RBRACE = 294,
     PRINT = 295,
     PRINTLN = 296,
     ADD = 297,
     SUB = 298,
     MUL = 299,
     QUO = 300,
     REM = 301,
     NOT = 302,
     LPAREN = 303,
     RPAREN = 304,
     INT_LIT = 305,
     FLOAT_LIT = 306,
     BOOL_LIT = 307,
     STRING_LIT = 308
   };
#endif
/* Tokens.  */
#define VAR 258
#define PACKAGE 259
#define NEWLINE 260
#define IDENT 261
#define RETURN 262
#define FUNC 263
#define SEMICOLON 264
#define COLON 265
#define COMMA 266
#define INT 267
#define FLOAT 268
#define BOOL 269
#define STRING 270
#define INC 271
#define DEC 272
#define GEQ 273
#define LOR 274
#define LAND 275
#define EQL 276
#define NEQ 277
#define LSS 278
#define LEQ 279
#define GTR 280
#define ASSIGN 281
#define ADD_ASSIGN 282
#define SUB_ASSIGN 283
#define MUL_ASSIGN 284
#define QUO_ASSIGN 285
#define REM_ASSIGN 286
#define IF 287
#define ELSE 288
#define FOR 289
#define SWITCH 290
#define CASE 291
#define DEFAULT 292
#define LBRACE 293
#define RBRACE 294
#define PRINT 295
#define PRINTLN 296
#define ADD 297
#define SUB 298
#define MUL 299
#define QUO 300
#define REM 301
#define NOT 302
#define LPAREN 303
#define RPAREN 304
#define INT_LIT 305
#define FLOAT_LIT 306
#define BOOL_LIT 307
#define STRING_LIT 308




/* Copy the first part of user declarations.  */
#line 4 "compiler_hw2.y"

    #include "compiler_hw_common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    /* Custom variables to matian symbol table */
    typedef struct node {
        int idx;
        int addr;
        int lineno;
        char name[32]; 
        char func[32];
        type_t type;

        struct node *next;
    } Node;

    typedef struct table {
        Node* head;
        Node* tail;
        int cnt;    // count address
    } Table;

    int scope;            // symbol table index
    Table* s_table[1024]; // symbol table

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol();
    static Node* lookup_symbol();
    static void dump_symbol();
    static void insert_node();
    static Node* init_node();
    static char get_type();

    /* Global variables */
    int scope = 0;
    int addr = 0;
    bool HAS_ERROR = false;

    int op_idx;
    op_t ops[1024];

    /* Function */
    const char* get_op_name(op_t op) {
        switch (op) {
            case OP_ADD:
                return "ADD";
            case OP_SUB:
                return "SUB";
            case OP_MUL:
                return "MUL";
            case OP_QUO:
                return "QUO";
            case OP_REM:
                return "REM";
            case OP_EQL:
                return "EQL";
            case OP_NEQ:
                return "NEQ";
            case OP_LSS:
                return "LSS";
            case OP_LEQ:
                return "LEQ";
            case OP_GTR:
                return "GTR";
            case OP_GEQ:
                return "GEQ";
            case OP_POS:
                return "POS";
            case OP_NEG:
                return "NEG";
            case OP_NOT:
                return "NOT";
            case OP_LOR:
                return "LOR";
            case OP_LAND:
                return "LAND";
            case OP_ASSIGN:
                return "ASSIGN";
            case OP_ADD_ASSIGN:
                return "ADD";
            case OP_SUB_ASSIGN:
                return "SUB";
            case OP_MUL_ASSIGN:
                return "MUL";
            case OP_QUO_ASSIGN:
                return "QUO";
            case OP_REM_ASSIGN:
                return "REM";
            default:
                return "unknown";
        }
    }

    const char* get_type_name(type_t type) {
        switch (type) {
            case TYPE_INT:
                return "int32";
            case TYPE_FLOAT:
                return "float32";
            case TYPE_BOOL:
                return "bool";
            case TYPE_STRING:
                return "string";
            case TYPE_FUNC:
                return "func";
            default:
                return "ERROR";
        }
    } 


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
#line 138 "compiler_hw2.y"
{
    struct {
        union {
            int i_val;
            float f_val;
            bool b_val;
            char* s_val;
        };
        type_t type;
    } val;
    char *s_val;
    op_t op;
    type_t type;
}
/* Line 193 of yacc.c.  */
#line 345 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 358 "y.tab.c"

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   307

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  166

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    17,    20,
      21,    29,    30,    36,    39,    43,    48,    50,    54,    57,
      62,    66,    68,    71,    73,    75,    77,    79,    81,    82,
      87,    89,    92,    94,    96,    98,   100,   102,   104,   106,
     108,   110,   112,   114,   116,   118,   120,   122,   124,   126,
     128,   130,   132,   134,   136,   138,   140,   144,   146,   148,
     150,   152,   157,   160,   163,   165,   167,   169,   171,   173,
     176,   179,   181,   183,   185,   187,   191,   197,   198,   203,
     205,   207,   209,   211,   213,   215,   217,   220,   223,   224,
     229,   231,   234,   238,   244,   250,   252,   256,   260,   266,
     268,   270,   274,   275,   281,   285,   290
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    -1,    56,    57,    -1,    57,    -1,
      58,     5,    -1,    59,    -1,     5,    -1,     4,     6,    -1,
      -1,    62,    48,    65,    49,    68,    60,    66,    -1,    -1,
      62,    48,    49,    61,    66,    -1,     8,     6,    -1,     6,
      48,    49,    -1,     6,    48,    64,    49,    -1,    69,    -1,
      64,    11,    69,    -1,     6,    68,    -1,    65,    11,     6,
      68,    -1,    38,    91,    39,    -1,     7,    -1,     7,    69,
      -1,    12,    -1,    13,    -1,    15,    -1,    14,    -1,    71,
      -1,    -1,    69,    72,    70,    69,    -1,    77,    -1,    76,
      71,    -1,    19,    -1,    20,    -1,    73,    -1,    74,    -1,
      75,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    18,    -1,    42,    -1,    43,    -1,    44,    -1,
      45,    -1,    46,    -1,    42,    -1,    43,    -1,    47,    -1,
      78,    -1,    63,    -1,    80,    -1,    79,    -1,     6,    -1,
      48,    69,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    68,    48,    69,    49,    -1,    83,     5,    -1,
      82,     5,    -1,    89,    -1,    92,    -1,    94,    -1,    98,
      -1,    99,    -1,   101,     5,    -1,    67,     5,    -1,     5,
      -1,    84,    -1,    87,    -1,    88,    -1,     3,     6,    68,
      -1,     3,     6,    68,    26,    69,    -1,    -1,    69,    86,
      85,    69,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,    30,    -1,    31,    -1,    69,    -1,    69,    16,    -1,
      69,    17,    -1,    -1,    38,    90,    91,    39,    -1,    81,
      -1,    81,    91,    -1,    32,    93,    89,    -1,    32,    93,
      89,    33,    89,    -1,    32,    93,    89,    33,    92,    -1,
      69,    -1,    34,    93,    89,    -1,    34,    95,    89,    -1,
      96,     9,    93,     9,    97,    -1,    82,    -1,    82,    -1,
      35,    69,    89,    -1,    -1,    36,    50,   100,    10,    89,
      -1,    37,    10,    89,    -1,    40,    48,    69,    49,    -1,
      41,    48,    69,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   189,   189,   193,   194,   198,   199,   200,   204,   211,
     211,   219,   219,   226,   234,   238,   245,   246,   250,   262,
     274,   278,   279,   285,   286,   287,   288,   294,   295,   295,
     333,   334,   343,   347,   351,   352,   353,   357,   358,   359,
     360,   361,   362,   366,   367,   371,   372,   373,   377,   378,
     379,   385,   386,   387,   391,   392,   403,   407,   412,   417,
     422,   431,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   454,   454,   454,   458,   463,   467,   467,   490,
     491,   492,   493,   494,   495,   499,   503,   504,   508,   508,
     513,   514,   518,   519,   520,   524,   531,   532,   536,   540,
     544,   548,   552,   552,   555,   559,   560
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR", "PACKAGE", "NEWLINE", "IDENT",
  "RETURN", "FUNC", "SEMICOLON", "COLON", "COMMA", "INT", "FLOAT", "BOOL",
  "STRING", "INC", "DEC", "GEQ", "LOR", "LAND", "EQL", "NEQ", "LSS", "LEQ",
  "GTR", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "QUO_ASSIGN",
  "REM_ASSIGN", "IF", "ELSE", "FOR", "SWITCH", "CASE", "DEFAULT", "LBRACE",
  "RBRACE", "PRINT", "PRINTLN", "ADD", "SUB", "MUL", "QUO", "REM", "NOT",
  "LPAREN", "RPAREN", "INT_LIT", "FLOAT_LIT", "BOOL_LIT", "STRING_LIT",
  "$accept", "Program", "GlobalStatementList", "GlobalStatement",
  "PackageStmt", "FunctionDeclStmt", "@1", "@2", "FuncOpen",
  "FuncCallStmt", "ArgumentList", "ParameterList", "FuncBlock",
  "ReturnStmt", "Type", "Expression", "@3", "UnaryExpr", "binary_op",
  "cmp_op", "add_op", "mul_op", "unary_op", "PrimaryExpr", "Operand",
  "Literal", "ConversionExpr", "Statement", "SimpleStmt",
  "DeclarationStmt", "AssignmentStmt", "@4", "assign_op", "ExpressionStmt",
  "IncDecStmt", "Block", "@5", "StatementList", "IfStmt", "Condition",
  "ForStmt", "ForClause", "InitStmt", "PostStmt", "SwitchStmt", "CaseStmt",
  "@6", "PrintStmt", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    57,    58,    60,
      59,    61,    59,    62,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    68,    68,    69,    70,    69,
      71,    71,    72,    72,    72,    72,    72,    73,    73,    73,
      73,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      76,    77,    77,    77,    78,    78,    78,    79,    79,    79,
      79,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    82,    82,    83,    83,    85,    84,    86,
      86,    86,    86,    86,    86,    87,    88,    88,    90,    89,
      91,    91,    92,    92,    92,    93,    94,    94,    95,    96,
      97,    98,   100,    99,    99,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     2,     0,
       7,     0,     5,     2,     3,     4,     1,     3,     2,     4,
       3,     1,     2,     1,     1,     1,     1,     1,     0,     4,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     4,     2,     2,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     3,     5,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     0,     4,
       1,     2,     3,     5,     5,     1,     3,     3,     5,     1,
       1,     3,     0,     5,     3,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     7,     0,     0,     2,     4,     0,     6,     0,
       8,    13,     1,     3,     5,     0,     0,    11,     0,    23,
      24,    26,    25,    18,     0,     0,     0,     0,    12,     0,
       9,     0,    71,    55,    21,     0,     0,     0,     0,     0,
      88,     0,     0,    48,    49,    50,     0,    57,    58,    59,
      60,    52,     0,     0,    85,    27,     0,    30,    51,    54,
      53,    90,     0,     0,    72,    73,    74,    64,     0,    65,
      66,    67,    68,     0,    19,     0,     0,     0,    22,    95,
       0,    85,    99,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,    70,     0,    86,    87,    42,    32,    33,
      37,    38,    39,    40,    41,    79,    80,    81,    82,    83,
      84,    43,    44,    45,    46,    47,    28,    34,    35,    36,
      77,    31,    91,    63,    62,    20,    69,    10,    75,    14,
       0,    16,    92,    96,    97,     0,   101,     0,   104,     0,
       0,     0,    56,     0,     0,     0,     0,     0,    15,     0,
       0,     0,    89,   105,   106,    61,    29,    78,    76,    17,
      93,    94,     0,   103,   100,    98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    75,    24,     9,    51,
     130,    18,    28,    52,    53,    54,   144,    55,   116,   117,
     118,   119,    56,    57,    58,    59,    60,    61,    62,    63,
      64,   145,   120,    65,    66,    67,    89,    68,    69,    80,
      70,    84,    85,   165,    71,    72,   137,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -75
static const yytype_int16 yypact[] =
{
      20,    12,   -75,    15,    23,    20,   -75,    32,   -75,   -22,
     -75,   -75,   -75,   -75,   -75,     5,    17,   -75,    -3,   -75,
     -75,   -75,   -75,   -75,     0,    33,    17,    93,   -75,    17,
     -75,    34,   -75,    -7,    36,    36,    36,    36,    -5,    42,
     -75,     7,     8,   -75,   -75,   -75,    36,   -75,   -75,   -75,
     -75,   -75,    38,    11,   218,   -75,    36,   -75,   -75,   -75,
     -75,    93,    55,    57,   -75,   -75,   -75,   -75,    26,   -75,
     -75,   -75,   -75,    61,   -75,     0,    17,    21,   261,   261,
      43,   187,   -75,    43,    43,    67,   232,   -75,    43,    93,
      36,    36,   129,   -75,    36,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    54,   -75,
       4,   261,    49,   -75,   -75,    36,   -75,    75,   -75,    51,
     137,   145,   -75,   177,    36,    36,    36,    36,   -75,   -16,
      82,    43,   -75,   -75,   -75,   -75,   261,   261,   261,   261,
     -75,   -75,    36,   -75,   -75,   -75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,    87,   -75,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,    18,   -75,    -9,   -33,   -75,    39,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   -36,   -75,
     -75,   -75,   -75,   -75,   -75,   -74,   -75,   -42,   -55,   -31,
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   -75
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -96
static const yytype_int16 yytable[] =
{
      82,    78,    79,    81,    86,    83,   132,    23,    25,   133,
     134,    16,   136,    92,   138,   147,    35,    30,    10,   122,
      74,    11,    40,    12,     1,     2,    15,    33,     3,    19,
      20,    21,    22,    19,    20,    21,    22,    14,    27,    29,
      76,    77,    33,    93,   131,    87,    26,   139,    19,    20,
      21,    22,    88,   148,    17,    90,    91,   140,   141,    94,
     123,   143,   124,    43,    44,   125,   126,   128,    45,    46,
     129,    47,    48,    49,    50,   160,   135,   163,    43,    44,
     146,    40,   149,    45,    46,   151,    47,    48,    49,    50,
     152,   162,    13,   127,   161,   121,    31,     0,    32,    33,
      34,     0,    79,     0,   150,    19,    20,    21,    22,     0,
       0,   156,   157,   158,   159,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,   164,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,     0,     0,     0,
      45,    46,     0,    47,    48,    49,    50,    97,    98,    99,
     100,   101,   102,   103,   104,    97,    98,    99,   100,   101,
     102,   103,   104,    97,    98,    99,   100,   101,   102,   103,
     104,   111,   112,   113,   114,   115,     0,     0,   142,   111,
     112,   113,   114,   115,     0,     0,   153,   111,   112,   113,
     114,   115,     0,     0,   154,    97,    98,    99,   100,   101,
     102,   103,   104,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     0,   -95,   155,     0,     0,   111,
     112,   113,   114,   115,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
      97,    98,    99,   100,   101,   102,   103,   104,     0,     0,
     111,   112,   113,   114,   115,     0,     0,     0,     0,     0,
      40,     0,     0,     0,   111,   112,   113,   114,   115,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   111,   112,   113,   114,   115
};

static const yytype_int16 yycheck[] =
{
      36,    34,    35,    36,    37,    36,    80,    16,    11,    83,
      84,     6,    86,    46,    88,    11,    32,    26,     6,    61,
      29,     6,    38,     0,     4,     5,    48,     6,     8,    12,
      13,    14,    15,    12,    13,    14,    15,     5,    38,     6,
       6,    48,     6,     5,    77,    50,    49,    89,    12,    13,
      14,    15,    10,    49,    49,    48,    48,    90,    91,    48,
       5,    94,     5,    42,    43,    39,     5,    76,    47,    48,
      49,    50,    51,    52,    53,   149,     9,   151,    42,    43,
      26,    38,    33,    47,    48,    10,    50,    51,    52,    53,
      39,     9,     5,    75,   149,    56,     3,    -1,     5,     6,
       7,    -1,   135,    -1,   135,    12,    13,    14,    15,    -1,
      -1,   144,   145,   146,   147,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,   162,    34,    35,    36,
      37,    38,    -1,    40,    41,    42,    43,    -1,    -1,    -1,
      47,    48,    -1,    50,    51,    52,    53,    18,    19,    20,
      21,    22,    23,    24,    25,    18,    19,    20,    21,    22,
      23,    24,    25,    18,    19,    20,    21,    22,    23,    24,
      25,    42,    43,    44,    45,    46,    -1,    -1,    49,    42,
      43,    44,    45,    46,    -1,    -1,    49,    42,    43,    44,
      45,    46,    -1,    -1,    49,    18,    19,    20,    21,    22,
      23,    24,    25,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    42,
      43,    44,    45,    46,    -1,    38,    49,    -1,    -1,    42,
      43,    44,    45,    46,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      18,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    42,    43,    44,    45,    46,    18,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     8,    55,    56,    57,    58,    59,    62,
       6,     6,     0,    57,     5,    48,     6,    49,    65,    12,
      13,    14,    15,    68,    61,    11,    49,    38,    66,     6,
      68,     3,     5,     6,     7,    32,    34,    35,    36,    37,
      38,    40,    41,    42,    43,    47,    48,    50,    51,    52,
      53,    63,    67,    68,    69,    71,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    87,    88,    89,    91,    92,
      94,    98,    99,   101,    68,    60,     6,    48,    69,    69,
      93,    69,    82,    93,    95,    96,    69,    50,    10,    90,
      48,    48,    69,     5,    48,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    42,    43,    44,    45,    46,    72,    73,    74,    75,
      86,    71,    91,     5,     5,    39,     5,    66,    68,    49,
      64,    69,    89,    89,    89,     9,    89,   100,    89,    91,
      69,    69,    49,    69,    70,    85,    26,    11,    49,    33,
      93,    10,    39,    49,    49,    49,    69,    69,    69,    69,
      89,    92,     9,    89,    82,    97
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
        case 8:
#line 204 "compiler_hw2.y"
    {
        create_symbol(scope++);
        printf("package: %s\n", (yyvsp[(2) - (2)].s_val));
    }
    break;

  case 9:
#line 211 "compiler_hw2.y"
    {
        char tmp[4];
        tmp[0] = ')', tmp[1] = get_type((yyvsp[(5) - (5)].type)), tmp[2] = '\0';
        strcat((yyvsp[(3) - (5)].s_val), tmp);
        scope--;
        insert_symbol((yyvsp[(1) - (5)].s_val), TYPE_FUNC, (yyvsp[(3) - (5)].s_val), yylineno + 1);
        scope++;
    }
    break;

  case 11:
#line 219 "compiler_hw2.y"
    {
        insert_symbol((yyvsp[(1) - (3)].s_val), TYPE_FUNC, "()V", yylineno + 1);
        scope++;
    }
    break;

  case 13:
#line 226 "compiler_hw2.y"
    {
        (yyval.s_val) = (yyvsp[(2) - (2)].s_val);
        printf("func: %s\n", (yyval.s_val));
        create_symbol(scope);
    }
    break;

  case 14:
#line 234 "compiler_hw2.y"
    { 
        Node* tmp = lookup_symbol((yyvsp[(1) - (3)].s_val));
        printf("call: %s%s\n", tmp->name, tmp->func);
    }
    break;

  case 15:
#line 238 "compiler_hw2.y"
    {
        Node* tmp = lookup_symbol((yyvsp[(1) - (4)].s_val));
        printf("call: %s%s\n", tmp->name, tmp->func);
    }
    break;

  case 18:
#line 250 "compiler_hw2.y"
    {
        scope++;
        // malloc space to store parameter string
        (yyval.s_val) = (char*)malloc(sizeof(char) * 1024);
        (yyval.s_val)[0] = '(';
        (yyval.s_val)[1] = get_type((yyvsp[(2) - (2)].type));
        (yyval.s_val)[2] = '\0';

        // insert parameter
        printf("param %s, type: %c\n", (yyvsp[(1) - (2)].s_val), get_type((yyvsp[(2) - (2)].type)));
        insert_symbol((yyvsp[(1) - (2)].s_val), (yyvsp[(2) - (2)].type), "", yylineno + 1);
    }
    break;

  case 19:
#line 262 "compiler_hw2.y"
    { 
        char tmp[2];
        tmp[0] = get_type((yyvsp[(4) - (4)].type)), tmp[1] = '\0';
        strcat((yyval.s_val), tmp);

        // insert parameter
        printf("param %s, type: %c\n", (yyvsp[(3) - (4)].s_val), get_type((yyvsp[(4) - (4)].type)));
        insert_symbol((yyvsp[(3) - (4)].s_val), (yyvsp[(4) - (4)].type), "", yylineno + 1);
    }
    break;

  case 21:
#line 278 "compiler_hw2.y"
    { puts("return"); dump_symbol(); }
    break;

  case 22:
#line 279 "compiler_hw2.y"
    { puts("ireturn"); dump_symbol(); }
    break;

  case 23:
#line 285 "compiler_hw2.y"
    { (yyval.type) = TYPE_INT; }
    break;

  case 24:
#line 286 "compiler_hw2.y"
    { (yyval.type) = TYPE_FLOAT; }
    break;

  case 25:
#line 287 "compiler_hw2.y"
    { (yyval.type) = TYPE_STRING; }
    break;

  case 26:
#line 288 "compiler_hw2.y"
    { (yyval.type) = TYPE_BOOL; }
    break;

  case 28:
#line 295 "compiler_hw2.y"
    { 
        ops[++op_idx] = (yyvsp[(2) - (2)].op);
    }
    break;

  case 29:
#line 297 "compiler_hw2.y"
    {
        while (op_idx) {
            if (ops[op_idx] == OP_REM && ((yyvsp[(1) - (4)].val).type == TYPE_FLOAT || (yyvsp[(4) - (4)].val).type == TYPE_FLOAT))
                printf("error:%d: invalid operation: (operator REM not defined on float32)\n", yylineno);
            else if (((yyvsp[(1) - (4)].val).type == TYPE_INT || (yyvsp[(1) - (4)].val).type == TYPE_FLOAT) && ((yyvsp[(4) - (4)].val).type == TYPE_INT || (yyvsp[(4) - (4)].val).type == TYPE_FLOAT) && (yyvsp[(1) - (4)].val).type != (yyvsp[(4) - (4)].val).type)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name((yyvsp[(1) - (4)].val).type),
                    get_type_name((yyvsp[(4) - (4)].val).type));
            else if ((ops[op_idx] == OP_LAND || ops[op_idx] == OP_LOR) && ((yyvsp[(1) - (4)].val).type != TYPE_BOOL || (yyvsp[(4) - (4)].val).type != TYPE_BOOL))
                printf("error:%d: invalid operation: (operator %s not defined on %s)\n", 
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name(((yyvsp[(1) - (4)].val).type == TYPE_BOOL ? (yyvsp[(4) - (4)].val).type : (yyvsp[(1) - (4)].val).type)));
            if (HAS_ERROR)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name((yyvsp[(1) - (4)].val).type),
                    get_type_name((yyvsp[(4) - (4)].val).type));
            printf("%s\n", get_op_name(ops[op_idx--]));
        }

        HAS_ERROR = false;

        if ((yyvsp[(2) - (4)].op) == OP_EQL || (yyvsp[(2) - (4)].op) == OP_NEQ || (yyvsp[(2) - (4)].op) == OP_LSS|| (yyvsp[(2) - (4)].op) == OP_LEQ || (yyvsp[(2) - (4)].op) == OP_GTR || (yyvsp[(2) - (4)].op) == OP_GEQ)
            (yyvsp[(1) - (4)].val).type = (yyvsp[(4) - (4)].val).type = TYPE_BOOL;

        if (((yyvsp[(1) - (4)].val).type == TYPE_BOOL) || ((yyvsp[(4) - (4)].val).type == TYPE_BOOL))        (yyval.val).type = TYPE_BOOL;
        else if (((yyvsp[(1) - (4)].val).type == TYPE_FLOAT) || ((yyvsp[(4) - (4)].val).type == TYPE_FLOAT)) (yyval.val).type = TYPE_FLOAT;
        else                                                         (yyval.val).type = TYPE_INT;
    }
    break;

  case 30:
#line 333 "compiler_hw2.y"
    { (yyval.val).type = (yyvsp[(1) - (1)].val).type; }
    break;

  case 31:
#line 334 "compiler_hw2.y"
    {
        (yyval.val).type = (yyvsp[(2) - (2)].val).type;
        if ((yyval.val).type == TYPE_INT)        (yyval.val).i_val = ((yyvsp[(1) - (2)].op) == OP_POS ? (yyvsp[(2) - (2)].val).i_val : -(yyvsp[(2) - (2)].val).i_val);
        else if ((yyval.val).type == TYPE_FLOAT) (yyval.val).f_val = ((yyvsp[(1) - (2)].op) == OP_POS ? (yyvsp[(2) - (2)].val).f_val : -(yyvsp[(2) - (2)].val).f_val);
        printf("%s\n", get_op_name((yyvsp[(1) - (2)].op)));
    }
    break;

  case 32:
#line 343 "compiler_hw2.y"
    { 
        while (op_idx && ops[op_idx] != OP_LOR && ops[op_idx] != OP_LAND) printf("%s\n", get_op_name(ops[op_idx--]));
        (yyval.op) = OP_LOR;
    }
    break;

  case 33:
#line 347 "compiler_hw2.y"
    { 
        while (op_idx && ops[op_idx] != OP_LOR && ops[op_idx] != OP_LAND) printf("%s\n", get_op_name(ops[op_idx--]));
        (yyval.op) = OP_LAND;
    }
    break;

  case 34:
#line 351 "compiler_hw2.y"
    { while (op_idx) printf("%s\n", get_op_name(ops[op_idx--])); }
    break;

  case 37:
#line 357 "compiler_hw2.y"
    { (yyval.op) = OP_EQL; }
    break;

  case 38:
#line 358 "compiler_hw2.y"
    { (yyval.op) = OP_NEQ; }
    break;

  case 39:
#line 359 "compiler_hw2.y"
    { (yyval.op) = OP_LSS; }
    break;

  case 40:
#line 360 "compiler_hw2.y"
    { (yyval.op) = OP_LEQ; }
    break;

  case 41:
#line 361 "compiler_hw2.y"
    { (yyval.op) = OP_GTR; }
    break;

  case 42:
#line 362 "compiler_hw2.y"
    { (yyval.op) = OP_GEQ; }
    break;

  case 43:
#line 366 "compiler_hw2.y"
    { (yyval.op) = OP_ADD; }
    break;

  case 44:
#line 367 "compiler_hw2.y"
    { (yyval.op) = OP_SUB; }
    break;

  case 45:
#line 371 "compiler_hw2.y"
    { (yyval.op) = OP_MUL; }
    break;

  case 46:
#line 372 "compiler_hw2.y"
    { (yyval.op) = OP_QUO; }
    break;

  case 47:
#line 373 "compiler_hw2.y"
    { (yyval.op) = OP_REM; }
    break;

  case 48:
#line 377 "compiler_hw2.y"
    { (yyval.op) = OP_POS; }
    break;

  case 49:
#line 378 "compiler_hw2.y"
    { (yyval.op) = OP_NEG; }
    break;

  case 50:
#line 379 "compiler_hw2.y"
    { (yyval.op) = OP_NOT; }
    break;

  case 53:
#line 387 "compiler_hw2.y"
    { (yyval.val).type = (yyvsp[(1) - (1)].val).type; }
    break;

  case 55:
#line 392 "compiler_hw2.y"
    { 
        Node* tmp = lookup_symbol((yyvsp[(1) - (1)].s_val));
        if (tmp) {
            (yyval.val).type = tmp->type;
            printf("IDENT (name=%s, address=%d)\n", tmp->name, tmp->addr);
        } else {
            printf("error:%d: undefined: %s\n", yylineno + 1, (yyvsp[(1) - (1)].s_val));
            HAS_ERROR = true;
            (yyval.val).type = 0x3f3f3f3f;
        }
    }
    break;

  case 56:
#line 403 "compiler_hw2.y"
    { (yyval.val).type = (yyvsp[(2) - (3)].val).type; }
    break;

  case 57:
#line 407 "compiler_hw2.y"
    {
        (yyval.val).type = TYPE_INT;
        (yyval.val).i_val = atoi((yyvsp[(1) - (1)].s_val));
        printf("INT_LIT %d\n", (yyval.val).i_val);
    }
    break;

  case 58:
#line 412 "compiler_hw2.y"
    {
        (yyval.val).type = TYPE_FLOAT;
        (yyval.val).f_val = atof((yyvsp[(1) - (1)].s_val));
        printf("FLOAT_LIT %f\n", (yyval.val).f_val);
    }
    break;

  case 59:
#line 417 "compiler_hw2.y"
    { 
        (yyval.val).type = TYPE_BOOL;
        (yyval.val).b_val = !strcmp((yyvsp[(1) - (1)].s_val), "true") ? true : false;
        printf("%s %d\n", (yyval.val).b_val ? "TRUE" : "FALSE", (yyval.val).b_val);
    }
    break;

  case 60:
#line 422 "compiler_hw2.y"
    {
        (yyval.val).type = TYPE_STRING;
        (yyval.val).s_val = (yyvsp[(1) - (1)].s_val);
        printf("STRING_LIT %s\n", (yyvsp[(1) - (1)].s_val)); }
    break;

  case 61:
#line 431 "compiler_hw2.y"
    { 
        (yyval.s_val) = (yyvsp[(1) - (4)].s_val);
        if ((yyvsp[(1) - (4)].type) == TYPE_INT) puts("f2i"), (yyval.val).type = TYPE_INT;
        else                puts("i2f"), (yyval.val).type = TYPE_FLOAT;
    }
    break;

  case 75:
#line 458 "compiler_hw2.y"
    {
        Node* tmp = lookup_symbol((yyvsp[(2) - (3)].s_val));
        if (tmp) printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, (yyvsp[(2) - (3)].s_val), tmp->lineno);
        insert_symbol((yyvsp[(2) - (3)].s_val), (yyvsp[(3) - (3)].type), "", yylineno);
    }
    break;

  case 76:
#line 463 "compiler_hw2.y"
    { insert_symbol((yyvsp[(2) - (5)].s_val), (yyvsp[(3) - (5)].type), "", yylineno); }
    break;

  case 77:
#line 467 "compiler_hw2.y"
    {
        ops[++op_idx] = (yyvsp[(2) - (2)].op);
    }
    break;

  case 78:
#line 469 "compiler_hw2.y"
    {
        while (op_idx) {
            if (((yyvsp[(1) - (4)].val).type == TYPE_INT || (yyvsp[(1) - (4)].val).type == TYPE_FLOAT) && ((yyvsp[(4) - (4)].val).type == TYPE_INT || (yyvsp[(4) - (4)].val).type == TYPE_FLOAT) && (yyvsp[(1) - (4)].val).type != (yyvsp[(4) - (4)].val).type)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name((yyvsp[(1) - (4)].val).type),
                    get_type_name((yyvsp[(4) - (4)].val).type));
            if (HAS_ERROR)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                        yylineno,
                        get_op_name(ops[op_idx]),
                        get_type_name((yyvsp[(1) - (4)].val).type),
                        get_type_name((yyvsp[(4) - (4)].val).type));
            printf("%s\n", get_op_name(ops[op_idx--]));
        }
        HAS_ERROR = false;
    }
    break;

  case 79:
#line 490 "compiler_hw2.y"
    { (yyval.op) = OP_ASSIGN;}
    break;

  case 80:
#line 491 "compiler_hw2.y"
    { (yyval.op) = OP_ADD_ASSIGN; }
    break;

  case 81:
#line 492 "compiler_hw2.y"
    { (yyval.op) = OP_SUB_ASSIGN; }
    break;

  case 82:
#line 493 "compiler_hw2.y"
    { (yyval.op) = OP_MUL_ASSIGN; }
    break;

  case 83:
#line 494 "compiler_hw2.y"
    { (yyval.op) = OP_QUO_ASSIGN; }
    break;

  case 84:
#line 495 "compiler_hw2.y"
    { (yyval.op) = OP_REM_ASSIGN; }
    break;

  case 86:
#line 503 "compiler_hw2.y"
    { puts("INC"); }
    break;

  case 87:
#line 504 "compiler_hw2.y"
    { puts("DEC"); }
    break;

  case 88:
#line 508 "compiler_hw2.y"
    { create_symbol(scope++); 
    }
    break;

  case 89:
#line 509 "compiler_hw2.y"
    { dump_symbol(); }
    break;

  case 95:
#line 524 "compiler_hw2.y"
    {
        if ((yyvsp[(1) - (1)].val).type != TYPE_BOOL)
            printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 1, get_type_name((yyvsp[(1) - (1)].val).type));
    }
    break;

  case 102:
#line 552 "compiler_hw2.y"
    {
        printf("case %s\n", (yyvsp[(2) - (2)].s_val));
    }
    break;

  case 105:
#line 559 "compiler_hw2.y"
    { printf("PRINT %s\n", get_type_name((yyvsp[(3) - (4)].val).type)); }
    break;

  case 106:
#line 560 "compiler_hw2.y"
    { printf("PRINTLN %s\n", get_type_name((yyvsp[(3) - (4)].val).type)); }
    break;


/* Line 1267 of yacc.c.  */
#line 2197 "y.tab.c"
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


#line 563 "compiler_hw2.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

    while (scope) dump_symbol();

	printf("Total lines: %d\n", yylineno + 1);
    fclose(yyin);
    return 0;
}

static void create_symbol(int scope) {
    printf("> Create symbol table (scope level %d)\n", scope);
    s_table[scope] = (Table*)malloc(sizeof(Table));
    s_table[scope]->head = NULL;
    s_table[scope]->tail = NULL;
    s_table[scope]->cnt = 0; 
}

static void insert_symbol(char* name, type_t type, char* func, int lineno) {
    Node* tmp = init_node(name, type, func, lineno);
    insert_node(tmp);

    printf("> Insert `%s` (addr: %d) to scope level %d\n", tmp->name, tmp->addr, scope - 1);
}

static Node* lookup_symbol(char* name) {
    int idx = scope - 1;
    while (idx >= 0) {
        Node* tmp = s_table[idx]->head;
        while (tmp) {
            if (!strcmp(tmp->name, name))
                return tmp;
            tmp = tmp->next;
        }
        idx--;
    }
    return NULL;
}

static void dump_symbol() {
    int idx = scope - 1;
    Node* tmp = s_table[idx]->head;
    printf("\n> Dump symbol table (scope level: %d)\n", idx);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s\n",
            "Index", "Name", "Type", "Addr", "Lineno", "Func_sig");

    while (tmp) {
        printf("%-10d%-10s%-10s%-10d%-10d%-10s\n",
                tmp->idx, tmp->name, get_type_name(tmp->type), tmp->addr, tmp->lineno, tmp->func);
        tmp = tmp->next;
    }

    puts(""), scope--;
}

static Node* init_node(char* name, type_t type, char* func, int lineno) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    int idx = scope - 1;
    
    // calculate address and index
    tmp->idx = (s_table[idx]->tail == NULL ? 0 : s_table[idx]->tail->idx + 1);
    
    tmp->type = type;
    strcpy(tmp->name, name);
    strcpy(tmp->func, func);

    if (strlen(func) != 0) {
        tmp->addr = -1;
        printf("func_signature: %s\n", func);
    } else {
        tmp->addr = addr++;
        strcpy(tmp->func, "-\0");
    }

    tmp->lineno = lineno;
    return tmp;
}

static void insert_node(Node* node) {
    int idx = scope - 1;
    if (!s_table[idx]->head) s_table[idx]->head = s_table[idx]->tail = node;
    else {
        s_table[idx]->tail->next = node;
        s_table[idx]->tail = node;
    }
}

static char get_type(type_t type) {
    return (char)(get_type_name(type)[0] - 'a' + 'A');
}
