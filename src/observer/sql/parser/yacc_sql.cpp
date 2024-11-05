/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"
#include "common/type/date_type.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

bool exp2value(Expression *exp, Value &value){
  if(exp->type() == ExprType::VALUE) {
    ValueExpr *tmp = static_cast<ValueExpr*>(exp);
    value = tmp->get_value();
    return true;
  }
  if(exp->type() == ExprType::ARITHMETIC) {
    ArithmeticExpr * tmp = static_cast<ArithmeticExpr *>(exp);
    if(tmp->arithmetic_type() != ArithmeticExpr::Type::NEGATIVE && tmp->left()->type() != ExprType::VALUE) {
      return false;
    }
    RC rc = tmp->try_get_value(value);
    if(rc != RC::SUCCESS) {
      return false;
    }
    return true;
  }
  return false;
}


#line 146 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_AS = 5,                         /* AS  */
  YYSYMBOL_CREATE = 6,                     /* CREATE  */
  YYSYMBOL_DROP = 7,                       /* DROP  */
  YYSYMBOL_GROUP = 8,                      /* GROUP  */
  YYSYMBOL_TABLE = 9,                      /* TABLE  */
  YYSYMBOL_TABLES = 10,                    /* TABLES  */
  YYSYMBOL_INDEX = 11,                     /* INDEX  */
  YYSYMBOL_VIEW = 12,                      /* VIEW  */
  YYSYMBOL_CALC = 13,                      /* CALC  */
  YYSYMBOL_SELECT = 14,                    /* SELECT  */
  YYSYMBOL_DESC = 15,                      /* DESC  */
  YYSYMBOL_SHOW = 16,                      /* SHOW  */
  YYSYMBOL_SYNC = 17,                      /* SYNC  */
  YYSYMBOL_INSERT = 18,                    /* INSERT  */
  YYSYMBOL_DELETE = 19,                    /* DELETE  */
  YYSYMBOL_UPDATE = 20,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 21,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 22,                    /* RBRACE  */
  YYSYMBOL_LBRACK = 23,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 24,                    /* RBRACK  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_L2_DISTANCE_T = 29,             /* L2_DISTANCE_T  */
  YYSYMBOL_COSINE_DISTANCE_T = 30,         /* COSINE_DISTANCE_T  */
  YYSYMBOL_INNER_PRODUCT_T = 31,           /* INNER_PRODUCT_T  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_DATE_T = 33,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 34,                    /* TEXT_T  */
  YYSYMBOL_VECTOR_T = 35,                  /* VECTOR_T  */
  YYSYMBOL_STRING_T = 36,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 37,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_OR = 46,                        /* OR  */
  YYSYMBOL_SET = 47,                       /* SET  */
  YYSYMBOL_ON = 48,                        /* ON  */
  YYSYMBOL_LOAD_DATA = 49,                 /* LOAD_DATA  */
  YYSYMBOL_INFILE = 50,                    /* INFILE  */
  YYSYMBOL_MAX_T = 51,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 52,                     /* MIN_T  */
  YYSYMBOL_AVG_T = 53,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 54,                     /* SUM_T  */
  YYSYMBOL_COUNT_T = 55,                   /* COUNT_T  */
  YYSYMBOL_EXPLAIN = 56,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 57,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 58,                    /* FORMAT  */
  YYSYMBOL_INNER = 59,                     /* INNER  */
  YYSYMBOL_JOIN = 60,                      /* JOIN  */
  YYSYMBOL_EQ = 61,                        /* EQ  */
  YYSYMBOL_LT = 62,                        /* LT  */
  YYSYMBOL_GT = 63,                        /* GT  */
  YYSYMBOL_LE = 64,                        /* LE  */
  YYSYMBOL_GE = 65,                        /* GE  */
  YYSYMBOL_NE = 66,                        /* NE  */
  YYSYMBOL_NOT = 67,                       /* NOT  */
  YYSYMBOL_LIKE = 68,                      /* LIKE  */
  YYSYMBOL_IN = 69,                        /* IN  */
  YYSYMBOL_EXISTS = 70,                    /* EXISTS  */
  YYSYMBOL_UNIQUE = 71,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 72,                     /* ORDER  */
  YYSYMBOL_ASC = 73,                       /* ASC  */
  YYSYMBOL_NULL_T = 74,                    /* NULL_T  */
  YYSYMBOL_IS = 75,                        /* IS  */
  YYSYMBOL_HAVING = 76,                    /* HAVING  */
  YYSYMBOL_WITH = 77,                      /* WITH  */
  YYSYMBOL_LIMIT = 78,                     /* LIMIT  */
  YYSYMBOL_NUMBER = 79,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 80,                     /* FLOAT  */
  YYSYMBOL_ID = 81,                        /* ID  */
  YYSYMBOL_SSS = 82,                       /* SSS  */
  YYSYMBOL_AGGR = 83,                      /* AGGR  */
  YYSYMBOL_DATE_STR = 84,                  /* DATE_STR  */
  YYSYMBOL_85_ = 85,                       /* '+'  */
  YYSYMBOL_86_ = 86,                       /* '-'  */
  YYSYMBOL_87_ = 87,                       /* '*'  */
  YYSYMBOL_88_ = 88,                       /* '/'  */
  YYSYMBOL_UMINUS = 89,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 90,                  /* $accept  */
  YYSYMBOL_commands = 91,                  /* commands  */
  YYSYMBOL_command_wrapper = 92,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 93,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 94,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 95,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 96,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 97,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 98,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 99,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 100,         /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 101,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 102,        /* create_index_stmt  */
  YYSYMBOL_vector_idx_prop_list = 103,     /* vector_idx_prop_list  */
  YYSYMBOL_vector_idx_prop = 104,          /* vector_idx_prop  */
  YYSYMBOL_unique_option = 105,            /* unique_option  */
  YYSYMBOL_idx_col_list = 106,             /* idx_col_list  */
  YYSYMBOL_drop_index_stmt = 107,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 108,        /* create_table_stmt  */
  YYSYMBOL_as_option = 109,                /* as_option  */
  YYSYMBOL_attr_def_list = 110,            /* attr_def_list  */
  YYSYMBOL_attr_def = 111,                 /* attr_def  */
  YYSYMBOL_null_option = 112,              /* null_option  */
  YYSYMBOL_create_view_stmt = 113,         /* create_view_stmt  */
  YYSYMBOL_number = 114,                   /* number  */
  YYSYMBOL_type = 115,                     /* type  */
  YYSYMBOL_insert_stmt = 116,              /* insert_stmt  */
  YYSYMBOL_value_list = 117,               /* value_list  */
  YYSYMBOL_value = 118,                    /* value  */
  YYSYMBOL_float_list = 119,               /* float_list  */
  YYSYMBOL_storage_format = 120,           /* storage_format  */
  YYSYMBOL_delete_stmt = 121,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 122,              /* update_stmt  */
  YYSYMBOL_update_kv_list = 123,           /* update_kv_list  */
  YYSYMBOL_update_kv = 124,                /* update_kv  */
  YYSYMBOL_from_list = 125,                /* from_list  */
  YYSYMBOL_alias = 126,                    /* alias  */
  YYSYMBOL_from_node = 127,                /* from_node  */
  YYSYMBOL_join_list = 128,                /* join_list  */
  YYSYMBOL_sub_query_expr = 129,           /* sub_query_expr  */
  YYSYMBOL_select_stmt = 130,              /* select_stmt  */
  YYSYMBOL_limit_clause = 131,             /* limit_clause  */
  YYSYMBOL_calc_stmt = 132,                /* calc_stmt  */
  YYSYMBOL_expression_list = 133,          /* expression_list  */
  YYSYMBOL_expression = 134,               /* expression  */
  YYSYMBOL_aggre_type = 135,               /* aggre_type  */
  YYSYMBOL_rel_attr = 136,                 /* rel_attr  */
  YYSYMBOL_where = 137,                    /* where  */
  YYSYMBOL_condition = 138,                /* condition  */
  YYSYMBOL_comp_op = 139,                  /* comp_op  */
  YYSYMBOL_exists_op = 140,                /* exists_op  */
  YYSYMBOL_group_by = 141,                 /* group_by  */
  YYSYMBOL_having = 142,                   /* having  */
  YYSYMBOL_sort_unit = 143,                /* sort_unit  */
  YYSYMBOL_sort_list = 144,                /* sort_list  */
  YYSYMBOL_opt_order_by = 145,             /* opt_order_by  */
  YYSYMBOL_load_data_stmt = 146,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 147,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 148,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 149             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  78
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   347

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  307

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   340


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    87,    85,     2,    86,     2,    88,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      89
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   273,   273,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   305,   311,   316,   322,   328,   334,
     340,   347,   353,   361,   380,   402,   405,   417,   420,   429,
     436,   443,   450,   462,   465,   472,   475,   488,   498,   519,
     540,   556,   559,   567,   570,   583,   592,   605,   608,   612,
     619,   626,   645,   648,   649,   650,   651,   652,   653,   656,
     673,   676,   685,   701,   705,   709,   725,   731,   735,   743,
     746,   751,   756,   766,   779,   782,   789,   801,   823,   826,
     839,   850,   853,   865,   868,   871,   877,   893,   896,   911,
     919,   924,   963,   966,   972,   981,   990,  1005,  1008,  1011,
    1014,  1017,  1020,  1023,  1028,  1033,  1037,  1040,  1044,  1047,
    1056,  1059,  1062,  1068,  1073,  1078,  1089,  1092,  1098,  1102,
    1107,  1111,  1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,
    1126,  1127,  1128,  1129,  1133,  1134,  1140,  1143,  1149,  1152,
    1159,  1166,  1173,  1181,  1188,  1196,  1199,  1206,  1219,  1227,
    1237,  1238
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "AS", "CREATE", "DROP", "GROUP", "TABLE", "TABLES", "INDEX", "VIEW",
  "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "LBRACE", "RBRACE", "LBRACK", "RBRACK", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "L2_DISTANCE_T", "COSINE_DISTANCE_T",
  "INNER_PRODUCT_T", "INT_T", "DATE_T", "TEXT_T", "VECTOR_T", "STRING_T",
  "FLOAT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "OR", "SET", "ON", "LOAD_DATA", "INFILE", "MAX_T", "MIN_T",
  "AVG_T", "SUM_T", "COUNT_T", "EXPLAIN", "STORAGE", "FORMAT", "INNER",
  "JOIN", "EQ", "LT", "GT", "LE", "GE", "NE", "NOT", "LIKE", "IN",
  "EXISTS", "UNIQUE", "ORDER", "ASC", "NULL_T", "IS", "HAVING", "WITH",
  "LIMIT", "NUMBER", "FLOAT", "ID", "SSS", "AGGR", "DATE_STR", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "vector_idx_prop_list",
  "vector_idx_prop", "unique_option", "idx_col_list", "drop_index_stmt",
  "create_table_stmt", "as_option", "attr_def_list", "attr_def",
  "null_option", "create_view_stmt", "number", "type", "insert_stmt",
  "value_list", "value", "float_list", "storage_format", "delete_stmt",
  "update_stmt", "update_kv_list", "update_kv", "from_list", "alias",
  "from_node", "join_list", "sub_query_expr", "select_stmt",
  "limit_clause", "calc_stmt", "expression_list", "expression",
  "aggre_type", "rel_attr", "where", "condition", "comp_op", "exists_op",
  "group_by", "having", "sort_unit", "sort_list", "opt_order_by",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     258,   110,    45,   176,   176,   -52,    22,  -211,    -1,    14,
     -16,  -211,  -211,  -211,  -211,  -211,   -12,    10,   258,   109,
     112,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,    39,    46,   119,  -211,   133,    68,    74,    87,
      27,   135,   141,   142,  -211,  -211,  -211,   124,  -211,  -211,
    -211,   176,   125,  -211,  -211,  -211,     0,   156,  -211,   136,
    -211,  -211,    99,   102,   137,   132,   103,  -211,  -211,  -211,
    -211,    15,    16,   105,   115,  -211,   153,   181,   196,   177,
     194,   198,   176,   176,   176,   -68,  -211,   138,   143,  -211,
     176,   176,   176,   176,   201,   176,   146,   188,   190,   151,
     149,   195,  -211,   157,   223,   223,   158,   192,   193,   161,
    -211,  -211,    27,    27,  -211,    38,    55,    72,  -211,  -211,
    -211,  -211,    26,    26,  -211,  -211,   176,   -14,     2,   218,
     224,   108,  -211,   183,   221,  -211,   238,   180,   226,   191,
    -211,   228,   168,   173,  -211,  -211,  -211,   176,   176,   176,
    -211,  -211,   202,   146,   190,   149,   197,  -211,   254,    88,
     176,   176,   151,   190,   185,  -211,  -211,  -211,  -211,  -211,
    -211,     1,   157,   246,   211,  -211,   189,   257,   259,   260,
       4,     8,    17,   222,  -211,   218,   275,   262,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,    67,  -211,  -211,   225,   176,
     108,   108,   -36,   -36,   221,  -211,  -211,   209,   215,  -211,
    -211,   226,    13,   229,   228,   286,   212,   213,  -211,  -211,
    -211,   214,  -211,   294,   227,   176,   277,  -211,  -211,  -211,
     -36,  -211,   255,  -211,  -211,   279,  -211,  -211,   223,  -211,
     230,  -211,   223,   280,   228,     2,   176,   108,   232,     6,
     123,  -211,   -19,   191,  -211,  -211,   231,   284,   261,  -211,
      88,   306,   234,  -211,  -211,  -211,  -211,   292,  -211,   108,
     176,   245,  -211,   244,   -21,    -9,   301,  -211,  -211,   266,
     303,  -211,  -211,  -211,   176,   -20,   244,   308,  -211,  -211,
    -211,  -211,  -211,  -211,   303,  -211,  -211
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    43,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     160,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,     8,    14,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,    44,     0,     0,     0,     0,
      79,     0,     0,     0,    78,    73,    74,   124,    76,   123,
      75,     0,   115,   113,   118,   104,    95,     0,   114,   100,
      32,    31,     0,     0,     0,     0,     0,   158,     1,   161,
       2,    51,     0,     0,     0,    30,     0,     0,     0,    80,
      81,     0,     0,     0,     0,     0,   111,     0,     0,    93,
       0,     0,     0,     0,   105,     0,     0,     0,   126,     0,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
      99,   119,    79,    79,    77,     0,     0,     0,   125,   116,
     117,    94,   107,   108,   109,   110,     0,     0,    95,    91,
       0,     0,    86,     0,    88,   159,     0,     0,    53,    84,
      60,    45,     0,     0,    47,    82,    83,     0,     0,     0,
     106,   112,    97,     0,   126,     0,     0,   144,     0,   127,
       0,     0,     0,   126,     0,    63,    66,    67,    68,    64,
      65,    57,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,    96,    91,   146,    70,   145,   132,
     133,   134,   135,   136,   137,     0,   138,   142,   141,     0,
       0,     0,   129,    90,    88,    87,   157,     0,     0,    58,
      56,    53,    84,     0,    45,     0,     0,     0,   120,   121,
     122,     0,    92,     0,   148,     0,     0,   139,   143,   140,
     128,   130,   131,    89,    62,     0,    59,    54,     0,    48,
       0,    46,     0,     0,    45,    95,     0,     0,   155,   113,
      70,    69,    57,    84,    85,    61,     0,     0,     0,   147,
     149,     0,   102,    71,    72,    55,    49,     0,    33,     0,
       0,     0,   101,    37,    97,   150,   153,   156,   103,     0,
      35,    98,   151,   152,     0,     0,    37,     0,   154,    40,
      41,    42,    39,    38,    35,    34,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,   313,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,    28,    37,  -211,  -207,  -211,  -211,   113,
     116,   152,    76,  -211,  -211,  -211,  -211,  -113,  -107,    31,
    -210,  -211,  -211,   122,   171,   150,  -134,   184,    60,  -211,
     -48,  -211,  -211,    -4,   -59,  -211,  -211,  -150,  -195,  -211,
    -211,  -211,  -211,  -211,    52,  -211,  -211,  -211,  -211,  -211
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   297,   290,    46,   187,    31,    32,   114,
     183,   148,   220,    33,   245,   181,    34,   236,    63,    91,
     185,    35,    36,   173,   144,   164,   104,   139,   194,    64,
      37,   282,    38,    65,    66,    67,    68,   142,   169,   209,
     170,   234,   258,   286,   287,   272,    39,    40,    41,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    87,    96,   145,   162,    98,   292,    98,   161,   299,
     300,   301,   249,   128,   196,   241,   242,   251,   112,   129,
     112,   115,   217,   215,   210,   211,   228,   -51,   -70,    70,
     229,   235,    71,   125,   126,   127,   113,   116,   193,   230,
      72,   132,   133,   134,   135,    88,   137,   267,   218,   100,
     101,   102,   103,   276,    47,   219,    48,    73,   197,   302,
      76,   303,   270,   157,   293,    74,   149,   150,   218,    75,
     184,   100,   101,   102,   103,   219,   100,   101,   102,   103,
     158,    99,   168,    99,   284,   100,   101,   102,   103,   100,
     101,   102,   103,   100,   101,   102,   103,   159,   190,   191,
     192,     4,   100,   101,   102,   103,    89,    90,    49,    78,
      50,   212,   213,   102,   103,    79,    51,    52,    53,    42,
      81,   268,    43,   100,   101,   102,   103,    82,   259,    49,
      83,    50,   160,   210,   211,   237,   238,    51,    52,    53,
     100,   101,   102,   103,    84,    44,   273,   274,   235,    85,
     240,   168,   168,   155,   156,    86,    92,   100,   101,   102,
     103,    54,    93,    94,    95,    97,    55,    56,    57,    58,
      59,    60,    50,    61,    62,   166,   260,   105,   167,   106,
     107,    45,    54,   108,   109,   111,   117,    55,    56,    57,
      58,    59,    60,   110,    61,    62,   118,    49,   168,    50,
     263,   119,   122,   120,   265,    51,    52,    53,   100,   101,
     102,   103,   175,   176,   177,   178,   179,   180,   121,   123,
     168,   285,   124,    54,   131,   130,   136,   138,    55,    56,
     140,    58,   143,    60,   141,   285,   146,     4,   147,   151,
     152,   153,   154,   163,   171,   165,   172,   174,   184,   188,
      54,   182,   269,   186,   189,    55,    56,    57,    58,    59,
      60,   193,    61,    62,     1,     2,   216,   198,   222,   223,
     224,     3,     4,     5,     6,     7,     8,     9,    10,   225,
     226,   227,   231,   233,    11,    12,    13,   235,   244,   246,
     250,   252,   239,   253,   254,   255,    14,    15,   256,   261,
     210,   262,   266,   257,   271,    16,   278,    17,   277,   279,
     280,   264,   281,   283,    18,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   288,   289,   294,   295,   296,   208,
     305,    77,   306,   304,   221,   248,   243,   247,   275,   100,
     101,   102,   103,   214,   291,   232,   298,   195
};

