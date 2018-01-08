/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 18 "sql.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#line 72 "sql.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sql.tab.h".  */
#ifndef YY_YY_SQL_TAB_H_INCLUDED
# define YY_YY_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 30 "sql.y" /* yacc.c:355  */

char *filename;

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
  char *filename;
} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1

# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)                                                            \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	  (Current).filename     = YYRHSLOC (Rhs, 1).filename;	        \
	}								\
      else								\
	{ /* empty RHS */						\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	  (Current).filename  = NULL;					\
	}								\
    while (0)

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

struct psql_state;

#line 142 "sql.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME = 258,
    STRING = 259,
    INTNUM = 260,
    BOOL = 261,
    APPROXNUM = 262,
    USERVAR = 263,
    ASSIGN = 264,
    OR = 265,
    XOR = 266,
    ANDOP = 267,
    IN = 268,
    IS = 269,
    LIKE = 270,
    REGEXP = 271,
    NOT = 272,
    BETWEEN = 273,
    COMPARISON = 274,
    SHIFT = 275,
    MOD = 276,
    UMINUS = 277,
    ADD = 278,
    ALL = 279,
    ALTER = 280,
    ANALYZE = 281,
    AND = 282,
    ANY = 283,
    AS = 284,
    ASC = 285,
    AUTO_INCREMENT = 286,
    BEFORE = 287,
    BIGINT = 288,
    BINARY = 289,
    BIT = 290,
    BLOB = 291,
    BOTH = 292,
    BY = 293,
    CALL = 294,
    CASCADE = 295,
    CASE = 296,
    CHANGE = 297,
    CHAR = 298,
    CHECK = 299,
    COLLATE = 300,
    COLUMN = 301,
    COMMENT = 302,
    CONDITION = 303,
    CONSTRAINT = 304,
    CONTINUE = 305,
    CONVERT = 306,
    CREATE = 307,
    CROSS = 308,
    CURRENT_DATE = 309,
    CURRENT_TIME = 310,
    CURRENT_TIMESTAMP = 311,
    CURRENT_USER = 312,
    CURSOR = 313,
    DATABASE = 314,
    DATABASES = 315,
    DATE = 316,
    DATETIME = 317,
    DAY_HOUR = 318,
    DAY_MICROSECOND = 319,
    DAY_MINUTE = 320,
    DAY_SECOND = 321,
    DECIMAL = 322,
    DECLARE = 323,
    DEFAULT = 324,
    DELAYED = 325,
    DELETE = 326,
    DESC = 327,
    DESCRIBE = 328,
    DETERMINISTIC = 329,
    DISTINCT = 330,
    DISTINCTROW = 331,
    DIV = 332,
    DOUBLE = 333,
    DROP = 334,
    DUAL = 335,
    EACH = 336,
    ELSE = 337,
    ELSEIF = 338,
    ENCLOSED = 339,
    END = 340,
    ENUM = 341,
    ESCAPED = 342,
    EXISTS = 343,
    EXIT = 344,
    EXPLAIN = 345,
    FETCH = 346,
    FLOAT = 347,
    FOR = 348,
    FORCE = 349,
    FOREIGN = 350,
    FROM = 351,
    FULLTEXT = 352,
    GRANT = 353,
    GROUP = 354,
    HAVING = 355,
    HIGH_PRIORITY = 356,
    HOUR_MICROSECOND = 357,
    HOUR_MINUTE = 358,
    HOUR_SECOND = 359,
    IF = 360,
    IGNORE = 361,
    INDEX = 362,
    INFILE = 363,
    INNER = 364,
    INOUT = 365,
    INSENSITIVE = 366,
    INSERT = 367,
    INT = 368,
    INTEGER = 369,
    INTERVAL = 370,
    INTO = 371,
    ITERATE = 372,
    JOIN = 373,
    KEY = 374,
    KEYS = 375,
    KILL = 376,
    LEADING = 377,
    LEAVE = 378,
    LEFT = 379,
    LIMIT = 380,
    LINES = 381,
    LOAD = 382,
    LOCALTIME = 383,
    LOCALTIMESTAMP = 384,
    LOCK = 385,
    LONG = 386,
    LONGBLOB = 387,
    LONGTEXT = 388,
    LOOP = 389,
    LOW_PRIORITY = 390,
    MATCH = 391,
    MEDIUMBLOB = 392,
    MEDIUMINT = 393,
    MEDIUMTEXT = 394,
    MINUTE_MICROSECOND = 395,
    MINUTE_SECOND = 396,
    MODIFIES = 397,
    NATURAL = 398,
    NO_WRITE_TO_BINLOG = 399,
    NULLX = 400,
    NUMBER = 401,
    ON = 402,
    ONDUPLICATE = 403,
    OPTIMIZE = 404,
    OPTION = 405,
    OPTIONALLY = 406,
    ORDER = 407,
    OUT = 408,
    OUTER = 409,
    OUTFILE = 410,
    PRECISION = 411,
    PRIMARY = 412,
    PROCEDURE = 413,
    PURGE = 414,
    QUICK = 415,
    READ = 416,
    READS = 417,
    REAL = 418,
    REFERENCES = 419,
    RELEASE = 420,
    RENAME = 421,
    REPEAT = 422,
    REPLACE = 423,
    REQUIRE = 424,
    RESTRICT = 425,
    RETURN = 426,
    REVOKE = 427,
    RIGHT = 428,
    ROLLUP = 429,
    SCHEMA = 430,
    SCHEMAS = 431,
    SECOND_MICROSECOND = 432,
    SELECT = 433,
    SENSITIVE = 434,
    SEPARATOR = 435,
    SET = 436,
    SHOW = 437,
    SMALLINT = 438,
    SOME = 439,
    SONAME = 440,
    SPATIAL = 441,
    SPECIFIC = 442,
    SQL = 443,
    SQLEXCEPTION = 444,
    SQLSTATE = 445,
    SQLWARNING = 446,
    SQL_BIG_RESULT = 447,
    SQL_CALC_FOUND_ROWS = 448,
    SQL_SMALL_RESULT = 449,
    SSL = 450,
    STARTING = 451,
    STRAIGHT_JOIN = 452,
    TABLE = 453,
    TEMPORARY = 454,
    TEXT = 455,
    TERMINATED = 456,
    THEN = 457,
    TIME = 458,
    TIMESTAMP = 459,
    TINYBLOB = 460,
    TINYINT = 461,
    TINYTEXT = 462,
    TO = 463,
    TRAILING = 464,
    TRIGGER = 465,
    UNDO = 466,
    UNION = 467,
    UNIQUE = 468,
    UNLOCK = 469,
    UNSIGNED = 470,
    UPDATE = 471,
    USAGE = 472,
    USE = 473,
    USING = 474,
    UTC_DATE = 475,
    UTC_TIME = 476,
    UTC_TIMESTAMP = 477,
    VALUES = 478,
    VARBINARY = 479,
    VARCHAR = 480,
    VARYING = 481,
    WHEN = 482,
    WHERE = 483,
    WHILE = 484,
    WITH = 485,
    WRITE = 486,
    YEAR = 487,
    YEAR_MONTH = 488,
    ZEROFILL = 489,
    FSUBSTRING = 490,
    FTRIM = 491,
    FDATE_ADD = 492,
    FDATE_SUB = 493,
    FCOUNT = 494
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "sql.y" /* yacc.c:355  */

	int intval;
	double floatval;
	char *strval;
	int subtok;

#line 401 "sql.tab.c" /* yacc.c:355  */
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



int yyparse (yyscan_t scanner, struct psql_state *pstate);

#endif /* !YY_YY_SQL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 77 "sql.y" /* yacc.c:358  */

#include "sql.lex.h"
#include "sql-parser.h"
#line 355 "sql.y" /* yacc.c:358  */

void yyerror(YYLTYPE *, yyscan_t scanner, struct psql_state *pstate, const char *s, ...);
void lyyerror(YYLTYPE t, const char *s, ...);
 

