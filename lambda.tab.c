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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lambda.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* --- VARIABLES GLOBALES --- */
char* lista_argumentos[100];
int contador_args = 0;

extern int yylineno;
extern int yylex();
extern char* yytext;
void yyerror(const char *s);

/* --- FUNCIONES AUXILIARES --- */

char* unir(const char* s1, const char* s2) {
    char* resultado = malloc(strlen(s1) + strlen(s2) + 1); 
    if (resultado == NULL) { fprintf(stderr, "Error de memoria\n"); exit(1); }
    strcpy(resultado, s1);
    strcat(resultado, s2);
    return resultado;
}

char* unir3(const char* s1, const char* s2, const char* s3) {
    char* resultado = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
    if (resultado == NULL) { fprintf(stderr, "Error de memoria\n"); exit(1); }
    strcpy(resultado, s1);
    strcat(resultado, s2);
    strcat(resultado, s3);
    return resultado;
}

void limpiar_args() {
    contador_args = 0;
}

void agregar_arg(char* nombre) {
    if (contador_args < 100) {
        lista_argumentos[contador_args] = strdup(nombre); 
        contador_args++;
    }
}

#line 117 "lambda.tab.c"

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

#include "lambda.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_FLOAT_LIT = 4,                  /* FLOAT_LIT  */
  YYSYMBOL_INT_LIT = 5,                    /* INT_LIT  */
  YYSYMBOL_TYPE_INT = 6,                   /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 7,                 /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_BOOL = 8,                  /* TYPE_BOOL  */
  YYSYMBOL_SUCC = 9,                       /* SUCC  */
  YYSYMBOL_PRED = 10,                      /* PRED  */
  YYSYMBOL_ISZERO = 11,                    /* ISZERO  */
  YYSYMBOL_DEF = 12,                       /* DEF  */
  YYSYMBOL_EVAL = 13,                      /* EVAL  */
  YYSYMBOL_LAMBDA = 14,                    /* LAMBDA  */
  YYSYMBOL_ARROW = 15,                     /* ARROW  */
  YYSYMBOL_COLON = 16,                     /* COLON  */
  YYSYMBOL_DOT = 17,                       /* DOT  */
  YYSYMBOL_ASSIGN = 18,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 19,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 20,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 21,                    /* RPAREN  */
  YYSYMBOL_PLUS = 22,                      /* PLUS  */
  YYSYMBOL_MINUS = 23,                     /* MINUS  */
  YYSYMBOL_MULT = 24,                      /* MULT  */
  YYSYMBOL_DIV = 25,                       /* DIV  */
  YYSYMBOL_IF = 26,                        /* IF  */
  YYSYMBOL_THEN = 27,                      /* THEN  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_programa = 30,                  /* programa  */
  YYSYMBOL_lista_sentencias = 31,          /* lista_sentencias  */
  YYSYMBOL_sentencia = 32,                 /* sentencia  */
  YYSYMBOL_definicion = 33,                /* definicion  */
  YYSYMBOL_34_1 = 34,                      /* $@1  */
  YYSYMBOL_definicion_var = 35,            /* definicion_var  */
  YYSYMBOL_cuerpo_lambda = 36,             /* cuerpo_lambda  */
  YYSYMBOL_evaluacion = 37,                /* evaluacion  */
  YYSYMBOL_ifelse = 38,                    /* ifelse  */
  YYSYMBOL_funcion_anonima = 39,           /* funcion_anonima  */
  YYSYMBOL_expresion = 40,                 /* expresion  */
  YYSYMBOL_termino = 41,                   /* termino  */
  YYSYMBOL_tipo = 42                       /* tipo  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  37
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  89

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    73,    73,    77,    78,    82,    83,    84,    87,    95,
      95,   115,   128,   129,   133,   143,   153,   168,   169,   170,
     171,   172,   174,   178,   181,   189,   190,   191,   192,   195,
     198,   202,   210,   222,   223,   224,   225,   226
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "FLOAT_LIT",
  "INT_LIT", "TYPE_INT", "TYPE_FLOAT", "TYPE_BOOL", "SUCC", "PRED",
  "ISZERO", "DEF", "EVAL", "LAMBDA", "ARROW", "COLON", "DOT", "ASSIGN",
  "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS", "MULT", "DIV", "IF",
  "THEN", "ELSE", "$accept", "programa", "lista_sentencias", "sentencia",
  "definicion", "$@1", "definicion_var", "cuerpo_lambda", "evaluacion",
  "ifelse", "funcion_anonima", "expresion", "termino", "tipo", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   -15,   -41,   -41,    15,    16,    30,    10,   143,    20,
     143,   143,    27,    29,   -41,   -41,   -41,   -41,   -41,   -41,
     169,   -41,    -1,   143,   143,   143,    33,    36,   192,    38,
     215,   118,   -41,   -41,   -41,   -41,   143,   143,   143,   143,
     -41,   -41,   -41,   -41,    -1,     3,   238,   261,   284,   -41,
      -1,   -41,    -1,   -41,   143,   353,   353,   365,   365,    -7,
      -1,   143,   -41,   -41,   -41,   156,     7,    -6,    92,   -41,
      41,   307,    55,    40,   330,   143,   143,   143,   -41,    44,
     -41,   330,   330,   330,    -1,     9,   156,   -41,   330
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    25,    27,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     5,     7,     6,    23,    29,
       0,    17,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,     1,     4,    25,     8,     0,     0,     0,     0,
      22,    33,    35,    34,     0,     0,     0,     0,     0,     9,
       0,    14,     0,    28,     0,    18,    19,    20,    21,     0,
       0,     0,    30,    31,    32,     0,     0,     0,     0,    36,
      37,     0,     0,     0,    13,     0,     0,     0,    11,     0,
      10,    24,    16,    15,     0,     0,     0,    12,    13
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -41,    48,   -41,   -41,   -41,   -24,   -41,   -41,
     -41,    -8,    17,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    65,    16,    73,    17,    18,
      19,    20,    21,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      28,    22,    30,    31,    59,    41,    42,    43,    60,    60,
      66,    76,    67,    26,    69,    46,    47,    48,    60,    44,
      70,    61,    60,    29,    60,    75,    86,    32,    55,    56,
      57,    58,     1,     2,     3,    23,    24,    40,     4,     5,
       6,     7,     8,     9,    85,    40,    68,    40,    40,    10,
      25,    49,    50,    71,    52,    11,    60,    74,    79,    80,
      84,    33,    87,    40,    40,    40,     0,    81,    82,    83,
       0,     0,    40,    40,    40,    40,     0,     0,    88,     0,
       0,     0,     0,     0,     0,    40,     0,     0,    40,     0,
       0,    40,     0,     0,     0,    34,     2,     3,    40,    40,
      40,     4,     5,     6,     0,    40,     9,     0,     0,     0,
       0,     0,    10,     0,    36,    37,    38,    39,     0,     0,
      77,    34,     2,     3,     0,     0,     0,     4,     5,     6,
       0,     0,     9,     0,     0,     0,     0,     0,    10,     0,
      36,    37,    38,    39,     0,    54,    27,     2,     3,     0,
       0,     0,     4,     5,     6,     0,     0,     9,     0,    27,
       2,     3,     0,    10,     0,     4,     5,     6,     0,    11,
      72,     0,    34,     2,     3,     0,    10,     0,     4,     5,
       6,     0,    11,     9,     0,     0,     0,     0,    35,    10,
       0,    36,    37,    38,    39,    34,     2,     3,     0,     0,
       0,     4,     5,     6,     0,     0,     9,     0,     0,     0,
       0,    51,    10,     0,    36,    37,    38,    39,    34,     2,
       3,     0,     0,     0,     4,     5,     6,     0,     0,     9,
       0,     0,     0,     0,     0,    10,    53,    36,    37,    38,
      39,    34,     2,     3,     0,     0,     0,     4,     5,     6,
       0,     0,     9,     0,     0,     0,     0,     0,    10,    62,
      36,    37,    38,    39,    34,     2,     3,     0,     0,     0,
       4,     5,     6,     0,     0,     9,     0,     0,     0,     0,
       0,    10,    63,    36,    37,    38,    39,    34,     2,     3,
       0,     0,     0,     4,     5,     6,     0,     0,     9,     0,
       0,     0,     0,     0,    10,    64,    36,    37,    38,    39,
      34,     2,     3,     0,     0,     0,     4,     5,     6,     0,
       0,     9,     0,     0,     0,     0,    78,    10,     0,    36,
      37,    38,    39,    34,     2,     3,     0,     0,     0,     4,
       5,     6,     0,     0,     9,     0,     0,     0,     0,     0,
      10,     0,    36,    37,    38,    39,    34,     2,     3,     0,
       0,     0,     4,     5,     6,     0,     0,     9,    34,     2,
       3,     0,     0,    10,     4,     5,     6,    38,    39,     9,
       0,     0,     0,     0,     0,    10
};

static const yytype_int8 yycheck[] =
{
       8,    16,    10,    11,    44,     6,     7,     8,    15,    15,
      50,    17,    52,     3,    21,    23,    24,    25,    15,    20,
      60,    18,    15,     3,    15,    18,    17,     0,    36,    37,
      38,    39,     3,     4,     5,    20,    20,    20,     9,    10,
      11,    12,    13,    14,    84,    28,    54,    30,    31,    20,
      20,    18,    16,    61,    16,    26,    15,    65,     3,    19,
      16,    13,    86,    46,    47,    48,    -1,    75,    76,    77,
      -1,    -1,    55,    56,    57,    58,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    -1,
      -1,    74,    -1,    -1,    -1,     3,     4,     5,    81,    82,
      83,     9,    10,    11,    -1,    88,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    22,    23,    24,    25,    -1,    -1,
      28,     3,     4,     5,    -1,    -1,    -1,     9,    10,    11,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      22,    23,    24,    25,    -1,    27,     3,     4,     5,    -1,
      -1,    -1,     9,    10,    11,    -1,    -1,    14,    -1,     3,
       4,     5,    -1,    20,    -1,     9,    10,    11,    -1,    26,
      14,    -1,     3,     4,     5,    -1,    20,    -1,     9,    10,
      11,    -1,    26,    14,    -1,    -1,    -1,    -1,    19,    20,
      -1,    22,    23,    24,    25,     3,     4,     5,    -1,    -1,
      -1,     9,    10,    11,    -1,    -1,    14,    -1,    -1,    -1,
      -1,    19,    20,    -1,    22,    23,    24,    25,     3,     4,
       5,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,     3,     4,     5,    -1,    -1,    -1,     9,    10,    11,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,     3,     4,     5,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    14,    -1,    -1,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,     3,     4,     5,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
       3,     4,     5,    -1,    -1,    -1,     9,    10,    11,    -1,
      -1,    14,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,
      23,    24,    25,     3,     4,     5,    -1,    -1,    -1,     9,
      10,    11,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    22,    23,    24,    25,     3,     4,     5,    -1,
      -1,    -1,     9,    10,    11,    -1,    -1,    14,     3,     4,
       5,    -1,    -1,    20,     9,    10,    11,    24,    25,    14,
      -1,    -1,    -1,    -1,    -1,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     9,    10,    11,    12,    13,    14,
      20,    26,    30,    31,    32,    33,    35,    37,    38,    39,
      40,    41,    16,    20,    20,    20,     3,     3,    40,     3,
      40,    40,     0,    32,     3,    19,    22,    23,    24,    25,
      41,     6,     7,     8,    20,    42,    40,    40,    40,    18,
      16,    19,    16,    21,    27,    40,    40,    40,    40,    42,
      15,    18,    21,    21,    21,    34,    42,    42,    40,    21,
      42,    40,    14,    36,    40,    18,    17,    28,    19,     3,
      19,    40,    40,    40,    16,    42,    17,    36,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    31,    31,    32,    32,    32,    32,    34,
      33,    35,    36,    36,    37,    38,    39,    40,    40,    40,
      40,    40,    40,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    42,    42,    42,    42,    42
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     2,     0,
       6,     6,     6,     1,     3,     6,     6,     1,     3,     3,
       3,     3,     2,     1,     5,     1,     1,     1,     3,     1,
       4,     4,     4,     1,     1,     1,     3,     3
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* sentencia: expresion SEMICOLON  */
#line 88 "lambda.y"
    {   
        printf("print(%s)\n", (yyvsp[-1].sval));
    }