static const yytype_int16 yycheck[] =
{
       4,    49,    61,   110,   138,     5,    15,     5,    22,    29,
      30,    31,   222,    81,   164,   210,   211,   224,     5,    87,
       5,     5,    21,   173,    45,    46,    22,    14,    22,    81,
      22,    25,    10,    92,    93,    94,    21,    21,    59,    22,
      41,   100,   101,   102,   103,    49,   105,   254,    67,    85,
      86,    87,    88,   263,     9,    74,    11,    43,   165,    79,
      50,    81,   257,    25,    73,    81,   114,   115,    67,    81,
      57,    85,    86,    87,    88,    74,    85,    86,    87,    88,
      25,    81,   141,    81,   279,    85,    86,    87,    88,    85,
      86,    87,    88,    85,    86,    87,    88,    25,   157,   158,
     159,    14,    85,    86,    87,    88,    79,    80,    21,     0,
      23,   170,   171,    87,    88,     3,    29,    30,    31,     9,
      81,   255,    12,    85,    86,    87,    88,    81,   235,    21,
      11,    23,   136,    45,    46,    68,    69,    29,    30,    31,
      85,    86,    87,    88,    11,    35,   259,   260,    25,    81,
     209,   210,   211,   122,   123,    81,    21,    85,    86,    87,
      88,    74,    21,    21,    40,    40,    79,    80,    81,    82,
      83,    84,    23,    86,    87,    67,   235,    21,    70,    43,
      81,    71,    74,    81,    47,    82,    81,    79,    80,    81,
      82,    83,    84,    61,    86,    87,    81,    21,   257,    23,
     248,    48,    25,    22,   252,    29,    30,    31,    85,    86,
      87,    88,    32,    33,    34,    35,    36,    37,    22,    25,
     279,   280,    24,    74,    81,    87,    25,    81,    79,    80,
      42,    82,    81,    84,    44,   294,    41,    14,    81,    81,
      48,    48,    81,    25,    61,    21,    25,     9,    57,    81,
      74,    25,   256,    25,    81,    79,    80,    81,    82,    83,
      84,    59,    86,    87,     6,     7,    81,    70,    22,    58,
      81,    13,    14,    15,    16,    17,    18,    19,    20,    22,
      21,    21,    60,     8,    26,    27,    28,    25,    79,    74,
      61,     5,    67,    81,    81,    81,    38,    39,     4,    22,
      45,    22,    22,    76,    72,    47,    22,    49,    77,    48,
       4,    81,    78,    21,    56,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    79,    81,    25,    61,    25,    75,
      22,    18,   304,   296,   182,   222,   214,   221,   262,    85,
      86,    87,    88,   172,   284,   195,   294,   163
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    13,    14,    15,    16,    17,    18,    19,
      20,    26,    27,    28,    38,    39,    47,    49,    56,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   107,   108,   113,   116,   121,   122,   130,   132,   146,
     147,   148,     9,    12,    35,    71,   105,     9,    11,    21,
      23,    29,    30,    31,    74,    79,    80,    81,    82,    83,
      84,    86,    87,   118,   129,   133,   134,   135,   136,   133,
      81,    10,    41,    43,    81,    81,    50,    92,     0,     3,
     149,    81,    81,    11,    11,    81,    81,   130,   133,    79,
      80,   119,    21,    21,    21,    40,   134,    40,     5,    81,
      85,    86,    87,    88,   126,    21,    43,    81,    81,    47,
      61,    82,     5,    21,   109,     5,    21,    81,    81,    48,
      22,    22,    25,    25,    24,   134,   134,   134,    81,    87,
      87,    81,   134,   134,   134,   134,    25,   134,    81,   127,
      42,    44,   137,    81,   124,   118,    41,    81,   111,   130,
     130,    81,    48,    48,    81,   119,   119,    25,    25,    25,
     133,    22,   126,    25,   125,    21,    67,    70,   134,   138,
     140,    61,    25,   123,     9,    32,    33,    34,    35,    36,
      37,   115,    25,   110,    57,   120,    25,   106,    81,    81,
     134,   134,   134,    59,   128,   127,   137,   118,    70,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    75,   139,
      45,    46,   134,   134,   124,   137,    81,    21,    67,    74,
     112,   111,    22,    58,    81,    22,    21,    21,    22,    22,
      22,    60,   125,     8,   141,    25,   117,    68,    69,    67,
     134,   138,   138,   123,    79,   114,    74,   110,   109,   120,
      61,   106,     5,    81,    81,    81,     4,    76,   142,   118,
     134,    22,    22,   130,    81,   130,    22,   106,   126,   133,
     138,    72,   145,   117,   117,   112,   120,    77,    22,    48,
       4,    78,   131,    21,   138,   134,   143,   144,    79,    81,
     104,   128,    15,    73,    25,    61,    25,   103,   144,    29,
      30,    31,    79,    81,   104,    22,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   102,   103,   103,   104,   104,   104,
     104,   104,   104,   105,   105,   106,   106,   107,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   112,   112,   112,
     113,   113,   114,   115,   115,   115,   115,   115,   115,   116,
     117,   117,   117,   118,   118,   118,   118,   118,   118,   119,
     119,   119,   119,   119,   120,   120,   121,   122,   123,   123,
     124,   125,   125,   126,   126,   126,   127,   128,   128,   129,
     130,   130,   131,   131,   132,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   136,   136,   137,   137,   138,   138,
     138,   138,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   140,   140,   141,   141,   142,   142,
     143,   143,   143,   144,   144,   145,   145,   146,   147,   148,
     149,   149
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,    10,    14,     0,     3,     0,     3,     3,
       3,     3,     3,     0,     1,     0,     3,     5,     8,    10,
       6,     0,     1,     0,     3,     6,     3,     0,     1,     2,
       5,     9,     1,     1,     1,     1,     1,     1,     1,     8,
       0,     3,     3,     1,     1,     1,     1,     3,     1,     0,
       1,     1,     3,     3,     0,     4,     4,     6,     0,     3,
       3,     0,     3,     1,     2,     0,     3,     0,     7,     3,
       2,    10,     0,     2,     2,     2,     4,     3,     3,     3,
       3,     2,     4,     1,     1,     1,     3,     3,     1,     3,
       6,     6,     6,     1,     1,     3,     0,     2,     3,     2,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     2,     1,     2,     0,     3,     0,     2,
       1,     2,     2,     1,     3,     0,     3,     6,     2,     4,
       0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 274 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1921 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 305 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1930 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 311 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1938 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 316 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1946 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 322 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1954 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 328 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 334 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 340 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 347 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1988 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 353 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1998 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE unique_option INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 362 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.is_unique = (yyvsp[-8].boolean);
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);

      std::vector<std::string> *idx_cols = (yyvsp[-1].relation_list);
      if (nullptr != idx_cols) {
        create_index.attr_names.swap(*idx_cols);
        delete (yyvsp[-1].relation_list);
      }
      create_index.attr_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attr_names.begin(), create_index.attr_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2021 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID RBRACE WITH LBRACE vector_idx_prop vector_idx_prop_list RBRACE  */
