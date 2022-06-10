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
/* Line 1529 of yacc.c.  */
#line 170 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

