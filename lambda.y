%{ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <strings.h> 
#include <ctype.h>


char* lista_argumentos[100];
int contador_args = 0;
FILE *out;

extern int yylineno;
extern int yylex();
extern char* yytext;
void yyerror(const char *s);

/* funciones auxiliares  */
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
    if (!res) { fprintf(stderr, "Error de memoria\n"); exit(1); } /*liberar memoria*/
    res[0] = '\0';

    va_start(ap, count);
    for(int i = 0; i < count; i++) {
        char* s = va_arg(ap, char*);
        if(s) strcat(res, s);
    }
    va_end(ap);
    return res;
}


void limpiar_args() { contador_args = 0; }
void agregar_arg(char* nombre) {
    if (contador_args < 100) {
        lista_argumentos[contador_args] = strdup(nombre); 
        contador_args++;
    }
}
%}

%union { char* sval; }

/* definición de los tokens */
%token <sval> ID FLOAT_LIT INT_LIT TYPE_INT TYPE_FLOAT TYPE_BOOL SUCC PRED ISZERO
%token DEF EVAL LAMBDA COLON DOT ASSIGN SEMICOLON LET IN COMMA
%token LPAREN RPAREN PLUS MINUS MULT DIV IF THEN ELSE

%type <sval> tipo expresion termino cuerpo_lambda ifelse  let_exp parametro lista_parametros

/*preferencia de operadores*/
%nonassoc LET IN IF THEN ELSE 
%left PLUS MINUS
%left MULT DIV
%left LPAREN RPAREN

%%

/* GRAMÁTICA PRINCIPAL */

programa: lista_sentencias ;

lista_sentencias: sentencia | lista_sentencias sentencia ;

sentencia:
    definicion
    | evaluacion
    | definicion_var
    | expresion SEMICOLON { 
        if ($1 != NULL) {
            fprintf(out,"%s\n\n", $1); 
            free($1); 
        }
    }
    
    | error SEMICOLON 
    { 
        yyerror; 
        YYABORT; 
    }
    ;

/*tipos  */
parametro: ID COLON tipo { agregar_arg($1); } ;

/*listas de tipos */
lista_parametros: parametro | parametro COMMA lista_parametros ;

/* funciones */
definicion:
    /* def f = lambda x... */
    DEF ID ASSIGN { limpiar_args(); } cuerpo_lambda SEMICOLON
    {
     
        if (contador_args > 0) {
            fprintf(out,"def %s(", $2);
            for (int i = contador_args - 1; i >= 0; i--) {
                fprintf(out,"%s", lista_argumentos[i]);
                if (i > 0) fprintf(out,", ");
            }
            fprintf(out,"):\n    return %s\n\n", $5); 
            free($5);
        } else {
            fprintf(out,"%s = %s\n\n", $2, $5); 
            free($5);
        }
        limpiar_args();/*liberar memoria */
    }
    /* 2. def f(x:T) =...*/
    | DEF ID LPAREN { limpiar_args(); } lista_parametros RPAREN ASSIGN expresion SEMICOLON
    {
        fprintf(out,"def %s(", $2);
        for (int i = 0; i < contador_args; i++) {
            fprintf(out,"%s", lista_argumentos[i]);
            if (i < contador_args - 1) fprintf(out,", ");
        }
        fprintf(out,"):\n    return %s\n\n", $8);
        free($8);
    }
    
    /* falta el cuerpo */
    | DEF ID error SEMICOLON
    {
        fprintf(stderr, "Error Sintactico: Definicion de funcion mal formada. Falta '=' o el cuerpo de la funcion (Linea %d)\n", yylineno);
        limpiar_args();
        YYABORT; 
    }
    ;