#line 440 "sql.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1499

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  254
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  313
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  642

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   494

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    18,     2,     2,     2,    28,    22,     2,
     252,   253,    26,    24,   250,    25,   251,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   249,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    21,     2,     2,     2,     2,     2,
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
      15,    16,    17,    19,    20,    23,    29,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   364,   364,   372,   380,   383,   385,   391,   392,   394,
     395,   399,   401,   405,   406,   407,   410,   411,   414,   414,
     416,   416,   419,   419,   420,   423,   424,   427,   428,   430,
     431,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     446,   447,   448,   451,   453,   454,   457,   458,   462,   463,
     465,   466,   469,   470,   473,   474,   475,   479,   481,   483,
     485,   487,   491,   492,   493,   496,   497,   500,   501,   504,
     505,   506,   509,   509,   512,   513,   517,   519,   521,   523,
     526,   527,   530,   531,   534,   539,   542,   547,   548,   549,
     550,   553,   558,   559,   563,   563,   565,   573,   576,   582,
     583,   586,   587,   588,   589,   590,   593,   593,   596,   597,
     600,   601,   604,   605,   606,   607,   610,   616,   622,   625,
     628,   631,   637,   640,   646,   652,   658,   661,   668,   669,
     670,   674,   677,   680,   683,   691,   695,   696,   699,   700,
     706,   710,   711,   714,   715,   720,   723,   727,   732,   737,
     741,   747,   752,   753,   756,   756,   759,   760,   761,   762,
     763,   766,   767,   768,   769,   770,   771,   772,   773,   774,
     775,   776,   777,   778,   781,   782,   783,   786,   787,   790,
     791,   792,   795,   796,   797,   801,   802,   803,   804,   805,
     806,   807,   808,   809,   810,   811,   812,   813,   814,   815,
     816,   817,   818,   819,   820,   821,   822,   823,   824,   825,
     826,   827,   828,   829,   830,   833,   834,   837,   840,   841,
     842,   845,   846,   851,   855,   858,   859,   861,   862,   868,
     871,   873,   873,   876,   878,   883,   884,   885,   886,   887,
     888,   889,   892,   893,   894,   895,   896,   897,   898,   899,
     900,   901,   902,   903,   904,   905,   906,   907,   908,   909,
     910,   911,   912,   913,   916,   917,   918,   919,   922,   926,
     927,   930,   931,   934,   935,   936,   937,   938,   941,   945,
     946,   948,   949,   950,   951,   952,   955,   956,   957,   960,
     961,   964,   965,   966,   967,   968,   969,   970,   971,   972,
     975,   976,   977,   978,   981,   982,   985,   986,   989,   990,
     993,   994,   995,   998
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "BOOL",
  "APPROXNUM", "USERVAR", "ASSIGN", "OR", "XOR", "ANDOP", "IN", "IS",
  "LIKE", "REGEXP", "NOT", "'!'", "BETWEEN", "COMPARISON", "'|'", "'&'",
  "SHIFT", "'+'", "'-'", "'*'", "'/'", "'%'", "MOD", "'^'", "UMINUS",
  "ADD", "ALL", "ALTER", "ANALYZE", "AND", "ANY", "AS", "ASC",
  "AUTO_INCREMENT", "BEFORE", "BIGINT", "BINARY", "BIT", "BLOB", "BOTH",
  "BY", "CALL", "CASCADE", "CASE", "CHANGE", "CHAR", "CHECK", "COLLATE",
  "COLUMN", "COMMENT", "CONDITION", "CONSTRAINT", "CONTINUE", "CONVERT",
  "CREATE", "CROSS", "CURRENT_DATE", "CURRENT_TIME", "CURRENT_TIMESTAMP",
  "CURRENT_USER", "CURSOR", "DATABASE", "DATABASES", "DATE", "DATETIME",
  "DAY_HOUR", "DAY_MICROSECOND", "DAY_MINUTE", "DAY_SECOND", "DECIMAL",
  "DECLARE", "DEFAULT", "DELAYED", "DELETE", "DESC", "DESCRIBE",
  "DETERMINISTIC", "DISTINCT", "DISTINCTROW", "DIV", "DOUBLE", "DROP",
  "DUAL", "EACH", "ELSE", "ELSEIF", "ENCLOSED", "END", "ENUM", "ESCAPED",
  "EXISTS", "EXIT", "EXPLAIN", "FETCH", "FLOAT", "FOR", "FORCE", "FOREIGN",
  "FROM", "FULLTEXT", "GRANT", "GROUP", "HAVING", "HIGH_PRIORITY",
  "HOUR_MICROSECOND", "HOUR_MINUTE", "HOUR_SECOND", "IF", "IGNORE",
  "INDEX", "INFILE", "INNER", "INOUT", "INSENSITIVE", "INSERT", "INT",
  "INTEGER", "INTERVAL", "INTO", "ITERATE", "JOIN", "KEY", "KEYS", "KILL",
  "LEADING", "LEAVE", "LEFT", "LIMIT", "LINES", "LOAD", "LOCALTIME",
  "LOCALTIMESTAMP", "LOCK", "LONG", "LONGBLOB", "LONGTEXT", "LOOP",
  "LOW_PRIORITY", "MATCH", "MEDIUMBLOB", "MEDIUMINT", "MEDIUMTEXT",
  "MINUTE_MICROSECOND", "MINUTE_SECOND", "MODIFIES", "NATURAL",
  "NO_WRITE_TO_BINLOG", "NULLX", "NUMBER", "ON", "ONDUPLICATE", "OPTIMIZE",
  "OPTION", "OPTIONALLY", "ORDER", "OUT", "OUTER", "OUTFILE", "PRECISION",
  "PRIMARY", "PROCEDURE", "PURGE", "QUICK", "READ", "READS", "REAL",
  "REFERENCES", "RELEASE", "RENAME", "REPEAT", "REPLACE", "REQUIRE",
  "RESTRICT", "RETURN", "REVOKE", "RIGHT", "ROLLUP", "SCHEMA", "SCHEMAS",
  "SECOND_MICROSECOND", "SELECT", "SENSITIVE", "SEPARATOR", "SET", "SHOW",
  "SMALLINT", "SOME", "SONAME", "SPATIAL", "SPECIFIC", "SQL",
  "SQLEXCEPTION", "SQLSTATE", "SQLWARNING", "SQL_BIG_RESULT",
  "SQL_CALC_FOUND_ROWS", "SQL_SMALL_RESULT", "SSL", "STARTING",
  "STRAIGHT_JOIN", "TABLE", "TEMPORARY", "TEXT", "TERMINATED", "THEN",
  "TIME", "TIMESTAMP", "TINYBLOB", "TINYINT", "TINYTEXT", "TO", "TRAILING",
  "TRIGGER", "UNDO", "UNION", "UNIQUE", "UNLOCK", "UNSIGNED", "UPDATE",
  "USAGE", "USE", "USING", "UTC_DATE", "UTC_TIME", "UTC_TIMESTAMP",
  "VALUES", "VARBINARY", "VARCHAR", "VARYING", "WHEN", "WHERE", "WHILE",
  "WITH", "WRITE", "YEAR", "YEAR_MONTH", "ZEROFILL", "FSUBSTRING", "FTRIM",
  "FDATE_ADD", "FDATE_SUB", "FCOUNT", "';'", "','", "'.'", "'('", "')'",
  "$accept", "stmt_list", "stmt", "select_stmt", "opt_where",
  "opt_groupby", "groupby_list", "opt_asc_desc", "opt_with_rollup",
  "opt_having", "opt_orderby", "opt_limit", "opt_into_list", "column_list",
  "select_opts", "select_expr_list", "select_expr", "table_references",
  "table_reference", "table_factor", "opt_as", "opt_as_alias",
  "join_table", "opt_inner_cross", "opt_outer", "left_or_right",
  "opt_left_or_right_outer", "opt_join_condition", "join_condition",
  "index_hint", "opt_for_join", "index_list", "table_subquery",
  "delete_stmt", "delete_opts", "delete_list", "opt_dot_star",
  "insert_stmt", "opt_ondupupdate", "insert_opts", "opt_into",
  "opt_col_names", "insert_vals_list", "insert_vals", "insert_asgn_list",
  "replace_stmt", "update_stmt", "update_opts", "update_asgn_list",
  "create_database_stmt", "opt_if_not_exists", "drop_database_stmt",
  "opt_if_exists", "create_table_stmt", "create_col_list",
  "create_definition", "$@1", "column_atts", "opt_length", "opt_binary",
  "opt_uz", "opt_csc", "data_type", "enum_list", "create_select_statement",
  "opt_ignore_replace", "opt_temporary", "drop_table_stmt", "table_list",
  "set_stmt", "set_list", "set_expr", "expr", "val_list", "opt_val_list",
  "trim_ltb", "interval_exp", "case_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    33,   273,
     274,   124,    38,   275,    43,    45,    42,    47,    37,   276,
      94,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,    59,
      44,    46,    40,    41
};
# endif

#define YYPACT_NINF -371

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-371)))

