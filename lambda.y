%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- VARIABLES GLOBALES PARA LA DES-CURRIFICACIÓN --- */
/* Usaremos un array estático simple para guardar los argumentos.
   Es suficiente para una práctica universitaria. */
char* lista_argumentos[100];
int contador_args = 0;

/* Declaraciones externas de Flex */
extern int yylineno;
extern int yylex();
extern char* yytext;
void yyerror(const char *s);

/* --- FUNCIONES AUXILIARES DE C --- */

/* Función para concatenar dos strings creando uno nuevo en memoria */
char* unir(const char* s1, const char* s2) {
    /* +1 para el terminador nulo */
    char* resultado = malloc(strlen(s1) + strlen(s2) + 1); 
    if (resultado == NULL) { fprintf(stderr, "Error de memoria\n"); exit(1); }
    strcpy(resultado, s1);
    strcat(resultado, s2);
    return resultado;
}

/* Función auxiliar para unir 3 partes (muy útil para operaciones a + b) */
char* unir3(const char* s1, const char* s2, const char* s3) {
    char* resultado = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);
    if (resultado == NULL) { fprintf(stderr, "Error de memoria\n"); exit(1); }
    strcpy(resultado, s1);
    strcat(resultado, s2);
    strcat(resultado, s3);
    return resultado;
}

/* Limpiar el buffer de argumentos */
void limpiar_args() {
    contador_args = 0;
}

/* Añadir argumento a la lista */
void agregar_arg(char* nombre) {
    if (contador_args < 100) {
        lista_argumentos[contador_args] = strdup(nombre); /* strdup duplica el string */
        contador_args++;
    }
}
%}

/* --- ESTRUCTURA DE DATOS (UNION) --- */
/* En C, definimos que los valores serán punteros a char (strings) */
%union {
    char* sval; 
}

/* --- TOKENS (Deben coincidir con tu lexer) --- */
%token <sval> ID NUMBER FLOAT_LIT INT_LIT TYPE_INT TYPE_FLOAT TYPE_BOOL
%token DEF EVAL LAMBDA ARROW COLON DOT ASSIGN SEMICOLON LET IN
%token LPAREN RPAREN PLUS MINUS MULT DIV

/* --- TIPOS DE NO-TERMINALES --- */
%type <sval> tipo expresion termino cuerpo_lambda

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
    ;

/* --- DEFINICIÓN (Traducción a Python) --- */
definicion:
    DEF ID ASSIGN { limpiar_args(); } cuerpo_lambda SEMICOLON
    {
        /* Cabecera de comentario */
        printf("# Funcion generada desde Lambda Calculo\n");
        
        if (contador_args > 0) {
            /* Imprimir: def nombre( */
            printf("def %s(", $2);
            
            /* Imprimir argumentos. 
               NOTA: Como la recursividad en Bison va de abajo a arriba,
               los argumentos se guardan en orden inverso (el último se procesa primero).
               Por eso recorremos el array al revés: de (contador-1) a 0. 
            */
            for (int i = contador_args - 1; i >= 0; i--) {
                printf("%s", lista_argumentos[i]);
                if (i > 0) printf(", "); /* Coma si no es el último */
            }
            
            printf("):\n");
            printf("    return %s\n\n", $5); /* $5 es el cuerpo ya traducido */
        } 
        else {
            /* Caso de constante: x = 5 */
            printf("%s = %s\n\n", $2, $5);
        }
        
        /* Liberar memoria de strings temporales sería ideal aquí, pero en prácticas
           se suele omitir para simplificar, ya que el SO limpia al terminar. */
    }
    ;

/* --- REGLAS RECURSIVAS DE LAMBDA --- */
cuerpo_lambda:
    LAMBDA ID COLON tipo DOT cuerpo_lambda
    {
        /* Guardamos el argumento en nuestra lista global */
        agregar_arg($2);
        
        /* Subimos el cuerpo hacia arriba */
        $$ = $6;
    }
    | expresion
    {
        /* Caso base: ya no hay lambdas, solo la fórmula matemática */
        $$ = $1;
    }
    ;

/* --- EVALUACIONES --- */
evaluacion:
    EVAL expresion SEMICOLON
    {
        printf("print(%s)\n", $2);
    }
    ;

/* --- EXPRESIONES MATEMÁTICAS --- */
expresion:
    termino                     { $$ = $1; }
    /* Usamos la funcion unir3 para crear el string "A + B" */
    | expresion PLUS expresion  { $$ = unir3($1, " + ", $3); }
    | expresion MINUS expresion { $$ = unir3($1, " - ", $3); }
    | expresion MULT expresion  { $$ = unir3($1, " * ", $3); }
    | expresion DIV expresion   { $$ = unir3($1, " / ", $3); }
    
    /* Aplicación: f x -> f(x) */
    | expresion termino         { 
        char* temp = unir($1, "(");
        char* temp2 = unir(temp, $2);
        $$ = unir(temp2, ")");
        /* Resultado: string "f(x)" */
    }
    ;

termino:
    ID                          { $$ = $1; }
    | INT_LIT                   { $$ = $1; }
    | FLOAT_LIT                 { $$ = $1; }
    | LPAREN expresion RPAREN   { $$ = unir3("(", $2, ")"); }
    ;

/* --- TIPOS (Solo validación sintáctica) --- */
tipo:
    TYPE_INT                    { $$ = $1; }
    | TYPE_FLOAT                { $$ = $1; }
    | LPAREN tipo RPAREN        { $$ = $2; }
    | tipo ARROW tipo           { $$ = unir3($1, " -> ", $3); }
    ;

%%


/* ========================================================================== */
/* CÓDIGO C                                                                   */
/* ========================================================================== */

/* Importante: Decimos que 'yyin' viene de fuera (del lexer) */
extern FILE *yyin;

void yyerror(const char *s) {
    fprintf(stderr, "Error sintactico en linea %d: %s antes del token '%s'\n", 
            yylineno, s, yytext);
}

int main(int argc, char **argv) {
    /* 1. Imprimimos la cabecera de Python (siempre en stdout) */
    printf("import math\n");
    printf("from functools import reduce\n\n");

    /* 2. Configuración de la entrada */
    yylineno = 1; // Reiniciamos contador de líneas
    if (argc > 1) {
        /* Si hay argumentos, intentamos abrir el fichero */
        yyin = fopen(argv[1], "r");
        if (!yyin) { 
            perror(argv[1]); /* Muestra el error estándar si falla (ej: "No such file") */
            return 1; 
        }
    } else {
        /* Si no hay argumentos, leemos de la consola */
        yyin = stdin;
    }

    /* 3. Iniciamos el análisis */
    int res = yyparse();

    /* 4. Limpieza */
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return res;
}