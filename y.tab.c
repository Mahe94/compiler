/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "sim.y" /* yacc.c:339  */
 

	#include<stdio.h> 
	#include<string.h>
	#include<stdlib.h>
	
	struct node {
		int type;	// 0 means operator, 1 means read, 2 means write, 3 means ID
		char *name;
		int integer;
		struct node *right, *middle, *left;
	};
	
	
	struct Gsymbol {	// for Symbol table
		char *NAME;
		int type;
		int size;
		int binding;
		struct Gsymbol *next;
	}*Symbol=NULL;
	
	void start(struct node *n);	//starting of parse tree generation
	int getloc(char *name);	
	void printSymbol();		
	void Ginstall(char *N, int t, int s);	//creating an entry in symbol table
	struct Gsymbol *Glookup(char *name);	//getting pointing from symbol table
	struct node *nodeCreate(int t, char *n, int i, struct node *l, struct node *m, struct node *r);	//creating a node for tree
	int get_datatype(struct node *n);	//returning datatype of node
	void check_datatypes(int t1, int t2, char *op); //checking datatypes
	
	int currentType;	//storing the current datatype while making the symbol table
	int currentBinding = 0;	//storing the starting available address for binding
	int array[26];	
	int loc, T1, T2;
	int val;
	
	FILE *fp=NULL;	//file pointer for storing the machine code
	
	int avail_reg=0, avail_l=0;	//for storing the current available register and jump symbol
	

#line 109 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AND = 258,
    OR = 259,
    NOT = 264,
    DECL = 265,
    ENDDECL = 266,
    TYPE = 267,
    DIGIT = 268,
    READ = 269,
    WRITE = 270,
    ID = 271,
    IF = 272,
    THEN = 273,
    ENDIF = 274,
    ELSE = 275,
    WHILE = 276,
    DO = 277,
    ENDWHILE = 278,
    BEGINING = 279,
    END = 280,
    TRUE = 281,
    FALSE = 282
  };
#endif
/* Tokens.  */
#define AND 258
#define OR 259
#define NOT 264
#define DECL 265
#define ENDDECL 266
#define TYPE 267
#define DIGIT 268
#define READ 269
#define WRITE 270
#define ID 271
#define IF 272
#define THEN 273
#define ENDIF 274
#define ELSE 275
#define WHILE 276
#define DO 277
#define ENDWHILE 278
#define BEGINING 279
#define END 280
#define TRUE 281
#define FALSE 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 44 "sim.y" /* yacc.c:355  */

	struct node *n;	

#line 199 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 214 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    16,     2,     2,
      40,    41,    14,    12,    37,    13,     2,    15,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
       8,     3,    10,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,     7,     9,    11,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    64,    66,    67,    70,    73,    76,    77,
      78,    79,    82,    92,    94,    97,    98,   100,   102,   105,
     108,   111,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "AND", "OR", "\"==\"", "\"!=\"",
  "'<'", "\"<=\"", "'>'", "\">=\"", "'+'", "'-'", "'*'", "'/'", "'%'",
  "NOT", "DECL", "ENDDECL", "TYPE", "DIGIT", "READ", "WRITE", "ID", "IF",
  "THEN", "ENDIF", "ELSE", "WHILE", "DO", "ENDWHILE", "BEGINING", "END",
  "TRUE", "FALSE", "';'", "','", "'['", "']'", "'('", "')'", "$accept",
  "Prog", "Declaration", "Decl_list", "decl", "type", "id_list", "Body",
  "Slist", "Stmt", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,   258,   259,   260,   261,    60,   262,
      62,   263,    43,    45,    42,    47,    37,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,    59,    44,    91,    93,
      40,    41
};
# endif