#define YYTABLE_NINF -148

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-148)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      67,  -221,   -12,  -371,    22,  -371,  -371,  -371,    93,     0,
     189,  -182,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,    36,    36,  -371,    13,    24,   154,   154,
      66,   252,   252,   127,   265,    30,  -371,   280,     7,  -371,
    -371,   190,   292,   316,    36,    76,   339,  -371,  -371,  -371,
     -76,   269,   365,   367,   154,  -371,  -371,  -371,  -371,  -371,
     378,   380,    42,  -371,  -371,  -371,  -371,   392,   681,   681,
     681,  -371,  -371,   681,   300,  -371,  -371,  -371,  -371,  -371,
     135,  -371,  -371,  -371,  -371,  -371,   198,   202,   225,   232,
     250,   -72,  -371,  1384,   681,   681,    93,    10,    11,    14,
      -1,   -32,   163,  -371,  -371,   372,  -371,  -371,  -371,   422,
     416,  -371,   170,   -15,     7,   502,  -371,  -371,  -371,   310,
    -147,   -42,   509,   681,   681,   619,   619,  -371,  -371,   681,
     972,   -41,   326,   681,   158,   681,   681,   410,     7,   681,
    -371,   681,   681,   681,   267,    25,   681,   681,   284,   681,
       1,   681,   681,   681,   681,   681,   681,   681,   681,   681,
     681,   514,  -371,  1449,  1449,  -371,   517,   -58,   268,  -112,
     519,     7,  -371,  -371,  -371,   -70,  -371,     7,   397,   374,
    -371,   540,   -20,  -371,   681,   388,     7,  -191,    76,  -371,
    -371,   301,   547,   343,  -133,   547,    39,  -371,   851,  -371,
     299,  1449,  1013,   -36,   681,  -371,   681,   304,   830,   305,
    -371,  -371,  -371,   313,   681,   872,   893,   314,    59,  -191,
    -371,  1469,  1145,   808,   426,  -371,    26,  -371,  1089,  1089,
     318,   681,   681,  1422,   319,   330,   331,   326,   638,   653,
     503,   599,   411,   411,   538,   538,   538,   538,  -371,  -371,
     104,   456,   457,   458,  -371,  -371,  -371,    -9,   -22,   163,
     374,   374,   460,   436,     7,  -371,   466,  -371,  -371,  -371,
     591,   113,  -371,   372,  1449,   548,   462,  -191,  -371,  -371,
     405,   578,  -110,  -371,  -371,    17,   349,   443,  -110,   349,
     443,   681,  -371,   681,   681,  -371,  1308,  1062,  -371,   681,
    -371,  -371,  1287,   478,   478,  -371,  -371,   495,   351,   352,
    -371,  -371,   426,  1089,  1089,   681,   326,   326,   326,   354,
     -58,   506,   506,   506,   681,   606,   607,   388,  -371,  -371,
       7,   681,  -117,     7,   -18,   111,   359,   360,   488,    71,
    -371,   614,   326,   681,   681,  -371,  -371,  -371,  -371,   475,
     490,   628,  -371,   468,  -371,   491,   -63,  -371,  -371,   -63,
    -371,  -371,  1449,  1329,  -371,   681,   737,   681,   681,   379,
     398,   586,   581,  -371,  -371,   438,   439,   785,   440,   454,
     455,  -371,  -371,   569,   463,   464,   465,  1449,   690,    -8,
     462,  -371,  1449,   681,   473,  -371,  -371,  -117,   113,  -371,
     474,   477,   343,   343,   480,   113,  -100,  1055,  -371,   483,
    1350,   926,  -371,  1449,   487,   694,  -371,  -371,  -371,    73,
    1449,   482,  -371,  -371,  -371,  1449,   681,  -371,   489,   947,
    -371,  -371,   681,   681,   388,  -371,  -371,  -371,  -371,  -371,
    -371,   724,   724,   724,   681,   681,   727,  -371,  1449,   343,
    -371,    84,   343,   343,    98,   103,   343,  -371,  -371,   516,
     516,   516,  -371,   516,  -371,  -371,   516,   516,   539,   516,
     516,   516,  -371,   698,  -371,   516,   698,   516,   541,   516,
     698,  -371,  -371,  -371,   516,   698,   542,   543,  -371,  -371,
     681,  -371,  -371,  -371,   681,   547,   556,   572,  -371,   491,
     760,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,
    -371,    70,  1449,   462,  -371,   108,   129,   141,  1449,  1449,
     723,   169,    92,   173,   199,  -371,  -371,   209,   750,  -371,
    -371,  -371,  -371,  -371,  -371,   765,  -371,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,   765,  -371,  -371,  -371,  -371,   787,
     792,   574,  1350,  1449,   549,  -371,  1449,  -371,  1449,   215,
    -371,   615,  -371,   701,   845,  -371,  -371,  -371,   681,  -371,
    -371,  -371,  -371,  -371,   217,   -10,   186,   -10,   -10,  -371,
     235,   -10,   -10,   -10,   186,   -10,   186,   -10,   251,   -10,
     186,   -10,   186,   616,   637,   757,  -371,   920,   441,  -371,
    -371,   802,  -106,  -371,  -371,  -371,   343,  -371,  -371,  1449,
     927,  -371,  -371,  -371,   741,   929,   930,  -371,  -371,  -371,
    -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,  -371,   343,
     715,   691,   974,  -371,  -371,   186,   186,   186,   253,  -371,
    -371,  -371
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,   221,    90,   221,   101,   101,    31,     0,   101,
       0,     0,     4,    85,    97,   122,   126,   135,   140,   145,
     223,   229,     3,   138,   138,   222,     0,     0,   143,   143,
       0,   107,   107,     0,     0,   230,   231,     0,     0,     1,
       2,     0,     0,     0,   138,    94,     0,    89,    87,    88,
       0,     0,     0,     0,   143,   103,   104,   105,   106,   102,
       0,     0,   235,   238,   239,   241,   240,   236,     0,     0,
       0,    42,    32,     0,     0,   311,   312,   310,    33,    34,
       0,    35,    38,    39,    37,    36,     0,     0,     0,     0,
       0,     5,    40,    56,     0,     0,     0,   105,   102,    56,
       0,     0,    44,    46,    47,    53,   139,   136,   137,     0,
       0,    92,     7,     0,     0,     0,   144,   141,   142,     0,
     108,   108,     0,   271,     0,   261,   262,   248,   313,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,   234,   233,   232,     0,    79,     0,     0,
       0,     0,    64,    63,    67,    71,    68,     0,     0,    65,
      52,     0,   218,    95,     0,    20,     0,     7,    94,   225,
     226,   224,     0,     0,     0,     0,     0,   237,   269,   272,
       0,   263,     0,     0,     0,   302,     0,     0,   269,     0,
     288,   286,   287,     0,     0,     0,     0,     0,     0,     7,
      41,   250,   251,   249,     0,   266,     0,   264,   306,   308,
       0,     0,     0,     0,     0,     0,     0,     0,   252,   257,
     258,   260,   242,   243,   244,   245,   246,   247,   259,    54,
      56,     0,     0,     0,    48,    84,    51,     0,     7,    45,
      65,    65,     0,    58,     0,    66,     0,    50,   219,   220,
       0,   154,   149,    53,     8,     0,    22,     7,    91,    93,
       0,     0,    99,    27,    28,     0,     0,    99,    99,     0,
      99,     0,   278,     0,     0,   300,     0,     0,   277,     0,
     281,   284,     0,     0,     0,   279,   280,     9,     0,     0,
     267,   265,     0,   307,   309,     0,     0,     0,     0,     0,
      79,    81,    81,    81,     0,     0,     0,    20,    69,    70,
       0,     0,    73,     0,   218,     0,     0,     0,     0,     0,
     152,     0,     0,     0,     0,    86,    96,   227,   228,     0,
       0,     0,   116,     0,   109,     0,    99,   117,   124,    99,
     125,   270,   304,     0,   303,     0,     0,     0,     0,     0,
       0,     0,    18,   275,   273,     0,     0,   268,     0,     0,
       0,   253,    49,     0,     0,     0,     0,   131,     0,     0,
      22,    61,    59,     0,     0,    57,    72,     0,   154,   151,
       0,     0,     0,     0,     0,   154,   218,     0,   217,    21,
      13,    23,   119,   118,     0,     0,    29,    30,   113,     0,
     112,     0,    98,   123,   301,   305,     0,   282,     0,     0,
     289,   290,     0,     0,    20,   276,   274,   256,   254,   255,
      80,     0,     0,     0,     0,     0,     0,   127,    74,     0,
      60,     0,     0,     0,     0,     0,     0,   153,   148,   174,
     174,   174,   206,   174,   196,   199,   174,   174,     0,   174,
     174,   174,   208,   177,   207,   174,   177,   174,     0,   174,
     177,   197,   198,   205,   174,   177,     0,     0,   200,   161,
       0,    14,    15,    11,     0,     0,     0,     0,   110,     0,
       0,   285,   291,   292,   293,   294,   297,   298,   299,   296,
     295,    16,    19,    22,    82,     0,     0,     0,   132,   133,
       0,     0,   218,     0,     0,   158,   157,     0,     0,   179,
     203,   185,   182,   179,   179,     0,   179,   179,   179,   178,
     182,   179,   182,   179,     0,   179,   182,   179,   182,     0,
       0,   155,    13,    24,   100,   121,   120,   115,   114,     0,
     283,     0,    10,    25,     0,    78,    77,    76,     0,    75,
     150,   159,   160,   156,     0,   191,   201,   195,   193,   215,
       0,   194,   189,   190,   212,   188,   211,   192,     0,   187,
     210,   186,   209,     0,     0,     0,   168,     0,     0,   172,
     163,     0,     0,    12,   111,    17,     0,     6,    83,   134,
       0,   175,   180,   181,     0,     0,     0,   182,   182,   204,
     182,   162,   173,   164,   165,   167,   166,   171,   170,     0,
      26,     0,     0,   184,   216,   213,   214,   202,     0,   176,
     183,   169
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -371,  -371,  -371,   -40,    -2,  -371,   571,   427,  -371,  -371,
    -297,  -370,  -371,   -64,  -371,  -371,   841,   150,   810,  -128,
     733,   -83,  -371,  -371,   226,  -371,  -371,  -371,   613,   695,
     188,    72,  -371,  -371,  -371,   965,   829,  -371,    -4,   348,
     999,   923,   756,   550,  -194,  -371,  -371,  -371,  -371,  -371,
     192,  -371,    -6,  -371,   648,   642,  -371,  -371,   234,  -136,
     471,  -162,  -371,   504,  -313,  -371,  1046,  -371,  -371,  -371,
    -371,   955,   -33,  -109,  -371,  -371,   748,   924
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,   185,   372,   409,   493,   562,   434,
     276,   345,   607,   285,    33,    91,    92,   101,   102,   103,
     181,   162,   104,   178,   266,   179,   262,   395,   396,   254,
     384,   515,   105,    13,    27,    50,   111,    14,   352,    31,
      60,   194,   356,   419,   282,    15,    16,    38,   258,    17,
      42,    18,    52,    19,   339,   340,   341,   551,   529,   540,
     575,   576,   489,   580,   272,   273,    26,    20,   191,    21,
      35,    36,   198,   199,   200,   214,   369,   131
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      93,   288,    99,  -128,    62,    63,    64,    65,    66,    67,
      99,   324,   445,  -130,  -129,   268,   167,   140,    68,    69,
     447,   399,   628,    53,   209,   213,    70,    45,    22,   114,
     390,   225,   310,   138,   234,   125,   126,   127,   235,   393,
     128,   130,   226,   192,    73,   251,   184,   350,   119,   263,
     204,    74,   161,   205,     7,   294,    23,   252,   295,   171,
     168,   163,   164,   260,    75,    76,    77,    40,     1,   141,
     142,   143,   144,   145,   146,   147,   148,   269,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
      28,   201,   207,   458,   350,   268,   202,   268,    80,   286,
     208,    34,   215,   216,   218,   193,    93,   140,   221,   222,
     223,   394,   261,   228,   229,   309,   233,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,     2,    46,
      62,    63,    64,    65,    66,    67,   332,   513,   171,    47,
     351,   256,   161,   563,    68,    69,   629,     3,   195,  -146,
      41,   274,    70,    71,   287,     4,   290,   269,   170,   269,
      72,    62,    63,    64,    65,    66,    67,   320,    48,   253,
      73,   296,    24,   297,   115,    68,    69,    74,   139,   227,
     311,   302,   361,    70,   308,   278,     7,   421,     5,    39,
      75,    76,    77,    49,   236,   206,    25,   319,   313,   314,
     206,    73,   391,   376,   210,   397,    29,   268,    74,   570,
     193,    78,    79,   186,   612,   184,    43,   307,   171,   335,
      44,    75,    76,    77,    80,   172,     7,   400,   326,   336,
      25,   270,   271,   613,   398,   115,   109,    81,   614,   401,
     615,   337,   325,   446,     6,    86,    87,    88,    89,    90,
     169,   100,  -128,   237,     7,    80,   327,     8,   428,   100,
     362,   363,  -130,  -129,   187,   166,   366,   353,    51,   269,
     354,   289,   375,    54,    94,   346,   378,   379,   380,   338,
      96,   173,   377,   357,   358,    95,   360,   106,   219,   211,
     -62,   387,     9,   122,   123,   107,   174,   230,   392,   231,
     232,   554,   408,    62,    63,    64,    65,    66,    67,   561,
     410,   411,   306,   189,   190,   175,   413,    68,    69,   108,
     490,   405,   420,   497,   406,    70,   498,   110,    82,    83,
      84,    55,   425,    85,   405,   429,   277,   522,   454,   455,
     542,  -147,   112,    73,   546,   176,   283,   284,   353,   548,
      74,   525,   422,   353,    32,   423,   526,    37,   564,    55,
     448,   565,    56,    75,    76,    77,   116,    57,   117,   177,
     118,    86,    87,    88,    89,    90,   212,    58,   584,   564,
     586,   120,   566,   121,   590,   521,   592,   132,   523,   524,
      56,   564,   527,   500,   567,    97,    59,    80,   -94,   410,
     512,   124,    86,    87,    88,    89,    90,   184,   347,   348,
     180,   518,   519,    62,    63,    64,    65,    66,    67,   353,
     -94,   110,   569,   353,    98,   182,   571,    68,    69,    62,
      63,    64,    65,    66,    67,    70,   217,   156,   157,   158,
     159,   160,   183,    68,    69,   623,   624,   625,   626,   353,
     133,    70,   572,    73,   134,   635,   636,   552,   637,   353,
      74,   553,   573,   556,   558,   497,   420,   610,   604,    73,
     611,   416,   417,    75,    76,    77,    74,   135,    62,    63,
      64,    65,    66,    67,   136,   616,   328,   329,   617,    75,
      76,    77,    68,    69,    62,    63,    64,    65,    66,    67,
      70,   616,   137,   353,   618,   188,   641,    80,    68,    69,
     385,   386,   197,     7,   516,   517,    70,   249,    73,   224,
     250,   255,   257,    80,   264,    74,   153,   154,   155,   156,
     157,   158,   159,   160,    73,   609,   129,   265,    75,    76,
      77,    74,   630,   267,    86,    87,    88,    89,    90,   275,
     281,   280,   292,   412,    75,    76,    77,   298,   300,    62,
      63,    64,    65,    66,    67,   638,   301,   305,   160,   418,
     312,   316,    80,    68,    69,    62,    63,    64,    65,    66,
      67,    70,   317,   318,   321,   322,   323,   330,    80,    68,
      69,   595,   331,   333,   334,   343,   344,    70,   349,    73,
     350,   355,   368,   371,   373,   374,    74,   381,   383,   388,
     389,   402,   403,     7,   596,    73,   404,   407,   414,    75,
      76,    77,    74,   154,   155,   156,   157,   158,   159,   160,
     597,   415,   430,   432,   555,    75,    76,    77,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     557,   431,   598,    80,    86,    87,    88,    89,    90,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,    80,
      86,    87,    88,    89,    90,   152,   153,   154,   155,   156,
     157,   158,   159,   160,    62,    63,    64,    65,    66,    67,
     433,   435,   436,   437,   530,   531,   440,   532,    68,    69,
     533,   534,   599,   536,   537,   538,    70,   438,   439,   541,
     444,   543,   495,   545,   496,   441,   442,   443,   547,    86,
      87,    88,    89,    90,    73,   449,   452,   514,   600,   453,
     520,    74,   456,   490,   499,    86,    87,    88,    89,    90,
     601,   539,   501,   568,    75,    76,    77,   141,   142,   143,
     144,   145,   146,   147,   148,   574,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   528,   579,
     141,   142,   143,   144,   145,   146,   147,   148,    80,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   535,   593,   544,   549,   550,   602,   594,   605,   351,
      86,    87,    88,    89,    90,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,    86,    87,    88,    89,
      90,   144,   145,   146,   147,   148,   606,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   426,
     141,   142,   143,   144,   145,   146,   147,   148,   608,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   141,   142,   143,   144,   145,   146,   147,   148,   619,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   141,   142,   143,   144,   145,   146,   147,   148,
     620,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   141,   142,   143,   144,   145,   146,   147,
     148,   621,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   622,    86,    87,    88,    89,    90,
     627,   632,   631,   633,   634,   299,   141,   142,   143,   144,
     145,   146,   147,   148,   639,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   141,   142,   143,
     144,   145,   146,   147,   148,   353,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   640,   603,
     220,   259,   141,   142,   143,   144,   145,   146,   147,   148,
     427,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   511,   577,   578,   342,   581,   582,   583,
     450,   113,   585,   560,   587,   382,   589,   279,   591,   502,
     503,   504,   505,   141,   142,   143,   144,   145,   146,   147,
     148,    61,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   196,   359,   451,   457,   588,   559,
      30,   165,   370,     0,   203,     0,     0,     0,   506,   507,
     508,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   141,   142,   143,   144,   145,   146,   147,   148,
     291,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,     0,     0,     0,     0,   459,   460,   461,
     462,   291,  -148,  -148,  -148,  -148,   148,   463,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
       0,     0,   303,     0,     0,   464,   465,     0,     0,     0,
       0,   466,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   467,   304,     0,     0,     0,     0,     0,     0,
     468,     0,     0,     0,     0,     0,   469,   143,   144,   145,
     146,   147,   148,     0,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   494,   470,   471,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   509,   510,
       0,     0,     0,     0,     0,     0,   472,   473,     0,     0,
       0,   474,   475,   476,     0,     0,     0,     0,   129,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   293,     0,     0,   477,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   478,     0,   479,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   480,     0,     0,   481,   482,   483,
     484,   485,     0,   365,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   486,   487,
       0,     0,     0,     0,     0,     0,   488,   141,   142,   143,
     144,   145,   146,   147,   148,     0,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   141,   142,
     143,   144,   145,   146,   147,   148,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   141,
     142,   143,   144,   145,   146,   147,   148,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     141,   142,   143,   144,   145,   146,   147,   148,     0,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,     0,     0,     0,     0,     0,     0,   140,     0,   491,
       0,     0,   367,     0,   141,   142,   143,   144,   145,   146,
     147,   148,   364,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,     0,     0,     0,     0,     0,
       0,     0,   161,   424,     0,     0,     0,     0,     0,     0,
       0,   492,   141,   142,   143,   144,   145,   146,   147,   148,
       0,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,     0,     0,     0,     0,     0,   315,   141,
     142,   143,   144,   145,   146,   147,   148,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     142,   143,   144,   145,   146,   147,   148,     0,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160
};

