%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

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

%type <sval> tipo expresion termino cuerpo_lambda ifelse funcion_anonima let_exp

/* PRECEDENCIA */
%right ARROW
%nonassoc LET IN IF THEN ELSE 
%left PLUS MINUS
%left MULT DIV
%left LPAREN RPAREN

%%

programa: lista_sentencias ;

lista_sentencias: sentencia | lista_sentencias sentencia ;

sentencia:
    definicion
    | evaluacion
    | definicion_var
    | expresion SEMICOLON { printf("%s\n", $1); free($1); }
    ;

/* Argumentos */
parametro: ID COLON tipo { agregar_arg($1); } ;
lista_parametros: parametro | parametro COMMA lista_parametros ;

definicion:
    /* Estilo Lambda Clasico: def f = lambda x... */
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
    /* Estilo C/Python: def f(x:T) = ... */
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
    ;

/* REGLA CORREGIDA Y UNIFICADA */
definicion_var:
    ID COLON TYPE_INT ASSIGN expresion SEMICOLON
    {
        

        if (strchr($5, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: Asignación de Float a Nat en '%s' (Linea %d)\n", $1, yylineno);
            YYERROR;
        }

        if (strcasecmp($5, "True") == 0 || strcasecmp($5, "False") == 0) {
            fprintf(stderr, "Error de Tipos: Asignación de Booleano (True/False) a Nat en '%s' (Linea %d)\n", $1, yylineno);
            YYERROR;
        }
        
        printf("%s = %s\n\n", $1, $5); 
        
    }
    | ID COLON TYPE_FLOAT ASSIGN expresion SEMICOLON
    {
        if (strcasecmp($5, "True") == 0 || strcasecmp($5, "False") == 0 || strstr($5, "==") != NULL) {
             fprintf(stderr, "Error de Tipos: Asignación de Booleano a Float en '%s' (Linea %d).\n", $1, yylineno);
             YYERROR;
        }
        printf("%s = %s\n\n", $1, $5);
    }
    | ID COLON TYPE_BOOL ASSIGN expresion SEMICOLON
    {
        if (strstr($5, "==") == NULL && strcasecmp($5, "True") != 0 && strcasecmp($5, "False") != 0) {
            fprintf(stderr, "Error de Tipos: Asignacion de No Booleano a Bool en variable '%s' (Linea %d).\n", $1, yylineno);
            YYERROR;
        }
        
        printf("%s = %s\n\n", $1, $5);
    }
    ;

cuerpo_lambda:
    LAMBDA ID COLON tipo DOT cuerpo_lambda { agregar_arg($2); $$ = $6; }
    | expresion { $$ = $1; }
    ;

evaluacion:
    EVAL expresion SEMICOLON { printf("%s\n", $2); free($2); }
    ;

ifelse: 
    IF expresion THEN expresion ELSE expresion 
    { $$ = concat(7, "(", $4, " if ", $2, " else ",$6, ")"); }
    ;

let_exp:
    LET ID COLON tipo ASSIGN expresion IN expresion
    {
        /* (lambda id: body)(val) */

        $$ = concat(6, $2 , "=", $6, "\n", $8, "\n");
    }
    ;

funcion_anonima:
    LAMBDA ID COLON tipo DOT expresion
    { $$ = concat(5, "(lambda ", $2, ": ", $6, ")"); }
    ;

expresion:
    termino  
    | termino COLON tipo { $$ = $1; }
    | expresion PLUS expresion { $$ = unir3($1, " + ", $3); }
    | expresion MINUS expresion { $$ = unir3($1, " - ", $3); }
    | expresion MULT expresion { $$ = unir3($1, " * ", $3); }
    | expresion DIV expresion { 
        if(strcmp($3, "0") == 0 || strcmp($3, "0.0") == 0) {
            fprintf(stderr, "Error de Ejecución: División por cero (Linea %d)\n", yylineno);
            YYERROR;
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
    | LPAREN expresion RPAREN { $$ = concat(3, "(", $2, ")"); }
    | funcion_anonima { $$ = $1; }
    | SUCC LPAREN expresion RPAREN { $$ = concat(3, "(", $3, " + 1)"); }
    
    | PRED LPAREN expresion RPAREN { 
        if (strchr($3, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: PRED no puede aplicarse a un Float (Linea %d)\n", yylineno);
            YYERROR;
        }
        if (strcmp($3, "True") == 0 || strcmp($3, "False") == 0) {
            fprintf(stderr, "Error de Tipos: PRED no puede aplicarse a un Bool (Linea %d)\n", yylineno);
            YYERROR;
        }

        if (strcmp($3, "0") == 0) {
           $$ = concat(3, "(", $3, " )");
        }else{
            $$ = concat(3, "(", $3, " - 1)");
        }
       
    }

    | ISZERO LPAREN expresion RPAREN {
        if (strchr($3, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: isZero no puede aplicarse a un Float (Linea %d)\n", yylineno);
            YYERROR;
        }
        /* isZero no tiene sentido en booleanos */
        if (strcmp($3, "True") == 0 || strcmp($3, "False") == 0) {
            fprintf(stderr, "Error de Tipos: isZero no puede aplicarse a un Bool (Linea %d)\n", yylineno);
            YYERROR;
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

/* --- CÓDIGO C --- */

extern FILE *yyin;

void yyerror(const char *s) {
    fprintf(stderr, "Error sintactico en linea %d: %s antes del token '%s'\n", 
            yylineno, s, yytext);
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