#line 1253 "lambda.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 95 "lambda.y"
                  { limpiar_args(); }
#line 1259 "lambda.tab.c"
    break;

  case 10: /* definicion: DEF ID ASSIGN $@1 cuerpo_lambda SEMICOLON  */
#line 96 "lambda.y"
    {
        printf("# Funcion generada\n");
        if (contador_args > 0) {
            printf("def %s(", (yyvsp[-4].sval));
            for (int i = contador_args - 1; i >= 0; i--) {
                printf("%s", lista_argumentos[i]);
                if (i > 0) printf(", "); 
            }
            printf("):\n");
            printf("    return %s\n\n", (yyvsp[-1].sval)); 
        } 
        else {
            printf("%s = %s\n\n", (yyvsp[-4].sval), (yyvsp[-1].sval));
        }
    }
#line 1279 "lambda.tab.c"
    break;

  case 11: /* definicion_var: ID COLON tipo ASSIGN expresion SEMICOLON  */
#line 116 "lambda.y"
    {
        if (strcmp((yyvsp[-3].sval), "Nat") == 0 && strchr((yyvsp[-1].sval), '.') != NULL) {
            fprintf(stderr, "Error de Tipos: Asignacion de decimal a Nat en variable '%s'.\n", (yyvsp[-5].sval));
            YYABORT;
        }
        
        printf("%s = %s\n\n", (yyvsp[-5].sval), (yyvsp[-1].sval)); 
    }
