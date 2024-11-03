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
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 24,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 25,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 26,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 27,                     /* INT_T  */
  YYSYMBOL_DATE_T = 28,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 29,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_SET = 41,                       /* SET  */
  YYSYMBOL_ON = 42,                        /* ON  */
  YYSYMBOL_LOAD_DATA = 43,                 /* LOAD_DATA  */
  YYSYMBOL_INFILE = 44,                    /* INFILE  */
  YYSYMBOL_MAX_T = 45,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 46,                     /* MIN_T  */
  YYSYMBOL_AVG_T = 47,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 48,                     /* SUM_T  */
  YYSYMBOL_COUNT_T = 49,                   /* COUNT_T  */
  YYSYMBOL_EXPLAIN = 50,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 51,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 52,                    /* FORMAT  */
  YYSYMBOL_INNER = 53,                     /* INNER  */
  YYSYMBOL_JOIN = 54,                      /* JOIN  */
  YYSYMBOL_EQ = 55,                        /* EQ  */
  YYSYMBOL_LT = 56,                        /* LT  */
  YYSYMBOL_GT = 57,                        /* GT  */
  YYSYMBOL_LE = 58,                        /* LE  */
  YYSYMBOL_GE = 59,                        /* GE  */
  YYSYMBOL_NE = 60,                        /* NE  */
  YYSYMBOL_NOT = 61,                       /* NOT  */
  YYSYMBOL_LIKE = 62,                      /* LIKE  */
  YYSYMBOL_IN = 63,                        /* IN  */
  YYSYMBOL_EXISTS = 64,                    /* EXISTS  */
  YYSYMBOL_UNIQUE = 65,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 66,                     /* ORDER  */
  YYSYMBOL_ASC = 67,                       /* ASC  */
  YYSYMBOL_NULL_T = 68,                    /* NULL_T  */
  YYSYMBOL_IS = 69,                        /* IS  */
  YYSYMBOL_HAVING = 70,                    /* HAVING  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_AGGR = 75,                      /* AGGR  */
  YYSYMBOL_DATE_STR = 76,                  /* DATE_STR  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '*'  */
  YYSYMBOL_80_ = 80,                       /* '/'  */
  YYSYMBOL_UMINUS = 81,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_commands = 83,                  /* commands  */
  YYSYMBOL_command_wrapper = 84,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 85,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 86,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 87,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 88,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 89,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 90,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 91,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 92,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 93,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 94,         /* create_index_stmt  */
  YYSYMBOL_unique_option = 95,             /* unique_option  */
  YYSYMBOL_idx_col_list = 96,              /* idx_col_list  */
  YYSYMBOL_drop_index_stmt = 97,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 98,         /* create_table_stmt  */
  YYSYMBOL_as_option = 99,                 /* as_option  */
  YYSYMBOL_attr_def_list = 100,            /* attr_def_list  */
  YYSYMBOL_attr_def = 101,                 /* attr_def  */
  YYSYMBOL_null_option = 102,              /* null_option  */
  YYSYMBOL_create_view_stmt = 103,         /* create_view_stmt  */
  YYSYMBOL_number = 104,                   /* number  */
  YYSYMBOL_type = 105,                     /* type  */
  YYSYMBOL_insert_stmt = 106,              /* insert_stmt  */
  YYSYMBOL_value_list = 107,               /* value_list  */
  YYSYMBOL_value = 108,                    /* value  */
  YYSYMBOL_storage_format = 109,           /* storage_format  */
  YYSYMBOL_delete_stmt = 110,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 111,              /* update_stmt  */
  YYSYMBOL_update_kv_list = 112,           /* update_kv_list  */
  YYSYMBOL_update_kv = 113,                /* update_kv  */
  YYSYMBOL_from_list = 114,                /* from_list  */
  YYSYMBOL_alias = 115,                    /* alias  */
  YYSYMBOL_from_node = 116,                /* from_node  */
  YYSYMBOL_join_list = 117,                /* join_list  */
  YYSYMBOL_sub_query_expr = 118,           /* sub_query_expr  */
  YYSYMBOL_select_stmt = 119,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 120,                /* calc_stmt  */
  YYSYMBOL_expression_list = 121,          /* expression_list  */
  YYSYMBOL_expression = 122,               /* expression  */
  YYSYMBOL_aggre_type = 123,               /* aggre_type  */
  YYSYMBOL_rel_attr = 124,                 /* rel_attr  */
  YYSYMBOL_where = 125,                    /* where  */
  YYSYMBOL_condition = 126,                /* condition  */
  YYSYMBOL_comp_op = 127,                  /* comp_op  */
  YYSYMBOL_exists_op = 128,                /* exists_op  */
  YYSYMBOL_group_by = 129,                 /* group_by  */
  YYSYMBOL_having = 130,                   /* having  */
  YYSYMBOL_sort_unit = 131,                /* sort_unit  */
  YYSYMBOL_sort_list = 132,                /* sort_list  */
  YYSYMBOL_opt_order_by = 133,             /* opt_order_by  */
  YYSYMBOL_load_data_stmt = 134,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 135,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 136,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 137             /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  73
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   264

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  253

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


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
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
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
      75,    76,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   259,   259,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   291,   297,   302,   308,   314,   320,
     326,   333,   339,   347,   370,   373,   380,   383,   396,   406,
     427,   448,   464,   467,   475,   478,   491,   500,   513,   516,
     520,   527,   534,   553,   556,   557,   558,   559,   560,   563,
     580,   583,   592,   608,   612,   616,   632,   638,   645,   648,
     655,   667,   689,   692,   705,   716,   719,   731,   734,   737,
     743,   759,   762,   777,   785,   790,   829,   838,   847,   862,
     865,   868,   871,   874,   877,   880,   885,   890,   894,   897,
     901,   904,   916,   921,   926,   937,   940,   946,   950,   955,
     959,   966,   967,   968,   969,   970,   971,   972,   973,   974,
     975,   976,   977,   981,   982,   988,   991,   997,  1000,  1007,
    1014,  1021,  1029,  1036,  1044,  1047,  1054,  1067,  1075,  1085,
    1086
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
  "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "DATE_T", "TEXT_T", "STRING_T", "FLOAT_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON",
  "LOAD_DATA", "INFILE", "MAX_T", "MIN_T", "AVG_T", "SUM_T", "COUNT_T",
  "EXPLAIN", "STORAGE", "FORMAT", "INNER", "JOIN", "EQ", "LT", "GT", "LE",
  "GE", "NE", "NOT", "LIKE", "IN", "EXISTS", "UNIQUE", "ORDER", "ASC",
  "NULL_T", "IS", "HAVING", "NUMBER", "FLOAT", "ID", "SSS", "AGGR",
  "DATE_STR", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "unique_option", "idx_col_list",
  "drop_index_stmt", "create_table_stmt", "as_option", "attr_def_list",
  "attr_def", "null_option", "create_view_stmt", "number", "type",
  "insert_stmt", "value_list", "value", "storage_format", "delete_stmt",
  "update_stmt", "update_kv_list", "update_kv", "from_list", "alias",
  "from_node", "join_list", "sub_query_expr", "select_stmt", "calc_stmt",
  "expression_list", "expression", "aggre_type", "rel_attr", "where",
  "condition", "comp_op", "exists_op", "group_by", "having", "sort_unit",
  "sort_list", "opt_order_by", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     186,     3,    21,    43,    43,   -45,    31,  -178,     8,    -6,
     -21,  -178,  -178,  -178,  -178,  -178,    29,    32,   186,    63,
      89,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,    39,    47,  -178,   112,    55,    56,    25,  -178,
    -178,  -178,    97,  -178,  -178,  -178,    43,    98,  -178,  -178,
    -178,     0,   114,  -178,    99,  -178,  -178,    60,    70,   106,
      93,    75,  -178,  -178,  -178,  -178,    16,    19,    77,  -178,
     124,   147,   148,   -50,  -178,    92,   105,  -178,    43,    43,
      43,    43,   156,    43,   111,   146,   151,   113,   109,   155,
    -178,   118,   180,   180,   122,   165,   125,  -178,  -178,  -178,
    -178,  -178,  -178,   -19,   -19,  -178,  -178,    43,     4,     1,
     174,   187,    66,  -178,   154,   190,  -178,   205,   133,   192,
     169,  -178,   193,   149,  -178,  -178,  -178,   168,   111,   151,
     109,   159,  -178,    96,    26,    43,    43,   113,   151,   152,
    -178,  -178,  -178,  -178,  -178,   -10,   118,   202,   176,  -178,
     153,   208,   210,   178,  -178,   174,   225,   211,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,    23,  -178,  -178,   177,    43,
      66,    66,   -30,   -30,   190,  -178,  -178,   164,   171,  -178,
    -178,   192,    11,   182,   193,   235,   170,   172,  -178,   237,
     179,    43,   220,  -178,  -178,  -178,   -30,  -178,   207,  -178,
    -178,   222,  -178,  -178,   180,  -178,   175,  -178,   180,   193,
       1,    43,    66,   181,    72,    30,  -178,   -41,   169,  -178,
    -178,   228,   209,  -178,    26,   248,  -178,  -178,  -178,  -178,
    -178,  -178,    66,    43,   -31,    -8,   230,  -178,  -178,  -178,
    -178,    43,  -178
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     139,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,     8,    14,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,    35,     0,     0,     0,     0,    67,
      63,    64,   103,    66,   102,    65,     0,    97,    95,   100,
      86,    79,     0,    96,    84,    32,    31,     0,     0,     0,
       0,     0,   137,     1,   140,     2,    42,     0,     0,    30,
       0,     0,     0,     0,    93,     0,     0,    77,     0,     0,
       0,     0,    87,     0,     0,     0,   105,     0,     0,     0,
      43,     0,     0,     0,     0,     0,     0,    83,   101,   104,
      98,    99,    78,    89,    90,    91,    92,     0,     0,    79,
      75,     0,     0,    70,     0,    72,   138,     0,     0,    44,
      68,    51,    36,     0,    38,    88,    94,    81,     0,   105,
       0,     0,   123,     0,   106,     0,     0,     0,   105,     0,
      54,    57,    58,    55,    56,    48,     0,     0,     0,    41,
       0,     0,     0,     0,    80,    75,   125,    60,   124,   111,
     112,   113,   114,   115,   116,     0,   117,   121,   120,     0,
       0,     0,   108,    74,    72,    71,   136,     0,     0,    49,
      47,    44,    68,     0,    36,     0,     0,     0,    76,     0,
     127,     0,     0,   118,   122,   119,   107,   109,   110,    73,
      53,     0,    50,    45,     0,    39,     0,    37,     0,    36,
      79,     0,     0,   134,    95,    60,    59,    48,    68,    69,
      52,     0,     0,   126,   128,     0,    85,    61,    62,    46,
      40,    33,     0,     0,    81,   129,   132,   135,    82,   130,
     131,     0,   133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,   236,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -177,  -178,  -178,    64,    67,   101,
      28,  -178,  -178,  -178,  -178,  -136,   -95,  -174,  -178,  -178,
      76,   115,    94,  -115,   123,    20,  -178,   -46,  -178,    -4,
     -55,  -178,  -178,  -129,  -167,  -178,  -178,  -178,  -178,  -178,
      12,  -178,  -178,  -178,  -178,  -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    45,   161,    31,    32,   102,   157,   129,
     190,    33,   211,   155,    34,   202,    58,   159,    35,    36,
     148,   125,   139,    92,   120,   164,    59,    37,    38,    60,
      61,    62,    63,   123,   144,   179,   145,   200,   223,   246,
     247,   236,    39,    40,    41,    75
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    84,    81,   126,   137,    86,    86,   249,   180,   181,
     166,   187,    42,   207,   208,    43,   100,   217,   215,   185,
     188,   100,   163,   109,   103,   -42,   136,   189,    65,   110,
      46,    68,    47,   113,   114,   115,   116,   101,   118,     4,
     104,    66,   231,    67,    82,   167,    48,    88,    89,    90,
      91,   188,    69,   201,   240,   234,   130,   131,   189,   250,
      90,    91,   158,    73,    48,   180,   181,   143,    44,    88,
      89,    90,    91,    87,    87,   244,    71,    88,    89,    90,
      91,    88,    89,    90,    91,   203,   204,    48,   237,   238,
     182,   183,    74,    49,   -60,   201,    50,    51,    52,    53,
      54,    55,    70,    56,    57,   232,   224,    88,    89,    90,
      91,    49,    76,   135,    50,    51,    52,    53,    54,    55,
      77,    56,    57,    78,   206,   143,   143,   141,    79,    80,
     142,    83,    85,    95,    49,    93,    94,    50,    51,    52,
      53,    54,    55,    96,    56,    57,   225,    97,    98,    99,
     105,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     150,   151,   152,   153,   154,   178,   106,   143,   228,   107,
     108,   111,   230,    88,    89,    90,    91,    49,   112,   117,
      50,    51,   121,    53,   119,    55,   124,   143,   245,   122,
     127,   128,     1,     2,     4,   132,   245,   138,   134,     3,
       4,     5,     6,     7,     8,     9,    10,   133,   140,   146,
      11,    12,    13,   147,   149,   156,   160,   233,    14,    15,
     158,   163,   162,   168,   192,   186,   194,    16,   193,    17,
     195,   196,   197,   199,   201,   210,    18,   216,   205,   212,
     218,   221,   226,   219,   227,   220,   180,   235,   229,   222,
     241,   242,   243,   251,    72,   239,   214,   191,   213,   198,
     209,   165,   184,   252,   248
};

