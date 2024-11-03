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
  YYSYMBOL_attr_def_list = 99,             /* attr_def_list  */
  YYSYMBOL_attr_def = 100,                 /* attr_def  */
  YYSYMBOL_null_option = 101,              /* null_option  */
  YYSYMBOL_create_view_stmt = 102,         /* create_view_stmt  */
  YYSYMBOL_number = 103,                   /* number  */
  YYSYMBOL_type = 104,                     /* type  */
  YYSYMBOL_insert_stmt = 105,              /* insert_stmt  */
  YYSYMBOL_value_list = 106,               /* value_list  */
  YYSYMBOL_value = 107,                    /* value  */
  YYSYMBOL_storage_format = 108,           /* storage_format  */
  YYSYMBOL_delete_stmt = 109,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 110,              /* update_stmt  */
  YYSYMBOL_update_kv_list = 111,           /* update_kv_list  */
  YYSYMBOL_update_kv = 112,                /* update_kv  */
  YYSYMBOL_from_list = 113,                /* from_list  */
  YYSYMBOL_alias = 114,                    /* alias  */
  YYSYMBOL_from_node = 115,                /* from_node  */
  YYSYMBOL_join_list = 116,                /* join_list  */
  YYSYMBOL_sub_query_expr = 117,           /* sub_query_expr  */
  YYSYMBOL_select_stmt = 118,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 119,                /* calc_stmt  */
  YYSYMBOL_expression_list = 120,          /* expression_list  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_aggre_type = 122,               /* aggre_type  */
  YYSYMBOL_rel_attr = 123,                 /* rel_attr  */
  YYSYMBOL_where = 124,                    /* where  */
  YYSYMBOL_condition = 125,                /* condition  */
  YYSYMBOL_comp_op = 126,                  /* comp_op  */
  YYSYMBOL_exists_op = 127,                /* exists_op  */
  YYSYMBOL_group_by = 128,                 /* group_by  */
  YYSYMBOL_having = 129,                   /* having  */
  YYSYMBOL_sort_unit = 130,                /* sort_unit  */
  YYSYMBOL_sort_list = 131,                /* sort_list  */
  YYSYMBOL_opt_order_by = 132,             /* opt_order_by  */
  YYSYMBOL_load_data_stmt = 133,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 134,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 135,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 136             /* opt_semicolon  */
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
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  252

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
       0,   258,   258,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   290,   296,   301,   307,   313,   319,
     325,   332,   338,   346,   369,   372,   379,   382,   395,   405,
     426,   447,   462,   465,   478,   487,   500,   503,   507,   514,
     521,   540,   543,   544,   545,   546,   547,   550,   567,   570,
     579,   595,   599,   603,   619,   625,   632,   635,   642,   654,
     676,   679,   692,   703,   706,   718,   721,   724,   730,   746,
     749,   764,   772,   777,   816,   825,   834,   849,   852,   855,
     858,   861,   864,   867,   872,   877,   881,   884,   888,   891,
     903,   908,   913,   924,   927,   933,   937,   942,   946,   953,
     954,   955,   956,   957,   958,   959,   960,   961,   962,   963,
     964,   968,   969,   975,   978,   984,   987,   994,  1001,  1008,
    1016,  1023,  1031,  1034,  1041,  1054,  1062,  1072,  1073
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
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "null_option", "create_view_stmt", "number", "type", "insert_stmt",
  "value_list", "value", "storage_format", "delete_stmt", "update_stmt",
  "update_kv_list", "update_kv", "from_list", "alias", "from_node",
  "join_list", "sub_query_expr", "select_stmt", "calc_stmt",
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

