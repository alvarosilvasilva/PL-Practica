%{
#include <string.h>
#include <stdlib.h>
#include "lambda.tab.h"

extern int yylineno; 
void yyerror(const char *s);
%}

%option yylineno
%x COMENTARIO

DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO}|_)*
ENTERO      {DIGITO}+
DECIMAL     {DIGITO}+\.{DIGITO}+

%%



"/*"            { BEGIN(COMENTARIO); printf("# "); }
<COMENTARIO>\n  { printf("\n# "); }
<COMENTARIO>.   { printf("%s", yytext); }
<COMENTARIO>"*/" { BEGIN(INITIAL); printf("\n"); }

[ \t\r\n]+      ; 


"def"           { return DEF; }
"eval"          { return EVAL; }
"let"           { return LET; }
"in"            { return IN; }
"Nat"           { yylval.sval = strdup(yytext); return TYPE_INT; }
"Float"         { yylval.sval = strdup(yytext); return TYPE_FLOAT; }
"Bool"          { yylval.sval = strdup(yytext); return TYPE_BOOL; }
"succ"          { return SUCC;}
"pred"          { return PRED;}
"isZero"        { return ISZERO;}
"if"            { return IF;}
"then"          { return THEN;}
"else"          { return ELSE;}

"lambda."       { return LAMBDA; }  
":"             { return COLON; }
"."             { return DOT; }
"="             { return ASSIGN; }
";;"            { return SEMICOLON; }
","             { return COMMA; }

"("             { return LPAREN; }
")"             { return RPAREN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }

{DECIMAL}       { yylval.sval = strdup(yytext); return FLOAT_LIT; }
{ENTERO}        { yylval.sval = strdup(yytext); return INT_LIT; }
{ID}            { yylval.sval = strdup(yytext); return ID; }

"-"{ENTERO}               { fprintf(stderr,"No se permiten enteros negativos \n"); exit(1);}

"-"{ENTERO}               { fprintf(stderr,"No se permiten decimales negativos \n"); exit(1);}


"#"               { fprintf(stderr,"Error lexico en linea %d: El comentario '%s'se hace con /* \n",yylineno,yytext); exit(1);}

.               { fprintf(stderr,"Error lexico en linea %d: Caracter inesperado '%s'\n",yylineno,yytext); exit(1);}

%%