#line 381 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VECTOR_INDEX);
      CreateIndexSqlNode &create_vector_index = (yyval.sql_node)->create_index;
      create_vector_index.index_name = (yyvsp[-10].string);
      create_vector_index.relation_name = (yyvsp[-8].string);
      create_vector_index.attr_names.push_back((yyvsp[-6].string));
      if ((yyvsp[-1].vidx_prop_list)!= nullptr) {
        create_vector_index.vector_idx_props.swap(*(yyvsp[-1].vidx_prop_list));
        delete (yyvsp[-1].vidx_prop_list);
      }
      create_vector_index.vector_idx_props.emplace_back(*(yyvsp[-2].vidx_prop));
      delete (yyvsp[-2].vidx_prop);
      free((yyvsp[-10].string));
      free((yyvsp[-8].string));
      free((yyvsp[-6].string));

    }
#line 2043 "yacc_sql.cpp"
    break;

  case 35: /* vector_idx_prop_list: %empty  */
#line 402 "yacc_sql.y"
    {
      (yyval.vidx_prop_list) = nullptr;
    }
#line 2051 "yacc_sql.cpp"
    break;

  case 36: /* vector_idx_prop_list: COMMA vector_idx_prop vector_idx_prop_list  */
#line 406 "yacc_sql.y"
    {
      if ((yyvsp[0].vidx_prop_list)!= nullptr) {
        (yyval.vidx_prop_list) = (yyvsp[0].vidx_prop_list);
      } else {
        (yyval.vidx_prop_list) = new std::vector<VectorIdxProp>;
      }
      (yyval.vidx_prop_list)->emplace_back(*(yyvsp[-1].vidx_prop));
      delete (yyvsp[-1].vidx_prop);

    }