#define YYPACT_NINF -28

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-28)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -6,    -4,    17,    24,   -28,     7,    -4,    33,   -28,   -16,
     -28,   -28,   -28,   -14,    22,    20,    21,    15,    23,    34,
      42,   -16,    33,    55,   -28,   143,    38,    38,    38,    38,
      38,   -28,   -28,   -28,    40,   -27,    38,   -28,   130,   -28,
     -28,    38,    36,   226,   141,    77,    90,   133,    38,   135,
     -28,    38,   128,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,   136,   -28,   170,   148,
     145,    33,   177,   -28,   190,   -28,   114,   101,   150,   150,
      53,    53,    53,    53,     5,     5,   -28,   -28,   -28,   -28,
      38,   -16,   -16,   -28,   137,   -28,   239,   149,   176,   140,
     -28,   -16,   -28,   -28,   152,   -28
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     7,     0,     5,     0,     1,    14,
       2,     3,     4,    10,     0,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     6,     0,     0,     0,     0,     0,
       0,    12,    13,     8,     0,     0,     0,    34,    35,    40,
      41,     0,     0,     0,     0,     0,     0,    11,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,     0,     0,
       0,     0,     0,    17,     0,    33,    36,    37,    30,    29,
      27,    31,    28,    32,    22,    23,    24,    25,    26,    19,
       0,    14,    14,     9,     0,    39,     0,     0,     0,     0,
      16,    14,    21,    18,     0,    20
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   202,   -28,   -28,   -17,   -28,   -21,   -28,
     -26
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     5,     6,     7,    14,    10,    20,    21,
      42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      32,    43,    44,    45,    46,    33,    15,    16,    17,    18,
      50,    48,     1,    19,    49,    52,     4,     8,    27,    63,
      64,    65,    72,    22,    23,    74,    11,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    28,    93,    36,     9,    13,    24,    37,
      25,    26,    38,    29,    96,    61,    62,    63,    64,    65,
      97,    98,    39,    40,    30,    31,    34,    66,    41,    47,
     104,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    69,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    70,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    35,    51,    75,
      71,    73,    89,    90,    91,    92,   103,   101,    99,   105,
      68,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,   102,    12,     0,
       0,     0,     0,     0,     0,     0,    94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   100
};

static const yytype_int8 yycheck[] =
{
      21,    27,    28,    29,    30,    22,    22,    23,    24,    25,
      36,    38,    18,    29,    41,    41,    20,     0,     3,    14,
      15,    16,    48,    37,    38,    51,    19,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    38,    71,    17,    32,    24,    36,    21,
      40,    40,    24,    40,    90,    12,    13,    14,    15,    16,
      91,    92,    34,    35,    40,    33,    21,    41,    40,    39,
     101,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    41,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    41,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    24,    38,    41,
      37,    36,    36,     3,    26,    30,    36,    28,    41,    27,
      39,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    31,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    43,    44,    20,    45,    46,    47,     0,    32,
      49,    19,    45,    24,    48,    22,    23,    24,    25,    29,
      50,    51,    37,    38,    36,    40,    40,     3,    38,    40,
      40,    33,    50,    48,    21,    24,    17,    21,    24,    34,
      35,    40,    52,    52,    52,    52,    52,    39,    38,    41,
      52,    38,    52,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    41,    36,    39,    41,
      41,    37,    52,    36,    52,    41,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    36,
       3,    26,    30,    48,    39,    39,    52,    50,    50,    41,
      36,    28,    31,    36,    50,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    45,    45,    46,    47,    48,    48,
      48,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     1,     3,     1,     3,     6,
       1,     4,     3,     2,     0,     4,     7,     5,     8,     5,
       9,     7,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     3,     3,     2,     4,
       1,     1
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 64 "sim.y" /* yacc.c:1646  */
    {printSymbol();}
#line 1389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 73 "sim.y" /* yacc.c:1646  */
    {currentType = (yyvsp[0].n)->type;}
#line 1395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 76 "sim.y" /* yacc.c:1646  */
    { Ginstall((yyvsp[-2].n)->name, currentType, 1);}
#line 1401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 77 "sim.y" /* yacc.c:1646  */
    { Ginstall((yyvsp[-5].n)->name, currentType, (yyvsp[-3].n)->integer); }
#line 1407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 78 "sim.y" /* yacc.c:1646  */
    { Ginstall((yyvsp[0].n)->name, currentType, 1); }
#line 1413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 79 "sim.y" /* yacc.c:1646  */
    { Ginstall((yyvsp[-3].n)->name, currentType, (yyvsp[-1].n)->integer); }
#line 1419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 82 "sim.y" /* yacc.c:1646  */
    {
				  (yyval.n)=(yyvsp[-1].n);
				  fp = fopen("output", "w+");	
				  fprintf(fp, "START\n");
				  start((yyval.n));
				  fprintf(fp, "HALT");
				  fclose(fp);
				  return 0; }
#line 1432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 92 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(100, NULL, 0, (yyvsp[-1].n), NULL, (yyvsp[0].n));
			}