static const yytype_uint8 yycheck[] =
{
       4,    56,    48,    98,   119,     5,     5,    15,    39,    40,
     139,    21,     9,   180,   181,    12,     5,   194,   192,   148,
      61,     5,    53,    73,     5,    14,    22,    68,    73,    79,
       9,    37,    11,    88,    89,    90,    91,    21,    93,    14,
      21,    10,   219,    35,    48,   140,    21,    77,    78,    79,
      80,    61,    73,    23,   228,   222,   102,   103,    68,    67,
      79,    80,    51,     0,    21,    39,    40,   122,    65,    77,
      78,    79,    80,    73,    73,   242,    44,    77,    78,    79,
      80,    77,    78,    79,    80,    62,    63,    21,   224,   225,
     145,   146,     3,    68,    22,    23,    71,    72,    73,    74,
      75,    76,    73,    78,    79,   220,   201,    77,    78,    79,
      80,    68,    73,   117,    71,    72,    73,    74,    75,    76,
      73,    78,    79,    11,   179,   180,   181,    61,    73,    73,
      64,    34,    34,    73,    68,    21,    37,    71,    72,    73,
      74,    75,    76,    73,    78,    79,   201,    41,    55,    74,
      73,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      27,    28,    29,    30,    31,    69,    42,   222,   214,    22,
      22,    79,   218,    77,    78,    79,    80,    68,    73,    23,
      71,    72,    36,    74,    73,    76,    73,   242,   243,    38,
      35,    73,     6,     7,    14,    73,   251,    23,    73,    13,
      14,    15,    16,    17,    18,    19,    20,    42,    21,    55,
      24,    25,    26,    23,     9,    23,    23,   221,    32,    33,
      51,    53,    73,    64,    22,    73,    73,    41,    52,    43,
      22,    21,    54,     8,    23,    71,    50,    55,    61,    68,
       5,     4,    22,    73,    22,    73,    39,    66,    73,    70,
      22,    42,     4,    23,    18,   227,   192,   156,   191,   165,
     184,   138,   147,   251,   244
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    13,    14,    15,    16,    17,    18,    19,
      20,    24,    25,    26,    32,    33,    41,    43,    50,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    97,    98,   103,   106,   110,   111,   119,   120,   134,
     135,   136,     9,    12,    65,    95,     9,    11,    21,    68,
      71,    72,    73,    74,    75,    76,    78,    79,   108,   118,
     121,   122,   123,   124,   121,    73,    10,    35,    37,    73,
      73,    44,    84,     0,     3,   137,    73,    73,    11,    73,
      73,   119,   121,    34,   122,    34,     5,    73,    77,    78,
      79,    80,   115,    21,    37,    73,    73,    41,    55,    74,
       5,    21,    99,     5,    21,    73,    42,    22,    22,    73,
      79,    79,    73,   122,   122,   122,   122,    23,   122,    73,
     116,    36,    38,   125,    73,   113,   108,    35,    73,   101,
     119,   119,    73,    42,    73,   121,    22,   115,    23,   114,
      21,    61,    64,   122,   126,   128,    55,    23,   112,     9,
      27,    28,    29,    30,    31,   105,    23,   100,    51,   109,
      23,    96,    73,    53,   117,   116,   125,   108,    64,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    69,   127,
      39,    40,   122,   122,   113,   125,    73,    21,    61,    68,
     102,   101,    22,    52,    73,    22,    21,    54,   114,     8,
     129,    23,   107,    62,    63,    61,   122,   126,   126,   112,
      71,   104,    68,   100,    99,   109,    55,    96,     5,    73,
      73,     4,    70,   130,   108,   122,    22,    22,   119,    73,
     119,    96,   115,   121,   126,    66,   133,   107,   107,   102,
     109,    22,    42,     4,   126,   122,   131,   132,   117,    15,
      67,    23,   132
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    95,    96,    96,    97,    98,
      98,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     102,   103,   103,   104,   105,   105,   105,   105,   105,   106,
     107,   107,   107,   108,   108,   108,   108,   108,   109,   109,
     110,   111,   112,   112,   113,   114,   114,   115,   115,   115,
     116,   117,   117,   118,   119,   119,   120,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   123,   124,   124,   125,   125,   126,   126,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   129,   129,   130,   130,   131,
     131,   131,   132,   132,   133,   133,   134,   135,   136,   137,
     137
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,    10,     0,     1,     0,     3,     5,     8,
      10,     6,     0,     1,     0,     3,     6,     3,     0,     1,
       2,     5,     9,     1,     1,     1,     1,     1,     1,     8,
       0,     3,     3,     1,     1,     1,     1,     1,     0,     4,
       4,     6,     0,     3,     3,     0,     3,     1,     2,     0,
       3,     0,     7,     3,     2,     9,     2,     2,     4,     3,
       3,     3,     3,     2,     4,     1,     1,     1,     3,     3,
       1,     3,     1,     1,     3,     0,     2,     3,     2,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       1,     1,     2,     1,     2,     0,     3,     0,     2,     1,
       2,     2,     1,     3,     0,     3,     6,     2,     4,     0,
       1
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
#line 260 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1868 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 291 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1877 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 297 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1885 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 302 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1893 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 308 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1901 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 314 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1909 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 320 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1917 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 326 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1927 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 333 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1935 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 339 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1945 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE unique_option INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 348 "yacc_sql.y"
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
#line 1968 "yacc_sql.cpp"
    break;

  case 34: /* unique_option: %empty  */
#line 370 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 35: /* unique_option: UNIQUE  */
#line 374 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1984 "yacc_sql.cpp"
    break;

  case 36: /* idx_col_list: %empty  */
#line 380 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1992 "yacc_sql.cpp"
    break;

  case 37: /* idx_col_list: COMMA ID idx_col_list  */
#line 384 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list)!= nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2006 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 397 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2018 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 407 "yacc_sql.y"
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
#line 2043 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_option select_stmt storage_format  */
#line 428 "yacc_sql.y"
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
#line 2068 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID as_option select_stmt storage_format  */
#line 449 "yacc_sql.y"
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
#line 2084 "yacc_sql.cpp"
    break;

  case 42: /* as_option: %empty  */
#line 464 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2092 "yacc_sql.cpp"
    break;

  case 43: /* as_option: AS  */
#line 468 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2100 "yacc_sql.cpp"
    break;

  case 44: /* attr_def_list: %empty  */
#line 475 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2108 "yacc_sql.cpp"
    break;

  case 45: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 479 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2122 "yacc_sql.cpp"
    break;

  case 46: /* attr_def: ID type LBRACE number RBRACE null_option  */
#line 492 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2135 "yacc_sql.cpp"
    break;

  case 47: /* attr_def: ID type null_option  */
#line 501 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2148 "yacc_sql.cpp"
    break;

  case 48: /* null_option: %empty  */
#line 513 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2156 "yacc_sql.cpp"
    break;

  case 49: /* null_option: NULL_T  */
#line 517 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2164 "yacc_sql.cpp"
    break;

  case 50: /* null_option: NOT NULL_T  */
#line 521 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 51: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 528 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2183 "yacc_sql.cpp"
    break;

  case 52: /* create_view_stmt: CREATE VIEW ID LBRACE ID idx_col_list RBRACE AS select_stmt  */
#line 535 "yacc_sql.y"
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
#line 2202 "yacc_sql.cpp"
    break;

  case 53: /* number: NUMBER  */
#line 553 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2208 "yacc_sql.cpp"
    break;

  case 54: /* type: INT_T  */
#line 556 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2214 "yacc_sql.cpp"
    break;

  case 55: /* type: STRING_T  */
#line 557 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2220 "yacc_sql.cpp"
    break;

  case 56: /* type: FLOAT_T  */
#line 558 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2226 "yacc_sql.cpp"
    break;

  case 57: /* type: DATE_T  */
#line 559 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2232 "yacc_sql.cpp"
    break;

  case 58: /* type: TEXT_T  */
#line 560 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2238 "yacc_sql.cpp"
    break;

  case 59: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 564 "yacc_sql.y"
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
#line 2255 "yacc_sql.cpp"
    break;

  case 60: /* value_list: %empty  */
#line 580 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2263 "yacc_sql.cpp"
    break;

  case 61: /* value_list: COMMA value value_list  */
#line 583 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2277 "yacc_sql.cpp"
    break;

  case 62: /* value_list: COMMA expression value_list  */
#line 592 "yacc_sql.y"
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
#line 2296 "yacc_sql.cpp"
    break;

  case 63: /* value: NUMBER  */
#line 608 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2305 "yacc_sql.cpp"
    break;

  case 64: /* value: FLOAT  */
#line 612 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2314 "yacc_sql.cpp"
    break;

  case 65: /* value: DATE_STR  */
#line 616 "yacc_sql.y"
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
#line 2335 "yacc_sql.cpp"
    break;

  case 66: /* value: SSS  */
#line 632 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2346 "yacc_sql.cpp"
    break;

  case 67: /* value: NULL_T  */
#line 638 "yacc_sql.y"
           {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2355 "yacc_sql.cpp"
    break;

  case 68: /* storage_format: %empty  */
#line 645 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2363 "yacc_sql.cpp"
    break;

  case 69: /* storage_format: STORAGE FORMAT EQ ID  */
#line 649 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2371 "yacc_sql.cpp"
    break;

  case 70: /* delete_stmt: DELETE FROM ID where  */
#line 656 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2385 "yacc_sql.cpp"
    break;

  case 71: /* update_stmt: UPDATE ID SET update_kv update_kv_list where  */
#line 668 "yacc_sql.y"
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
#line 2408 "yacc_sql.cpp"
    break;

  case 72: /* update_kv_list: %empty  */
#line 689 "yacc_sql.y"
    {
      (yyval.update_kv_list) = nullptr;
    }
#line 2416 "yacc_sql.cpp"
    break;

  case 73: /* update_kv_list: COMMA update_kv update_kv_list  */
#line 693 "yacc_sql.y"
    {
      if ((yyvsp[0].update_kv_list)!= nullptr) {
        (yyval.update_kv_list) = (yyvsp[0].update_kv_list);
      } else {
        (yyval.update_kv_list) = new std::vector<UpdateKV>;
      }
      (yyval.update_kv_list)->emplace_back(*(yyvsp[-1].update_kv));
      delete (yyvsp[-1].update_kv);
    }
#line 2430 "yacc_sql.cpp"
    break;

  case 74: /* update_kv: ID EQ expression  */
#line 706 "yacc_sql.y"
    {
      (yyval.update_kv) = new UpdateKV;
      (yyval.update_kv)->attr_name = (yyvsp[-2].string);
      (yyval.update_kv)->expression = (yyvsp[0].expression);
      free((yyvsp[-2].string));
    }
#line 2441 "yacc_sql.cpp"
    break;

  case 75: /* from_list: %empty  */
#line 716 "yacc_sql.y"
                {
      (yyval.inner_joins_list) = nullptr;
    }
#line 2449 "yacc_sql.cpp"
    break;

  case 76: /* from_list: COMMA from_node from_list  */
#line 719 "yacc_sql.y"
                                {
      if (nullptr != (yyvsp[0].inner_joins_list)) {
        (yyval.inner_joins_list) = (yyvsp[0].inner_joins_list);
      } else {
        (yyval.inner_joins_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_joins_list)->emplace_back(*(yyvsp[-1].inner_joins));
      delete (yyvsp[-1].inner_joins);
    }
#line 2463 "yacc_sql.cpp"
    break;

  case 77: /* alias: ID  */
#line 731 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 78: /* alias: AS ID  */
#line 734 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2479 "yacc_sql.cpp"
    break;

  case 79: /* alias: %empty  */
#line 737 "yacc_sql.y"
                  {
      (yyval.string) = nullptr;
    }
#line 2487 "yacc_sql.cpp"
    break;

  case 80: /* from_node: ID alias join_list  */
#line 743 "yacc_sql.y"
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
#line 2505 "yacc_sql.cpp"
    break;

  case 81: /* join_list: %empty  */
#line 759 "yacc_sql.y"
                {
      (yyval.inner_joins) = nullptr;
    }
#line 2513 "yacc_sql.cpp"
    break;

  case 82: /* join_list: INNER JOIN ID alias ON condition join_list  */
#line 762 "yacc_sql.y"
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
#line 2530 "yacc_sql.cpp"
    break;

  case 83: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 778 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 84: /* select_stmt: SELECT expression_list  */
#line 785 "yacc_sql.y"
                           {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 85: /* select_stmt: SELECT expression_list FROM from_node from_list where group_by having opt_order_by  */
#line 791 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }
      if ((yyvsp[-4].inner_joins_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-4].inner_joins_list));
        delete (yyvsp[-4].inner_joins_list);
      }
      (yyval.sql_node)->selection.relations.push_back(*(yyvsp[-5].inner_joins));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-3].expression) != nullptr) {
        (yyval.sql_node)->selection.conditions = (yyvsp[-3].expression);
      }

      if ((yyvsp[-2].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-2].expression_list));
        delete (yyvsp[-2].expression_list);
        std::reverse((yyval.sql_node)->selection.group_by.begin(), (yyval.sql_node)->selection.group_by.end());
      }

      (yyval.sql_node)->selection.having_conditions = nullptr;
      if ((yyvsp[-1].expression) != nullptr) {
        (yyval.sql_node)->selection.having_conditions = (yyvsp[-1].expression);
      }

      if ((yyvsp[0].orderby_unit_list) != nullptr) {
        (yyval.sql_node)->selection.orderbys.swap(*(yyvsp[0].orderby_unit_list));
        delete (yyvsp[0].orderby_unit_list);
      }

      delete (yyvsp[-5].inner_joins);

    }
