#include "main.h"

/**
 * Inicializa una red desde una matriz de adyacencia representando las capacidades.
 * @param red Puntero a la estructura Red que se inicializará.
 * @param matriz Matriz de capacidades para inicializar la red.
 * @note Esta función asigna dinámicamente memoria para almacenar la matriz de capacidades.
 * @warning Se debe llamar a la función freeRedFlujo para evitar fugas de memoria.
 */
void inicializarRed(Red *red, const int matriz[V][V]) {
    red->capacidades = (int **)malloc(V * sizeof(int *));

    if (red->capacidades == NULL) {
        // Devuelve un código de error o maneja el error según sea necesario
        return;
    }

    for (int i = 0; i < V; i++) {
        red->capacidades[i] = (int *)malloc(V * sizeof(int));

        if (red->capacidades[i] == NULL) {
            // Manejar el error y liberar memoria asignada previamente
            for (int j = i - 1; j >= 0; j--) {
                free(red->capacidades[j]);
            }
            free(red->capacidades);
            red->capacidades = NULL;
            return;
        }

        for (int j = 0; j < V; j++) {
            red->capacidades[i][j] = matriz[i][j];
        }
    }
}

/**
 * Realiza una búsqueda en amplitud en la red residual para encontrar un camino de aumento.
 * @param red puntero a la estructura red el cual representa la red residual (matriz de adyacencia).
 * @param fuente Nodo de inicio para la búsqueda.
 * @param sumidero Nodo de destino para la búsqueda.
 * @param bfs Estructura para almacenar los resultados de la búsqueda en amplitud.
 * @return true si se encuentra un camino de aumento, false en caso contrario.
 * @note Esta función asigna dinámicamente memoria para los arrays de visitados y caminos.
 */
bool bfsAlgorithm(const Red *red, BreadthFirstSearch *bfs, int fuente, int sumidero) {
    
    // Inicializa los arrays de visitados y caminos
    bfs->visitados = (int *)malloc(V * sizeof(int));
    bfs->camino = (int *)malloc(V * sizeof(int));

    // Verifica si la asignación de memoria fue exitosa
    if (bfs->visitados == NULL || bfs->camino == NULL) {
        // Manejar el error y retornar false, por ejemplo, liberando la memoria si es necesario
        free(bfs->visitados);
        free(bfs->camino);
        return false;
    }

    memset(bfs->visitados, 0, V * sizeof(int));
    memset(bfs->camino, -1, V * sizeof(int));

    // Inicializa la cola para la búsqueda en amplitud
    int cola[V];
    int frente = 0, fin = 0;

    // Agrega el nodo fuente a la cola y marca como visitado
    cola[fin] = fuente;
    bfs->visitados[fuente] = true;
    fin++;
    
    // Búsqueda en amplitud
    while (frente < fin) {
        int nodoActual = cola[frente++];

        // Explora los vecinos del nodo actual
        for (int vecino = 0; vecino < V; vecino++) {
            if (!bfs->visitados[vecino] && red->capacidades[nodoActual][vecino] > 0) {
                cola[fin] = vecino;
                fin++;
                bfs->camino[vecino] = nodoActual;
                bfs->visitados[vecino] = true;
            }
        }
    }

    // Devuelve true si se alcanzó el nodo sumidero durante la búsqueda
    return bfs->visitados[sumidero];
}


/**
 * Implementa el algoritmo de Ford-Fulkerson para encontrar el flujo máximo en una red.
 * @param red puntero a la estructura red (matriz de adyacencia).
 * @param bfs puntero a la estructura bfs para almacenar los resultados de la búsqueda en amplitud.
 * @param fuente Nodo fuente para el flujo.
 * @param sumidero Nodo sumidero para el flujo.
 * @return Flujo máximo en la red.
 */
int fordFulkerson(Red *red, BreadthFirstSearch *bfs, int fuente, int sumidero) {
    Red redResidual = *red;
    int flujoMaximo = 0;

    while (bfsAlgorithm(&redResidual, bfs, fuente, sumidero)) {
        int flujoCamino = INT_MAX;

        // Encuentra la capacidad mínima en el camino de aumento
        int destino = sumidero;
        while (destino != fuente) {
            int origen = bfs->camino[destino];
            int capacidad = redResidual.capacidades[origen][destino];
            flujoCamino = lower(flujoCamino, capacidad);
            
            // Actualizar destino para la próxima iteración
            destino = bfs->camino[destino];
        }

        // Actualiza las capacidades en el grafo residual
        destino = sumidero;
        while (destino != fuente) {
            int origen = bfs->camino[destino];
            
            // Actualizar capacidades en el grafo residual
            redResidual.capacidades[origen][destino] -= flujoCamino;
            redResidual.capacidades[destino][origen] += flujoCamino; // Añadir flujo en sentido opuesto
            
            // Actualizar destino para la próxima iteración
            destino = bfs->camino[destino];
        }

        flujoMaximo += flujoCamino;
    }

    return flujoMaximo;
}

void freeRed(Red *red) {
    for (int i = 0; i < V; i++) {
        free(red->capacidades[i]);
    }
    free(red->capacidades);
    red->capacidades = NULL;
}

void freeBfs(BreadthFirstSearch *bfs) {
    free(bfs->visitados);
    free(bfs->camino);
    bfs->visitados = NULL;
    bfs->camino = NULL;
}

/**
 * Libera la memoria dinámica utilizada.
 * @param red puntero a la estructura red (matriz de adyacencia).
 * @param bfs puntero a la estructura bfs.
 * @param fuente Nodo fuente para el flujo.
 * @param sumidero Nodo sumidero para el flujo.
 * @return Flujo máximo en la red.
 */
void freeMemory(Red *red, BreadthFirstSearch* bfs) {
    freeRed(red);
    freeBfs(bfs);
}

/**
 * Función principal que utiliza el algoritmo de Ford-Fulkerson para encontrar el flujo máximo.
 * @return 0 si la ejecución fue exitosa.
 */
int main(void) {
    Red red;
    BreadthFirstSearch bfs;

    const int matrizAdyacencia[V][V] = {
        {0, 8, 5, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 9, 0, 0, 0},
        {0, 3, 0, 0, 0, 4, 0, 0},
        {0, 0, 6, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 3, 0, 8},
        {0, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 2, 0, 9},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    inicializarRed(&red, matrizAdyacencia);

    int fuente = 0;
    int sumidero = 7;

    printf("El flujo máximo posible es: %d\n", fordFulkerson(&red, &bfs, fuente, sumidero));

    freeMemory(&red, &bfs);

    return 0;
}