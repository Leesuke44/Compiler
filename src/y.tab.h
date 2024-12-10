
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     INUMBER = 259,
     FNUMBER = 260,
     PROGRAM = 261,
     START = 262,
     END = 263,
     DECLARE = 264,
     AS = 265,
     INTEGER = 266,
     INTEGER_ARRAY = 267,
     FLOAT = 268,
     FLOAT_ARRAY = 269,
     FOR = 270,
     ENDFOR = 271,
     TO = 272,
     DOWNTO = 273,
     UMINUS = 274
   };
#endif
/* Tokens.  */
#define NAME 258
#define INUMBER 259
#define FNUMBER 260
#define PROGRAM 261
#define START 262
#define END 263
#define DECLARE 264
#define AS 265
#define INTEGER 266
#define INTEGER_ARRAY 267
#define FLOAT 268
#define FLOAT_ARRAY 269
#define FOR 270
#define ENDFOR 271
#define TO 272
#define DOWNTO 273
#define UMINUS 274




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 8 "yacc_microEX_compiler.y"

	int ival;
	float fval;
	struct symtab *symp;
	char* charp;
	int dataType;
	struct AssignInfo *assignInfo;
	struct ForloopInfo *forloopInfo;  



/* Line 1676 of yacc.c  */
#line 102 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