#define YYPACT_NINF (-176)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     185,     3,    28,    61,    61,   -65,    13,  -176,    15,    -6,
     -33,  -176,  -176,  -176,  -176,  -176,    10,   -17,   185,    65,
      60,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,    14,    24,  -176,    56,    32,    40,    43,  -176,
    -176,  -176,    42,  -176,  -176,  -176,    61,    86,  -176,  -176,
    -176,     0,   107,  -176,    93,  -176,  -176,    58,    74,   102,
      94,    91,  -176,  -176,  -176,  -176,     4,     5,    75,  -176,
     125,   147,   148,   -49,  -176,   101,   108,  -176,    61,    61,
      61,    61,   159,    61,   110,   149,   146,   115,    70,   154,
     176,   120,   176,   121,   155,   123,  -176,  -176,  -176,  -176,
    -176,  -176,   -37,   -37,  -176,  -176,    61,    30,     1,   183,
     186,    20,  -176,   153,   189,  -176,   204,   163,   132,   192,
    -176,   196,   150,  -176,  -176,  -176,   167,   110,   146,    70,
     157,  -176,    95,     9,    61,    61,   115,   146,   151,   170,
    -176,  -176,  -176,  -176,  -176,  -176,   -10,   120,   203,   156,
     205,   209,   177,  -176,   183,   224,   210,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,    -2,  -176,  -176,   173,    61,    20,
      20,    99,    99,   189,  -176,  -176,   181,   166,   171,  -176,
    -176,   192,    11,   196,   233,   168,   169,  -176,   236,   174,
      61,   221,  -176,  -176,  -176,    99,  -176,   206,  -176,   175,
    -176,   225,  -176,  -176,   176,  -176,  -176,   176,   196,     1,
      61,    20,   180,    63,    23,  -176,  -176,   -40,   163,  -176,
     227,   208,  -176,     9,   247,  -176,  -176,  -176,  -176,  -176,
    -176,    20,    61,   -21,    -8,   229,  -176,  -176,  -176,  -176,
      61,  -176
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     137,    23,    22,    15,    16,    17,    18,     9,    10,    11,
      12,    13,     8,    14,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,    35,     0,     0,     0,     0,    65,
      61,    62,   101,    64,   100,    63,     0,    95,    93,    98,
      84,    77,     0,    94,    82,    32,    31,     0,     0,     0,
       0,     0,   135,     1,   138,     2,     0,     0,     0,    30,
       0,     0,     0,     0,    91,     0,     0,    75,     0,     0,
       0,     0,    85,     0,     0,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    99,   102,    96,
      97,    76,    87,    88,    89,    90,     0,     0,    77,    73,
       0,     0,    68,     0,    70,   136,     0,    66,     0,    42,
      49,    36,     0,    38,    86,    92,    79,     0,   103,     0,
       0,   121,     0,   104,     0,     0,     0,   103,     0,     0,
      41,    52,    55,    56,    53,    54,    46,     0,     0,     0,
       0,     0,     0,    78,    73,   123,    58,   122,   109,   110,
     111,   112,   113,   114,     0,   115,   119,   118,     0,     0,
       0,   106,    72,    70,    69,   134,     0,     0,     0,    47,
      45,    42,    66,    36,     0,     0,     0,    74,     0,   125,
       0,     0,   116,   120,   117,   105,   107,   108,    71,     0,
      51,     0,    48,    43,     0,    39,    37,     0,    36,    77,
       0,     0,   132,    93,    58,    57,    67,    46,    66,    50,
       0,     0,   124,   126,     0,    83,    59,    60,    44,    40,
      33,     0,     0,    79,   127,   130,   133,    80,   128,   129,
       0,   131
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -176,  -176,   235,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -171,  -176,  -176,    64,    97,    29,
    -176,  -176,  -176,  -176,   -97,   -94,  -175,  -176,  -176,    76,
     111,    96,  -115,   124,    19,  -176,   -46,  -176,    -4,   -55,
    -176,  -176,  -118,  -166,  -176,  -176,  -176,  -176,  -176,     8,
    -176,  -176,  -176,  -176,  -176
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    45,   160,    31,    32,   158,   129,   190,
      33,   211,   156,    34,   201,    58,   150,    35,    36,   147,
     124,   138,    92,   119,   163,    59,    37,    38,    60,    61,
      62,    63,   122,   143,   178,   144,   199,   222,   245,   246,
     235,    39,    40,    41,    75
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    84,    81,   136,   125,    86,    86,   248,    65,   100,
     102,   187,    42,   206,   207,    43,   214,   215,   179,   180,
     165,   188,   216,    66,   108,   101,   103,    71,   189,   184,
     109,    68,   162,   112,   113,   114,   115,    46,   117,    47,
      69,    48,    90,    91,    82,   166,   200,   230,   179,   180,
      67,   188,   135,   239,   127,   233,   130,     4,   189,   249,
     202,   203,   149,    74,    48,    73,   142,    78,    44,    88,
      89,    90,    91,    87,    87,   243,    83,    88,    89,    90,
      91,   140,    48,    70,   141,   -58,   200,    76,    49,   181,
     182,    50,    51,    52,    53,    54,    55,    77,    56,    57,
      88,    89,    90,    91,   231,    79,   223,    88,    89,    90,
      91,    49,   134,    80,    50,    51,    52,    53,    54,    55,
      85,    56,    57,   205,   142,   142,   236,   237,    93,    49,
      94,    95,    50,    51,    52,    53,    54,    55,    49,    56,
      57,    50,    51,    97,    53,   224,    55,    96,   104,    98,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   151,
     152,   153,   154,   155,   177,    99,   142,   105,   228,   106,
     107,   229,    88,    89,    90,    91,    88,    89,    90,    91,
     110,   111,   116,   118,   121,   120,   142,   244,   123,   126,
       4,     1,     2,   128,   131,   244,   133,   132,     3,     4,
       5,     6,     7,     8,     9,    10,   137,   139,   145,    11,
      12,    13,   146,   148,   149,   157,   232,    14,    15,   159,
     162,   167,   186,   161,   185,   192,    16,   194,    17,   193,
     195,   196,   198,   200,   204,    18,   209,   210,   217,   212,
     220,   218,   219,   225,   221,   179,   234,   227,   226,   240,
     241,   242,   250,    72,   191,   213,   238,   183,   251,   208,
     197,   164,   247
};