#line 2590 "yacc_sql.cpp"
    break;

  case 86: /* calc_stmt: CALC expression_list  */
#line 830 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression alias  */
#line 839 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2613 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression alias COMMA expression_list  */
#line 848 "yacc_sql.y"
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
#line 2630 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '+' expression  */
#line 862 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '-' expression  */
#line 865 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '*' expression  */
#line 868 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '/' expression  */
#line 871 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2662 "yacc_sql.cpp"
    break;

  case 93: /* expression: '-' expression  */
#line 874 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 94: /* expression: aggre_type LBRACE expression RBRACE  */
#line 877 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 95: /* expression: value  */
#line 880 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 96: /* expression: rel_attr  */
#line 885 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2698 "yacc_sql.cpp"
    break;

  case 97: /* expression: '*'  */
#line 890 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2706 "yacc_sql.cpp"
    break;

  case 98: /* expression: ID DOT '*'  */
#line 894 "yacc_sql.y"
                {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2714 "yacc_sql.cpp"
    break;

  case 99: /* expression: '*' DOT '*'  */
#line 897 "yacc_sql.y"
                 {
      const char* tmp = "*";
      (yyval.expression) = new StarExpr(tmp);
    }
#line 2723 "yacc_sql.cpp"
    break;

  case 100: /* expression: sub_query_expr  */
#line 901 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2731 "yacc_sql.cpp"
    break;

  case 101: /* expression: LBRACE expression_list RBRACE  */
#line 904 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 102: /* aggre_type: AGGR  */
#line 916 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2753 "yacc_sql.cpp"
    break;

  case 103: /* rel_attr: ID  */
#line 921 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 104: /* rel_attr: ID DOT ID  */
#line 926 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2775 "yacc_sql.cpp"
    break;

  case 105: /* where: %empty  */
#line 937 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2783 "yacc_sql.cpp"
    break;

  case 106: /* where: WHERE condition  */
#line 940 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].condition);  
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 107: /* condition: expression comp_op expression  */
#line 947 "yacc_sql.y"
    {
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2799 "yacc_sql.cpp"
    break;

  case 108: /* condition: exists_op expression  */
#line 951 "yacc_sql.y"
    {
      NullExpr *null_expr = new NullExpr();
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), null_expr, (yyvsp[0].expression));
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 109: /* condition: condition AND condition  */
#line 956 "yacc_sql.y"
    {
      (yyval.condition) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].condition), (yyvsp[0].condition));
    }