#line 2066 "yacc_sql.cpp"
    break;

  case 37: /* vector_idx_prop: %empty  */
#line 417 "yacc_sql.y"
    {
      (yyval.vidx_prop) = nullptr;
    }
#line 2074 "yacc_sql.cpp"
    break;

  case 38: /* vector_idx_prop: ID EQ ID  */
#line 421 "yacc_sql.y"
    {
      LOG_DEBUG("vector_idx_prop");
      (yyval.vidx_prop) = new VectorIdxProp;
      (yyval.vidx_prop)->attr_name = (yyvsp[-2].string);
      (yyval.vidx_prop)->attr_value = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 39: /* vector_idx_prop: ID EQ NUMBER  */
#line 430 "yacc_sql.y"
    {
      (yyval.vidx_prop) = new VectorIdxProp;
      (yyval.vidx_prop)->attr_name = (yyvsp[-2].string);
      (yyval.vidx_prop)->attr_value = std::to_string((yyvsp[0].number));
      free((yyvsp[-2].string));
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 40: /* vector_idx_prop: ID EQ L2_DISTANCE_T  */
#line 437 "yacc_sql.y"
    {
      (yyval.vidx_prop) = new VectorIdxProp;
      (yyval.vidx_prop)->attr_name = (yyvsp[-2].string);
      (yyval.vidx_prop)->attr_value = std::string("L2_DISTANCE_T");
      free((yyvsp[-2].string));
    }
#line 2109 "yacc_sql.cpp"
    break;

  case 41: /* vector_idx_prop: ID EQ COSINE_DISTANCE_T  */
#line 444 "yacc_sql.y"
    {
      (yyval.vidx_prop) = new VectorIdxProp;
      (yyval.vidx_prop)->attr_name = (yyvsp[-2].string);
      (yyval.vidx_prop)->attr_value = std::string("COSINE_DISTANCE_T");
      free((yyvsp[-2].string));
    }
#line 2120 "yacc_sql.cpp"
    break;

  case 42: /* vector_idx_prop: ID EQ INNER_PRODUCT_T  */
#line 451 "yacc_sql.y"
    {
      (yyval.vidx_prop) = new VectorIdxProp;
      (yyval.vidx_prop)->attr_name = (yyvsp[-2].string);
      (yyval.vidx_prop)->attr_value = std::string("INNER_PRODUCT_T");
      free((yyvsp[-2].string));
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 43: /* unique_option: %empty  */
#line 462 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2139 "yacc_sql.cpp"
    break;

  case 44: /* unique_option: UNIQUE  */
#line 466 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2147 "yacc_sql.cpp"
    break;

  case 45: /* idx_col_list: %empty  */
#line 472 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2155 "yacc_sql.cpp"
    break;

  case 46: /* idx_col_list: COMMA ID idx_col_list  */
#line 476 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list)!= nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2169 "yacc_sql.cpp"
    break;

  case 47: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 489 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 48: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 499 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2206 "yacc_sql.cpp"
    break;

  case 49: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_option select_stmt storage_format  */
#line 520 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-7].string);
      free((yyvsp[-7].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-4].attr_infos);
      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-5].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-5].attr_info);
      if ((yyvsp[0].string)!= nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 50: /* create_table_stmt: CREATE TABLE ID as_option select_stmt storage_format  */
#line 541 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[-1].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_TABLE;
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-3].string);
      free((yyvsp[-3].string));
      if ((yyvsp[0].string)!= nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2247 "yacc_sql.cpp"
    break;

  case 51: /* as_option: %empty  */
#line 556 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2255 "yacc_sql.cpp"
    break;

  case 52: /* as_option: AS  */
#line 560 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2263 "yacc_sql.cpp"
    break;

  case 53: /* attr_def_list: %empty  */
#line 567 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2271 "yacc_sql.cpp"
    break;

  case 54: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 571 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 55: /* attr_def: ID type LBRACE number RBRACE null_option  */
#line 584 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2298 "yacc_sql.cpp"
    break;

  case 56: /* attr_def: ID type null_option  */
#line 593 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2311 "yacc_sql.cpp"
    break;

  case 57: /* null_option: %empty  */
#line 605 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2319 "yacc_sql.cpp"
    break;

  case 58: /* null_option: NULL_T  */
#line 609 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2327 "yacc_sql.cpp"
    break;

  case 59: /* null_option: NOT NULL_T  */
#line 613 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 60: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 620 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2346 "yacc_sql.cpp"
    break;

  case 61: /* create_view_stmt: CREATE VIEW ID LBRACE ID idx_col_list RBRACE AS select_stmt  */
#line 627 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-6].string);

      std::vector<std::string> &col_names = (yyval.sql_node)->create_view.col_names;
      if (nullptr != (yyvsp[-3].relation_list)) {
        col_names.swap(*(yyvsp[-3].relation_list));
        delete (yyvsp[-3].relation_list);
      }
      col_names.emplace_back((yyvsp[-4].string));
      std::reverse(col_names.begin(), col_names.end());
      free((yyvsp[-6].string));
    }
