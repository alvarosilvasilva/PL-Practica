%{
#include <string.h>
#include <stdlib.h>
#include "lambda.tab.h"

extern int yylineno; 
void yyerror(const char *s);
%}

%option yylineno

/* Declaramos un estado exclusivo para manejar el bloque de comentario */
%x COMENTARIO

DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO}|_)*
ENTERO      {DIGITO}+
DECIMAL     {DIGITO}+\.{DIGITO}+

%%

    /* --------------------------------------------------------- */
    /* 1. COMENTARIOS ESTILO SHELL (#) -> SE IGNORAN ("pasar de ellos") */
    /* --------------------------------------------------------- */
"#"[^\n]* ; 


    /* --------------------------------------------------------- */
    /* 2. COMENTARIOS ESTILO C -> TRADUCCIÓN A PYTHON */
    /* --------------------------------------------------------- */
    /* Al encontrar "/*", iniciamos estado COMENTARIO e imprimimos '#' */
"/*"            { BEGIN(COMENTARIO); printf("# "); }

    /* Si hay salto de línea dentro del comentario, cerramos la línea python anterior y abrimos otro '#' */
<COMENTARIO>\n  { printf("\n# "); }

    /* Cualquier otro carácter dentro del comentario se imprime tal cual */
<COMENTARIO>.   { printf("%s", yytext); }

    /* Al encontrar el cierre, volvemos al estado inicial y damos un salto de linea */
<COMENTARIO>"*/" { BEGIN(INITIAL); printf("\n"); }


    /* --------------------------------------------------------- */
    /* REGLAS ESTÁNDAR (Mantenemos tu código original abajo)     */
    /* --------------------------------------------------------- */

[ \t\r\n]+      ; /* Ignoramos espacios en blanco y saltos de línea normales */

"let"           { return LET; }
"in"            { return IN; }
"def"           { return DEF; }
"eval"          { return EVAL; }
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

.               { fprintf(stderr,"Error léxico en línea %d: Caracter inesperado '%s'\n",yylineno,yytext); }

%%