#line 2816 "yacc_sql.cpp"
    break;

  case 110: /* condition: condition OR condition  */
#line 960 "yacc_sql.y"
    {
      (yyval.condition) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].condition), (yyvsp[0].condition));
    }
#line 2824 "yacc_sql.cpp"
    break;

  case 111: /* comp_op: EQ  */
#line 966 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2830 "yacc_sql.cpp"
    break;

  case 112: /* comp_op: LT  */
#line 967 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2836 "yacc_sql.cpp"
    break;

  case 113: /* comp_op: GT  */
#line 968 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2842 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: LE  */
#line 969 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2848 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: GE  */
#line 970 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2854 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: NE  */
#line 971 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2860 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: LIKE  */
#line 972 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 2866 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: NOT LIKE  */
#line 973 "yacc_sql.y"
               {(yyval.comp) = NOT_LIKE_OP;}
#line 2872 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: IS NOT  */
#line 974 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_OP;}
#line 2878 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: IS  */
#line 975 "yacc_sql.y"
         {(yyval.comp) = IS_OP;}
#line 2884 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: IN  */
#line 976 "yacc_sql.y"
          {(yyval.comp) = IN_OP;}
#line 2890 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: NOT IN  */
#line 977 "yacc_sql.y"
             {(yyval.comp) = NOT_IN_OP;}