/* definicion de variables */
definicion_var:
    /* x:Nat = 10;; */

    ID COLON TYPE_INT ASSIGN expresion SEMICOLON
    {
        if (strchr($5, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: Asignación de Float a Nat en '%s' (Linea %d)\n", $1, yylineno);
            YYABORT;
        }
        if (strcasecmp($5, "True") == 0 || strcasecmp($5, "False") == 0 || strstr($5, "==") != NULL) {
            fprintf(stderr, "Error de Tipos: Asignación de Booleano a Nat en '%s' (Linea %d)\n", $1, yylineno);
            YYABORT;
        }
        fprintf(out,"%s = %s\n\n", $1, $5); 
    }
    /* x:Float = 10.0;; */
    | ID COLON TYPE_FLOAT ASSIGN expresion SEMICOLON
    {
        if (strcasecmp($5, "True") == 0 || strcasecmp($5, "False") == 0 || strstr($5, "==") != NULL) {
             fprintf(stderr, "Error de Tipos: Asignación de Booleano a Float en '%s' (Linea %d).\n", $1, yylineno);
             YYABORT;
        }
        fprintf(out,"%s = %s\n\n", $1, $5);
    }
    /* x:Bool = True;; */
    | ID COLON TYPE_BOOL ASSIGN expresion SEMICOLON
    {
        if (strstr($5, "==") == NULL && strcasecmp($5, "True") != 0 && strcasecmp($5, "False") != 0) {
            /* CORREGIDO: ffprintf -> fprintf y uso de stderr */
            fprintf(stderr, "Error de Tipos: Asignacion de No Booleano a Bool en variable '%s' (Linea %d).\n", $1, yylineno);
            YYABORT;
        }
        fprintf(out,"%s = %s\n\n", $1, $5);
    }
    ;

/* lambda */
cuerpo_lambda:
    /* lambda. x:Tipo. cuerpo */
    LAMBDA ID COLON tipo DOT cuerpo_lambda { agregar_arg($2); $$ = $6; }
    | expresion { $$ = $1; }
    ;

/* eval */
evaluacion:
    /* eval r 10;; */
    EVAL expresion SEMICOLON { fprintf(out,"print(%s)\n\n", $2); free($2); }
    
    /* ERROR SINTÁCTICO: Eval incompleto */
    | EVAL error SEMICOLON
    {
        fprintf(stderr, "Error Sintactico: Instruccion 'eval' mal formada o expresion invalida (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* if-then-else */
ifelse: 
    /* if True then 1 else 0 */
    IF expresion THEN expresion ELSE expresion 
    { $$ = concat(7, "(", $4, " if ", $2, " else ",$6, ")"); }
    
    /* falta else */
    | IF expresion THEN expresion error 
    {
        fprintf(stderr, "Error Sintactico: Estructura 'if' incompleta. Falta la rama 'else' (Linea %d)\n", yylineno);
        YYABORT;
    }
    
    /* falta then */
    | IF expresion error
    {
        fprintf(stderr, "Error Sintactico: Estructura 'if' mal formada. Falta 'then' o la condicion es invalida (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* let */
let_exp:
    /*let x.Nat = 10 in x+1 */
    LET ID COLON tipo ASSIGN expresion IN expresion
    {
        $$ = concat(5 , $2 , " = ", $6, "\n", $8);
    }
    
    /* falta cuerpo, tipo */
    | LET ID error 
    {
        fprintf(stderr, "Error Sintactico: 'let' incompleto. Falta ': Tipo' tras '%s' (Linea %d)\n", $2, yylineno);
        YYABORT; 
    }
    /* falta cuerpo, asignacion */
    | LET ID COLON tipo error
    {
        fprintf(stderr, "Error Sintactico: 'let' incompleto. Falta '=' despues del tipo (Linea %d)\n", yylineno);
        YYABORT;
    }
    /* falta cuerpo, expresion */
    | LET ID COLON tipo ASSIGN expresion error
    {
        fprintf(stderr, "Error Sintactico: 'let' incompleto. Falta 'in' o el cuerpo final (Linea %d)\n", yylineno);
        YYABORT;
    }
    ;

/* operaciones y terminos */
expresion:
    termino 
    | termino COLON tipo { $$ = $1; }
    | expresion PLUS expresion { $$ = concat(3,$1, " + ", $3); }
    | expresion MINUS expresion { $$ = concat(3,$1, " - ", $3); }
    | expresion MULT expresion { $$ = concat(3,$1, " * ", $3); }
    | expresion DIV expresion { 
        if(strcmp($3, "0") == 0 || strcmp($3, "0.0") == 0) {
            fprintf(stderr, "Error de Ejecución: División por cero (Linea %d)\n", yylineno);
            YYABORT;
        }
        $$ = concat(3, $1, " / ", $3); }
    | expresion termino { $$ = concat(4, $1, "(", $2, ")"); }
    | ifelse { $$ = $1; }
    | let_exp { $$ = $1; } 
    ;

termino:
    ID { $$ = $1; }
    | INT_LIT { $$ = $1; }
    | FLOAT_LIT { $$ = $1; }
    
    | LPAREN expresion RPAREN { $$ = concat(3, "(", $2, ")"); }
   
    /*falta parentesis de cierre*/
    | LPAREN expresion error
    {
        fprintf(stderr, "Error Sintactico: Falta el parentesis de cierre ')' (Linea %d)\n", yylineno);
        YYABORT;
    }

    

    | SUCC LPAREN expresion RPAREN {
    
        if (strchr($3, '.') != NULL) {
            fprintf(stderr, "Error de Tipos: PRED no puede aplicarse a un Float (Linea %d)\n", yylineno);
            YYABORT;
        }
        if (strcasecmp($3, "True") == 0 || strcasecmp($3, "False") == 0 || strstr($3, "==") != NULL) {
            fprintf(stderr, "Error de Tipos: PRED no puede aplicarse a un Bool (Linea %d)\n", yylineno);
            YYABORT;
        }
        $$ = concat(3, "(", $3, " + 1)");
        }

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
    ;

%%

extern FILE *yyin;

void yyerror(const char *s) {
    fprintf(stderr, "Error de analisis (Bison) en linea %d: %s antes de '%s'\n", yylineno, s, yytext);
}

/* se guarda todo el codigo generado en salida.py */

int main(int argc, char **argv) {

    out = fopen("salida.py", "w");
    if (!out) {
        perror("salida.py");
        return 1;
    }


    fprintf(out, "import math\n");
    fprintf(out, "from functools import reduce\n\n");
    fprintf(out, "# Codigo generado autolambda\n\n");

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

    /* Ejecutar el parser */
    int res = yyparse();

    /* Cerrar archivos */
    if (yyin != stdin) fclose(yyin);
    fclose(out);

    /* se ejecute siempre que no hubiese errores */
    if (res == 0) {
        system("python3 salida.py");
    }

    return res;
}