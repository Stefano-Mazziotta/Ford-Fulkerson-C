#include "index.h"

/*
    Función: busqueda_camino

    Descripción:
    - Realiza una búsqueda en amplitud (BFS) para encontrar un camino desde la fuente al sumidero en una red auxiliar.

    Parámetros:
    - red_aux: Matriz de adyacencia de la red residual.
    - fuente: Nodo fuente del camino.
    - sumidero: Nodo sumidero del camino.
    - semicamino: Array para almacenar el camino.

    Retorno:
    - 1 si hay un camino desde la fuente al sumidero, 0 en caso contrario.
*/
int busqueda_camino(int red_aux[V][V], int fuente, int sumidero, int semicamino[]) {

    int visitado[V];
    memset(visitado, 0, sizeof(visitado));

    // Creación de una cola, vértice fuente en cola y marcar vértices fuente como visitado
    // Se recorre red_aux para encontrar las adyacencias y los semicaminos

    int cola[V];
    int frente = 0;
    int fin = 0;

    // Empezamos en el nodo fuente
    cola[fin++] = fuente;
    visitado[fuente] = true;
    semicamino[fuente] = -1;

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
    return (visitado[sumidero] == true);
}

/*
    Función: fordFulkerson

    Descripción:
    - Implementa el algoritmo de Ford-Fulkerson para encontrar el flujo máximo en una red de flujo.

    Parámetros:
    - red: Matriz de adyacencia que representa la red original.
    - fuente: Nodo fuente de la red.
    - sumidero: Nodo sumidero de la red.

    Retorno:
    - Flujo máximo desde la fuente hasta el sumidero en la red dada.
*/
int fordFulkerson(int red[V][V], int fuente, int sumidero){
   
    int red_aux[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            red_aux[i][j] = red[i][j];
        }
    }

    int flujo_maximo = 0;
    int semicamino[V];

    while (busqueda_camino(red_aux, fuente, sumidero, semicamino)) {
        int flujo_camino = INT_MAX;

        // Encuentra la capacidad mínima en el camino de aumento
        for (int v = sumidero; v != fuente; v = semicamino[v]) {
            int u = semicamino[v];
            flujo_camino = lower(flujo_camino, red_aux[u][v]);
        }

        // Actualiza las capacidades en el grafo residual
        for (int v = sumidero; v != fuente; v = semicamino[v]) {
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

    // Verificar si hay flujos negativos antes de ejecutar el algoritmo
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (red[i][j] < 0) {
                printf("Error: La red contiene flujos negativos. El algoritmo de Ford-Fulkerson no maneja flujos negativos.\n");
                return 1;
            }
        }
    }

    printf("El flujo máximo posible es: %d\n", fordFulkerson(red, fuente, sumidero));

    return 0;
}
