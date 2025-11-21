%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* lista_argumentos[100];
int contador_args = 0;
bool ifelse = false;

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
%}

/* --- ESTRUCTURA DE DATOS --- */
%union {
    char* sval; 
}

/* --- TOKENS --- */
%token <sval> ID NUMBER FLOAT_LIT INT_LIT TYPE_INT TYPE_FLOAT TYPE_BOOL SUCC PRED ISZERO
%token DEF EVAL LAMBDA ARROW COLON DOT ASSIGN SEMICOLON LET IN
%token LPAREN RPAREN PLUS MINUS MULT DIV IF THEN ELSE

/* --- TIPOS --- */
%type <sval> tipo expresion termino cuerpo_lambda ifelse

/* --- PRECEDENCIA --- */
%right ARROW
%left PLUS MINUS
%left MULT DIV
%left LPAREN RPAREN

%%

/* ========================================================================== */
/* GRAMÁTICA                                                                  */
/* ========================================================================== */

programa:
    lista_sentencias
    ;

lista_sentencias:
    sentencia
    | lista_sentencias sentencia
    ;

sentencia:
    definicion
    | evaluacion
    | definicion_var
    /* Regla para expresiones sueltas (IFs, sumas, etc.) terminadas en ;; */
    | expresion SEMICOLON 
    {   
        if(ifelse=false){
            printf("print(%s)\n", $1);
        }
    }
    ;

/* --- DEFINICIÓN GLOBAL DE FUNCIÓN (def f = ...) --- */
definicion:
    DEF ID ASSIGN { limpiar_args(); } cuerpo_lambda SEMICOLON
    {
        printf("# Funcion generada\n");
        if (contador_args > 0) {
            printf("def %s(", $2);
            for (int i = contador_args - 1; i >= 0; i--) {
                printf("%s", lista_argumentos[i]);
                if (i > 0) printf(", "); 
            }
            printf("):\n");
            printf("    return %s\n\n", $5); 
        } 
        else {
            printf("%s = %s\n\n", $2, $5);
        }
    }
    ;

/* --- ASIGNACIÓN GLOBAL (Variable estática) --- */
definicion_var:
    ID COLON tipo ASSIGN expresion SEMICOLON
    {
        printf("%s = %s\n\n", $1, $5); 
    }
    ;

cuerpo_lambda:
    LAMBDA ID COLON tipo DOT cuerpo_lambda { agregar_arg($2); $$ = $6; }
    | expresion { $$ = $1; }
    ;

evaluacion:
    EVAL expresion SEMICOLON
    {
        printf("print(%s)\n", $2);
    }
    ;

/* --- CONDICIONAL TERNARIO (ANIDABLE) --- */
ifelse: 
    IF expresion THEN expresion ELSE expresion 
    {
        ifelse = true;
        $$ = unir3("(", unir3($4, " if ", unir3($2, " else ", $6)), ")");

        printf("%s", $4);
        printf("if(%s)", $2);
        printf(" else(%s)\n", $6);
    }
    ;

/* --- EXPRESIONES --- */
expresion:
    termino                     { $$ = $1; }
    | expresion PLUS expresion  { $$ = unir3($1, " + ", $3); }
    | expresion MINUS expresion { $$ = unir3($1, " - ", $3); }
    | expresion MULT expresion  { $$ = unir3($1, " * ", $3); }
    | expresion DIV expresion   { $$ = unir3($1, " / ", $3); }
    
    /* Aplicación de función */
    | expresion termino         { 
        $$ = unir3(unir($1, "("), $2, ")");
    }
    
    /* Condicional */
    | ifelse                    { $$ = $1; }

    /* NUEVA REGLA: Asignación en línea (Expresión Walrus) 
       Permite: if ... then x:Nat = 1 else ...
       Traducción: (x := 1)
    */
    | ID COLON tipo ASSIGN expresion 
    {
        $$ = unir3("(", unir3($1, " := ", $5), ")");
    }
    ;

termino:
    ID                          { $$ = $1; }
    | INT_LIT                   { $$ = $1; }
    | FLOAT_LIT                 { $$ = $1; }
    | LPAREN expresion RPAREN   { $$ = unir3("(", $2, ")"); }
    
    /* Funciones primitivas */
    | SUCC LPAREN expresion RPAREN 
    {
        $$ = unir3("(", unir3($3, " + ", "1"), ")");
    }
    | PRED LPAREN expresion RPAREN 
    {
        $$ = unir3("(", unir3($3, " - ", "1"), ")");
    }
    | ISZERO LPAREN expresion RPAREN
    {
        $$ = unir3("(", unir3($3, " == ", "0"), ")");
    }
    ; 

/* --- TIPOS --- */
tipo:
    TYPE_INT             { $$ = $1; }
    | TYPE_BOOL          { $$ = $1; }
    | TYPE_FLOAT         { $$ = $1; }
    | LPAREN tipo RPAREN { $$ = $2; }
    | tipo ARROW tipo    { $$ = unir3($1, " -> ", $3); }
    ;

%%

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