static const yytype_int16 yycheck[] =
{
      33,   195,     3,     3,     3,     4,     5,     6,     7,     8,
       3,    20,    20,     3,     3,   115,    99,     3,    17,    18,
     390,   334,   128,    29,   133,   134,    25,     3,   249,   105,
     327,     6,     6,   105,    33,    68,    69,    70,    37,   156,
      73,    74,    17,   190,    43,   103,   237,   157,    54,   177,
      91,    50,    38,    94,   187,    91,    68,   115,    94,   250,
     100,    94,    95,   133,    63,    64,    65,   249,     1,    10,
      11,    12,    13,    14,    15,    16,    17,   177,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      68,   124,   132,   406,   157,   115,   129,   115,    97,   232,
     133,     8,   135,   136,   137,   252,   139,     3,   141,   142,
     143,   228,   182,   146,   147,   224,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,    61,   105,
       3,     4,     5,     6,     7,     8,   264,   434,   250,   115,
     250,   253,    38,   513,    17,    18,   252,    80,   190,   249,
     114,   184,    25,    26,   194,    88,   196,   177,   190,   177,
      33,     3,     4,     5,     6,     7,     8,   250,   144,   227,
      43,   204,   184,   206,   250,    17,    18,    50,   250,   154,
     154,   214,   291,    25,   224,   187,   187,   250,   121,     0,
      63,    64,    65,   169,   193,   236,   208,   237,   231,   232,
     236,    43,   330,   312,    46,   333,   184,   115,    50,   522,
     252,    84,    85,   228,   224,   237,    24,   219,   250,   106,
     207,    63,    64,    65,    97,    62,   187,   116,   250,   116,
     208,   251,   252,   243,   252,   250,    44,   110,    52,   128,
      54,   128,   251,   251,   177,   244,   245,   246,   247,   248,
     100,   252,   252,   252,   187,    97,   258,   190,   367,   252,
     293,   294,   252,   252,   114,   251,   299,   250,   114,   177,
     253,   232,   312,   207,     9,   277,   316,   317,   318,   166,
     250,   118,   315,   287,   288,    20,   290,    97,   138,   131,
     127,   324,   225,   251,   252,     3,   133,    13,   331,    15,
      16,   495,   342,     3,     4,     5,     6,     7,     8,   239,
     343,   344,   253,     3,     4,   152,   349,    17,    18,     3,
     250,   250,   355,   250,   253,    25,   253,   251,   201,   202,
     203,    79,   365,   206,   250,   368,   186,   253,   402,   403,
     476,   249,     3,    43,   480,   182,     3,     4,   250,   485,
      50,   253,   356,   250,     6,   359,   253,     9,   250,    79,
     393,   253,   110,    63,    64,    65,    97,   115,     3,   206,
       3,   244,   245,   246,   247,   248,   218,   125,   540,   250,
     542,     3,   253,     3,   546,   449,   548,   252,   452,   453,
     110,   250,   456,   426,   253,   115,   144,    97,   228,   432,
     433,     9,   244,   245,   246,   247,   248,   237,     3,     4,
      38,   444,   445,     3,     4,     5,     6,     7,     8,   250,
     250,   251,   253,   250,   144,     3,   253,    17,    18,     3,
       4,     5,     6,     7,     8,    25,    26,    26,    27,    28,
      29,    30,    26,    17,    18,     4,     5,     6,     7,   250,
     252,    25,   253,    43,   252,   617,   618,   490,   620,   250,
      50,   494,   253,   496,   497,   250,   499,   250,   253,    43,
     253,     3,     4,    63,    64,    65,    50,   252,     3,     4,
       5,     6,     7,     8,   252,   250,   260,   261,   253,    63,
      64,    65,    17,    18,     3,     4,     5,     6,     7,     8,
      25,   250,   252,   250,   253,     3,   253,    97,    17,    18,
     322,   323,     3,   187,   442,   443,    25,     3,    43,   252,
       3,   253,     3,    97,   127,    50,    23,    24,    25,    26,
      27,    28,    29,    30,    43,   568,   236,   163,    63,    64,
      65,    50,   606,     3,   244,   245,   246,   247,   248,   161,
       3,   250,   253,    78,    63,    64,    65,   253,   253,     3,
       4,     5,     6,     7,     8,   629,   253,   253,    30,    78,
     252,   252,    97,    17,    18,     3,     4,     5,     6,     7,
       8,    25,   252,   252,   128,   128,   128,   127,    97,    17,
      18,    17,   156,   127,     3,    47,   134,    25,    20,    43,
     157,   252,   124,   108,   253,   253,    50,   253,   102,     3,
       3,   252,   252,   187,    40,    43,   128,     3,   128,    63,
      64,    65,    50,    24,    25,    26,    27,    28,    29,    30,
      56,     3,   253,    47,    78,    63,    64,    65,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      78,   253,    78,    97,   244,   245,   246,   247,   248,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    97,
     244,   245,   246,   247,   248,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     3,     4,     5,     6,     7,     8,
     109,   253,   253,   253,   460,   461,   127,   463,    17,    18,
     466,   467,   128,   469,   470,   471,    25,   253,   253,   475,
      20,   477,   225,   479,    20,   252,   252,   252,   484,   244,
     245,   246,   247,   248,    43,   252,   252,     3,   154,   252,
       3,    50,   252,   250,   252,   244,   245,   246,   247,   248,
     166,    43,   253,    20,    63,    64,    65,    10,    11,    12,
      13,    14,    15,    16,    17,     5,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,   252,     4,
      10,    11,    12,    13,    14,    15,    16,    17,    97,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,   252,     5,   252,   252,   252,   222,     5,   183,   250,
     244,   245,   246,   247,   248,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,   244,   245,   246,   247,
     248,    13,    14,    15,    16,    17,   125,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,   102,
      10,    11,    12,    13,    14,    15,    16,    17,     3,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    10,    11,    12,    13,    14,    15,    16,    17,   253,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    10,    11,    12,    13,    14,    15,    16,    17,
     253,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    10,    11,    12,    13,    14,    15,    16,
      17,   154,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,     4,   244,   245,   246,   247,   248,
     128,   190,     5,     4,     4,   105,    10,    11,    12,    13,
      14,    15,    16,    17,   253,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    10,    11,    12,
      13,    14,    15,    16,    17,   250,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     4,   552,
     139,   171,    10,    11,    12,    13,    14,    15,    16,    17,
     253,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   432,   533,   534,   273,   536,   537,   538,
     397,    46,   541,   253,   543,   320,   545,   188,   547,    72,
      73,    74,    75,    10,    11,    12,    13,    14,    15,    16,
      17,    32,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   121,   289,   398,   405,   544,   499,
       4,    96,   304,    -1,   130,    -1,    -1,    -1,   111,   112,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
     250,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    42,    43,    44,
      45,   250,    13,    14,    15,    16,    17,    52,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,   250,    -1,    -1,    70,    71,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    87,   250,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,    -1,    -1,    -1,    -1,   101,    12,    13,    14,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,   250,   122,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   241,   242,
      -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,
      -1,   146,   147,   148,    -1,    -1,    -1,    -1,   236,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   211,    -1,    -1,   172,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   190,    -1,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   209,    -1,    -1,   212,   213,   214,
     215,   216,    -1,   211,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   233,   234,
      -1,    -1,    -1,    -1,    -1,    -1,   241,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    39,
      -1,    -1,   105,    -1,    10,    11,    12,    13,    14,    15,
      16,    17,    94,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    61,    80,    88,   121,   177,   187,   190,   225,
     255,   256,   257,   287,   291,   299,   300,   303,   305,   307,
     321,   323,   249,    68,   184,   208,   320,   288,    68,   184,
     320,   293,   293,   268,     8,   324,   325,   293,   301,     0,
     249,   114,   304,   304,   207,     3,   105,   115,   144,   169,
     289,   114,   306,   306,   207,    79,   110,   115,   125,   144,
     294,   294,     3,     4,     5,     6,     7,     8,    17,    18,
      25,    26,    33,    43,    50,    63,    64,    65,    84,    85,
      97,   110,   201,   202,   203,   206,   244,   245,   246,   247,
     248,   269,   270,   326,     9,    20,   250,   115,   144,     3,
     252,   271,   272,   273,   276,   286,    97,     3,     3,   304,
     251,   290,     3,   289,   105,   250,    97,     3,     3,   306,
       3,     3,   251,   252,     9,   326,   326,   326,   326,   236,
     326,   331,   252,   252,   252,   252,   252,   252,   105,   250,
       3,    10,    11,    12,    13,    14,    15,    16,    17,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    38,   275,   326,   326,   325,   251,   275,   257,   271,
     190,   250,    62,   118,   133,   152,   182,   206,   277,   279,
      38,   274,     3,    26,   237,   258,   228,   271,     3,     3,
       4,   322,   190,   252,   295,   190,   295,     3,   326,   327,
     328,   326,   326,   331,    91,    94,   236,   257,   326,   327,
      46,   131,   218,   327,   329,   326,   326,    26,   326,   271,
     270,   326,   326,   326,   252,     6,    17,   154,   326,   326,
      13,    15,    16,   326,    33,    37,   193,   252,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,     3,
       3,   103,   115,   227,   283,   253,   253,     3,   302,   272,
     133,   182,   280,   273,   127,   163,   278,     3,   115,   177,
     251,   252,   318,   319,   326,   161,   264,   271,   258,   290,
     250,     3,   298,     3,     4,   267,   232,   257,   298,   232,
     257,   250,   253,   211,    91,    94,   326,   326,   253,   105,
     253,   253,   326,   250,   250,   253,   253,   258,   257,   327,
       6,   154,   252,   326,   326,    36,   252,   252,   252,   257,
     275,   128,   128,   128,    20,   251,   250,   258,   278,   278,
     127,   156,   273,   127,     3,   106,   116,   128,   166,   308,
     309,   310,   274,    47,   134,   265,   258,     3,     4,    20,
     157,   250,   292,   250,   253,   252,   296,   292,   292,   296,
     292,   327,   326,   326,    94,   211,   326,   105,   124,   330,
     330,   108,   259,   253,   253,   257,   327,   326,   257,   257,
     257,   253,   283,   102,   284,   284,   284,   326,     3,     3,
     264,   273,   326,   156,   228,   281,   282,   273,   252,   318,
     116,   128,   252,   252,   128,   250,   253,     3,   257,   260,
     326,   326,    78,   326,   128,     3,     3,     4,    78,   297,
     326,   250,   292,   292,    94,   326,   102,   253,   327,   326,
     253,   253,    47,   109,   263,   253,   253,   253,   253,   253,
     127,   252,   252,   252,    20,    20,   251,   265,   326,   252,
     282,   308,   252,   252,   267,   267,   252,   309,   318,    42,
      43,    44,    45,    52,    70,    71,    76,    87,    95,   101,
     122,   123,   141,   142,   146,   147,   148,   172,   190,   192,
     209,   212,   213,   214,   215,   216,   233,   234,   241,   316,
     250,    39,    81,   261,   250,   225,    20,   250,   253,   252,
     326,   253,    72,    73,    74,    75,   111,   112,   113,   241,
     242,   260,   326,   264,     3,   285,   285,   285,   326,   326,
       3,   267,   253,   267,   267,   253,   253,   267,   252,   312,
     312,   312,   312,   312,   312,   252,   312,   312,   312,    43,
     313,   312,   313,   312,   252,   312,   313,   312,   313,   252,
     252,   311,   326,   326,   298,    78,   326,    78,   326,   297,
     253,   239,   262,   265,   250,   253,   253,   253,    20,   253,
     318,   253,   253,   253,     5,   314,   315,   314,   314,     4,
     317,   314,   314,   314,   315,   314,   315,   314,   317,   314,
     315,   314,   315,     5,     5,    17,    40,    56,    78,   128,
     154,   166,   222,   261,   253,   183,   125,   266,     3,   326,
     250,   253,   224,   243,    52,    54,   250,   253,   253,   253,
     253,   154,     4,     4,     5,     6,     7,   128,   128,   252,
     267,     5,   190,     4,     4,   315,   315,   315,   267,   253,
       4,   253
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   254,   255,   255,   256,   257,   257,   258,   258,   259,
     259,   260,   260,   261,   261,   261,   262,   262,   263,   263,
     264,   264,   265,   265,   265,   266,   266,   267,   267,   267,
     267,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     269,   269,   269,   270,   271,   271,   272,   272,   273,   273,
     273,   273,   274,   274,   275,   275,   275,   276,   276,   276,
     276,   276,   277,   277,   277,   278,   278,   279,   279,   280,
     280,   280,   281,   281,   282,   282,   283,   283,   283,   283,
     284,   284,   285,   285,   286,   256,   287,   288,   288,   288,
     288,   287,   289,   289,   290,   290,   287,   256,   291,   292,
     292,   293,   293,   293,   293,   293,   294,   294,   295,   295,
     296,   296,   297,   297,   297,   297,   291,   291,   298,   298,
     298,   298,   256,   299,   299,   299,   256,   300,   301,   301,
     301,   302,   302,   302,   302,   256,   303,   303,   304,   304,
     256,   305,   305,   306,   306,   256,   307,   307,   307,   307,
     307,   307,   308,   308,   310,   309,   309,   309,   309,   309,
     309,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   312,   312,   312,   313,   313,   314,
     314,   314,   315,   315,   315,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   316,   316,
     316,   316,   316,   316,   316,   317,   317,   318,   319,   319,
     319,   320,   320,   256,   321,   322,   322,   322,   322,   256,
     323,   324,   324,   325,   325,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   327,
     327,   328,   328,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   329,   329,   329,   326,
     326,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     326,   326,   326,   326,   331,   331,   326,   326,   326,   326,
     326,   326,   326,   326
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     3,    11,     0,     2,     0,
       4,     2,     4,     0,     1,     1,     0,     2,     0,     2,
       0,     3,     0,     2,     4,     0,     2,     1,     1,     3,
       3,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     3,     1,     2,     1,     3,     1,     1,     3,     5,
       3,     3,     1,     0,     2,     1,     0,     5,     3,     5,
       6,     5,     0,     1,     1,     0,     1,     1,     1,     2,
       2,     0,     1,     0,     2,     4,     6,     6,     6,     0,
       2,     0,     1,     3,     3,     1,     7,     2,     2,     2,
       0,     6,     2,     4,     0,     2,     7,     1,     8,     0,
       4,     0,     2,     2,     2,     2,     1,     0,     0,     3,
       3,     5,     1,     1,     3,     3,     7,     7,     3,     3,
       5,     5,     1,     8,     7,     7,     1,     8,     0,     2,
       2,     3,     5,     5,     7,     1,     4,     4,     0,     2,
       1,     4,     4,     0,     2,     1,     8,    10,     9,     6,
      11,     8,     1,     3,     0,     4,     5,     4,     4,     5,
       5,     0,     3,     2,     3,     3,     3,     3,     2,     5,
       3,     3,     2,     3,     0,     3,     5,     0,     1,     0,
       2,     2,     0,     4,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     3,     5,     2,     4,     1,     1,     1,     1,     3,
       3,     3,     3,     5,     5,     1,     3,     3,     0,     1,
       1,     0,     1,     1,     5,     1,     1,     3,     3,     1,
       2,     1,     3,     3,     3,     1,     1,     3,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     5,     6,     6,     6,     3,     3,     3,
       3,     2,     2,     3,     3,     4,     3,     4,     5,     1,
       3,     0,     1,     5,     6,     5,     6,     4,     4,     4,
       4,     4,     6,     8,     4,     7,     1,     1,     1,     6,
       6,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     6,     3,     5,     4,     5,     3,     4,     3,     4,
       1,     1,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, scanner, pstate, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, scanner, pstate); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, struct psql_state *pstate)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (pstate);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, struct psql_state *pstate)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, pstate);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t scanner, struct psql_state *pstate)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , scanner, pstate);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, pstate); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, struct psql_state *pstate)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (pstate);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3: /* NAME  */
