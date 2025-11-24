%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <strings.h> /* Necesario para strcasecmp en Linux */
#include <ctype.h>

/* --- VARIABLES GLOBALES --- */
char* lista_argumentos[100];
int contador_args = 0;

extern int yylineno;
extern int yylex();
extern char* yytext;
void yyerror(const char *s);

/* --- FUNCIONES AUXILIARES --- */
char* concat(int count, ...) {
    va_list ap;
    int len = 0;
    va_start(ap, count);
    for(int i = 0; i < count; i++) {
        char* s = va_arg(ap, char*);
        if(s) len += strlen(s);
    }
    va_end(ap);

    char* res = malloc(len + 1);
    if (!res) { fprintf(stderr, "Error de memoria\n"); exit(1); }
    res[0] = '\0';

    va_start(ap, count);
    for(int i = 0; i < count; i++) {
        char* s = va_arg(ap, char*);
        if(s) strcat(res, s);
    }
    va_end(ap);
    return res;
}

char* unir3(const char* s1, const char* s2, const char* s3) { return concat(3, s1, s2, s3); }

void limpiar_args() { contador_args = 0; }
void agregar_arg(char* nombre) {
    if (contador_args < 100) {
        lista_argumentos[contador_args] = strdup(nombre); 
        contador_args++;
    }
}
%}

%union { char* sval; }

%token <sval> ID FLOAT_LIT INT_LIT TYPE_INT TYPE_FLOAT TYPE_BOOL SUCC PRED ISZERO
%token DEF EVAL LAMBDA ARROW COLON DOT ASSIGN SEMICOLON LET IN COMMA
%token LPAREN RPAREN PLUS MINUS MULT DIV IF THEN ELSE

%type <sval> tipo expresion termino cuerpo_lambda ifelse funcion_anonima let_exp parametro lista_parametros

/* PRECEDENCIA Y ASOCIATIVIDAD */
%right ARROW
%nonassoc LET IN IF THEN ELSE 
%left PLUS MINUS
%left MULT DIV
%left LPAREN RPAREN

%%

/* ========================================================================== */
/* GRAMÁTICA PRINCIPAL                                                        */
/* ========================================================================== */

programa: lista_sentencias ;

lista_sentencias: sentencia | lista_sentencias sentencia ;

sentencia:
    definicion
    | evaluacion
    | definicion_var
    | expresion SEMICOLON { 
        if ($1 != NULL) {
            printf("%s\n", $1); 
            free($1); 
        }
    }
    
    /* Error Sintáctico General: Basura suelta antes de un punto y coma */
    | error SEMICOLON 
    { 
        yyerrok; 
        YYABORT; /* Paramos para evitar problemas de memoria */
    }
    ;

/* Argumentos para funciones estilo C/Python */
parametro: ID COLON tipo { agregar_arg($1); } ;
lista_parametros: parametro | parametro COMMA lista_parametros ;

/* --- DEFINICIONES DE FUNCIONES --- */
definicion:
    /* 1. Estilo Lambda: def f = lambda x... */
    DEF ID ASSIGN cuerpo_lambda SEMICOLON
    {
        if (contador_args > 0) {
            printf("def %s(", $2);
            for (int i = contador_args - 1; i >= 0; i--) {
                printf("%s", lista_argumentos[i]);
                if (i > 0) printf(", ");
            }
            printf("):\n    return %s\n\n", $4); 
            free($4);
        } else {
            printf("%s = %s\n\n", $2, $4);
            free($4);
        }
        limpiar_args(); 
    }
    /* 2. Estilo Python: def f(x:T) = ... */
    | DEF ID LPAREN { limpiar_args(); } lista_parametros RPAREN ASSIGN expresion SEMICOLON
    {
        printf("def %s(", $2);
        for (int i = 0; i < contador_args; i++) {
            printf("%s", lista_argumentos[i]);
            if (i < contador_args - 1) printf(", ");
        }
        printf("):\n    return %s\n\n", $8);
        free($8);
    }
    
    /* ERROR SINTÁCTICO: Definición rota */
    | DEF ID error SEMICOLON
    {
        fprintf(stderr, "Error Sintactico: Definicion de funcion mal formada. Falta '=' o el cuerpo de la funcion (Linea %d)\n", yylineno);
        limpiar_args();
        YYABORT; /* IMPORTANTE: Parar ejecución */
    }
    ;