#line 2365 "yacc_sql.cpp"
    break;

  case 62: /* number: NUMBER  */
#line 645 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2371 "yacc_sql.cpp"
    break;

  case 63: /* type: INT_T  */
#line 648 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2377 "yacc_sql.cpp"
    break;

  case 64: /* type: STRING_T  */
#line 649 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2383 "yacc_sql.cpp"
    break;

  case 65: /* type: FLOAT_T  */
#line 650 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2389 "yacc_sql.cpp"
    break;

  case 66: /* type: DATE_T  */
#line 651 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2395 "yacc_sql.cpp"
    break;

  case 67: /* type: TEXT_T  */
#line 652 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2401 "yacc_sql.cpp"
    break;

  case 68: /* type: VECTOR_T  */
#line 653 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2407 "yacc_sql.cpp"
    break;

  case 69: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 657 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2424 "yacc_sql.cpp"
    break;

  case 70: /* value_list: %empty  */
#line 673 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2432 "yacc_sql.cpp"
    break;

  case 71: /* value_list: COMMA value value_list  */
#line 676 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2446 "yacc_sql.cpp"
    break;

  case 72: /* value_list: COMMA expression value_list  */
#line 685 "yacc_sql.y"
                                   { 
      Value tmp;
      if(!exp2value((yyvsp[-1].expression), tmp)) {
        yyerror(&(yyloc), sql_string, sql_result, scanner, "error");
        YYERROR;
      }
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(tmp);
      delete (yyvsp[-1].expression);
    }