#line 1292 "lambda.tab.c"
    break;

  case 12: /* cuerpo_lambda: LAMBDA ID COLON tipo DOT cuerpo_lambda  */
#line 128 "lambda.y"
                                           { agregar_arg((yyvsp[-4].sval)); (yyval.sval) = (yyvsp[0].sval); }
#line 1298 "lambda.tab.c"
    break;

  case 13: /* cuerpo_lambda: expresion  */
#line 129 "lambda.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 1304 "lambda.tab.c"
    break;

  case 14: /* evaluacion: EVAL expresion SEMICOLON  */
#line 134 "lambda.y"
    {
        printf("print(%s)\n", (yyvsp[-1].sval));
    }
#line 1312 "lambda.tab.c"
    break;

  case 15: /* ifelse: IF expresion THEN expresion ELSE expresion  */
#line 144 "lambda.y"
    {
        (yyval.sval) = unir3("(", unir3((yyvsp[-2].sval), " if ", unir3((yyvsp[-4].sval), " else ", (yyvsp[0].sval))), ")");
    }
#line 1320 "lambda.tab.c"
    break;

  case 16: /* funcion_anonima: LAMBDA ID COLON tipo DOT expresion  */
#line 154 "lambda.y"
    {
        /* Traduce a Python: (lambda x: cuerpo) */
        char* cabecera = (yyvsp[-4].sval);
        char* cuerpo = unir(":=", (yyvsp[0].sval));
        
        /* Paréntesis importantes para proteger la precedencia */
        (yyval.sval) = unir3("(", unir(cabecera, cuerpo), ")");
        
        free(cabecera); free(cuerpo);
    }