#line 2896 "yacc_sql.cpp"
    break;

  case 123: /* exists_op: EXISTS  */
#line 981 "yacc_sql.y"
           {(yyval.comp) = EXISTS_OP;}
#line 2902 "yacc_sql.cpp"
    break;

  case 124: /* exists_op: NOT EXISTS  */
#line 982 "yacc_sql.y"
                 {(yyval.comp) = NOT_EXISTS_OP;}
#line 2908 "yacc_sql.cpp"
    break;

  case 125: /* group_by: %empty  */
#line 988 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2916 "yacc_sql.cpp"
    break;

  case 126: /* group_by: GROUP BY expression_list  */
#line 991 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2924 "yacc_sql.cpp"
    break;

  case 127: /* having: %empty  */
#line 997 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2932 "yacc_sql.cpp"
    break;

  case 128: /* having: HAVING condition  */
#line 1000 "yacc_sql.y"
                       {
      (yyval.expression) = (yyvsp[0].condition);
    }
#line 2940 "yacc_sql.cpp"
    break;

  case 129: /* sort_unit: expression  */
#line 1008 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[0].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 2950 "yacc_sql.cpp"
    break;

  case 130: /* sort_unit: expression DESC  */
#line 1015 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = false;
	}
#line 2960 "yacc_sql.cpp"
    break;

  case 131: /* sort_unit: expression ASC  */