#line 2465 "yacc_sql.cpp"
    break;

  case 73: /* value: NUMBER  */
#line 701 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 74: /* value: FLOAT  */
#line 705 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2483 "yacc_sql.cpp"
    break;

  case 75: /* value: DATE_STR  */
#line 709 "yacc_sql.y"
              {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      std::string str(tmp);
      Value * value = new Value();
      int date;
      if(string_to_date(str,date) < 0) {
        yyerror(&(yyloc),sql_string,sql_result,scanner,"date invaid");
        YYERROR;
      }
      else
      {
        value->set_date(date);
      }
      (yyval.value) = value;
      free(tmp);
    }
#line 2504 "yacc_sql.cpp"
    break;

  case 76: /* value: SSS  */
#line 725 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2515 "yacc_sql.cpp"
    break;

  case 77: /* value: LBRACK float_list RBRACK  */
#line 731 "yacc_sql.y"
                               {
      (yyval.value) = new Value((yyvsp[-1].float_list));
      delete (yyvsp[-1].float_list);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 78: /* value: NULL_T  */
#line 735 "yacc_sql.y"
           {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2533 "yacc_sql.cpp"
    break;

  case 79: /* float_list: %empty  */
#line 743 "yacc_sql.y"
    {
      (yyval.float_list) = new vector<float>();
    }
#line 2541 "yacc_sql.cpp"
    break;

  case 80: /* float_list: NUMBER  */
#line 747 "yacc_sql.y"
    {
      (yyval.float_list) = new vector<float>();
      (yyval.float_list)->emplace_back((float)(yyvsp[0].number));
    }
#line 2550 "yacc_sql.cpp"
    break;

  case 81: /* float_list: FLOAT  */
#line 752 "yacc_sql.y"
    {
      (yyval.float_list) = new vector<float>();
      (yyval.float_list)->emplace_back((float)(yyvsp[0].floats));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 82: /* float_list: NUMBER COMMA float_list  */
#line 757 "yacc_sql.y"
    {
      if((yyvsp[0].float_list) == nullptr){
        (yyval.float_list) = new vector<float>();
      }else{
        (yyval.float_list) = (yyvsp[0].float_list);
      }
      (yyval.float_list)->emplace((yyval.float_list)->begin(), (float)(yyvsp[-2].number));

    }
#line 2573 "yacc_sql.cpp"
    break;

  case 83: /* float_list: FLOAT COMMA float_list  */
#line 767 "yacc_sql.y"
    {
      if((yyvsp[0].float_list) == nullptr){
        (yyval.float_list) = new vector<float>();
      }else{
        (yyval.float_list) = (yyvsp[0].float_list);
      }
      (yyval.float_list)->emplace((yyval.float_list)->begin(), (float)(yyvsp[-2].floats));
    }
#line 2586 "yacc_sql.cpp"
    break;

  case 84: /* storage_format: %empty  */
#line 779 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2594 "yacc_sql.cpp"
    break;

  case 85: /* storage_format: STORAGE FORMAT EQ ID  */
#line 783 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2602 "yacc_sql.cpp"
    break;

  case 86: /* delete_stmt: DELETE FROM ID where  */
#line 790 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2616 "yacc_sql.cpp"
    break;

  case 87: /* update_stmt: UPDATE ID SET update_kv update_kv_list where  */
#line 802 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);
      (yyval.sql_node)->update.attribute_names.emplace_back((yyvsp[-2].update_kv)->attr_name);
      (yyval.sql_node)->update.expressions.emplace_back((yyvsp[-2].update_kv)->expression);
      if ((yyvsp[-1].update_kv_list) != nullptr) {
        for (UpdateKV kv : *(yyvsp[-1].update_kv_list)) {
          (yyval.sql_node)->update.attribute_names.emplace_back(kv.attr_name);
          (yyval.sql_node)->update.expressions.emplace_back(kv.expression);
        }
        delete (yyvsp[-1].update_kv_list);
      } 
      (yyval.sql_node)->update.conditions = nullptr;
      if ((yyvsp[0].expression)!= nullptr) {
        (yyval.sql_node)->update.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-4].string));
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 88: /* update_kv_list: %empty  */
#line 823 "yacc_sql.y"
    {
      (yyval.update_kv_list) = nullptr;
    }
#line 2647 "yacc_sql.cpp"
    break;

  case 89: /* update_kv_list: COMMA update_kv update_kv_list  */
#line 827 "yacc_sql.y"
    {
      if ((yyvsp[0].update_kv_list)!= nullptr) {
        (yyval.update_kv_list) = (yyvsp[0].update_kv_list);
      } else {
        (yyval.update_kv_list) = new std::vector<UpdateKV>;
      }
      (yyval.update_kv_list)->emplace_back(*(yyvsp[-1].update_kv));
      delete (yyvsp[-1].update_kv);
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 90: /* update_kv: ID EQ expression  */
#line 840 "yacc_sql.y"
    {
      (yyval.update_kv) = new UpdateKV;
      (yyval.update_kv)->attr_name = (yyvsp[-2].string);
      (yyval.update_kv)->expression = (yyvsp[0].expression);
      free((yyvsp[-2].string));
    }
#line 2672 "yacc_sql.cpp"
    break;

  case 91: /* from_list: %empty  */
#line 850 "yacc_sql.y"
                {
      (yyval.inner_joins_list) = nullptr;
    }
#line 2680 "yacc_sql.cpp"
    break;

  case 92: /* from_list: COMMA from_node from_list  */
#line 853 "yacc_sql.y"
                                {
      if (nullptr != (yyvsp[0].inner_joins_list)) {
        (yyval.inner_joins_list) = (yyvsp[0].inner_joins_list);
      } else {
        (yyval.inner_joins_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_joins_list)->emplace_back(*(yyvsp[-1].inner_joins));
      delete (yyvsp[-1].inner_joins);
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 93: /* alias: ID  */
#line 865 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 94: /* alias: AS ID  */
#line 868 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2710 "yacc_sql.cpp"
    break;

  case 95: /* alias: %empty  */
#line 871 "yacc_sql.y"
                  {
      (yyval.string) = nullptr;
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 96: /* from_node: ID alias join_list  */
#line 877 "yacc_sql.y"
                       {
      if (nullptr != (yyvsp[0].inner_joins)) {
        (yyval.inner_joins) = (yyvsp[0].inner_joins);
      } else {
        (yyval.inner_joins) = new InnerJoinSqlNode;
      }
      (yyval.inner_joins)->base_relation.first = (yyvsp[-2].string);
      (yyval.inner_joins)->base_relation.second = nullptr == (yyvsp[-1].string) ? "" : std::string((yyvsp[-1].string));
      std::reverse((yyval.inner_joins)->join_relations.begin(), (yyval.inner_joins)->join_relations.end());
      std::reverse((yyval.inner_joins)->conditions.begin(), (yyval.inner_joins)->conditions.end());
      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 97: /* join_list: %empty  */
#line 893 "yacc_sql.y"
                {
      (yyval.inner_joins) = nullptr;
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 98: /* join_list: INNER JOIN ID alias ON condition join_list  */
#line 896 "yacc_sql.y"
                                                 {
      if (nullptr != (yyvsp[0].inner_joins)) {
        (yyval.inner_joins) = (yyvsp[0].inner_joins);
      } else {
        (yyval.inner_joins) = new InnerJoinSqlNode;
      }
      std::string alias_name = (yyvsp[-3].string) == nullptr ? "" : (yyvsp[-3].string);
      (yyval.inner_joins)->join_relations.emplace_back((yyvsp[-4].string), alias_name);
      free((yyvsp[-3].string));
      (yyval.inner_joins)->conditions.emplace_back((yyvsp[-1].condition));
      free((yyvsp[-4].string));
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 99: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 912 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
    }
#line 2770 "yacc_sql.cpp"
    break;

  case 100: /* select_stmt: SELECT expression_list  */
#line 919 "yacc_sql.y"
                           {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2780 "yacc_sql.cpp"
    break;

  case 101: /* select_stmt: SELECT expression_list FROM from_node from_list where group_by having opt_order_by limit_clause  */
#line 925 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }
      if ((yyvsp[-5].inner_joins_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].inner_joins_list));
        delete (yyvsp[-5].inner_joins_list);
      }
      (yyval.sql_node)->selection.relations.push_back(*(yyvsp[-6].inner_joins));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-4].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-4].expression);
      }

      if ((yyvsp[-3].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-3].expression_list));
        delete (yyvsp[-3].expression_list);
        std::reverse((yyval.sql_node)->selection.group_by.begin(), (yyval.sql_node)->selection.group_by.end());
      }

      (yyval.sql_node)->selection.having_conditions = nullptr;
      if ((yyvsp[-2].expression) != nullptr) {
        (yyval.sql_node)->selection.having_conditions = (yyvsp[-2].expression);
      }

      if ((yyvsp[-1].orderby_unit_list) != nullptr) {
        (yyval.sql_node)->selection.orderbys.swap(*(yyvsp[-1].orderby_unit_list));
        delete (yyvsp[-1].orderby_unit_list);
      }

      delete (yyvsp[-6].inner_joins);
      (yyval.sql_node)->selection.limit = (yyvsp[0].number);
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 102: /* limit_clause: %empty  */
#line 963 "yacc_sql.y"
    {
      (yyval.number) = -1;
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 103: /* limit_clause: LIMIT NUMBER  */
#line 967 "yacc_sql.y"
    {
      (yyval.number) = (int) (yyvsp[0].number);
    }
#line 2837 "yacc_sql.cpp"
    break;

  case 104: /* calc_stmt: CALC expression_list  */
#line 973 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 105: /* expression_list: expression alias  */
#line 982 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2860 "yacc_sql.cpp"
    break;

  case 106: /* expression_list: expression alias COMMA expression_list  */
#line 991 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression*>;
      }
      if((yyvsp[-2].string) != nullptr){
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
        free((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
    }
#line 2877 "yacc_sql.cpp"
    break;

  case 107: /* expression: expression '+' expression  */
#line 1005 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2885 "yacc_sql.cpp"
    break;

  case 108: /* expression: expression '-' expression  */
#line 1008 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2893 "yacc_sql.cpp"
    break;

  case 109: /* expression: expression '*' expression  */
#line 1011 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 110: /* expression: expression '/' expression  */
#line 1014 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2909 "yacc_sql.cpp"
    break;

  case 111: /* expression: '-' expression  */
#line 1017 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2917 "yacc_sql.cpp"
    break;

  case 112: /* expression: aggre_type LBRACE expression RBRACE  */
#line 1020 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2925 "yacc_sql.cpp"
    break;

  case 113: /* expression: value  */
#line 1023 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2935 "yacc_sql.cpp"
    break;

  case 114: /* expression: rel_attr  */
#line 1028 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2945 "yacc_sql.cpp"
    break;

  case 115: /* expression: '*'  */
#line 1033 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2953 "yacc_sql.cpp"
    break;

  case 116: /* expression: ID DOT '*'  */
#line 1037 "yacc_sql.y"
                {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2961 "yacc_sql.cpp"
    break;

  case 117: /* expression: '*' DOT '*'  */
#line 1040 "yacc_sql.y"
                 {
      const char* tmp = "*";
      (yyval.expression) = new StarExpr(tmp);
    }
#line 2970 "yacc_sql.cpp"
    break;

  case 118: /* expression: sub_query_expr  */
#line 1044 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2978 "yacc_sql.cpp"
    break;

  case 119: /* expression: LBRACE expression_list RBRACE  */
#line 1047 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 120: /* expression: L2_DISTANCE_T LBRACE expression COMMA expression RBRACE  */
#line 1056 "yacc_sql.y"
                                                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 121: /* expression: COSINE_DISTANCE_T LBRACE expression COMMA expression RBRACE  */
#line 1059 "yacc_sql.y"
                                                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3008 "yacc_sql.cpp"
    break;

  case 122: /* expression: INNER_PRODUCT_T LBRACE expression COMMA expression RBRACE  */
#line 1062 "yacc_sql.y"
                                                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 3016 "yacc_sql.cpp"
    break;

  case 123: /* aggre_type: AGGR  */
#line 1068 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 3024 "yacc_sql.cpp"
    break;

  case 124: /* rel_attr: ID  */
#line 1073 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3034 "yacc_sql.cpp"
    break;

  case 125: /* rel_attr: ID DOT ID  */
#line 1078 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 126: /* where: %empty  */
#line 1089 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3054 "yacc_sql.cpp"
    break;

  case 127: /* where: WHERE condition  */
#line 1092 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].condition);  
    }
#line 3062 "yacc_sql.cpp"
    break;

  case 128: /* condition: expression comp_op expression  */
#line 1099 "yacc_sql.y"
    {
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 129: /* condition: exists_op expression  */
#line 1103 "yacc_sql.y"
    {
      NullExpr *null_expr = new NullExpr();
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), null_expr, (yyvsp[0].expression));
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 130: /* condition: condition AND condition  */
#line 1108 "yacc_sql.y"
    {
      (yyval.condition) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].condition), (yyvsp[0].condition));
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 131: /* condition: condition OR condition  */
#line 1112 "yacc_sql.y"
    {
      (yyval.condition) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].condition), (yyvsp[0].condition));
    }
