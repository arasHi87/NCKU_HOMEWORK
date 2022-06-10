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
     FOR = 288,
     SWITCH = 289,
     CASE = 290,
     DEFAULT = 291,
     LBRACE = 292,
     RBRACE = 293,
     PRINT = 294,
     PRINTLN = 295,
     ADD = 296,
     SUB = 297,
     MUL = 298,
     QUO = 299,
     REM = 300,
     NOT = 301,
     LPAREN = 302,
     RPAREN = 303,
     INT_LIT = 304,
     FLOAT_LIT = 305,
     BOOL_LIT = 306,
     STRING_LIT = 307
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
#define FOR 288
#define SWITCH 289
#define CASE 290
#define DEFAULT 291
#define LBRACE 292
#define RBRACE 293
#define PRINT 294
#define PRINTLN 295
#define ADD 296
#define SUB 297
#define MUL 298
#define QUO 299
#define REM 300
#define NOT 301
#define LPAREN 302
#define RPAREN 303
#define INT_LIT 304
#define FLOAT_LIT 305
#define BOOL_LIT 306
#define STRING_LIT 307




/* Copy the first part of user declarations.  */
#line 4 "compiler_hw3.y"

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

    /* Used to generate code */
    /* As printf; the usage: CODEGEN("%d - %s\n", 100, "Hello world"); */
    /* We do not enforce the use of this macro */
    #define CODEGEN(...) \
        do { \
            for (int i = 0; i < g_indent_cnt; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

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
    static Node* insert_symbol();
    static Node* lookup_symbol();
    static void dump_symbol();
    static void insert_node();
    static Node* init_node();
    static char get_type();

    const char* get_op_name();
    const char* get_ls_name();
    const char* get_type_name();
    const char* get_print_type();

    void get_op_inst(); // operation instruct

    /* Global variables */
    bool g_has_error = false;
    FILE *fout = NULL;
    char buffer[128]; // use to store string function return value
    char assign[128]; // use to store which parameter should be assign
    int kase[128];    // use to store case expression
    int label[128];   // use to matain label
    int g_indent_cnt = 0;
    int scope = 0;
    int addr = 0;
    int c_exp;        // use to check if current expression is const expression
    int returned = 0; // if function already returned;
    int op_idx;       // operation stake index
    int lb_idx;       // label stake index
    int ks_idx;       // kase stake index
    int sw_cnt;       // switch statement count
    int fr_cnt;       // for statement count
    int ce_cnt;       // const expression count
    op_t ops[1024];


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
#line 100 "compiler_hw3.y"
{
    struct {
        union {
            int i_val;
            float f_val;
            bool b_val;
            char* s_val;
        };
        char name[16];
        type_t type;
    } val;
    char *s_val;
    op_t op;
    type_t type;
}
/* Line 193 of yacc.c.  */
#line 305 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 318 "y.tab.c"

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
#define YYLAST   239

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      45,    46,    47,    48,    49,    50,    51,    52
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
     229,   231,   234,   235,   240,   242,   243,   244,   250,   251,
     256,   257,   263,   264,   269,   270,   276,   277
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    55,    -1,    55,    56,    -1,    56,    -1,
      57,     5,    -1,    58,    -1,     5,    -1,     4,     6,    -1,
      -1,    61,    47,    64,    48,    67,    59,    65,    -1,    -1,
      61,    47,    48,    60,    65,    -1,     8,     6,    -1,     6,
      47,    48,    -1,     6,    47,    63,    48,    -1,    68,    -1,
      63,    11,    68,    -1,     6,    67,    -1,    64,    11,     6,
      67,    -1,    37,    90,    38,    -1,     7,    -1,     7,    68,
      -1,    12,    -1,    13,    -1,    15,    -1,    14,    -1,    70,
      -1,    -1,    68,    71,    69,    68,    -1,    76,    -1,    75,
      70,    -1,    19,    -1,    20,    -1,    72,    -1,    73,    -1,
      74,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
      25,    -1,    18,    -1,    41,    -1,    42,    -1,    43,    -1,
      44,    -1,    45,    -1,    41,    -1,    42,    -1,    46,    -1,
      77,    -1,    62,    -1,    79,    -1,    78,    -1,     6,    -1,
      47,    68,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    67,    47,    68,    48,    -1,    82,     5,    -1,
      81,     5,    -1,    88,    -1,    91,    -1,    94,    -1,    97,
      -1,    99,    -1,   102,     5,    -1,    66,     5,    -1,     5,
      -1,    83,    -1,    86,    -1,    87,    -1,     3,     6,    67,
      -1,     3,     6,    67,    26,    68,    -1,    -1,    68,    85,
      84,    68,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,    30,    -1,    31,    -1,    68,    -1,    68,    16,    -1,
      68,    17,    -1,    -1,    37,    89,    90,    38,    -1,    80,
      -1,    80,    90,    -1,    -1,    32,    93,    92,    88,    -1,
      68,    -1,    -1,    -1,    33,    95,    93,    96,    88,    -1,
      -1,    34,    68,    98,    88,    -1,    -1,    35,    49,   100,
      10,    88,    -1,    -1,    36,    10,   101,    88,    -1,    -1,
      39,   103,    47,    68,    48,    -1,    -1,    40,   104,    47,
      68,    48,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   152,   152,   156,   157,   161,   162,   163,   167,   174,
     174,   192,   192,   210,   218,   223,   231,   232,   236,   248,
     260,   264,   270,   281,   282,   283,   284,   290,   291,   291,
     374,   375,   393,   394,   395,   396,   397,   401,   402,   403,
     404,   405,   406,   410,   411,   415,   416,   417,   421,   422,
     423,   429,   430,   431,   435,   436,   449,   453,   460,   466,
     473,   484,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   514,   515,   516,   520,   536,   545,   545,   578,
     579,   580,   581,   582,   583,   587,   591,   605,   621,   621,
     626,   627,   631,   631,   639,   648,   650,   648,   659,   659,
     673,   673,   680,   680,   688,   688,   697,   697
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
  "REM_ASSIGN", "IF", "FOR", "SWITCH", "CASE", "DEFAULT", "LBRACE",
  "RBRACE", "PRINT", "PRINTLN", "ADD", "SUB", "MUL", "QUO", "REM", "NOT",
  "LPAREN", "RPAREN", "INT_LIT", "FLOAT_LIT", "BOOL_LIT", "STRING_LIT",
  "$accept", "Program", "GlobalStatementList", "GlobalStatement",
  "PackageStmt", "FunctionDeclStmt", "@1", "@2", "FuncOpen",
  "FuncCallStmt", "ArgumentList", "ParameterList", "FuncBlock",
  "ReturnStmt", "Type", "Expression", "@3", "UnaryExpr", "binary_op",
  "cmp_op", "add_op", "mul_op", "unary_op", "PrimaryExpr", "Operand",
  "Literal", "ConversionExpr", "Statement", "SimpleStmt",
  "DeclarationStmt", "AssignmentStmt", "@4", "assign_op", "ExpressionStmt",
  "IncDecStmt", "Block", "@5", "StatementList", "IfStmt", "@6",
  "Condition", "ForStmt", "@7", "@8", "SwitchStmt", "@9", "CaseStmt",
  "@10", "@11", "PrintStmt", "@12", "@13", 0
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
     305,   306,   307
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    57,    59,
      58,    60,    58,    61,    62,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    67,    67,    67,    68,    69,    68,
      70,    70,    71,    71,    71,    71,    71,    72,    72,    72,
      72,    72,    72,    73,    73,    74,    74,    74,    75,    75,
      75,    76,    76,    76,    77,    77,    77,    78,    78,    78,
      78,    79,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    81,    82,    82,    84,    83,    85,
      85,    85,    85,    85,    85,    86,    87,    87,    89,    88,
      90,    90,    92,    91,    93,    95,    96,    94,    98,    97,
     100,    99,   101,    99,   103,   102,   104,   102
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
       1,     2,     0,     4,     1,     0,     0,     5,     0,     4,
       0,     5,     0,     4,     0,     5,     0,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     7,     0,     0,     2,     4,     0,     6,     0,
       8,    13,     1,     3,     5,     0,     0,    11,     0,    23,
      24,    26,    25,    18,     0,     0,     0,     0,    12,     0,
       9,     0,    71,    55,    21,     0,    95,     0,     0,     0,
      88,   104,   106,    48,    49,    50,     0,    57,    58,    59,
      60,    52,     0,     0,    85,    27,     0,    30,    51,    54,
      53,    90,     0,     0,    72,    73,    74,    64,     0,    65,
      66,    67,    68,     0,    19,     0,     0,     0,    22,    94,
      92,     0,    98,   100,   102,     0,     0,     0,     0,    70,
       0,    86,    87,    42,    32,    33,    37,    38,    39,    40,
      41,    79,    80,    81,    82,    83,    84,    43,    44,    45,
      46,    47,    28,    34,    35,    36,    77,    31,    91,    63,
      62,    20,    69,    10,    75,    14,     0,    16,     0,    96,
       0,     0,     0,     0,     0,     0,    56,     0,     0,     0,
       0,     0,    15,    93,     0,    99,     0,   103,    89,     0,
       0,    61,    29,    78,    76,    17,    97,   101,   105,   107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    75,    24,     9,    51,
     126,    18,    28,    52,    53,    54,   138,    55,   112,   113,
     114,   115,    56,    57,    58,    59,    60,    61,    62,    63,
      64,   139,   116,    65,    66,    67,    85,    68,    69,   128,
      80,    70,    81,   144,    71,   130,    72,   131,   132,    73,
      86,    87
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -122
static const yytype_int16 yypact[] =
{
      11,     4,  -122,     7,    18,    11,  -122,    15,  -122,   -26,
    -122,  -122,  -122,  -122,  -122,     0,    22,  -122,    -6,  -122,
    -122,  -122,  -122,  -122,   -15,    21,    22,    26,  -122,    22,
    -122,    24,  -122,   -23,    96,    96,  -122,    96,   -21,    36,
    -122,  -122,  -122,  -122,  -122,  -122,    96,  -122,  -122,  -122,
    -122,  -122,    44,     8,   180,  -122,    96,  -122,  -122,  -122,
    -122,    26,    49,    52,  -122,  -122,  -122,  -122,    31,  -122,
    -122,  -122,  -122,    65,  -122,   -15,    22,    38,   194,   194,
    -122,    96,   194,  -122,  -122,    26,    27,    34,    73,  -122,
      96,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,    45,  -122,    -3,   194,    46,  -122,
      46,    72,    46,    61,    96,    96,  -122,   108,    96,    96,
      96,    96,  -122,  -122,    46,  -122,    46,  -122,  -122,   139,
     147,  -122,   194,   194,   194,   194,  -122,  -122,  -122,  -122
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -122,  -122,  -122,    98,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,    37,  -122,   -12,   -34,  -122,    57,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -121,  -122,   -59,  -122,  -122,
      39,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      78,    79,   118,    82,    23,    25,    16,   143,   141,   145,
      10,   147,    88,    11,    30,     1,     2,    74,    12,     3,
      14,    15,    27,   156,    77,   157,   133,    29,    83,    31,
      76,    32,    33,    34,    19,    20,    21,    22,    19,    20,
      21,    22,    26,   127,    33,   142,    84,    79,    17,    89,
      19,    20,    21,    22,   119,    90,   137,   120,    35,    36,
      37,    38,    39,    40,   124,    41,    42,    43,    44,   121,
     122,   140,    45,    46,   134,    47,    48,    49,    50,    43,
      44,   135,   146,    40,    45,    46,   125,    47,    48,    49,
      50,    93,    94,    95,    96,    97,    98,    99,   100,   148,
     149,   150,    33,    13,   152,   153,   154,   155,    19,    20,
      21,    22,   123,   117,   107,   108,   109,   110,   111,     0,
     129,   136,     0,     0,     0,     0,    93,    94,    95,    96,
      97,    98,    99,   100,     0,     0,     0,    43,    44,     0,
       0,     0,    45,    46,     0,    47,    48,    49,    50,   107,
     108,   109,   110,   111,     0,     0,   151,    93,    94,    95,
      96,    97,    98,    99,   100,    93,    94,    95,    96,    97,
      98,    99,   100,     0,     0,     0,     0,     0,     0,     0,
     107,   108,   109,   110,   111,     0,     0,   158,   107,   108,
     109,   110,   111,     0,     0,   159,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,    93,    94,    95,    96,    97,    98,    99,   100,
       0,   107,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111
};

static const yytype_int16 yycheck[] =
{
      34,    35,    61,    37,    16,    11,     6,   128,    11,   130,
       6,   132,    46,     6,    26,     4,     5,    29,     0,     8,
       5,    47,    37,   144,    47,   146,    85,     6,    49,     3,
       6,     5,     6,     7,    12,    13,    14,    15,    12,    13,
      14,    15,    48,    77,     6,    48,    10,    81,    48,     5,
      12,    13,    14,    15,     5,    47,    90,     5,    32,    33,
      34,    35,    36,    37,    76,    39,    40,    41,    42,    38,
       5,    26,    46,    47,    47,    49,    50,    51,    52,    41,
      42,    47,    10,    37,    46,    47,    48,    49,    50,    51,
      52,    18,    19,    20,    21,    22,    23,    24,    25,    38,
     134,   135,     6,     5,   138,   139,   140,   141,    12,    13,
      14,    15,    75,    56,    41,    42,    43,    44,    45,    -1,
      81,    48,    -1,    -1,    -1,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    46,    47,    -1,    49,    50,    51,    52,    41,
      42,    43,    44,    45,    -1,    -1,    48,    18,    19,    20,
      21,    22,    23,    24,    25,    18,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    -1,    -1,    48,    41,    42,
      43,    44,    45,    -1,    -1,    48,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    18,    19,    20,    21,    22,    23,    24,    25,
      -1,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     8,    54,    55,    56,    57,    58,    61,
       6,     6,     0,    56,     5,    47,     6,    48,    64,    12,
      13,    14,    15,    67,    60,    11,    48,    37,    65,     6,
      67,     3,     5,     6,     7,    32,    33,    34,    35,    36,
      37,    39,    40,    41,    42,    46,    47,    49,    50,    51,
      52,    62,    66,    67,    68,    70,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    86,    87,    88,    90,    91,
      94,    97,    99,   102,    67,    59,     6,    47,    68,    68,
      93,    95,    68,    49,    10,    89,   103,   104,    68,     5,
      47,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    41,    42,    43,
      44,    45,    71,    72,    73,    74,    85,    70,    90,     5,
       5,    38,     5,    65,    67,    48,    63,    68,    92,    93,
      98,   100,   101,    90,    47,    47,    48,    68,    69,    84,
      26,    11,    48,    88,    96,    88,    10,    88,    38,    68,
      68,    48,    68,    68,    68,    68,    88,    88,    48,    48
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
#line 167 "compiler_hw3.y"
    {
        create_symbol(scope++);
        printf("package: %s\n", (yyvsp[(2) - (2)].s_val));
    }
    break;

  case 9:
#line 174 "compiler_hw3.y"
    {
        char tmp[4];
        tmp[0] = ')', tmp[1] = get_type((yyvsp[(5) - (5)].type)), tmp[2] = '\0';
        strcat((yyvsp[(3) - (5)].s_val), tmp);
        scope--;
        insert_symbol((yyvsp[(1) - (5)].s_val), TYPE_FUNC, (yyvsp[(3) - (5)].s_val), yylineno + 1);
        CODEGEN(".method public static %s%s\n", (yyvsp[(1) - (5)].s_val), (yyvsp[(3) - (5)].s_val));
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
        scope++;
        returned = 0;
    }
    break;

  case 10:
#line 185 "compiler_hw3.y"
    {
        if (!returned) {
            returned = 1;
            CODEGEN("\treturn\n");
            CODEGEN(".end method\n");
        }
    }
    break;

  case 11:
#line 192 "compiler_hw3.y"
    {
        insert_symbol((yyvsp[(1) - (3)].s_val), TYPE_FUNC, "()V", yylineno + 1);
        if (!strcmp((yyvsp[(1) - (3)].s_val), "main")) CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        else                     CODEGEN(".method public static %s()V\n", (yyvsp[(1) - (3)].s_val));
        CODEGEN(".limit stack 128\n");
        CODEGEN(".limit locals 128\n");
        scope++;
        returned = 0;
    }
    break;

  case 12:
#line 200 "compiler_hw3.y"
    {
        if (!returned) {
            returned = 1;
            CODEGEN("\treturn\n");
            CODEGEN(".end method\n");
        }
    }
    break;

  case 13:
#line 210 "compiler_hw3.y"
    {
        (yyval.s_val) = (yyvsp[(2) - (2)].s_val);
        printf("func: %s\n", (yyval.s_val));
        create_symbol(scope);
    }
    break;

  case 14:
#line 218 "compiler_hw3.y"
    { 
        Node* tmp = lookup_symbol((yyvsp[(1) - (3)].s_val));
        printf("call: %s%s\n", tmp->name, tmp->func);
        CODEGEN("\tinvokestatic Main/%s%s\n", tmp->name, tmp->func);
    }
    break;

  case 15:
#line 223 "compiler_hw3.y"
    {
        Node* tmp = lookup_symbol((yyvsp[(1) - (4)].s_val));
        printf("call: %s%s\n", tmp->name, tmp->func);
        CODEGEN("\tinvokestatic Main/%s%s\n", tmp->name, tmp->func);
    }
    break;

  case 18:
#line 236 "compiler_hw3.y"
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
#line 248 "compiler_hw3.y"
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
#line 264 "compiler_hw3.y"
    {
        puts("return");
        dump_symbol();
        CODEGEN("\treturn\n");
        CODEGEN(".end method\n");
    }
    break;

  case 22:
#line 270 "compiler_hw3.y"
    {
        puts("ireturn");
        dump_symbol(); 
        CODEGEN("\tireturn\n");
        CODEGEN(".end method\n");
    }
    break;

  case 23:
#line 281 "compiler_hw3.y"
    { (yyval.type) = TYPE_INT; }
    break;

  case 24:
#line 282 "compiler_hw3.y"
    { (yyval.type) = TYPE_FLOAT; }
    break;

  case 25:
#line 283 "compiler_hw3.y"
    { (yyval.type) = TYPE_STRING; }
    break;

  case 26:
#line 284 "compiler_hw3.y"
    { (yyval.type) = TYPE_BOOL; }
    break;

  case 28:
#line 291 "compiler_hw3.y"
    {
        // Lgogic operation
        if ((yyvsp[(2) - (2)].op) == OP_LOR || (yyvsp[(2) - (2)].op) == OP_LAND) {
            while (op_idx && ops[op_idx] != OP_LOR && ops[op_idx] != OP_LAND) {
                get_op_inst(buffer, (yyvsp[(1) - (2)].val).type, ops[op_idx]);
                CODEGEN("\t%s", buffer);

                // deal compare op
                if ((yyvsp[(1) - (2)].val).type == TYPE_FLOAT) CODEGEN("\n");
                else {
                    if (ops[op_idx] == EQL || ops[op_idx] == OP_NEQ || ops[op_idx] == OP_LSS
                    || ops[op_idx] == OP_LEQ || ops[op_idx] == OP_GTR || ops[op_idx] == OP_GEQ){
                        CODEGEN(" L_cmp_%d\n", ce_cnt++);
                        CODEGEN("\ticonst_1\n");
                        CODEGEN("\tgoto L_cmp_%d\n", ce_cnt++);
                        CODEGEN("L_cmp_%d:\n", ce_cnt - 2);
                        CODEGEN("\ticonst_0\n");
                        CODEGEN("L_cmp_%d:\n", ce_cnt - 1);
                    } else CODEGEN("\n");
                }
                printf("%s\n", get_op_name(ops[op_idx--]));
            }
        }

        // compare operation
        if ((yyvsp[(2) - (2)].op) == EQL || (yyvsp[(2) - (2)].op) == OP_NEQ || (yyvsp[(2) - (2)].op) == OP_LSS || (yyvsp[(2) - (2)].op) == OP_LEQ || (yyvsp[(2) - (2)].op) == OP_GTR || (yyvsp[(2) - (2)].op) == OP_GEQ ) {
            while (op_idx) { 
                get_op_inst(buffer, (yyvsp[(1) - (2)].val).type, ops[op_idx]);
                printf("%s\n", get_op_name(ops[op_idx--]));
                CODEGEN("\t%s\n", buffer);
            }
        }
        ops[++op_idx] = (yyvsp[(2) - (2)].op);
    }
    break;

  case 29:
#line 324 "compiler_hw3.y"
    {
        // check expression type
        if ((yyvsp[(2) - (4)].op) == OP_EQL || (yyvsp[(2) - (4)].op) == OP_NEQ || (yyvsp[(2) - (4)].op) == OP_LSS|| (yyvsp[(2) - (4)].op) == OP_LEQ || (yyvsp[(2) - (4)].op) == OP_GTR || (yyvsp[(2) - (4)].op) == OP_GEQ)
            (yyvsp[(1) - (4)].val).type = (yyvsp[(4) - (4)].val).type = TYPE_BOOL;
        if (((yyvsp[(1) - (4)].val).type == TYPE_BOOL) || ((yyvsp[(4) - (4)].val).type == TYPE_BOOL))        (yyval.val).type = TYPE_BOOL;
        else if (((yyvsp[(1) - (4)].val).type == TYPE_FLOAT) || ((yyvsp[(4) - (4)].val).type == TYPE_FLOAT)) (yyval.val).type = TYPE_FLOAT;
        else                                                         (yyval.val).type = TYPE_INT;

        // detect error and print operation stack
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
            if (g_has_error)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name((yyvsp[(1) - (4)].val).type),
                    get_type_name((yyvsp[(4) - (4)].val).type));
            if (ops[op_idx] != OP_ASSIGN) {
                get_op_inst(buffer, (yyval.val).type, ops[op_idx]);
                if (ops[op_idx] == OP_EQL || ops[op_idx] == OP_NEQ || ops[op_idx] == OP_LSS
                || ops[op_idx] == OP_LEQ || ops[op_idx] == OP_GTR || ops[op_idx] == OP_GEQ) {
                    if (!c_exp) CODEGEN("\t%s Label_%d\n", buffer, lb_idx);
                    else {
                        
                    }
                } else
                    CODEGEN("\t%s\n", buffer);
            } else {
                Node* tmp = lookup_symbol(assign);
                CODEGEN("\t%s %d\n", get_ls_name((yyvsp[(1) - (4)].val).type, 1), tmp->addr);
            }
            printf("%s\n", get_op_name(ops[op_idx--]));
        }
        g_has_error = false;
    }
    break;

  case 30:
#line 374 "compiler_hw3.y"
    { (yyval.val).type = (yyvsp[(1) - (1)].val).type; }
    break;

  case 31:
#line 375 "compiler_hw3.y"
    {
        (yyval.val).type = (yyvsp[(2) - (2)].val).type;
        if ((yyval.val).type == TYPE_INT || (yyval.val).type == TYPE_BOOL) {
            if ((yyvsp[(1) - (2)].op) == OP_POS)      (yyval.val).i_val = (yyvsp[(2) - (2)].val).i_val;
            else if ((yyvsp[(1) - (2)].op) == OP_NEG) (yyval.val).i_val = -(yyvsp[(2) - (2)].val).i_val;
            else                   (yyval.val).i_val = ~(yyvsp[(2) - (2)].val).i_val + 2;
            if ((yyvsp[(1) - (2)].op) == OP_NEG) CODEGEN("\tineg\n");
        }
        else if ((yyval.val).type == TYPE_FLOAT) {
            (yyval.val).f_val = ((yyvsp[(1) - (2)].op) == OP_POS ? (yyvsp[(2) - (2)].val).f_val : -(yyvsp[(2) - (2)].val).f_val);
            if ((yyvsp[(1) - (2)].op) == OP_NEG) CODEGEN("\tfneg\n");
        }

        printf("%s\n", get_op_name((yyvsp[(1) - (2)].op)));
    }
    break;

  case 32:
#line 393 "compiler_hw3.y"
    { (yyval.op) = OP_LOR; }
    break;

  case 33:
#line 394 "compiler_hw3.y"
    { (yyval.op) = OP_LAND; }
    break;

  case 37:
#line 401 "compiler_hw3.y"
    { (yyval.op) = OP_EQL; }
    break;

  case 38:
#line 402 "compiler_hw3.y"
    { (yyval.op) = OP_NEQ; }
    break;

  case 39:
#line 403 "compiler_hw3.y"
    { (yyval.op) = OP_LSS; }
    break;

  case 40:
#line 404 "compiler_hw3.y"
    { (yyval.op) = OP_LEQ; }
    break;

  case 41:
#line 405 "compiler_hw3.y"
    { (yyval.op) = OP_GTR; }
    break;

  case 42:
#line 406 "compiler_hw3.y"
    { (yyval.op) = OP_GEQ; }
    break;

  case 43:
#line 410 "compiler_hw3.y"
    { (yyval.op) = OP_ADD; }
    break;

  case 44:
#line 411 "compiler_hw3.y"
    { (yyval.op) = OP_SUB; }
    break;

  case 45:
#line 415 "compiler_hw3.y"
    { (yyval.op) = OP_MUL; }
    break;

  case 46:
#line 416 "compiler_hw3.y"
    { (yyval.op) = OP_QUO; }
    break;

  case 47:
#line 417 "compiler_hw3.y"
    { (yyval.op) = OP_REM; }
    break;

  case 48:
#line 421 "compiler_hw3.y"
    { (yyval.op) = OP_POS; }
    break;

  case 49:
#line 422 "compiler_hw3.y"
    { (yyval.op) = OP_NEG; }
    break;

  case 50:
#line 423 "compiler_hw3.y"
    { (yyval.op) = OP_NOT; }
    break;

  case 53:
#line 431 "compiler_hw3.y"
    { (yyval.val).type = (yyvsp[(1) - (1)].val).type; }
    break;

  case 55:
#line 436 "compiler_hw3.y"
    { 
        Node* tmp = lookup_symbol((yyvsp[(1) - (1)].s_val));
        if (tmp) {
            (yyval.val).type = tmp->type;
            strcpy((yyval.val).name, tmp->name);
            CODEGEN("\t%s %d\n", get_ls_name((yyval.val).type, 0), tmp->addr);
            printf("IDENT (name=%s, address=%d)\n", tmp->name, tmp->addr);
        } else {
            printf("error:%d: undefined: %s\n", yylineno + 1, (yyvsp[(1) - (1)].s_val));
            g_has_error = true;
            (yyval.val).type = 0x3f3f3f3f;
        }
    }
    break;

  case 56:
#line 449 "compiler_hw3.y"
    { (yyval.val).type = (yyvsp[(2) - (3)].val).type; }
    break;

  case 57:
#line 453 "compiler_hw3.y"
    {
        (yyval.val).type = TYPE_INT;
        (yyval.val).i_val = atoi((yyvsp[(1) - (1)].s_val));
        printf("INT_LIT %d\n", (yyval.val).i_val);
        if ((yyval.val).i_val >= 0 && (yyval.val).i_val <= 5) CODEGEN("\ticonst_%d\n", (yyval.val).i_val);
        else                                CODEGEN("\tldc %d\n", (yyval.val).i_val);
    }
    break;

  case 58:
#line 460 "compiler_hw3.y"
    {
        (yyval.val).type = TYPE_FLOAT;
        (yyval.val).f_val = atof((yyvsp[(1) - (1)].s_val));
        printf("FLOAT_LIT %f\n", (yyval.val).f_val);
        CODEGEN("\tldc %f\n", (yyval.val).f_val);
    }
    break;

  case 59:
#line 466 "compiler_hw3.y"
    { 
        (yyval.val).type = TYPE_BOOL;
        (yyval.val).b_val = !strcmp((yyvsp[(1) - (1)].s_val), "true") ? true : false;
        (yyval.val).i_val = (yyval.val).b_val;
        printf("%s %d\n", (yyval.val).b_val ? "TRUE" : "FALSE", (yyval.val).b_val);
        CODEGEN("\tldc %d\n", (yyval.val).b_val);
    }
    break;

  case 60:
#line 473 "compiler_hw3.y"
    {
        (yyval.val).type = TYPE_STRING;
        (yyval.val).s_val = (yyvsp[(1) - (1)].s_val);
        printf("STRING_LIT %s\n", (yyvsp[(1) - (1)].s_val)); 
        CODEGEN("\tldc \"%s\"\n", (yyval.val).s_val);
    }
    break;

  case 61:
#line 484 "compiler_hw3.y"
    { 
        (yyval.s_val) = (yyvsp[(1) - (4)].s_val);
        if ((yyvsp[(1) - (4)].type) == TYPE_INT) {
            (yyval.val).type = TYPE_INT;
            puts("f2i");
            CODEGEN("\tf2i\n");
        } else { 
            (yyval.val).type = TYPE_FLOAT;
            puts("i2f");
            CODEGEN("\ti2f\n");
        }
    }
    break;

  case 70:
#line 509 "compiler_hw3.y"
    { returned = 1; }
    break;

  case 75:
#line 520 "compiler_hw3.y"
    {
        Node* tmp = lookup_symbol((yyvsp[(2) - (3)].s_val));

        // check re-declaration
        if (tmp) printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, (yyvsp[(2) - (3)].s_val), tmp->lineno);
        
        // push default val to operation stack
        if ((yyvsp[(3) - (3)].type) == TYPE_INT)         CODEGEN("\tldc 0\n");
        else if ((yyvsp[(3) - (3)].type) == TYPE_FLOAT)  CODEGEN("\tldc 0.0\n");
        else if ((yyvsp[(3) - (3)].type) == TYPE_STRING) CODEGEN("\tldc \"\"\n");
        else                        CODEGEN("\terror\n");

        // get insert node and write buffer
        tmp = insert_symbol((yyvsp[(2) - (3)].s_val), (yyvsp[(3) - (3)].type), "", yylineno);
        CODEGEN("\t%s %d\n",get_ls_name((yyvsp[(3) - (3)].type), 1), tmp->addr);
    }
    break;

  case 76:
#line 536 "compiler_hw3.y"
    { 
        Node* tmp = insert_symbol((yyvsp[(2) - (5)].s_val), (yyvsp[(3) - (5)].type), "", yylineno);

        // store variable to local variable
        CODEGEN("\t%s %d\n", get_ls_name((yyvsp[(3) - (5)].type), 1), tmp->addr);
    }
    break;

  case 77:
#line 545 "compiler_hw3.y"
    {
        ops[++op_idx] = (yyvsp[(2) - (2)].op);
        strcpy(assign, (yyvsp[(1) - (2)].val).name);
    }
    break;

  case 78:
#line 548 "compiler_hw3.y"
    {
        Node* tmp = lookup_symbol((yyvsp[(1) - (4)].val).name);
        while (op_idx) {
            // detect error
            if (((yyvsp[(1) - (4)].val).type == TYPE_INT || (yyvsp[(1) - (4)].val).type == TYPE_FLOAT) && ((yyvsp[(4) - (4)].val).type == TYPE_INT || (yyvsp[(4) - (4)].val).type == TYPE_FLOAT) && (yyvsp[(1) - (4)].val).type != (yyvsp[(4) - (4)].val).type)
                printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                    yylineno,
                    get_op_name(ops[op_idx]),
                    get_type_name((yyvsp[(1) - (4)].val).type),
                    get_type_name((yyvsp[(4) - (4)].val).type));
            if (g_has_error)
                    printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n",
                        yylineno,
                        get_op_name(ops[op_idx]),
                        get_type_name((yyvsp[(1) - (4)].val).type),
                        get_type_name((yyvsp[(4) - (4)].val).type));
            
            // push instruct
            if ((yyvsp[(2) - (4)].op) != OP_ASSIGN) {
                get_op_inst(buffer, (yyvsp[(1) - (4)].val).type, ops[op_idx]);
                CODEGEN("\t%s\n", buffer);
            }
            CODEGEN("\t%s %d\n", get_ls_name((yyvsp[(1) - (4)].val).type, 1), tmp->addr);
            printf("%s\n", get_op_name(ops[op_idx--]));
        }
        g_has_error = false;
    }
    break;

  case 79:
#line 578 "compiler_hw3.y"
    { (yyval.op) = OP_ASSIGN; }
    break;

  case 80:
#line 579 "compiler_hw3.y"
    { (yyval.op) = OP_ADD_ASSIGN; }
    break;

  case 81:
#line 580 "compiler_hw3.y"
    { (yyval.op) = OP_SUB_ASSIGN; }
    break;

  case 82:
#line 581 "compiler_hw3.y"
    { (yyval.op) = OP_MUL_ASSIGN; }
    break;

  case 83:
#line 582 "compiler_hw3.y"
    { (yyval.op) = OP_QUO_ASSIGN; }
    break;

  case 84:
#line 583 "compiler_hw3.y"
    { (yyval.op) = OP_REM_ASSIGN; }
    break;

  case 86:
#line 591 "compiler_hw3.y"
    {
        Node* node = lookup_symbol((yyvsp[(1) - (2)].val).name);
        puts("INC");
        if ((yyvsp[(1) - (2)].val).type == TYPE_INT) {
            CODEGEN("\tldc 1\n");
            CODEGEN("\tiadd\n");
            CODEGEN("\tistore %d\n", node->addr);
        }
        else {
            CODEGEN("\tldc 1.0\n");
            CODEGEN("\tfadd\n");
            CODEGEN("\tfstore %d\n", node->addr);
        }
    }
    break;

  case 87:
#line 605 "compiler_hw3.y"
    {
        Node* node = lookup_symbol((yyvsp[(1) - (2)].val).name);
        puts("DEC");
        if ((yyvsp[(1) - (2)].val).type == TYPE_INT) {
            CODEGEN("\tldc -1\n");
            CODEGEN("\tiadd\n");
            CODEGEN("\tistore %d\n", node->addr);
        } else { 
            CODEGEN("\tldc -1.0\n");
            CODEGEN("\tfadd\n");
            CODEGEN("\tfstore %d\n", node->addr);
        }
    }
    break;

  case 88:
#line 621 "compiler_hw3.y"
    { create_symbol(scope++); 
    }
    break;

  case 89:
#line 622 "compiler_hw3.y"
    { dump_symbol(); }
    break;

  case 92:
#line 631 "compiler_hw3.y"
    {
        CODEGEN("Label_%d:\n", lb_idx++);
    }
    break;

  case 93:
#line 633 "compiler_hw3.y"
    {
        CODEGEN("Exit_%d:\n", --lb_idx);
    }
    break;

  case 94:
#line 639 "compiler_hw3.y"
    {
        if ((yyvsp[(1) - (1)].val).type != TYPE_BOOL)
            printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 1, get_type_name((yyvsp[(1) - (1)].val).type));
        else
            CODEGEN("\tgoto Exit_%d\n", lb_idx);
    }
    break;

  case 95:
#line 648 "compiler_hw3.y"
    {
        CODEGEN("For_%d:\n", fr_cnt++);
    }
    break;

  case 96:
#line 650 "compiler_hw3.y"
    { 
        CODEGEN("Label_%d:\n", lb_idx++);
    }
    break;

  case 97:
#line 652 "compiler_hw3.y"
    {
        CODEGEN("\tgoto For_%d\n", --fr_cnt);
        CODEGEN("Exit_%d:\n", --lb_idx);
    }
    break;

  case 98:
#line 659 "compiler_hw3.y"
    {
        CODEGEN("\tgoto Switch_%d\n", sw_cnt++);
    }
    break;

  case 99:
#line 661 "compiler_hw3.y"
    {
        CODEGEN("Switch_%d:\n", sw_cnt - 1);
        CODEGEN("\tlookupswitch\n");
        for (int i = 0; i < ks_idx; i++)
            CODEGEN("\t\t%d: Case_%d\n", kase[i], kase[i]);
        CODEGEN("\t\tdefault: Default_%d\n", sw_cnt - 1);
        CODEGEN("End_%d:\n", sw_cnt - 1);
        ks_idx = 0;
    }
    break;

  case 100:
#line 673 "compiler_hw3.y"
    {
        printf("case %s\n", (yyvsp[(2) - (2)].s_val));
        CODEGEN("Case_%s:\n", (yyvsp[(2) - (2)].s_val));
        kase[ks_idx++] = atoi((yyvsp[(2) - (2)].s_val));
    }
    break;

  case 101:
#line 677 "compiler_hw3.y"
    {
        CODEGEN("\tgoto End_%d\n", sw_cnt - 1);
    }
    break;

  case 102:
#line 680 "compiler_hw3.y"
    {
        CODEGEN("Default_%d:\n", sw_cnt - 1);
    }
    break;

  case 103:
#line 682 "compiler_hw3.y"
    {
        CODEGEN("\tgoto End_%d\n", sw_cnt - 1);
    }
    break;

  case 104:
#line 688 "compiler_hw3.y"
    {
        c_exp = 1;
    }
    break;

  case 105:
#line 690 "compiler_hw3.y"
    {
        c_exp = 0;
        printf("PRINT %s\n", get_type_name((yyvsp[(4) - (5)].val).type));
        CODEGEN("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        CODEGEN("\tswap\n");
        CODEGEN("\tinvokevirtual java/io/PrintStream/print(%s)V\n", get_print_type((yyvsp[(4) - (5)].val).type));
    }
    break;

  case 106:
#line 697 "compiler_hw3.y"
    {
        c_exp = 1;
    }
    break;

  case 107:
#line 699 "compiler_hw3.y"
    {
        c_exp = 0;
        printf("PRINTLN %s\n", get_type_name((yyvsp[(4) - (5)].val).type));
        CODEGEN("\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        CODEGEN("\tswap\n");
        CODEGEN("\tinvokevirtual java/io/PrintStream/println(%s)V\n", get_print_type((yyvsp[(4) - (5)].val).type));
    }
    break;


/* Line 1267 of yacc.c.  */
#line 2406 "y.tab.c"
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


#line 708 "compiler_hw3.y"


/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    CODEGEN(".source hw3.j\n");
    CODEGEN(".class public Main\n");
    CODEGEN(".super java/lang/Object\n");

    /* Symbol table init */
    // Add your code

    yylineno = 0;
    yyparse();

    while (scope) dump_symbol();

    /* Symbol table dump */
    // Add your code

	printf("Total lines: %d\n", yylineno + 1);
    fclose(fout);
    fclose(yyin);

    if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
    return 0;
}


static void create_symbol(int scope) {
    printf("> Create symbol table (scope level %d)\n", scope);
    s_table[scope] = (Table*)malloc(sizeof(Table));
    s_table[scope]->head = NULL;
    s_table[scope]->tail = NULL;
    s_table[scope]->cnt = 0; 
}

static Node* insert_symbol(char* name, type_t type, char* func, int lineno) {
    Node* tmp = init_node(name, type, func, lineno);
    insert_node(tmp);

    printf("> Insert `%s` (addr: %d) to scope level %d\n", tmp->name, tmp->addr, scope - 1);
    return tmp;
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

const char* get_ls_name(type_t type, int inst) {
    // inst = 0 => load
    // inst = 1 => store
    switch (type) {
        case TYPE_INT:
            return (!inst ? "iload" : "istore");
        case TYPE_FLOAT:
            return (!inst ? "fload" : "fstore");
        case TYPE_BOOL:
            return (!inst ? "iload" : "istore");
        case TYPE_STRING:
            return (!inst ? "aload" : "astore");
        case TYPE_FUNC:
            return "func";
        default:
            return "ERROR";
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

const char* get_print_type(type_t type) {
    switch (type) {
        case TYPE_INT:
            return "I";
        case TYPE_FLOAT:
            return "F";
        case TYPE_BOOL:
            return "Z";
        case TYPE_STRING:
            return "Ljava/lang/String;";
        case TYPE_FUNC:
            return "func";
        default:
            return "ERROR";
    }
}

void get_op_inst(char* buf, type_t type, op_t op) {
    char tmp[16];
    int idx = 0;

    buf[0] = get_type_name(type)[0], idx = 1;
    if (type == -1 || op == OP_EQL || op == OP_NEQ || op == OP_LSS || op == OP_LEQ || op == OP_GTR || op == OP_GTR || op == OP_GEQ || op == OP_LOR || op == OP_LAND)
        idx = 0;

    switch (op) {
        case OP_QUO:
        case OP_QUO_ASSIGN:
            strcpy(tmp, "DIV");
            break;
        case OP_LOR:
            strcpy(tmp, "IOR");
            break;
        case OP_LAND:
            strcpy(tmp, "IAND");
            break;
        case OP_EQL:
            strcpy(tmp, "IF_ICMPEQ");
            break;
        case OP_NEQ:
            strcpy(tmp, "IF_ICMPNE");
            break;
        case OP_LSS:
            strcpy(tmp, "IF_ICMPLS");
            break;
        case OP_LEQ:
            strcpy(tmp, "IF_ICMPLE");
            break;
        case OP_GTR:
            if (type == TYPE_INT || type == TYPE_BOOL) c_exp ? strcpy(tmp, "IFGT") : strcpy(tmp, "IF_ICMPGT");
            else                                       strcpy(tmp, "fcmpg");
            break;
        case OP_GEQ:
            strcpy(tmp, "IF_ICMPGE");
            break;
        default:
            strcpy(tmp, get_op_name(op));
            break;
    }

    for (int i = 0; i < strlen(tmp); i++)
        buf[i + idx] = ((tmp[i] >= 'A' && tmp[i] <= 'Z') ? (char)(tmp[i] + 32) : tmp[i]);
    buf[strlen(tmp) + idx] = '\0';
}
