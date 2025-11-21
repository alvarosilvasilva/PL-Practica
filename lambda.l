%{
#include <string.h>
#include <stdlib.h>

#include "lambda.tab.h"

extern int yylineno; 

void yyerror(const char *s);
%}

%option yylineno


DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO}|_)*
ENTERO      {DIGITO}+
DECIMAL     {DIGITO}+\.{DIGITO}+

%%

[ \t\r\n]+      ; /* Ignoramos espacios en blanco y saltos de línea */

"let"           {return LET;}
"in"            {return IN;}
"def"           { return DEF; }
"eval"          { return EVAL; }
"Nat"           { yylval.sval = strdup(yytext); return TYPE_INT; }
"Float"         { yylval.sval =strdup(yytext); return TYPE_FLOAT; }
"Bool"          { yylval.sval = strdup(yytext); return TYPE_BOOL; }
"succ"          { return SUCC;}
"pred"          { return PRED;}
"isZero"        {return ISZERO;}
"if"             { return IF;}
"then"           { return THEN;}
"else"           { return ELSE;}


"lambda."        { return LAMBDA; }  
"->"            { return ARROW; }
":"             { return COLON; }
"."             { return DOT; }
"="             { return ASSIGN; }
";;"            { return SEMICOLON; }


"("             { return LPAREN; }
")"             { return RPAREN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }


{DECIMAL}       { yylval.sval = strdup(yytext); return FLOAT_LIT; }
{ENTERO}        { yylval.sval = strdup(yytext); return INT_LIT; }
{ID}            { yylval.sval = strdup(yytext); return ID; }


.               { 
                  fprintf(stderr,"Error léxico en línea %d:Cáracter inesperado '%s'\n",yylineno,yytext);;
                }

%%