#line 360 "sql.y" /* yacc.c:1257  */
      { printf ("free at %d %s\n",(*yylocationp).first_line, ((*yyvaluep).strval)); free(((*yyvaluep).strval)); }
#line 2029 "sql.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* STRING  */
#line 360 "sql.y" /* yacc.c:1257  */
      { printf ("free at %d %s\n",(*yylocationp).first_line, ((*yyvaluep).strval)); free(((*yyvaluep).strval)); }
#line 2035 "sql.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* USERVAR  */
#line 360 "sql.y" /* yacc.c:1257  */
      { printf ("free at %d %s\n",(*yylocationp).first_line, ((*yyvaluep).strval)); free(((*yyvaluep).strval)); }
#line 2041 "sql.tab.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, struct psql_state *pstate)
{
/* The lookahead symbol.  */
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
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 365 "sql.y" /* yacc.c:1646  */
    { return yyresult;}
#line 2335 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 373 "sql.y" /* yacc.c:1646  */
    { return yyresult;}
#line 2341 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 380 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 2347 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 384 "sql.y" /* yacc.c:1646  */
    { sqlp_select_nodata(pstate, (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 2353 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 388 "sql.y" /* yacc.c:1646  */
    { sqlp_select(pstate, (yyvsp[-9].intval), (yyvsp[-8].intval), (yyvsp[-6].intval)); }
#line 2359 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 392 "sql.y" /* yacc.c:1646  */
    { sqlp_where(pstate); }
#line 2365 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 396 "sql.y" /* yacc.c:1646  */
    { sqlp_group_by_list(pstate, (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 2371 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 400 "sql.y" /* yacc.c:1646  */
    { sqlp_group_by(pstate, (yyvsp[0].intval)); (yyval.intval) = 1; }
#line 2377 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 402 "sql.y" /* yacc.c:1646  */
    { sqlp_group_by(pstate, (yyvsp[0].intval)); (yyval.intval) = (yyvsp[-3].intval) + 1; }
#line 2383 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 405 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2389 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 406 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2395 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 407 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2401 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 410 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2407 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 411 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2413 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 414 "sql.y" /* yacc.c:1646  */
    { sqlp_having(pstate); }
#line 2419 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 416 "sql.y" /* yacc.c:1646  */
    { sqlp_order_by(pstate, (yyvsp[0].intval)); }
#line 2425 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 419 "sql.y" /* yacc.c:1646  */
    { sqlp_limit(pstate, 0); }
#line 2431 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 420 "sql.y" /* yacc.c:1646  */
    { sqlp_limit(pstate, 1); }
#line 2437 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 424 "sql.y" /* yacc.c:1646  */
    { sqlp_into(pstate, (yyvsp[0].intval)); }
#line 2443 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 427 "sql.y" /* yacc.c:1646  */
    { sqlp_column(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = 1; }
#line 2449 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 428 "sql.y" /* yacc.c:1646  */
    { lyyerror((yylsp[0]), "string %s found where name required", (yyvsp[0].strval));
                              sqlp_column(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = 1; }
#line 2456 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 430 "sql.y" /* yacc.c:1646  */
    { sqlp_column(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2462 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 431 "sql.y" /* yacc.c:1646  */
    { lyyerror((yylsp[0]), "string %s found where name required", (yyvsp[-2].intval));
                            sqlp_column(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2469 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 435 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2475 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 436 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 01) lyyerror((yylsp[0]),"duplicate ALL option"); (yyval.intval) = (yyvsp[-1].intval) | 01; }
#line 2481 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 437 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 02) lyyerror((yylsp[0]),"duplicate DISTINCT option"); (yyval.intval) = (yyvsp[-1].intval) | 02; }
#line 2487 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 438 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 04) lyyerror((yylsp[0]),"duplicate DISTINCTROW option"); (yyval.intval) = (yyvsp[-1].intval) | 04; }
#line 2493 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 439 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 010) lyyerror((yylsp[0]),"duplicate HIGH_PRIORITY option"); (yyval.intval) = (yyvsp[-1].intval) | 010; }
#line 2499 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 440 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 020) lyyerror((yylsp[0]),"duplicate STRAIGHT_JOIN option"); (yyval.intval) = (yyvsp[-1].intval) | 020; }
#line 2505 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 441 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 040) lyyerror((yylsp[0]),"duplicate SQL_SMALL_RESULT option"); (yyval.intval) = (yyvsp[-1].intval) | 040; }
#line 2511 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 442 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 0100) lyyerror((yylsp[0]),"duplicate SQL_BIG_RESULT option"); (yyval.intval) = (yyvsp[-1].intval) | 0100; }
#line 2517 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 443 "sql.y" /* yacc.c:1646  */
    { if((yyval.intval) & 0200) lyyerror((yylsp[0]),"duplicate SQL_CALC_FOUND_ROWS option"); (yyval.intval) = (yyvsp[-1].intval) | 0200; }
#line 2523 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 446 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2529 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 447 "sql.y" /* yacc.c:1646  */
    {(yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2535 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 448 "sql.y" /* yacc.c:1646  */
    { sqlp_select_all(pstate); (yyval.intval) = 1; }
#line 2541 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 453 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2547 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 454 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2553 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 462 "sql.y" /* yacc.c:1646  */
    { sqlp_table(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); }
#line 2559 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 463 "sql.y" /* yacc.c:1646  */
    { sqlp_table(pstate, (yyvsp[-4].strval), (yyvsp[-2].strval));
                               free((yyvsp[-4].strval)); free((yyvsp[-2].strval)); }
#line 2566 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 465 "sql.y" /* yacc.c:1646  */
    { sqlp_subquery_as(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 2572 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 466 "sql.y" /* yacc.c:1646  */
    { sqlp_table_refs(pstate, (yyvsp[-1].intval)); }
#line 2578 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 473 "sql.y" /* yacc.c:1646  */
    { sqlp_alias(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 2584 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 474 "sql.y" /* yacc.c:1646  */
    { sqlp_alias(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 2590 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 480 "sql.y" /* yacc.c:1646  */
    { sqlp_join(pstate, 0100+(yyvsp[-3].intval)); }
#line 2596 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 482 "sql.y" /* yacc.c:1646  */
    { sqlp_join(pstate, 0200); }
#line 2602 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 484 "sql.y" /* yacc.c:1646  */
    { sqlp_join(pstate, 0200); }
#line 2608 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 486 "sql.y" /* yacc.c:1646  */
    { sqlp_join(pstate, 0300+(yyvsp[-4].intval)+(yyvsp[-3].intval)); }
#line 2614 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 488 "sql.y" /* yacc.c:1646  */
    { sqlp_join(pstate, 0400+(yyvsp[-2].intval)); }
#line 2620 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 491 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2626 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 492 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2632 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 493 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 2; }
#line 2638 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 496 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2644 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 497 "sql.y" /* yacc.c:1646  */
    {(yyval.intval) = 4; }
#line 2650 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 500 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2656 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 501 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 2; }
#line 2662 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 504 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1 + (yyvsp[0].intval); }
#line 2668 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 505 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 2 + (yyvsp[0].intval); }
#line 2674 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 506 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2680 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 512 "sql.y" /* yacc.c:1646  */
    { sqlp_join_expr(pstate); }
#line 2686 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 513 "sql.y" /* yacc.c:1646  */
    { sqlp_join_using(pstate, (yyvsp[-1].intval)); }
#line 2692 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 518 "sql.y" /* yacc.c:1646  */
    { sqlp_index_hint(pstate, (yyvsp[-1].intval), 010+(yyvsp[-3].intval)); }
#line 2698 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 520 "sql.y" /* yacc.c:1646  */
    { sqlp_index_hint(pstate, (yyvsp[-1].intval), 020+(yyvsp[-3].intval)); }
#line 2704 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 522 "sql.y" /* yacc.c:1646  */
    { sqlp_index_hint(pstate, (yyvsp[-1].intval), 030+(yyvsp[-3].intval)); }
#line 2710 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 526 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2716 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 527 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2722 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 530 "sql.y" /* yacc.c:1646  */
    { sqlp_index(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = 1; }
#line 2728 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 531 "sql.y" /* yacc.c:1646  */
    { sqlp_index(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2734 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 534 "sql.y" /* yacc.c:1646  */
    { sqlp_subquery(pstate); }
#line 2740 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 539 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 2746 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 544 "sql.y" /* yacc.c:1646  */
    { sqlp_delete(pstate, (yyvsp[-5].intval), (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 2752 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 547 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) + 01; }
#line 2758 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 548 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) + 02; }
#line 2764 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 549 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) + 04; }
#line 2770 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 550 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2776 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 556 "sql.y" /* yacc.c:1646  */
    { sqlp_delete_multi(pstate, (yyvsp[-4].intval), (yyvsp[-3].intval), (yyvsp[-1].intval)); }
#line 2782 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 558 "sql.y" /* yacc.c:1646  */
    { sqlp_table(pstate, NULL, (yyvsp[-1].strval)); free((yyvsp[-1].strval)); (yyval.intval) = 1; }
#line 2788 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 560 "sql.y" /* yacc.c:1646  */
    { sqlp_table(pstate, NULL, (yyvsp[-1].strval)); free((yyvsp[-1].strval)); (yyval.intval) = (yyvsp[-3].intval) + 1; }
#line 2794 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 568 "sql.y" /* yacc.c:1646  */
    { sqlp_delete_multi(pstate, (yyvsp[-5].intval), (yyvsp[-3].intval), (yyvsp[-1].intval)); }
#line 2800 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 573 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 2806 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 579 "sql.y" /* yacc.c:1646  */
    { sqlp_insert(pstate, (yyvsp[-6].intval), (yyvsp[-1].intval), (yyvsp[-4].strval)); free((yyvsp[-4].strval)); }
#line 2812 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 583 "sql.y" /* yacc.c:1646  */
    { sqlp_ins_dup_update(pstate, (yyvsp[0].intval)); }
#line 2818 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 586 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2824 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 587 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 01 ; }
#line 2830 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 588 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 02 ; }
#line 2836 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 589 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 04 ; }
#line 2842 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 590 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 010 ; }
#line 2848 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 597 "sql.y" /* yacc.c:1646  */
    { sqlp_ins_cols(pstate, (yyvsp[-1].intval)); }
#line 2854 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 600 "sql.y" /* yacc.c:1646  */
    { sqlp_values(pstate, (yyvsp[-1].intval)); (yyval.intval) = 1; }
#line 2860 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 601 "sql.y" /* yacc.c:1646  */
    { sqlp_values(pstate, (yyvsp[-1].intval)); (yyval.intval) = (yyvsp[-4].intval) + 1; }
#line 2866 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 604 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 2872 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 605 "sql.y" /* yacc.c:1646  */
    { sqlp_ins_default(pstate); (yyval.intval) = 1; }
#line 2878 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 606 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2884 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 607 "sql.y" /* yacc.c:1646  */
    { sqlp_ins_default(pstate); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 2890 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 613 "sql.y" /* yacc.c:1646  */
    { sqlp_insert_assn(pstate, (yyvsp[-5].intval), (yyvsp[-1].intval), (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 2896 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 618 "sql.y" /* yacc.c:1646  */
    { sqlp_insert_sel(pstate, (yyvsp[-5].intval), (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 2902 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 623 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad insert assignment to %s", (yyvsp[-2].strval)); YYERROR; }
       sqlp_assign(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); (yyval.intval) = 1; }
#line 2909 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 626 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad insert assignment to %s", (yyvsp[-2].strval)); YYERROR; }
                 sqlp_ins_default(pstate); sqlp_assign(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); (yyval.intval) = 1; }
#line 2916 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 629 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad insert assignment to %s", (yyvsp[-4].intval)); YYERROR; }
                 sqlp_assign(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); (yyval.intval) = (yyvsp[-4].intval) + 1; }
#line 2923 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 632 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad insert assignment to %s", (yyvsp[-4].intval)); YYERROR; }
                 sqlp_ins_default(pstate); sqlp_assign(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); (yyval.intval) = (yyvsp[-4].intval) + 1; }
#line 2930 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 637 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 2936 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 643 "sql.y" /* yacc.c:1646  */
    { sqlp_replace_vals(pstate, (yyvsp[-6].intval), (yyvsp[-1].intval), (yyvsp[-4].strval)); free((yyvsp[-4].strval)); }
#line 2942 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 649 "sql.y" /* yacc.c:1646  */
    { sqlp_replace_assn(pstate, (yyvsp[-5].intval), (yyvsp[-1].intval), (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 2948 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 654 "sql.y" /* yacc.c:1646  */
    { sqlp_replace_sel(pstate, (yyvsp[-5].intval), (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 2954 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 658 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 2960 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 665 "sql.y" /* yacc.c:1646  */
    { sqlp_update(pstate, (yyvsp[-6].intval), (yyvsp[-5].intval), (yyvsp[-3].intval)); }
#line 2966 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 668 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 2972 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 669 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 01 ; }
#line 2978 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 670 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 010 ; }
#line 2984 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 675 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad update assignment to %s", (yyvsp[-2].strval)); YYERROR; }
	 sqlp_assign(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); (yyval.intval) = 1; }
#line 2991 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 678 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad update assignment to %s", (yyvsp[-4].strval)); YYERROR; }
	 sqlp_assign(pstate, (yyvsp[-4].strval), (yyvsp[-2].strval)); free((yyvsp[-4].strval)); free((yyvsp[-2].strval)); (yyval.intval) = 1; }
#line 2998 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 681 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad update assignment to %s", (yyvsp[-2].strval)); YYERROR; }
	 sqlp_assign(pstate, NULL, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); (yyval.intval) = (yyvsp[-4].intval) + 1; }
#line 3005 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 684 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad update  assignment to %s.$s", (yyvsp[-4].strval), (yyvsp[-2].strval)); YYERROR; }
	 sqlp_assign(pstate, (yyvsp[-4].strval), (yyvsp[-2].strval)); free((yyvsp[-4].strval)); free((yyvsp[-2].strval)); (yyval.intval) = 1; }
#line 3012 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 691 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 3018 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 695 "sql.y" /* yacc.c:1646  */
    { sqlp_create_db(pstate, (yyvsp[-1].intval), (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3024 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 696 "sql.y" /* yacc.c:1646  */
    { sqlp_create_db(pstate, (yyvsp[-1].intval), (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3030 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 699 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3036 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 700 "sql.y" /* yacc.c:1646  */
    { if(!(yyvsp[0].subtok)) { lyyerror((yylsp[0]),"IF EXISTS doesn't exist"); YYERROR; }
                        (yyval.intval) = (yyvsp[0].subtok); /* NOT EXISTS hack */ }
#line 3043 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 706 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 3049 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 710 "sql.y" /* yacc.c:1646  */
    { sqlp_drop_db(pstate, (yyvsp[-1].intval), (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3055 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 711 "sql.y" /* yacc.c:1646  */
    { sqlp_drop_db(pstate, (yyvsp[-1].intval), (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3061 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 714 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3067 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 715 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 3073 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 720 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 3079 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 724 "sql.y" /* yacc.c:1646  */
    { sqlp_create_tbl(pstate, (yyvsp[-6].intval), (yyvsp[-4].intval), (yyvsp[-1].intval), NULL, (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 3085 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 728 "sql.y" /* yacc.c:1646  */
    { sqlp_create_tbl(pstate, (yyvsp[-8].intval), (yyvsp[-6].intval), (yyvsp[-1].intval), (yyvsp[-5].strval), (yyvsp[-3].strval));
                          free((yyvsp[-5].strval)); free((yyvsp[-3].strval)); }
#line 3092 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 734 "sql.y" /* yacc.c:1646  */
    { sqlp_create_tbl_sel(pstate, (yyvsp[-7].intval), (yyvsp[-5].intval), (yyvsp[-2].intval), NULL, (yyvsp[-4].strval)); free((yyvsp[-4].strval)); }
#line 3098 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 738 "sql.y" /* yacc.c:1646  */
    { sqlp_create_tbl_sel(pstate, (yyvsp[-4].intval), (yyvsp[-2].intval), 0, NULL, (yyvsp[-1].strval)); free((yyvsp[-1].strval)); }
#line 3104 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 743 "sql.y" /* yacc.c:1646  */
    { sqlp_create_tbl_sel(pstate, (yyvsp[-9].intval), (yyvsp[-7].intval), 0, (yyvsp[-6].strval), (yyvsp[-4].strval));
                              free((yyvsp[-6].strval)); free((yyvsp[-4].strval)); }
#line 3111 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 748 "sql.y" /* yacc.c:1646  */
    { sqlp_create_tbl_sel(pstate, (yyvsp[-6].intval), (yyvsp[-4].intval), 0, (yyvsp[-3].strval), (yyvsp[-1].strval));
                          free((yyvsp[-3].strval)); free((yyvsp[-1].strval)); }
#line 3118 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 752 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 3124 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 753 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3130 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 756 "sql.y" /* yacc.c:1646  */
    { sqlp_start_col(pstate); }
#line 3136 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 757 "sql.y" /* yacc.c:1646  */
    { sqlp_def_col(pstate, (yyvsp[-1].intval), (yyvsp[-2].strval)); free((yyvsp[-2].strval)); }
#line 3142 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 759 "sql.y" /* yacc.c:1646  */
    { sqlp_col_key_pri(pstate, (yyvsp[-1].intval)); }
#line 3148 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 760 "sql.y" /* yacc.c:1646  */
    { sqlp_col_key(pstate, (yyvsp[-1].intval)); }
#line 3154 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 761 "sql.y" /* yacc.c:1646  */
    { sqlp_col_key(pstate, (yyvsp[-1].intval)); }
#line 3160 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 762 "sql.y" /* yacc.c:1646  */
    { sqlp_col_key_textidx(pstate, (yyvsp[-1].intval)); }
#line 3166 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 763 "sql.y" /* yacc.c:1646  */
    { sqlp_col_key_textidx(pstate, (yyvsp[-1].intval)); }
#line 3172 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 766 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3178 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 767 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr(pstate, SCA_NOTNULL); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3184 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 769 "sql.y" /* yacc.c:1646  */
    { sqlp_col_def_str(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3190 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 770 "sql.y" /* yacc.c:1646  */
    { sqlp_col_def_num(pstate, (yyvsp[0].intval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3196 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 771 "sql.y" /* yacc.c:1646  */
    { sqlp_col_def_float(pstate, (yyvsp[0].floatval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3202 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 772 "sql.y" /* yacc.c:1646  */
    { sqlp_col_def_bool(pstate, (yyvsp[0].intval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3208 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 773 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr(pstate, SCA_AUTOINC); (yyval.intval) = (yyvsp[-1].intval) + 1; }
#line 3214 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 774 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr_uniq(pstate, (yyvsp[-1].intval)); (yyval.intval) = (yyvsp[-4].intval) + 1; }
#line 3220 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 775 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr_uniq(pstate, 0); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3226 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 776 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr(pstate, SCA_PRIMARY_KEY); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3232 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 777 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr(pstate, SCA_PRIMARY_KEY); (yyval.intval) = (yyvsp[-1].intval) + 1; }
#line 3238 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 778 "sql.y" /* yacc.c:1646  */
    { sqlp_col_attr_comm(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3244 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 781 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3250 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 782 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval); }
#line 3256 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 783 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-3].intval) + 1000*(yyvsp[-1].intval); }
#line 3262 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 786 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3268 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 787 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 4000; }
#line 3274 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 790 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3280 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 791 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 1000; }
#line 3286 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 792 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-1].intval) | 2000; }
#line 3292 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 796 "sql.y" /* yacc.c:1646  */
    { sqlp_col_charset(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3298 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 797 "sql.y" /* yacc.c:1646  */
    { sqlp_col_collate(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3304 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 801 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 10000 + (yyvsp[0].intval); }
#line 3310 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 802 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 10000 + (yyvsp[-1].intval); }
#line 3316 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 803 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 20000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3322 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 804 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 30000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3328 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 805 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 40000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3334 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 806 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 50000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3340 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 807 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 60000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3346 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 808 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 70000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3352 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 809 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 80000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3358 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 810 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 90000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3364 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 811 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 110000 + (yyvsp[-1].intval) + (yyvsp[0].intval); }
#line 3370 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 812 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 100001; }
#line 3376 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 813 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 100002; }
#line 3382 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 814 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 100003; }
#line 3388 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 815 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 100004; }
#line 3394 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 816 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 100005; }
#line 3400 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 817 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 120000 + (yyvsp[-1].intval); }
#line 3406 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 818 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 130000 + (yyvsp[-2].intval); }
#line 3412 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 819 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 140000 + (yyvsp[0].intval); }
#line 3418 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 820 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 150000 + (yyvsp[-1].intval); }
#line 3424 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 821 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 160001; }
#line 3430 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 822 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 160002; }
#line 3436 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 823 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 160003; }
#line 3442 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 824 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 160004; }
#line 3448 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 825 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 170000 + (yyvsp[-1].intval); }
#line 3454 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 826 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 171000 + (yyvsp[-1].intval); }
#line 3460 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 827 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 172000 + (yyvsp[-1].intval); }
#line 3466 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 828 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 173000 + (yyvsp[-1].intval); }
#line 3472 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 829 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 200000 + (yyvsp[-2].intval); }
#line 3478 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 830 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 210000 + (yyvsp[-2].intval); }
#line 3484 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 833 "sql.y" /* yacc.c:1646  */
    { sqlp_enum_val(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = 1; }
#line 3490 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 834 "sql.y" /* yacc.c:1646  */
    { sqlp_enum_val(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3496 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 837 "sql.y" /* yacc.c:1646  */
    { sqlp_create_sel(pstate, (yyvsp[-2].intval)); }
#line 3502 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 840 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3508 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 841 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 3514 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 842 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 2; }
#line 3520 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 845 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3526 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 846 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1;}
#line 3532 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 851 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 3538 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 855 "sql.y" /* yacc.c:1646  */
    { sqlp_drop_table(pstate, (yyvsp[-3].intval), (yyvsp[-1].intval), (yyvsp[0].intval)); }
#line 3544 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 858 "sql.y" /* yacc.c:1646  */
    { sqlp_table(pstate, NULL, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = 1; }
#line 3550 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 859 "sql.y" /* yacc.c:1646  */
    { lyyerror((yylsp[0]), "string %s found where name required", (yyvsp[0].strval));
                              sqlp_table(pstate, NULL, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = 1; }
#line 3557 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 861 "sql.y" /* yacc.c:1646  */
    { sqlp_table(pstate, NULL, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3563 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 862 "sql.y" /* yacc.c:1646  */
    { lyyerror((yylsp[0]), "string %s found where name required", (yyvsp[-2].intval));
                            sqlp_table(pstate, NULL, (yyvsp[0].strval)); free((yyvsp[0].strval)); (yyval.intval) = (yyvsp[-2].intval) + 1; }
#line 3570 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 868 "sql.y" /* yacc.c:1646  */
    { sqlp_stmt(pstate); }
#line 3576 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 876 "sql.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].subtok) != 4) { lyyerror((yylsp[-1]),"bad set to @%s", (yyvsp[-2].strval)); YYERROR; }
		 sqlp_set(pstate, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); }
#line 3583 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 878 "sql.y" /* yacc.c:1646  */
    { sqlp_set(pstate, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); }
#line 3589 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 883 "sql.y" /* yacc.c:1646  */
    { sqlp_name(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3595 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 884 "sql.y" /* yacc.c:1646  */
    { sqlp_uservar(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3601 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 885 "sql.y" /* yacc.c:1646  */
    { sqlp_fieldname(pstate, (yyvsp[-2].strval), (yyvsp[0].strval)); free((yyvsp[-2].strval)); free((yyvsp[0].strval)); }
#line 3607 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 886 "sql.y" /* yacc.c:1646  */
    { sqlp_string(pstate, (yyvsp[0].strval)); free((yyvsp[0].strval)); }
#line 3613 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 887 "sql.y" /* yacc.c:1646  */
    { sqlp_number(pstate, (yyvsp[0].intval)); }
#line 3619 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 888 "sql.y" /* yacc.c:1646  */
    { sqlp_float(pstate, (yyvsp[0].floatval)); }
#line 3625 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 889 "sql.y" /* yacc.c:1646  */
    { sqlp_bool(pstate, (yyvsp[0].intval)); }
#line 3631 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 892 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_ADD); }
#line 3637 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 893 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_SUB); }
#line 3643 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 894 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_MUL); }
#line 3649 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 895 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_DIV); }
#line 3655 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 896 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_MOD); }
#line 3661 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 897 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_MOD); }
#line 3667 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 898 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_NEG); }
#line 3673 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 899 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_AND); }
#line 3679 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 900 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_OR); }
#line 3685 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 901 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_XOR); }
#line 3691 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 902 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_cmp(pstate, (yyvsp[-1].subtok)); }
#line 3697 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 903 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_cmp_sel(pstate, 0, (yyvsp[-3].subtok)); }
#line 3703 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 904 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_cmp_sel(pstate, 1, (yyvsp[-4].subtok)); }
#line 3709 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 905 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_cmp_sel(pstate, 2, (yyvsp[-4].subtok)); }
#line 3715 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 906 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_cmp_sel(pstate, 3, (yyvsp[-4].subtok)); }
#line 3721 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 907 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_BITOR); }
#line 3727 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 908 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_BITAND); }
#line 3733 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 909 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_BITXOR); }
#line 3739 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 910 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, (yyvsp[-1].subtok) == 1 ? SEO_SHL : SEO_SHR); }
#line 3745 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 911 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_NOT); }
#line 3751 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 912 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_NOT); }
#line 3757 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 913 "sql.y" /* yacc.c:1646  */
    { sqlp_assign_at(pstate, (yyvsp[-2].strval)); free((yyvsp[-2].strval)); }
#line 3763 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 916 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_IS_NULL); }
#line 3769 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 917 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_IS_NULL); sqlp_expr_op(pstate, SEO_NOT); }
#line 3775 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 918 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_is_bool(pstate, (yyvsp[0].intval)); }
#line 3781 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 919 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_is_bool(pstate, (yyvsp[0].intval)); sqlp_expr_op(pstate, SEO_NOT); }
#line 3787 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 922 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_BETWEEN); }
#line 3793 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 926 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 3799 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 927 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1 + (yyvsp[0].intval); }
#line 3805 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 930 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 0; }
#line 3811 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 934 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_is_in(pstate, (yyvsp[-1].intval)); }
#line 3817 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 935 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_is_in(pstate, (yyvsp[-1].intval)); sqlp_expr_op(pstate, SEO_NOT); }
#line 3823 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 936 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_IN_SELECT); }
#line 3829 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 937 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_IN_SELECT); sqlp_expr_op(pstate, SEO_NOT); }
#line 3835 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 938 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_EXISTS); if((yyvsp[-3].subtok))sqlp_expr_op(pstate, SEO_NOT); }
#line 3841 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 941 "sql.y" /* yacc.c:1646  */
    {  sqlp_call(pstate, (yyvsp[-1].intval), (yyvsp[-3].strval)); free((yyvsp[-3].strval)); }
#line 3847 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 945 "sql.y" /* yacc.c:1646  */
    { sqlp_call(pstate, 0, "COUNTALL"); }
#line 3853 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 946 "sql.y" /* yacc.c:1646  */
    { sqlp_call(pstate, 1, "COUNT"); }
#line 3859 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 948 "sql.y" /* yacc.c:1646  */
    {  sqlp_call(pstate, (yyvsp[-1].intval), "SUBSTR");}
#line 3865 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 949 "sql.y" /* yacc.c:1646  */
    {  sqlp_call(pstate, 2, "SUBSTR"); }
#line 3871 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 950 "sql.y" /* yacc.c:1646  */
    {  sqlp_call(pstate, 3, "SUBSTR"); }
#line 3877 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 951 "sql.y" /* yacc.c:1646  */
    { sqlp_call(pstate, (yyvsp[-1].intval), "TRIM"); }
#line 3883 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 952 "sql.y" /* yacc.c:1646  */
    { sqlp_call(pstate, 3, "TRIM"); }
#line 3889 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 955 "sql.y" /* yacc.c:1646  */
    { sqlp_call_trim_opts(pstate, 0); }
#line 3895 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 956 "sql.y" /* yacc.c:1646  */
    { sqlp_call_trim_opts(pstate, 1); }
#line 3901 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 957 "sql.y" /* yacc.c:1646  */
    { sqlp_call_trim_opts(pstate, 2); }
#line 3907 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 960 "sql.y" /* yacc.c:1646  */
    { sqlp_call_date(pstate, 3, SEO_ADD); }
#line 3913 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 961 "sql.y" /* yacc.c:1646  */
    { sqlp_call_date(pstate, 3, SEO_SUB); }
#line 3919 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 964 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_DAY_HOUR); }
#line 3925 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 965 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_DAY_MICROSECOND); }
#line 3931 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 966 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_DAY_MINUTE); }
#line 3937 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 967 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_DAY_SECOND); }
#line 3943 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 968 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_YEAR_MONTH); }
#line 3949 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 969 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_YEAR); }
#line 3955 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 970 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_HOUR_MICROSECOND); }
#line 3961 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 971 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_HOUR_MINUTE); }
#line 3967 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 972 "sql.y" /* yacc.c:1646  */
    { sqlp_date_interval(pstate, SDI_HOUR_SECOND); }
#line 3973 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 975 "sql.y" /* yacc.c:1646  */
    { sqlp_caseval(pstate, (yyvsp[-1].intval), 0); }
#line 3979 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 976 "sql.y" /* yacc.c:1646  */
    { sqlp_caseval(pstate, (yyvsp[-3].intval), 1); }
#line 3985 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 977 "sql.y" /* yacc.c:1646  */
    { sqlp_case(pstate, (yyvsp[-1].intval), 0); }
#line 3991 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 978 "sql.y" /* yacc.c:1646  */
    { sqlp_case(pstate, (yyvsp[-3].intval), 1); }
#line 3997 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 981 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = 1; }
#line 4003 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 982 "sql.y" /* yacc.c:1646  */
    { (yyval.intval) = (yyvsp[-4].intval)+1; }
#line 4009 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 985 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_LIKE); }
#line 4015 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 986 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_LIKE); sqlp_expr_op(pstate, SEO_NOT); }
#line 4021 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 989 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_REGEX); }
#line 4027 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 990 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_REGEX); sqlp_expr_op(pstate, SEO_NOT); }
#line 4033 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 993 "sql.y" /* yacc.c:1646  */
    { sqlp_now(pstate); }
#line 4039 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 994 "sql.y" /* yacc.c:1646  */
    { sqlp_now(pstate); }
#line 4045 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 995 "sql.y" /* yacc.c:1646  */
    { sqlp_now(pstate); }
#line 4051 "sql.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 998 "sql.y" /* yacc.c:1646  */
    { sqlp_expr_op(pstate, SEO_STRTOBIN); }
#line 4057 "sql.tab.c" /* yacc.c:1646  */
    break;


#line 4061 "sql.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, scanner, pstate, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, scanner, pstate, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, &yylloc, scanner, pstate);
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

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, scanner, pstate);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, pstate, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, pstate);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, scanner, pstate);
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
  return yyresult;
}
#line 1001 "sql.y" /* yacc.c:1906  */


void
yyerror(YYLTYPE *t, yyscan_t scanner, struct psql_state *pstate, const char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  if(t->first_line)
    fprintf(stderr, "%s:%d.%d-%d.%d: error: ", t->filename, t->first_line, t->first_column,
	    t->last_line, t->last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");

}

void
lyyerror(YYLTYPE t, const char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  if(t.first_line)
    fprintf(stderr, "%s:%d.%d-%d.%d: error: ", t.filename, t.first_line, t.first_column,
	    t.last_line, t.last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}
/*
int
main(int ac, char **av)
{
  FILE *in_f;
  struct psql_state pstate;

  if(ac > 1 && !strcmp(av[1], "-d")) {
    yydebug = 1; ac--; av++;
  }

  memset(&pstate, 0, sizeof(pstate));
  if (yylex_init_extra(&pstate, &pstate.scanner))
  	return 1;

  if(ac > 1) {
    if((in_f = fopen(av[1], "r")) == NULL) {
      perror(av[1]);
      exit(1);
    }
    filename = av[1];
  } else {
    filename = "(stdin)";
    in_f = stdin;
  }

  yyset_in(in_f, pstate.scanner);

  if(!yyparse(pstate.scanner, &pstate)) {
    printf("SQL parse worked\n");
    return 0;
  } else {
    printf("SQL parse failed\n");
    return 1;
  }
}*//* main */
