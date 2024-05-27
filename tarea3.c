#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/queue.h"
#include "tdas/stack.h"
#include <string.h>

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions; //Secuencia de movimientos para llegar al estado
} State;

// Función para copiar un estado dado
State *copia_estado(State *estado)
{
    State *copia = (State*) malloc(sizeof(State));
    int i,j;
    // Copia los valores de la matriz y las posiciones x, y
    for (i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            copia->square[i][j] = estado->square[i][j];
    copia->x = estado->x;
    copia->y = estado->y;
    copia->actions = list_create();// Crea una nueva lista para las acciones
    // Copia las acciones del estado original a la copia
    List * aux = list_first(estado->actions);
    while(aux != NULL){
        list_pushBack(copia->actions, aux);
        aux = list_next(estado->actions);
    }
    return copia;
}

// Función para realizar una transición en el puzzle
State *transicion(State *estado, int lugar)
{
    int x_vacia = estado->x;
    int y_vacia = estado->y;
    int nueva_x = x_vacia;
    int nueva_y = y_vacia;
    // Calcula la nueva posición de la ficha vacía según la dirección indicada
    switch(lugar){
        case 1:
            nueva_x -= 1;
            break;
        case 2:
            nueva_x += 1;
            break;
        case 3:
            nueva_y -= 1;
            break;
        case 4:
            nueva_y += 1;
            break;
        default:
            return NULL;
    }
    // Verifica si la nueva posición está dentro de los límites del tablero
    if(nueva_x < 0 || nueva_x > 2 || nueva_y < 0 || nueva_y > 2)
        return NULL;
    // Crea un nuevo estado y realiza la transición
    State *nuevo_estado = (State*)malloc(sizeof(State));
    nuevo_estado = copia_estado(estado); // Copia el estado actual
    nuevo_estado->square[x_vacia][y_vacia] = nuevo_estado->square[nueva_x][nueva_y];
    nuevo_estado->square[nueva_x][nueva_y] = 0; // Actualiza la posición de la ficha vacía
    nuevo_estado->x = nueva_x;
    nuevo_estado->y = nueva_y;

    // Agrega la acción a la lista de acciones del nuevo estado
    int *lista_de_accion = (int*)malloc(sizeof(int));
    *lista_de_accion = lugar;
    list_pushBack(nuevo_estado->actions, lista_de_accion);
    return nuevo_estado;
}

// Función para obtener los estados adyacentes a un estado dado
List * get_adj_nodes(State *estado)
{
    List * get_nodes = list_create();
// Intenta realizar una transición en cada dirección y agrega el estado resultante a la lista
    State *movimiento_hacia_arriba = transicion(estado, 1);
    if(movimiento_hacia_arriba != NULL)
        list_pushBack(get_nodes, movimiento_hacia_arriba);
    
    State *movimiento_hacia_abajo = transicion(estado, 2);
    if(movimiento_hacia_abajo != NULL)
        list_pushBack(get_nodes, movimiento_hacia_abajo);
    
    State *movimiento_hacia_izquierda = transicion(estado, 3);
    if(movimiento_hacia_izquierda != NULL)
        list_pushBack(get_nodes, movimiento_hacia_izquierda);

    State *movimiento_hacia_derecha = transicion(estado, 4);
    if(movimiento_hacia_derecha != NULL)
        list_pushBack(get_nodes, movimiento_hacia_derecha);

    return get_nodes;
}

// Función para verificar si un estado es el estado final (solución)
int estado_final(State *estado){
    int aux = 0;
    // Verifica si la matriz del estado es igual a la matriz objetivo
    for(size_t i = 0; i < 3; i++){
        for(size_t j = 0; j < 3; j++){
            if(estado->square[i][j] != aux)
                return 0;
            aux++;
        }
    }
    return 1; // Retorna 1 si es el estado final, 0 en caso contrario
}
// Función para mostrar el estado actual del puzzle
void mostrar_estado(State *estado){
    int i,j;
    for (i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(estado->square[i][j] == 0){
                printf("x ");// Muestra 'x' para la ficha vacía
            }
            else{
                printf("%d ", estado->square[i][j]); // Muestra el número en la ficha
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Función de búsqueda en profundidad (DFS)
// Realiza una búsqueda en profundidad para encontrar la solución del puzzle
State *DFS(State estado, int *cont){
    Stack *pila = stack_create(); // Crea una pila para almacenar los estados durante la búsqueda

    // Reserva memoria para el estado inicial y lo copia
    State *estado_inicial = (State *) malloc(sizeof(State));
    *estado_inicial = estado;

    State *aux = (State *) malloc(sizeof(State));
    stack_push(pila, estado_inicial); // Empuja el estado inicial a la pila
    while(stack_top(pila) != NULL){ // Mientras haya estados en la pila
        aux = stack_top(pila); // Toma el estado en la cima de la pila
        stack_pop(pila); // Elimina el estado de la cima de la pila
        (*cont)++; // Incrementa el contador de iteraciones
        if(estado_final(aux)){ // Verifica si el estado actual es el estado final
            return aux; // Retorna el estado si es el estado final
        }
        if(tamano_lista(aux->actions) >= 13) // Límite de profundidad para evitar bucles infinitos
        {
            free(aux); // Libera la memoria del estado actual
            continue; // Continua con la siguiente iteración
        }
        List *adj_nodes = get_adj_nodes(aux); // Obtiene los estados adyacentes

        // Itera sobre los estados adyacentes y los empuja a la pila
        State* nuevo_aux = list_first(adj_nodes);
        while(nuevo_aux != NULL){
            stack_push(pila, nuevo_aux);
            nuevo_aux = list_next(adj_nodes);
        }
        free(nuevo_aux); // Libera la memoria del estado auxiliar
        list_clean(adj_nodes); // Limpia la lista de estados adyacentes
    }
    return NULL; // Retorna NULL si no se encuentra una solución
}

// Función de búsqueda en anchura (BFS)
// Realiza una búsqueda en anchura para encontrar la solución del puzzle
State *BFS(State estado, int *cont){
    Queue *cola = queue_create(); // Crea una cola para almacenar los estados durante la búsqueda

    // Reserva memoria para el estado inicial y lo copia
    State *estado_inicial = (State *) malloc(sizeof(State));
    *estado_inicial = estado;

    State *aux = (State *) malloc(sizeof(State));
    queue_insert(cola, estado_inicial); // Inserta el estado inicial en la cola
    while(queue_front(cola) != NULL){ // Mientras haya estados en la cola
        aux = queue_front(cola); // Toma el estado al frente de la cola
        queue_remove(cola); // Elimina el estado del frente de la cola
        (*cont)++; // Incrementa el contador de iteraciones

        if(estado_final(aux)){ // Verifica si el estado actual es el estado final
            return aux; // Retorna el estado si es el estado final
        }

        List *adj_nodes = get_adj_nodes(aux); // Obtiene los estados adyacentes

        // Itera sobre los estados adyacentes y los inserta en la cola
        State *nuevo_aux = list_first(adj_nodes);
        while(nuevo_aux){
            queue_insert(cola, nuevo_aux);
            nuevo_aux = list_next(adj_nodes);
        }
        list_clean(adj_nodes); // Limpia la lista de estados adyacentes
        free(aux); // Libera la memoria del estado auxiliar
    }
    return NULL; // Retorna NULL si no se encuentra una solución
}

// Función para mostrar los pasos de la solución
void mostrar_pasos(State *estado, List *actions)
{
    State *aux = estado;
    int *accion = list_first(actions);
    int contador = 0;

    printf("\n");
    puts("================================================");
    puts(" Movimientos realizados para resolver el puzzle ");
    puts("================================================");

    printf("\nEstado inicial del puzzle: \n");
    mostrar_estado(aux);
    while(accion != NULL){
        contador++;
        aux = transicion(aux, *accion);
        accion = list_next(actions);
        printf("\nEstado %d: \n", contador);
        mostrar_estado(aux);
    }
}

// Función para mostrar la solución encontrada
void mostrar_solucion(State *estado, State *estado_resuelto, int *cont){
    printf("\nEl numero de iteraciones que se realizaron para resolver el puzzle fue de: %d\n", *cont);
    mostrar_pasos(estado, estado_resuelto->actions);
    puts("======================================================");
    printf("El puzzle fue resuelto con exito en %d movimientos\n", tamano_lista(estado_resuelto->actions));
    puts("======================================================");
}

// Función para mostrar la solución usando búsqueda en profundidad (DFS)
void mostrar_dfs(State estado, int *cont){
    *cont = 0; // Inicializa el contador de iteraciones a 0
    State *solucion = DFS(estado, cont); // Llama a la función DFS para encontrar la solución
    mostrar_solucion(&estado, solucion, cont); // Muestra la solución encontrada
}

// Función para mostrar la solución usando búsqueda en anchura (BFS)
void mostrar_bfs(State estado, int *cont){
    *cont = 0; // Inicializa el contador de iteraciones a 0
    State *solucion = BFS(estado, cont); // Llama a la función BFS para encontrar la solución
    mostrar_solucion(&estado, solucion, cont); // Muestra la solución encontrada
}     

int main() {
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0  // Posición del espacio vacío (fila 0, columna 0)
    };
    estado_inicial.actions = list_create();
    
    char opcion;
    int contador;
    do {
        puts("========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");
        
        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Buscar Mejor Primero");
        puts("4) Salir");
    
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
    
        switch (opcion) {
        case '1':
          mostrar_dfs(estado_inicial, &contador);
          break;
        case '2':
          mostrar_bfs(estado_inicial, &contador);
          break;
        case '3':
          printf("Se implementara esta funcion proximamente\n");
          break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();
  } while (opcion != '4');
    printf("Gracias por ocupar la aplicacion :D");
  return 0;
}
