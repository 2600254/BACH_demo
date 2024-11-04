/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    AS = 260,                      /* AS  */
    CREATE = 261,                  /* CREATE  */
    DROP = 262,                    /* DROP  */
    GROUP = 263,                   /* GROUP  */
    TABLE = 264,                   /* TABLE  */
    TABLES = 265,                  /* TABLES  */
    INDEX = 266,                   /* INDEX  */
    VIEW = 267,                    /* VIEW  */
    CALC = 268,                    /* CALC  */
    SELECT = 269,                  /* SELECT  */
    DESC = 270,                    /* DESC  */
    SHOW = 271,                    /* SHOW  */
    SYNC = 272,                    /* SYNC  */
    INSERT = 273,                  /* INSERT  */
    DELETE = 274,                  /* DELETE  */
    UPDATE = 275,                  /* UPDATE  */
    LBRACE = 276,                  /* LBRACE  */
    RBRACE = 277,                  /* RBRACE  */
    LBRACK = 278,                  /* LBRACK  */
    RBRACK = 279,                  /* RBRACK  */
    COMMA = 280,                   /* COMMA  */
    TRX_BEGIN = 281,               /* TRX_BEGIN  */
    TRX_COMMIT = 282,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 283,            /* TRX_ROLLBACK  */
    L2_DISTANCE_T = 284,           /* L2_DISTANCE_T  */
    COSINE_DISTANCE_T = 285,       /* COSINE_DISTANCE_T  */
    INNER_PRODUCT_T = 286,         /* INNER_PRODUCT_T  */
    INT_T = 287,                   /* INT_T  */
    DATE_T = 288,                  /* DATE_T  */
    TEXT_T = 289,                  /* TEXT_T  */
    VECTOR_T = 290,                /* VECTOR_T  */
    STRING_T = 291,                /* STRING_T  */
    FLOAT_T = 292,                 /* FLOAT_T  */
    HELP = 293,                    /* HELP  */
    EXIT = 294,                    /* EXIT  */
    DOT = 295,                     /* DOT  */
    INTO = 296,                    /* INTO  */
    VALUES = 297,                  /* VALUES  */
    FROM = 298,                    /* FROM  */
    WHERE = 299,                   /* WHERE  */
    AND = 300,                     /* AND  */
    OR = 301,                      /* OR  */
    SET = 302,                     /* SET  */
    ON = 303,                      /* ON  */
    LOAD_DATA = 304,               /* LOAD_DATA  */
    INFILE = 305,                  /* INFILE  */
    MAX_T = 306,                   /* MAX_T  */
    MIN_T = 307,                   /* MIN_T  */
    AVG_T = 308,                   /* AVG_T  */
    SUM_T = 309,                   /* SUM_T  */
    COUNT_T = 310,                 /* COUNT_T  */
    EXPLAIN = 311,                 /* EXPLAIN  */
    STORAGE = 312,                 /* STORAGE  */
    FORMAT = 313,                  /* FORMAT  */
    INNER = 314,                   /* INNER  */
    JOIN = 315,                    /* JOIN  */
    EQ = 316,                      /* EQ  */
    LT = 317,                      /* LT  */
    GT = 318,                      /* GT  */
    LE = 319,                      /* LE  */
    GE = 320,                      /* GE  */
    NE = 321,                      /* NE  */
    NOT = 322,                     /* NOT  */
    LIKE = 323,                    /* LIKE  */
    IN = 324,                      /* IN  */
    EXISTS = 325,                  /* EXISTS  */
    UNIQUE = 326,                  /* UNIQUE  */
    ORDER = 327,                   /* ORDER  */
    ASC = 328,                     /* ASC  */
    NULL_T = 329,                  /* NULL_T  */
    IS = 330,                      /* IS  */
    HAVING = 331,                  /* HAVING  */
    NUMBER = 332,                  /* NUMBER  */
    FLOAT = 333,                   /* FLOAT  */
    ID = 334,                      /* ID  */
    SSS = 335,                     /* SSS  */
    AGGR = 336,                    /* AGGR  */
    DATE_STR = 337,                /* DATE_STR  */
    UMINUS = 338                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 165 "yacc_sql.y"

  ParsedSqlNode *                            sql_node;
  Expression *                               condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<Expression*> *                 expression_list;
  std::vector<float> *                       float_list;
  UpdateKV *                                 update_kv;
  std::vector<UpdateKV> *                    update_kv_list;
  std::vector<Value> *                       value_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  InnerJoinSqlNode *                inner_joins;
  std::vector<InnerJoinSqlNode> *   inner_joins_list;
  OrderBySqlNode*                   orderby_unit;
  std::vector<OrderBySqlNode> *     orderby_unit_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;

#line 173 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
