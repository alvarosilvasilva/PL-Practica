
El objetivo de este proyecto es desarrollar un transpilador que convierta expresiones escritas en Cálculo Lambda Tipado (CLT o λT​) a código Python.
La gramática permitira la definición de variables, funciones, y la evaluación de expresiones, con un sistema de tipos simple que se mapee a Python.
Teniendo en cuenta la deteccion de los propios errores tanto lexicos, estructuras mal formadas o tipos incoherentes.

Entrada:
    Definición de Variables:.
        Ejemplo: let x: int = 5

    Definición de Funciones (Abstracción Lambda):
        Ejemplo: def sum: fun(int, int -> int) = \x: int . \y: int . x + y

    Aplicación de Funciones:ls
        Ejemplo: EVAL sum 2 3

    Operaciones Básicas:
        Ejemplo: (x * 2) - 1


Salidas: 

    x = 10

    def sum(int x,int y):
        return (x + y) 

    resultado = sum(2,3)

Estos serian algunos de los ejemplos simples que se pueden realizar. 