#line 1335 "lambda.tab.c"
    break;

  case 17: /* expresion: termino  */
#line 168 "lambda.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 1341 "lambda.tab.c"
    break;

  case 18: /* expresion: expresion PLUS expresion  */
#line 169 "lambda.y"
                                { (yyval.sval) = unir3((yyvsp[-2].sval), " + ", (yyvsp[0].sval)); }
#line 1347 "lambda.tab.c"
    break;

  case 19: /* expresion: expresion MINUS expresion  */
#line 170 "lambda.y"
                                { (yyval.sval) = unir3((yyvsp[-2].sval), " - ", (yyvsp[0].sval)); }
#line 1353 "lambda.tab.c"
    break;

  case 20: /* expresion: expresion MULT expresion  */
#line 171 "lambda.y"
                                { (yyval.sval) = unir3((yyvsp[-2].sval), " * ", (yyvsp[0].sval)); }
#line 1359 "lambda.tab.c"
    break;

  case 21: /* expresion: expresion DIV expresion  */
#line 172 "lambda.y"
                                { (yyval.sval) = unir3((yyvsp[-2].sval), " / ", (yyvsp[0].sval)); }
#line 1365 "lambda.tab.c"
    break;

  case 22: /* expresion: expresion termino  */
#line 174 "lambda.y"
                                { 
        (yyval.sval) = unir3(unir((yyvsp[-1].sval), "("), (yyvsp[0].sval), ")");
    }