static const yytype_uint8 yycheck[] =
{
       4,    56,    48,   118,    98,     5,     5,    15,    73,     5,
       5,    21,     9,   179,   180,    12,     5,   192,    39,    40,
     138,    61,   193,    10,    73,    21,    21,    44,    68,   147,
      79,    37,    53,    88,    89,    90,    91,     9,    93,    11,
      73,    21,    79,    80,    48,   139,    23,   218,    39,    40,
      35,    61,    22,   228,   100,   221,   102,    14,    68,    67,
      62,    63,    51,     3,    21,     0,   121,    11,    65,    77,
      78,    79,    80,    73,    73,   241,    34,    77,    78,    79,
      80,    61,    21,    73,    64,    22,    23,    73,    68,   144,
     145,    71,    72,    73,    74,    75,    76,    73,    78,    79,
      77,    78,    79,    80,   219,    73,   200,    77,    78,    79,
      80,    68,   116,    73,    71,    72,    73,    74,    75,    76,
      34,    78,    79,   178,   179,   180,   223,   224,    21,    68,
      37,    73,    71,    72,    73,    74,    75,    76,    68,    78,
      79,    71,    72,    41,    74,   200,    76,    73,    73,    55,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    27,
      28,    29,    30,    31,    69,    74,   221,    42,   214,    22,
      22,   217,    77,    78,    79,    80,    77,    78,    79,    80,
      79,    73,    23,    73,    38,    36,   241,   242,    73,    35,
      14,     6,     7,    73,    73,   250,    73,    42,    13,    14,
      15,    16,    17,    18,    19,    20,    23,    21,    55,    24,
      25,    26,    23,     9,    51,    23,   220,    32,    33,    23,
      53,    64,    52,    73,    73,    22,    41,    22,    43,    73,
      21,    54,     8,    23,    61,    50,    55,    71,     5,    68,
       4,    73,    73,    22,    70,    39,    66,    22,    73,    22,
      42,     4,    23,    18,   157,   191,   227,   146,   250,   183,
     164,   137,   243
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    13,    14,    15,    16,    17,    18,    19,
      20,    24,    25,    26,    32,    33,    41,    43,    50,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    97,    98,   102,   105,   109,   110,   118,   119,   133,
     134,   135,     9,    12,    65,    95,     9,    11,    21,    68,
      71,    72,    73,    74,    75,    76,    78,    79,   107,   117,
     120,   121,   122,   123,   120,    73,    10,    35,    37,    73,
      73,    44,    84,     0,     3,   136,    73,    73,    11,    73,
      73,   118,   120,    34,   121,    34,     5,    73,    77,    78,
      79,    80,   114,    21,    37,    73,    73,    41,    55,    74,
       5,    21,     5,    21,    73,    42,    22,    22,    73,    79,
      79,    73,   121,   121,   121,   121,    23,   121,    73,   115,
      36,    38,   124,    73,   112,   107,    35,   118,    73,   100,
     118,    73,    42,    73,   120,    22,   114,    23,   113,    21,
      61,    64,   121,   125,   127,    55,    23,   111,     9,    51,
     108,    27,    28,    29,    30,    31,   104,    23,    99,    23,
      96,    73,    53,   116,   115,   124,   107,    64,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    69,   126,    39,
      40,   121,   121,   112,   124,    73,    52,    21,    61,    68,
     101,   100,    22,    73,    22,    21,    54,   113,     8,   128,
      23,   106,    62,    63,    61,   121,   125,   125,   111,    55,
      71,   103,    68,    99,     5,   108,    96,     5,    73,    73,
       4,    70,   129,   107,   121,    22,    73,    22,   118,   118,
      96,   114,   120,   125,    66,   132,   106,   106,   101,   108,
      22,    42,     4,   125,   121,   130,   131,   116,    15,    67,
      23,   131
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    95,    96,    96,    97,    98,
      98,    98,    99,    99,   100,   100,   101,   101,   101,   102,
     102,   103,   104,   104,   104,   104,   104,   105,   106,   106,
     106,   107,   107,   107,   107,   107,   108,   108,   109,   110,
     111,   111,   112,   113,   113,   114,   114,   114,   115,   116,
     116,   117,   118,   118,   119,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   123,   123,   124,   124,   125,   125,   125,   125,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   128,   128,   129,   129,   130,   130,   130,
     131,   131,   132,   132,   133,   134,   135,   136,   136
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,    10,     0,     1,     0,     3,     5,     8,
      10,     6,     0,     3,     6,     3,     0,     1,     2,     5,
       9,     1,     1,     1,     1,     1,     1,     8,     0,     3,
       3,     1,     1,     1,     1,     1,     0,     4,     4,     6,
       0,     3,     3,     0,     3,     1,     2,     0,     3,     0,
       7,     3,     2,     9,     2,     2,     4,     3,     3,     3,
       3,     2,     4,     1,     1,     1,     3,     3,     1,     3,
       1,     1,     3,     0,     2,     3,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       2,     1,     2,     0,     3,     0,     2,     1,     2,     2,
       1,     3,     0,     3,     6,     2,     4,     0,     1
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
#line 259 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1864 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 290 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1873 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 296 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1881 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 301 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1889 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 307 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1897 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 313 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1905 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 319 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1913 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 325 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1923 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 332 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1931 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 338 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1941 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE unique_option INDEX ID ON ID LBRACE ID idx_col_list RBRACE  */
#line 347 "yacc_sql.y"
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
#line 1964 "yacc_sql.cpp"
    break;

  case 34: /* unique_option: %empty  */
#line 369 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 1972 "yacc_sql.cpp"
    break;

  case 35: /* unique_option: UNIQUE  */
#line 373 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 36: /* idx_col_list: %empty  */
#line 379 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 1988 "yacc_sql.cpp"
    break;

  case 37: /* idx_col_list: COMMA ID idx_col_list  */
#line 383 "yacc_sql.y"
    {
      if ((yyvsp[0].relation_list)!= nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::string>;
      }
      (yyval.relation_list)->emplace_back((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 38: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 396 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 39: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 406 "yacc_sql.y"
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
#line 2039 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE AS select_stmt storage_format  */
#line 427 "yacc_sql.y"
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
#line 2064 "yacc_sql.cpp"
    break;

  case 41: /* create_table_stmt: CREATE TABLE ID AS select_stmt storage_format  */
#line 448 "yacc_sql.y"
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
#line 2080 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: %empty  */
#line 462 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 43: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 466 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2102 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type LBRACE number RBRACE null_option  */
#line 479 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-5].string));
    }
#line 2115 "yacc_sql.cpp"
    break;

  case 45: /* attr_def: ID type null_option  */
#line 488 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].boolean);
      free((yyvsp[-2].string));
    }
#line 2128 "yacc_sql.cpp"
    break;

  case 46: /* null_option: %empty  */
#line 500 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2136 "yacc_sql.cpp"
    break;

  case 47: /* null_option: NULL_T  */
#line 504 "yacc_sql.y"
    {
      (yyval.boolean) = true;
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 48: /* null_option: NOT NULL_T  */
#line 508 "yacc_sql.y"
    {
      (yyval.boolean) = false;
    }
#line 2152 "yacc_sql.cpp"
    break;

  case 49: /* create_view_stmt: CREATE VIEW ID AS select_stmt  */
#line 515 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->flag = SCF_CREATE_VIEW;
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 50: /* create_view_stmt: CREATE VIEW ID LBRACE ID idx_col_list RBRACE AS select_stmt  */
#line 522 "yacc_sql.y"
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
#line 2182 "yacc_sql.cpp"
    break;

  case 51: /* number: NUMBER  */
#line 540 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2188 "yacc_sql.cpp"
    break;

  case 52: /* type: INT_T  */
#line 543 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2194 "yacc_sql.cpp"
    break;

  case 53: /* type: STRING_T  */
#line 544 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2200 "yacc_sql.cpp"
    break;

  case 54: /* type: FLOAT_T  */
#line 545 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2206 "yacc_sql.cpp"
    break;

  case 55: /* type: DATE_T  */
#line 546 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2212 "yacc_sql.cpp"
    break;

  case 56: /* type: TEXT_T  */
#line 547 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2218 "yacc_sql.cpp"
    break;

  case 57: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 551 "yacc_sql.y"
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
#line 2235 "yacc_sql.cpp"
    break;

  case 58: /* value_list: %empty  */
#line 567 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2243 "yacc_sql.cpp"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 570 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 60: /* value_list: COMMA expression value_list  */
#line 579 "yacc_sql.y"
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
#line 2276 "yacc_sql.cpp"
    break;

  case 61: /* value: NUMBER  */
#line 595 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2285 "yacc_sql.cpp"
    break;

  case 62: /* value: FLOAT  */
#line 599 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2294 "yacc_sql.cpp"
    break;

  case 63: /* value: DATE_STR  */
#line 603 "yacc_sql.y"
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
#line 2315 "yacc_sql.cpp"
    break;

  case 64: /* value: SSS  */
#line 619 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2326 "yacc_sql.cpp"
    break;

  case 65: /* value: NULL_T  */
#line 625 "yacc_sql.y"
           {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 66: /* storage_format: %empty  */
#line 632 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2343 "yacc_sql.cpp"
    break;

  case 67: /* storage_format: STORAGE FORMAT EQ ID  */
#line 636 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2351 "yacc_sql.cpp"
    break;

  case 68: /* delete_stmt: DELETE FROM ID where  */
#line 643 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      (yyval.sql_node)->deletion.conditions = nullptr;
      if ((yyvsp[0].expression) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].expression);
      }
      free((yyvsp[-1].string));
    }
#line 2365 "yacc_sql.cpp"
    break;

  case 69: /* update_stmt: UPDATE ID SET update_kv update_kv_list where  */
#line 655 "yacc_sql.y"
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
#line 2388 "yacc_sql.cpp"
    break;

  case 70: /* update_kv_list: %empty  */
#line 676 "yacc_sql.y"
    {
      (yyval.update_kv_list) = nullptr;
    }
#line 2396 "yacc_sql.cpp"
    break;

  case 71: /* update_kv_list: COMMA update_kv update_kv_list  */
#line 680 "yacc_sql.y"
    {
      if ((yyvsp[0].update_kv_list)!= nullptr) {
        (yyval.update_kv_list) = (yyvsp[0].update_kv_list);
      } else {
        (yyval.update_kv_list) = new std::vector<UpdateKV>;
      }
      (yyval.update_kv_list)->emplace_back(*(yyvsp[-1].update_kv));
      delete (yyvsp[-1].update_kv);
    }
#line 2410 "yacc_sql.cpp"
    break;

  case 72: /* update_kv: ID EQ expression  */
#line 693 "yacc_sql.y"
    {
      (yyval.update_kv) = new UpdateKV;
      (yyval.update_kv)->attr_name = (yyvsp[-2].string);
      (yyval.update_kv)->expression = (yyvsp[0].expression);
      free((yyvsp[-2].string));
    }
#line 2421 "yacc_sql.cpp"
    break;

  case 73: /* from_list: %empty  */
#line 703 "yacc_sql.y"
                {
      (yyval.inner_joins_list) = nullptr;
    }
#line 2429 "yacc_sql.cpp"
    break;

  case 74: /* from_list: COMMA from_node from_list  */
#line 706 "yacc_sql.y"
                                {
      if (nullptr != (yyvsp[0].inner_joins_list)) {
        (yyval.inner_joins_list) = (yyvsp[0].inner_joins_list);
      } else {
        (yyval.inner_joins_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_joins_list)->emplace_back(*(yyvsp[-1].inner_joins));
      delete (yyvsp[-1].inner_joins);
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 75: /* alias: ID  */
#line 718 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 76: /* alias: AS ID  */
#line 721 "yacc_sql.y"
            {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2459 "yacc_sql.cpp"
    break;

  case 77: /* alias: %empty  */
#line 724 "yacc_sql.y"
                  {
      (yyval.string) = nullptr;
    }
#line 2467 "yacc_sql.cpp"
    break;

  case 78: /* from_node: ID alias join_list  */
#line 730 "yacc_sql.y"
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
#line 2485 "yacc_sql.cpp"
    break;

  case 79: /* join_list: %empty  */
#line 746 "yacc_sql.y"
                {
      (yyval.inner_joins) = nullptr;
    }
#line 2493 "yacc_sql.cpp"
    break;

  case 80: /* join_list: INNER JOIN ID alias ON condition join_list  */
#line 749 "yacc_sql.y"
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
#line 2510 "yacc_sql.cpp"
    break;

  case 81: /* sub_query_expr: LBRACE select_stmt RBRACE  */
#line 765 "yacc_sql.y"
    {
      (yyval.expression) = new SubQueryExpr((yyvsp[-1].sql_node)->selection);
      delete (yyvsp[-1].sql_node);
    }
#line 2519 "yacc_sql.cpp"
    break;

  case 82: /* select_stmt: SELECT expression_list  */
#line 772 "yacc_sql.y"
                           {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 83: /* select_stmt: SELECT expression_list FROM from_node from_list where group_by having opt_order_by  */
#line 778 "yacc_sql.y"
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
#line 2570 "yacc_sql.cpp"
    break;

  case 84: /* calc_stmt: CALC expression_list  */
#line 817 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 85: /* expression_list: expression alias  */
#line 826 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      if((yyvsp[0].string) != nullptr){
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2593 "yacc_sql.cpp"
    break;

  case 86: /* expression_list: expression alias COMMA expression_list  */
#line 835 "yacc_sql.y"
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
#line 2610 "yacc_sql.cpp"
    break;

  case 87: /* expression: expression '+' expression  */
#line 849 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2618 "yacc_sql.cpp"
    break;

  case 88: /* expression: expression '-' expression  */
#line 852 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2626 "yacc_sql.cpp"
    break;

  case 89: /* expression: expression '*' expression  */
#line 855 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2634 "yacc_sql.cpp"
    break;

  case 90: /* expression: expression '/' expression  */
#line 858 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2642 "yacc_sql.cpp"
    break;

  case 91: /* expression: '-' expression  */
#line 861 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2650 "yacc_sql.cpp"
    break;

  case 92: /* expression: aggre_type LBRACE expression RBRACE  */
#line 864 "yacc_sql.y"
                                          {
      (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2658 "yacc_sql.cpp"
    break;

  case 93: /* expression: value  */
#line 867 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 94: /* expression: rel_attr  */
#line 872 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr((yyvsp[0].rel_attr)->relation_name, (yyvsp[0].rel_attr)->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2678 "yacc_sql.cpp"
    break;

  case 95: /* expression: '*'  */
#line 877 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 96: /* expression: ID DOT '*'  */
#line 881 "yacc_sql.y"
                {
      (yyval.expression) = new StarExpr((yyvsp[-2].string));
    }
#line 2694 "yacc_sql.cpp"
    break;

  case 97: /* expression: '*' DOT '*'  */
#line 884 "yacc_sql.y"
                 {
      const char* tmp = "*";
      (yyval.expression) = new StarExpr(tmp);
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 98: /* expression: sub_query_expr  */
#line 888 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 99: /* expression: LBRACE expression_list RBRACE  */
#line 891 "yacc_sql.y"
                                    {
      if ((yyvsp[-1].expression_list)->size() == 1) {
        (yyval.expression) = (yyvsp[-1].expression_list)->front();
      } else {
        (yyval.expression) = new ExprListExpr(std::move(*(yyvsp[-1].expression_list)));
      }
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[-1].expression_list);
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 100: /* aggre_type: AGGR  */
#line 903 "yacc_sql.y"
         {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 101: /* rel_attr: ID  */
#line 908 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2743 "yacc_sql.cpp"
    break;

  case 102: /* rel_attr: ID DOT ID  */
#line 913 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2755 "yacc_sql.cpp"
    break;

  case 103: /* where: %empty  */
#line 924 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 104: /* where: WHERE condition  */
#line 927 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[0].condition);  
    }
#line 2771 "yacc_sql.cpp"
    break;

  case 105: /* condition: expression comp_op expression  */
#line 934 "yacc_sql.y"
    {
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), (yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 2779 "yacc_sql.cpp"
    break;

  case 106: /* condition: exists_op expression  */
#line 938 "yacc_sql.y"
    {
      NullExpr *null_expr = new NullExpr();
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), null_expr, (yyvsp[0].expression));
    }
#line 2788 "yacc_sql.cpp"
    break;

  case 107: /* condition: condition AND condition  */
#line 943 "yacc_sql.y"
    {
      (yyval.condition) = new ConjunctionExpr(ConjunctionExpr::Type::AND, (yyvsp[-2].condition), (yyvsp[0].condition));
    }
#line 2796 "yacc_sql.cpp"
    break;

  case 108: /* condition: condition OR condition  */
#line 947 "yacc_sql.y"
    {
      (yyval.condition) = new ConjunctionExpr(ConjunctionExpr::Type::OR, (yyvsp[-2].condition), (yyvsp[0].condition));
    }
#line 2804 "yacc_sql.cpp"
    break;

  case 109: /* comp_op: EQ  */
#line 953 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2810 "yacc_sql.cpp"
    break;

  case 110: /* comp_op: LT  */
#line 954 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2816 "yacc_sql.cpp"
    break;

  case 111: /* comp_op: GT  */
#line 955 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2822 "yacc_sql.cpp"
    break;

  case 112: /* comp_op: LE  */
#line 956 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2828 "yacc_sql.cpp"
    break;

  case 113: /* comp_op: GE  */
#line 957 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2834 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: NE  */
#line 958 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2840 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: LIKE  */
#line 959 "yacc_sql.y"
           { (yyval.comp) = LIKE_OP;}
#line 2846 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: NOT LIKE  */
#line 960 "yacc_sql.y"
               {(yyval.comp) = NOT_LIKE_OP;}
#line 2852 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: IS NOT  */
#line 961 "yacc_sql.y"
             {(yyval.comp) = IS_NOT_OP;}
#line 2858 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: IS  */
#line 962 "yacc_sql.y"
         {(yyval.comp) = IS_OP;}
#line 2864 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: IN  */
#line 963 "yacc_sql.y"
          {(yyval.comp) = IN_OP;}
#line 2870 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: NOT IN  */
#line 964 "yacc_sql.y"
             {(yyval.comp) = NOT_IN_OP;}
#line 2876 "yacc_sql.cpp"
    break;

  case 121: /* exists_op: EXISTS  */
#line 968 "yacc_sql.y"
           {(yyval.comp) = EXISTS_OP;}
#line 2882 "yacc_sql.cpp"
    break;

  case 122: /* exists_op: NOT EXISTS  */
#line 969 "yacc_sql.y"
                 {(yyval.comp) = NOT_EXISTS_OP;}
#line 2888 "yacc_sql.cpp"
    break;

  case 123: /* group_by: %empty  */
#line 975 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2896 "yacc_sql.cpp"
    break;

  case 124: /* group_by: GROUP BY expression_list  */
#line 978 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 125: /* having: %empty  */
#line 984 "yacc_sql.y"
    {
      (yyval.expression) = nullptr;
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 126: /* having: HAVING condition  */
#line 987 "yacc_sql.y"
                       {
      (yyval.expression) = (yyvsp[0].condition);
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 127: /* sort_unit: expression  */
#line 995 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[0].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 2930 "yacc_sql.cpp"
    break;

  case 128: /* sort_unit: expression DESC  */
#line 1002 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = false;
	}
#line 2940 "yacc_sql.cpp"
    break;

  case 129: /* sort_unit: expression ASC  */
#line 1009 "yacc_sql.y"
        {
    (yyval.orderby_unit) = new OrderBySqlNode();//默认是升序
    (yyval.orderby_unit)->expr = (yyvsp[-1].expression);
    (yyval.orderby_unit)->is_asc = true;
	}
#line 2950 "yacc_sql.cpp"
    break;

  case 130: /* sort_list: sort_unit  */
#line 1017 "yacc_sql.y"
        {
    (yyval.orderby_unit_list) = new std::vector<OrderBySqlNode>;
    (yyval.orderby_unit_list)->emplace_back(*(yyvsp[0].orderby_unit));
    delete (yyvsp[0].orderby_unit);
	}
#line 2960 "yacc_sql.cpp"
    break;

  case 131: /* sort_list: sort_unit COMMA sort_list  */
#line 1024 "yacc_sql.y"
        {
    (yyvsp[0].orderby_unit_list)->emplace_back(*(yyvsp[-2].orderby_unit));
    (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
    delete (yyvsp[-2].orderby_unit);
	}
#line 2970 "yacc_sql.cpp"
    break;

  case 132: /* opt_order_by: %empty  */
#line 1031 "yacc_sql.y"
                    {
   (yyval.orderby_unit_list) = nullptr;
  }
#line 2978 "yacc_sql.cpp"
    break;

  case 133: /* opt_order_by: ORDER BY sort_list  */
#line 1035 "yacc_sql.y"
        {
      (yyval.orderby_unit_list) = (yyvsp[0].orderby_unit_list);
      std::reverse((yyval.orderby_unit_list)->begin(),(yyval.orderby_unit_list)->end());
	}
#line 2987 "yacc_sql.cpp"
    break;

  case 134: /* load_data_stmt: LOAD_DATA INFILE SSS INTO TABLE ID  */
#line 1042 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 135: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1055 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3010 "yacc_sql.cpp"
    break;

  case 136: /* set_variable_stmt: SET ID EQ value  */
#line 1063 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3022 "yacc_sql.cpp"
    break;


#line 3026 "yacc_sql.cpp"

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

#line 1075 "yacc_sql.y"

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