/* --- DEFINICIÓN DE VARIABLES GLOBALES (Con Chequeo de Tipos) --- */
definicion_var:
    ID COLON TYPE_INT ASSIGN expresion SEMICOLON
    {
        if (strchr($5, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: Asignación de Float a Nat en '%s' (Linea %d)\n", $1, yylineno);
            YYABORT;
        }
        if (strcasecmp($5, "True") == 0 || strcasecmp($5, "False") == 0 || strstr($5, "==") != NULL) {
            fprintf(stderr, "Error de Tipos: Asignación de Booleano a Nat en '%s' (Linea %d)\n", yylineno);
            YYABORT;
        }
        printf("%s = %s\n\n", $1, $5); 
    }
    | ID COLON TYPE_FLOAT ASSIGN expresion SEMICOLON
    {
        if (strcasecmp($5, "True") == 0 || strcasecmp($5, "False") == 0 || strstr($5, "==") != NULL) {
             fprintf(stderr, "Error de Tipos: Asignación de Booleano a Float en '%s' (Linea %d).\n", $1, yylineno);
             YYABORT;
        }
        printf("%s = %s\n\n", $1, $5);
    }
    | ID COLON TYPE_BOOL ASSIGN expresion SEMICOLON
    {
        if (strstr($5, "==") == NULL && strcasecmp($5, "True") != 0 && strcasecmp($5, "False") != 0) {
            fprintf(stderr, "Error de Tipos: Asignacion de No Booleano a Bool en variable '%s' (Linea %d).\n", $1, yylineno);
            YYABORT;
        }
        printf("%s = %s\n\n", $1, $5);
    }
    ;

/* --- CUERPO DE LAMBDA (RECURSIVO) --- */
cuerpo_lambda:
    LAMBDA ID COLON tipo DOT cuerpo_lambda { agregar_arg($2); $$ = $6; }
    | expresion { $$ = $1; }
    ;

/* --- EVALUACIÓN --- */
evaluacion:
    EVAL expresion SEMICOLON { printf("%s\n", $2); free($2); }
    
    /* ERROR SINTÁCTICO: Eval incompleto */
    | EVAL error SEMICOLON
    {
        fprintf(stderr, "Error Sintactico: Instruccion 'eval' mal formada o expresion invalida (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* --- CONDICIONAL IF-ELSE --- */
ifelse: 
    /* Caso Correcto */
    IF expresion THEN expresion ELSE expresion 
    { $$ = concat(7, "(", $4, " if ", $2, " else ",$6, ")"); }
    
    /* ERROR SINTÁCTICO: Falta el ELSE */
    | IF expresion THEN expresion error 
    {
        fprintf(stderr, "Error Sintactico: Estructura 'if' incompleta. Falta la rama 'else' (Linea %d)\n", yylineno);
        YYABORT;
    }
    
    /* ERROR SINTÁCTICO: Falta el THEN */
    | IF expresion error
    {
        fprintf(stderr, "Error Sintactico: Estructura 'if' mal formada. Falta 'then' o la condicion es invalida (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* --- EXPRESIÓN LET --- */
let_exp:
    /* Caso Correcto */
    LET ID COLON tipo ASSIGN expresion IN expresion
    {
        $$ = concat(6, "(", $2 , " := ", $6, "; ", $8, ")");
    }
    
    /* ERRORES SINTÁCTICOS DEL LET */
    /* Usamos YYABORT para evitar que $$ quede con basura y cause Segmentation Fault arriba */
    | LET ID error 
    {
        fprintf(stderr, "Error Sintactico: 'let' incompleto. Falta ': Tipo' tras '%s' (Linea %d)\n", $2, yylineno);
        YYABORT; 
    }
    | LET ID COLON tipo error
    {
        fprintf(stderr, "Error Sintactico: 'let' incompleto. Falta '=' despues del tipo (Linea %d)\n", yylineno);
        YYABORT;
    }
    | LET ID COLON tipo ASSIGN expresion error
    {
        fprintf(stderr, "Error Sintactico: 'let' incompleto. Falta 'in' o el cuerpo final (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* --- FUNCIONES ANÓNIMAS --- */
funcion_anonima:
    /* Caso Correcto */
    LAMBDA ID COLON tipo DOT expresion
    { $$ = concat(5, "(lambda ", $2, ": ", $6, ")"); }
    
    /* ERROR SINTÁCTICO: Falta el punto */
    | LAMBDA ID COLON tipo error
    {
        fprintf(stderr, "Error Sintactico: Lambda mal formada. Falta el punto '.' despues del tipo (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* --- EXPRESIONES Y TÉRMINOS --- */
expresion:
    termino  
    | termino COLON tipo { $$ = $1; }
    | expresion PLUS expresion { $$ = unir3($1, " + ", $3); }
    | expresion MINUS expresion { $$ = unir3($1, " - ", $3); }
    | expresion MULT expresion { $$ = unir3($1, " * ", $3); }
    | expresion DIV expresion { 
        if(strcmp($3, "0") == 0 || strcmp($3, "0.0") == 0) {
            fprintf(stderr, "Error de Ejecución: División por cero (Linea %d)\n", yylineno);
            YYABORT;
        }
        $$ = unir3($1, " / ", $3); }
    | expresion termino { $$ = concat(4, $1, "(", $2, ")"); }
    | ifelse { $$ = $1; }
    | let_exp { $$ = $1; } 
    ;

termino:
    ID { $$ = $1; }
    | INT_LIT { $$ = $1; }
    | FLOAT_LIT { $$ = $1; }
    
    /* Caso Correcto Paréntesis */
    | LPAREN expresion RPAREN { $$ = concat(3, "(", $2, ")"); }
    
    /* ERROR SINTÁCTICO: Falta cerrar paréntesis */
    | LPAREN expresion error
    {
        fprintf(stderr, "Error Sintactico: Falta el parentesis de cierre ')' (Linea %d)\n", yylineno);
        YYABORT;
    }

    | funcion_anonima { $$ = $1; }
    
    /* Primitivas con Chequeo de Tipos */
    | SUCC LPAREN expresion RPAREN { $$ = concat(3, "(", $3, " + 1)"); }
    
    | PRED LPAREN expresion RPAREN { 
        if (strchr($3, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: PRED no puede aplicarse a un Float (Linea %d)\n", yylineno);
            YYABORT;
        }
        if (strcasecmp($3, "True") == 0 || strcasecmp($3, "False") == 0 || strstr($3, "==") != NULL) {
            fprintf(stderr, "Error de Tipos: PRED no puede aplicarse a un Bool (Linea %d)\n", yylineno);
            YYABORT;
        }
        if (strcmp($3, "0") == 0) {
           fprintf(stderr, "Error Semantico: PRED no puede aplicarse a 0 (Linea %d)\n", yylineno);
           YYABORT;
        }
        $$ = concat(3, "(", $3, " - 1)");
    }

    | ISZERO LPAREN expresion RPAREN {
        if (strchr($3, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: isZero no puede aplicarse a un Float (Linea %d)\n", yylineno);
            YYABORT;
        }
        if (strcasecmp($3, "True") == 0 || strcasecmp($3, "False") == 0 || strstr($3, "==") != NULL) {
            fprintf(stderr, "Error de Tipos: isZero no puede aplicarse a un Bool (Linea %d)\n", yylineno);
            YYABORT;
        }
        $$ = concat(3, "(", $3, " == 0)"); 
    }
    ; 

tipo:
    TYPE_INT | TYPE_BOOL | TYPE_FLOAT 
    | LPAREN tipo RPAREN { $$ = $2; }
    | tipo ARROW tipo { $$ = concat(3, $1, " -> ", $3); }
    ;

%%

extern FILE *yyin;

void yyerror(const char *s) {
    /* Imprime el error estándar de Bison solo si no hemos impreso uno personalizado nosotros antes */
    fprintf(stderr, "Error de analisis (Bison) en linea %d: %s antes de '%s'\n", yylineno, s, yytext);
}

int main(int argc, char **argv) {
    printf("import math\n");
    printf("from functools import reduce\n\n");
    printf("# Codigo generado autolambda\n\n");

    yylineno = 1;

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    int res = yyparse();

    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return res;
}