#line 1022 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 2970 "yacc_sql.cpp"
    break;

  case 132: /* sort_list: sort_unit  */
#line 1030 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = new std::vector<OrderBySqlNode>;
    (yyval.orderby_unit_list)->emplace_back(*(yyvsp[0].orderby_unit));
    delete (yyvsp[0].orderby_unit);
	}
#line 2980 "yacc_sql.cpp"
    break;

  case 133: /* sort_list: sort_unit COMMA sort_list  */
#line 1037 "yacc_sql.y"
        {
    (yyvsp[0].orderby_unit_list)->emplace_back(*(yyvsp[-2].orderby_unit));
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    delete (yyvsp[-2].orderby_unit);
	}
#line 2990 "yacc_sql.cpp"
    break;

  case 134: /* opt_order_by: %empty  */
#line 1044 "yacc_sql.y"
                    {
   (yyval.orderby_unit_list) = nullptr;
  }
#line 2998 "yacc_sql.cpp"
    break;

  case 135: /* opt_order_by: ORDER BY sort_list  */
#line 1048 "yacc_sql.y"
        {
      (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
      std::reverse((yyval.orderby_unit_list)->begin(),(yyval.orderby_unit_list)->end());
	}
#line 3007 "yacc_sql.cpp"
    break;

  case 136: /* load_data_stmt: LOAD_DATA INFILE SSS INTO TABLE ID  */
#line 1055 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 137: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1068 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3030 "yacc_sql.cpp"
    break;

  case 138: /* set_variable_stmt: SET ID EQ value  */
#line 1076 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3042 "yacc_sql.cpp"
    break;


#line 3046 "yacc_sql.cpp"

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

#line 1088 "yacc_sql.y"

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
