## Descripción del Programa
Este programa permite, a través de un estado inicial de un puzzle 8, encontrar sus solución utilizando los mecanismos de búsqueda asociados a la estructura del grafo.

Con esta aplicación tenemos la intención de darle al usuario una experiencia dinámica a la hora de poder resolver el algoritmo del puzzle 8.

## Como compilar y ejecutar
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/F4CH/Puzzle-8`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar la aplicación.

# Funcionalidades

## Funcionando correctamente:
* Busqueda Depth First Search o DFS
* Busqueda Breadth First Search o BFS
* Mostrar cada accion realizada hasta llegar al estado final deseado
* Generar los estados del puzzle por los movimientos que se realizan


## Problemas conocidos:
* Que si se ingresa otro puzzle mas complejo que se entrego de ejemplo en el replit el programa se cae por la cantidad de iteraciones y la falta de memoria , la cual con la plataforma replit se encuentra limitada.

## A mejorar:
* Mejorar el rendimiento en cuanto a la cantidad de iteraciones segun el rango de profundidad
* Implementar la funcion de "Buscar Mejor Primero"
* Agregar o mejorar una interfaz mas amigable con el usuario
* 
# Ejemplo de uso

* Opción 1: Búsqueda en profundidad
````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 1
````

El usuario al escoger la opcion 1 realiza la busqueda en profundidad

````
El numero de iteraciones que se realizaron para resolver el puzzle fue de: 455536

================================================
 Movimientos realizados para resolver el puzzle 
================================================

Estado inicial del puzzle: 
x 2 8 
1 3 4 
6 5 7 


Estado 1: 
1 2 8 
x 3 4 
6 5 7 


Estado 2: 
1 2 8 
3 x 4 
6 5 7 


Estado 3: 
1 2 8 
3 4 x 
6 5 7 


Estado 4: 
1 2 x 
3 4 8 
6 5 7 


Estado 5: 
1 x 2 
3 4 8 
6 5 7 


Estado 6: 
1 4 2 
3 x 8 
6 5 7 


Estado 7: 
1 4 2 
3 5 8 
6 x 7 


Estado 8: 
1 4 2 
3 5 8 
6 7 x 


Estado 9: 
1 4 2 
3 5 x 
6 7 8 


Estado 10: 
1 4 2 
3 x 5 
6 7 8 


Estado 11: 
1 x 2 
3 4 5 
6 7 8 


Estado 12: 
x 1 2 
3 4 5 
6 7 8 

======================================================
El puzzle fue resuelto con exito en 12 movimientos
======================================================
Presione una tecla para continuar...
````
* Opción 2: Buscar en Anchura
````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 2
````
El usuario al escoger la opcion 2 realiza la busqueda en anchura

````
El numero de iteraciones que se realizaron para resolver el puzzle fue de: 190887

================================================
 Movimientos realizados para resolver el puzzle 
================================================

Estado inicial del puzzle: 
x 2 8 
1 3 4 
6 5 7 


Estado 1: 
1 2 8 
x 3 4 
6 5 7 


Estado 2: 
1 2 8 
3 x 4 
6 5 7 


Estado 3: 
1 2 8 
3 4 x 
6 5 7 


Estado 4: 
1 2 x 
3 4 8 
6 5 7 


Estado 5: 
1 x 2 
3 4 8 
6 5 7 


Estado 6: 
1 4 2 
3 x 8 
6 5 7 


Estado 7: 
1 4 2 
3 5 8 
6 x 7 


Estado 8: 
1 4 2 
3 5 8 
6 7 x 


Estado 9: 
1 4 2 
3 5 x 
6 7 8 


Estado 10: 
1 4 2 
3 x 5 
6 7 8 


Estado 11: 
1 x 2 
3 4 5 
6 7 8 


Estado 12: 
x 1 2 
3 4 5 
6 7 8 

======================================================
El puzzle fue resuelto con exito en 12 movimientos
======================================================
Presione una tecla para continuar...
````

*Opción 3: Buscar Mejor Primero
````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 3
````

El usuario al escoger la opcion 3 se deberia el Mejor Primero, pero esta funcion no esta implementada por lo que le mostrara esto al usuario.

````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 3
Se implementara esta funcion proximamente
Presione una tecla para continuar...
````

* Opción 4: Salir
````
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 4
````

El usuario al seleccionar la opcion 4 saldra de la aplicacion y le mostrara un mensaje en pantalla que dira "Gracias por ocupar la aplicacion :D".