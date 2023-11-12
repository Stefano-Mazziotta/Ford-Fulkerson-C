#include <stdio.h>
#include <limits.h>
#include <string.h>
//#include "tail.h"


// --- Macros ---

// Número de vértices en el gráfico dado
#define V 6
#define true 1
#define false 0
#define lower(X, Y) ( (X < Y) ? X : Y )

// Definimos la red como matríz de adyacencia.
int red[V][V] = {
  {0, 4, 6, 0, 0, 0},
  {0, 0, 0, 3, 5, 0},
  {0, 0, 0, 0, 6, 0},
  {0, 0, 9, 0, 0, 5},
  {0, 0, 0, 0, 0, 4},
  {0, 0, 0, 0, 0, 0}
};


/* 
    Devuelve true si hay un camino desde la fuente de ’s’ bajando a ’t’ en red auxiliar.
    También se llena de los semicamino [] para almacenar el camino 
*/
int busqueda_camino(int red_aux[V][V], int s, int t, int semicamino[]) {

    // Crear vector visitado y marcar todos los vértices como no visitados
    int visitado[V];
    memset(visitado, 0, sizeof(visitado));

    // Creación de una cola, vértice fuente en cola y marcar vértices fuente como visitado
    // Se recorre red_aux para encontrar las adyacencias y los semicaminos
    // Consejo: Buscar , investigar sobre algoritmo de recorrido de grafos BSF

    // Usaremos una cola para BFS
    int cola[V];
    int frente = 0;
    int fin = 0;

    // Empezamos en el nodo fuente
    cola[fin++] = s;
    visitado[s] = true;
    semicamino[s] = -1;

    while (frente != fin) {
        int u = cola[frente++];
        
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && red_aux[u][v] > 0) {
                cola[fin++] = v;
                semicamino[v] = u;
                visitado[v] = true;
            }
        }
    }

    // Si llegamos al nodo sumidero en el BFS, hay un camino
    return (visitado[t] == true);
}

// Retorna el maximo flujo de s a t en el grafico dado
int fordFulkerson(int red[V][V], int s, int t){
   
    int red_aux[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            red_aux[i][j] = red[i][j];
        }
    }

    int flujo_maximo = 0;
    int semicamino[V];

    while (busqueda_camino(red_aux, s, t, semicamino)) {
        int flujo_camino = INT_MAX;

        // Encuentra la capacidad mínima en el camino de aumento
        for (int v = t; v != s; v = semicamino[v]) {
            int u = semicamino[v];
            flujo_camino = lower(flujo_camino, red_aux[u][v]);
        }

        // Actualiza las capacidades en el grafo residual
        for (int v = t; v != s; v = semicamino[v]) {
            int u = semicamino[v];
            red_aux[u][v] -= flujo_camino;
            red_aux[v][u] += flujo_camino; // Añadir flujo en sentido opuesto
        }

        flujo_maximo += flujo_camino;
    }

    return flujo_maximo;
}

int main(void){
    int fuente = 0;
    int sumidero = 5;
    printf("El flujo máximo posible es: %d\n", fordFulkerson(red, fuente, sumidero));
    return 0;
}

/*

    // mis notaciones
    grafos con pesos podría representarse con una matriz de adyacencia y una de capacidades.

    // resumen pdf
    Este segundo método lo podemos generalizar de la siguiente manera: Suponer
    que hay un camino de S a algún nodo Y, un camino de algún nodo X a T y un
    camino de X a Y con flujo positivo. Entonces, el flujo a lo largo del camino de
    X a Y puede ser reducido y esta cantidad es el mínimo del flujo de X a Y y las
    diferencias entre capacidades y flujo en los caminos de S a Y y X a T

    // pseudocodigo 

    // Matriz de adyacencia con los pesos o capacidades
     int Grafo[V][V]

    // inicia siendo igual que Grafo , pero se iran modificando los pesos segun el flujo
    int Grafo_aux[V][V]

    // Se armaran los semicaminos de s a T usando a los nodos como indices
    // en el pseudocodigo lo llamamos p
    int semicamino[V]

    // Marcaremos con 0/1 si se visito al vertice para no volver a hacerlo
    int visitado[V];

*/