#line 1439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 94 "sim.y" /* yacc.c:1646  */
    {(yyval.n)=NULL;}
#line 1445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 97 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(3, NULL, 0, (yyvsp[-3].n), NULL, (yyvsp[-1].n)); }
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 98 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(3, NULL, 0, (yyvsp[-6].n), (yyvsp[-4].n), (yyvsp[-1].n)); }
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 101 "sim.y" /* yacc.c:1646  */
    {(yyval.n) = nodeCreate(1, NULL, 0, (yyvsp[-2].n), NULL, NULL); }
#line 1463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 103 "sim.y" /* yacc.c:1646  */
    {(yyval.n) = nodeCreate(1, NULL, 0, (yyvsp[-5].n), NULL, (yyvsp[-3].n)); }
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 106 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(2, NULL, 0, (yyvsp[-2].n), NULL, NULL); }
#line 1475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 109 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(4, NULL, 0, (yyvsp[-6].n), (yyvsp[-3].n), (yyvsp[-1].n)); }
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 112 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(5, NULL, 0, (yyvsp[-4].n), NULL, (yyvsp[-1].n)); }
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 115 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "+", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 116 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "-", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 117 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "*", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 118 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "/", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 119 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "%", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 120 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "<", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 121 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, ">", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 122 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "!=", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 123 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "==", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 124 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, "<=", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 125 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(0, ">=", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 126 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[-1].n); }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 127 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 128 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 129 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(10, "and", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 130 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(10, "or", 0, (yyvsp[-2].n), NULL, (yyvsp[0].n)); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 131 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(10, "not", 0, (yyvsp[0].n), NULL, NULL); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 132 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(8, (yyvsp[-3].n)->name, 0, (yyvsp[-1].n), NULL, NULL); }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 133 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(9, "true", 1, NULL, NULL, NULL); }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 134 "sim.y" /* yacc.c:1646  */
    { (yyval.n) = nodeCreate(9, "false", 0, NULL, NULL, NULL); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1611 "y.tab.c" /* yacc.c:1646  */
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 137 "sim.y" /* yacc.c:1906  */
     

#include "lex.yy.c"

void printSymbol() {
	struct Gsymbol *symbol = Symbol;
	while(symbol != NULL) {
		printf("%s %d %d %d\n", symbol->NAME, symbol->type, symbol->size, symbol->binding);
		symbol = symbol->next;
	}
}

struct Gsymbol *Glookup(char *name) {
	struct Gsymbol *symbol = Symbol;
	while(symbol != NULL) {
		if(strcmp(symbol->NAME,name)==0)
			return symbol;
		symbol = symbol->next;
	}
	return NULL;
}

void Ginstall(char *N, int t, int s) {
	if(Glookup(N)!=NULL) {
		yyerror(strcat(N ," has been declared earlier"));
		exit(1);
	}
	struct Gsymbol *symbol = Symbol;
	if(symbol != NULL) {
		while(symbol->next != NULL)
			symbol = symbol->next;
		symbol->next = (struct Gsymbol*)malloc(sizeof(struct Gsymbol));
		symbol = symbol->next;
	}
	else {
		symbol = (struct Gsymbol*)malloc(sizeof(struct Gsymbol));
		Symbol = symbol;
	}

	symbol->NAME = (char*)malloc(sizeof(N));
	strcpy(symbol->NAME,N);
	symbol->type = t;
	symbol->size = s;
	symbol->binding = currentBinding;
	symbol->next = NULL;

	currentBinding = currentBinding + s;	
}

struct node *nodeCreate(int t, char *n, int i, struct node *l, struct node *m, struct node *r) {
	struct node *N = (struct node*)malloc(sizeof(struct node));
	N->type = t;
	if(n!=NULL) {
		N->name = (char *)malloc(sizeof(n));
		strcpy(N->name, n);
	}
	N->integer  = i;
	N->right = r;
	N->left = l;
	N->middle = m;
	return N;
}

void compute_bool(char *op) {
	if(!strcmp(op, "and")) {
		fprintf(fp, "MUL R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return;
	}
	if(!strcmp(op, "or")) {
		fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
		fprintf(fp, "MOV R%d, 1\n", avail_reg+1);
		fprintf(fp, "GE R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return;
	}
	if(!strcmp(op, "not")) {
		fprintf(fp, "MOV R%d, 0\n", avail_reg+1);
		fprintf(fp, "EQ R%d, R%d\n", avail_reg, avail_reg+1);
		fprintf(fp, "JNZ R%d, L%d\n", avail_reg, avail_l);
		fprintf(fp, "MOV R%d, 0\nL%d:\n", avail_reg, avail_l);
		++avail_l;
		currentType = 0;
		return;
	}
}

void compute(char *op) {
	if(!strcmp(op, "+")) {
		fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 1;
		return ;
	}
	if(!strcmp(op, "-")) {
		fprintf(fp, "SUB R%d, R%d\n", avail_reg, avail_reg+1);	
		currentType = 1;
		return ;
	}
	if(!strcmp(op, "*")) {
		fprintf(fp, "MUL R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 1;
		return ;
	}
	if(!strcmp(op, "/")) {
		fprintf(fp, "DIV R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 1;
		return ;
	}
	if(!strcmp(op, "%")) {
		fprintf(fp, "MOV R%d, R%d\n", avail_reg+2, avail_reg);
		fprintf(fp, "DIV R%d, R%d\n", avail_reg+2, avail_reg+1);
		fprintf(fp, "MUL R%d, R%d\n", avail_reg+2, avail_reg+1);
		fprintf(fp, "SUB R%d, R%d\n", avail_reg, avail_reg+2);
		currentType = 1;
		return ;
	}
	if(!strcmp(op, "<")) {
		fprintf(fp, "LT R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return ;
	}
	if(!strcmp(op, ">")) {
		fprintf(fp, "GT R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return ;
	}
	if(!strcmp(op, "!=")) {
		fprintf(fp, "NE R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return ;
	}
	if(!strcmp(op, "==")) {
		fprintf(fp, "EQ R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return ;
	}
	if(!strcmp(op, "<=")) {
		fprintf(fp, "LE R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return ;
	}
	if(!strcmp(op, ">=")) {
		fprintf(fp, "GE R%d, R%d\n", avail_reg, avail_reg+1);
		currentType = 0;
		return ;
	}
	char error[100] = "Operands not matching with operator ";
	strcat(error, op);
	yyerror(error);
}

int leaf(struct node *n) {
	if(n->right==NULL && n->left==NULL)
		return 1;
	else
		return 0;
}

int getloc(char *name) {
	struct Gsymbol *symbol = Glookup(name);
	return symbol->binding;
}

int get_datatype(struct node *n) {
	struct Gsymbol *s;
	s = Glookup(n->name);
	return s->type;
}

void check_datatypes(int t1, int t2, char *op) {
	if(t1 != t2) {
		char error[100] = "Conflicting operands for operator ";
		strcat(error, op);
		yyerror(error);
		exit(1);
	}
	currentType = t1;
}

int variable(struct node *n) {
	int t;
	switch(n->type) {
		case 0:
			start(n);
			t = currentType;
			break;
		case 6:
			fprintf(fp, "MOV R%d, %d\n", avail_reg, n->integer);
			t = 1;
			break;
	
		case 7:
			loc = getloc(n->name);
			fprintf(fp, "MOV R%d, [%d]\n", avail_reg, loc);
			t = get_datatype(n);
			break;
		case 8:
			t = variable(n->left);
			check_datatypes(t, 1, "");
			loc = getloc(n->name);
			fprintf(fp, "MOV R%d, %d\n", avail_reg+1, loc);
			fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
			fprintf(fp, "MOV R%d, [R%d]\n", avail_reg, avail_reg);
			t = get_datatype(n);
			break;
		case 10:
			start(n);
			t = currentType;
			break;
		case 9:
			fprintf(fp, "MOV R%d, %d\n", avail_reg,	 n->integer);
			t = 0;
			break;
		default:
			yyerror("Type 0 error");				
	}
	return t;			
}

void start(struct node *n) {
//	printf("STARTED\n");
//	scanf("%d", avail_reg);
	int l1, l2;
	if(!leaf(n)) {
		switch(n->type) {
			case 0:						//operations
				T1 = variable(n->left);
				check_datatypes(T1, 1 , n->name);
				++avail_reg;
				T1 = variable(n->right);
				--avail_reg;
				check_datatypes(T1, 1 , n->name);
				compute(n->name);
				break;
			case 1:					//read
				loc = getloc(n->left->name);
				fprintf(fp, "MOV R%d, %d\n", avail_reg + 1, loc);
				if(n->right != NULL) {
					avail_reg = avail_reg + 2;
					variable(n->right);
					avail_reg = avail_reg - 2;
					fprintf(fp, "ADD R%d, R%d\n", avail_reg+1, avail_reg+2);
				}
				fprintf(fp, "IN R%d\n", avail_reg);
				fprintf(fp, "MOV [R%d], R%d\n", avail_reg+1, avail_reg);
				break;
			case 2:						//write
				variable(n->left);
				fprintf(fp, "OUT R%d\n", avail_reg);
				break;
			case 3:				//assignment
				loc = getloc(n->left->name);
				fprintf(fp, "MOV R%d, %d\n", avail_reg, loc);
				if(n->middle != NULL) {
					++avail_reg;
					T1 = variable(n->middle);
					--avail_reg;
					check_datatypes(T1, 1, "");
					fprintf(fp, "ADD R%d, R%d\n", avail_reg, avail_reg+1);
				}
				T1 = get_datatype(n->left);
				++avail_reg;
				T2 = variable(n->right);
				--avail_reg;
				fprintf(fp, "MOV [R%d], R%d\n", avail_reg, avail_reg+1);
				break;
				
			case 4:				//if
				l1=avail_l, l2=avail_l+1;
				avail_l+=2;
				T1=variable(n->left);
				check_datatypes(T1, 0, "");
				fprintf(fp, "JZ R%d, L%d\n", avail_reg, l1);
				start(n->middle);
				fprintf(fp, "JMP L%d\nL%d:\n", l2, l1);
				if(n->right != NULL)
					start(n->right);
				fprintf(fp, "L%d:\n", l2);
				break;
			
			case 5:				//while
				l1=avail_l, l2=avail_l+1;
				avail_l+=2;
				fprintf(fp, "L%d:\n", l1);
				start(n->left);
				fprintf(fp, "JZ R%d, L%d\n", avail_reg, l2);
				start(n->right);
				fprintf(fp, "JMP L%d\nL%d:\n", l1, l2);
				break;
				
			case 10:			//boolean 
				T1 = variable(n->left);
				check_datatypes(T1, 0, "");
				if(n->right != NULL) {
					T2 = variable(n->right);
					check_datatypes(T2, 0, "");
				}
				compute_bool(n->name);
				break;
				
			case 100:
				start(n->left);
				if(n->right!=NULL)
					start(n->right);
				break;
				
			default:
				break;
		}	
	}
}

yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap()
{
        return 1;
} 

int main(int argc, char *argv[]) 
{ 
   if(argc > 1) {
   	FILE *fp = fopen(argv[1], "r");
   	if(fp)
   		yyin = fp;
   }
    yyparse(); 
} 