#line 3095 "yacc_sql.cpp"
    break;

  case 132: /* comp_op: EQ  */
#line 1118 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3101 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: LT  */
#line 1119 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3107 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: GT  */
#line 1120 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3113 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: LE  */
#line 1121 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3119 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: GE  */
#line 1122 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3125 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: NE  */
#line 1123 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3131 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: LIKE  */
#line 1124 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 3137 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: NOT LIKE  */
#line 1125 "yacc_sql.y"
               {(yyval.comp) = NOT_LIKE_OP;}
#line 3143 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: IS NOT  */
#line 1126 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_OP;}
#line 3149 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: IS  */
#line 1127 "yacc_sql.y"
         {(yyval.comp) = IS_OP;}
#line 3155 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: IN  */
#line 1128 "yacc_sql.y"
          {(yyval.comp) = IN_OP;}
#line 3161 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: NOT IN  */
#line 1129 "yacc_sql.y"
             {(yyval.comp) = NOT_IN_OP;}
#line 3167 "yacc_sql.cpp"
    break;

  case 144: /* exists_op: EXISTS  */
#line 1133 "yacc_sql.y"
           {(yyval.comp) = EXISTS_OP;}
#line 3173 "yacc_sql.cpp"
    break;

  case 145: /* exists_op: NOT EXISTS  */