#line 1373 "lambda.tab.c"
    break;

  case 23: /* expresion: ifelse  */
#line 178 "lambda.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 1379 "lambda.tab.c"
    break;

  case 24: /* expresion: ID COLON tipo ASSIGN expresion  */
#line 182 "lambda.y"
    {
        
        (yyval.sval) = unir3("(", unir3((yyvsp[-4].sval), " := ", (yyvsp[0].sval)), ")");
    }
#line 1388 "lambda.tab.c"
    break;

  case 25: /* termino: ID  */
#line 189 "lambda.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 1394 "lambda.tab.c"
    break;

  case 26: /* termino: INT_LIT  */
#line 190 "lambda.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 1400 "lambda.tab.c"
    break;

  case 27: /* termino: FLOAT_LIT  */
#line 191 "lambda.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 1406 "lambda.tab.c"
    break;

  case 28: /* termino: LPAREN expresion RPAREN  */
#line 192 "lambda.y"
                                { (yyval.sval) = unir3("(", (yyvsp[-1].sval), ")"); }
#line 1412 "lambda.tab.c"
    break;

  case 29: /* termino: funcion_anonima  */
#line 195 "lambda.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 1418 "lambda.tab.c"
    break;

  case 30: /* termino: SUCC LPAREN expresion RPAREN  */
#line 199 "lambda.y"
    {
        (yyval.sval) = unir3("(", unir3((yyvsp[-1].sval), " + ", "1"), ")");
    }
#line 1426 "lambda.tab.c"
    break;

  case 31: /* termino: PRED LPAREN expresion RPAREN  */
#line 203 "lambda.y"
    {
        if(strcmp((yyvsp[-1].sval), "0")==0){
            fprintf(stderr, "Error: PRED no puede aplicarse a 0 (Linea %d)\n", yylineno);
            YYABORT;
        }
        (yyval.sval) = unir3("(", unir3((yyvsp[-1].sval), " - ", "1"), ")");
    }
#line 1438 "lambda.tab.c"
    break;

  case 32: /* termino: ISZERO LPAREN expresion RPAREN  */
#line 211 "lambda.y"
    {
        if (strstr((yyvsp[-1].sval), "==") != NULL) {
            fprintf(stderr, "Error de Tipos: isZero espera un Numero, pero recibió una expresión Booleana (Linea %d)\n", yylineno);
            YYABORT;
        }
        (yyval.sval) = unir3("(", unir3((yyvsp[-1].sval), " == ", "0"), ")");
    }
#line 1450 "lambda.tab.c"
    break;

  case 33: /* tipo: TYPE_INT  */
#line 222 "lambda.y"
                         { (yyval.sval) = (yyvsp[0].sval); }
#line 1456 "lambda.tab.c"
    break;

  case 34: /* tipo: TYPE_BOOL  */
#line 223 "lambda.y"
                         { (yyval.sval) = (yyvsp[0].sval); }
#line 1462 "lambda.tab.c"
    break;

  case 35: /* tipo: TYPE_FLOAT  */
#line 224 "lambda.y"
                         { (yyval.sval) = (yyvsp[0].sval); }
#line 1468 "lambda.tab.c"
    break;

  case 36: /* tipo: LPAREN tipo RPAREN  */
#line 225 "lambda.y"
                         { (yyval.sval) = (yyvsp[-1].sval); }
#line 1474 "lambda.tab.c"
    break;

  case 37: /* tipo: tipo ARROW tipo  */
#line 226 "lambda.y"
                         { (yyval.sval) = unir3((yyvsp[-2].sval), " -> ", (yyvsp[0].sval)); }
#line 1480 "lambda.tab.c"
    break;


#line 1484 "lambda.tab.c"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 229 "lambda.y"


extern FILE *yyin;

void yyerror(const char *s) {
    fprintf(stderr, "Error sintactico en linea %d: %s antes del token '%s'\n", 
            yylineno, s, yytext);
}

int main(int argc, char **argv) {
    printf("import math\n");
    printf("from functools import reduce\n\n");

    yylineno = 1;
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror(argv[1]); return 1; }
    } else {
        yyin = stdin;
    }

    int res = yyparse();

    if (yyin != stdin) fclose(yyin);
    
    return res;
}
