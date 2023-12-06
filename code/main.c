#include "main.h"

/**
 * Inicializa una red de flujo desde una matriz de capacidades.
 * @param redFlujo Puntero a la estructura RedFlujo que se inicializará.
 * @param matriz Matriz de capacidades para inicializar la red.
*/
void inicializarRedFlujoDesdeMatriz(struct RedFlujo* redFlujo, const int matriz[V][V]) {
    redFlujo->capacidad = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        redFlujo->capacidad[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            redFlujo->capacidad[i][j] = matriz[i][j];
        }
    }
}

/**
 * Realiza una búsqueda en amplitud en la red residual para encontrar un camino de aumento.
 * @param red Puntero a la estructura RedFlujo que representa la red residual.
 * @param fuente Nodo de inicio para la búsqueda.
 * @param sumidero Nodo de destino para la búsqueda.
 * @param bfs Estructura para almacenar los resultados de la búsqueda en amplitud.
 * @return true si se encuentra un camino de aumento, false en caso contrario.
 */
bool busquedaAmplitud(const struct RedFlujo* red, int fuente, int sumidero, struct BusquedaAmplitud* bfs) {
    
    // Inicializa los arrays de visitados y caminos
    bfs->visitado = (int *)malloc(V * sizeof(int));
    bfs->camino = (int *)malloc(V * sizeof(int));

    // Verifica si la asignación de memoria fue exitosa
    if (bfs->visitado == NULL || bfs->camino == NULL) {
        // Manejar el error y retornar false, por ejemplo, liberando la memoria si es necesario
        free(bfs->visitado);
        free(bfs->camino);
        return false;
    }

    memset(bfs->visitado, 0, V * sizeof(int));
    memset(bfs->camino, -1, V * sizeof(int));

    // Inicializa la cola para la búsqueda en amplitud
    int cola[V];
    int frente = 0, fin = 0;

    // Agrega el nodo fuente a la cola y marca como visitado
    cola[fin] = fuente;
    bfs->visitado[fuente] = true;
    fin++;
    
    // Búsqueda en amplitud
    while (frente < fin) {
        int nodoActual = cola[frente++];

        // Explora los vecinos del nodo actual
        for (int vecino = 0; vecino < V; vecino++) {
            if (!bfs->visitado[vecino] && red->capacidad[nodoActual][vecino] > 0) {
                cola[fin] = vecino;
                fin++;
                bfs->camino[vecino] = nodoActual;
                bfs->visitado[vecino] = true;
            }
        }
    }

    // Devuelve true si se alcanzó el nodo sumidero durante la búsqueda
    return bfs->visitado[sumidero];
}


/**
 * Implementa el algoritmo de Ford-Fulkerson para encontrar el flujo máximo en una red.
 * @param red Puntero a la estructura RedFlujo que representa la red original.
 * @param fuente Nodo fuente para el flujo.
 * @param sumidero Nodo sumidero para el flujo.
 * @return Flujo máximo en la red.
 */
int fordFulkerson(struct RedFlujo* red, int fuente, int sumidero) {
    struct RedFlujo redResidual = *red;
    int flujoMaximo = 0;

    struct BusquedaAmplitud bfs;

    while (busquedaAmplitud(&redResidual, fuente, sumidero, &bfs)) {
        int flujoCamino = INT_MAX;

        // Encuentra la capacidad mínima en el camino de aumento
        for (int destino = sumidero; destino != fuente; destino = bfs.camino[destino]) {
            int origen = bfs.camino[destino];
            flujoCamino = lower(flujoCamino, redResidual.capacidad[origen][destino]);
        }

        // Actualiza las capacidades en el grafo residual
        for (int destino = sumidero; destino != fuente; destino = bfs.camino[destino]) {
            int origen = bfs.camino[destino];
            redResidual.capacidad[origen][destino] -= flujoCamino;
            redResidual.capacidad[destino][origen] += flujoCamino; // Añadir flujo en sentido opuesto
        }

        flujoMaximo += flujoCamino;
    }

    return flujoMaximo;
}

void freeRedFlujo(struct RedFlujo* redFlujo) {
    for (int i = 0; i < V; i++) {
        free(redFlujo->capacidad[i]);
    }
    free(redFlujo->capacidad);
    redFlujo->capacidad = NULL;  // Importante: establecer el puntero a NULL después de liberar
}

/**
 * Función principal que utiliza el algoritmo de Ford-Fulkerson para encontrar el flujo máximo.
 * @return 0 si la ejecución fue exitosa.
 */
int main(void) {
    struct RedFlujo redFlujo;
    inicializarRedFlujoDesdeMatriz(&redFlujo, (int[V][V]){
        {0, 4, 6, 0, 0, 0},
        {0, 0, 0, 3, 5, 0},
        {0, 0, 0, 0, 6, 0},
        {0, 0, 9, 0, 0, 5},
        {0, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0}
    });

    int fuente = 0;
    int sumidero = 5;

    printf("El flujo máximo posible es: %d\n", fordFulkerson(&redFlujo, fuente, sumidero));

    // Libera la memoria asignada para la red de flujo
    freeRedFlujo(&redFlujo);

    return 0;
}