#line 1134 "yacc_sql.y"
                 {(yyval.comp) = NOT_EXISTS_OP;}
#line 3179 "yacc_sql.cpp"
    break;

  case 146: /* group_by: %empty  */
#line 1140 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3187 "yacc_sql.cpp"
    break;

  case 147: /* group_by: GROUP BY expression_list  */
#line 1143 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3195 "yacc_sql.cpp"
    break;

  case 148: /* having: %empty  */
#line 1149 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 3203 "yacc_sql.cpp"
    break;

  case 149: /* having: HAVING condition  */
#line 1152 "yacc_sql.y"
                       {
      (yyval.expression) = (yyvsp[0].condition);
    }
#line 3211 "yacc_sql.cpp"
    break;

  case 150: /* sort_unit: expression  */
#line 1160 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[0].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 3221 "yacc_sql.cpp"
    break;

  case 151: /* sort_unit: expression DESC  */
#line 1167 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = false;
	}
#line 3231 "yacc_sql.cpp"
    break;

  case 152: /* sort_unit: expression ASC  */
#line 1174 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 3241 "yacc_sql.cpp"
    break;

  case 153: /* sort_list: sort_unit  */
#line 1182 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = new std::vector<OrderBySqlNode>;
    (yyval.orderby_unit_list)->emplace_back(*(yyvsp[0].orderby_unit));
    delete (yyvsp[0].orderby_unit);
	}
#line 3251 "yacc_sql.cpp"
    break;

  case 154: /* sort_list: sort_unit COMMA sort_list  */
#line 1189 "yacc_sql.y"
        {
    (yyvsp[0].orderby_unit_list)->emplace_back(*(yyvsp[-2].orderby_unit));
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    delete (yyvsp[-2].orderby_unit);
	}
#line 3261 "yacc_sql.cpp"
    break;

  case 155: /* opt_order_by: %empty  */
#line 1196 "yacc_sql.y"
                    {
   (yyval.orderby_unit_list) = nullptr;
  }
#line 3269 "yacc_sql.cpp"
    break;

  case 156: /* opt_order_by: ORDER BY sort_list  */
#line 1200 "yacc_sql.y"
        {
      (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
      std::reverse((yyval.orderby_unit_list)->begin(),(yyval.orderby_unit_list)->end());
	}
#line 3278 "yacc_sql.cpp"
    break;

  case 157: /* load_data_stmt: LOAD_DATA INFILE SSS INTO TABLE ID  */
#line 1207 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3292 "yacc_sql.cpp"
    break;

  case 158: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1220 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3301 "yacc_sql.cpp"
    break;

  case 159: /* set_variable_stmt: SET ID EQ value  */
#line 1228 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3313 "yacc_sql.cpp"
    break;


#line 3317 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1240 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
