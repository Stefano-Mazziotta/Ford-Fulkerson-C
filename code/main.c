#include "index.h"

void inicializarRedFlujoDesdeMatriz(struct RedFlujo* redFlujo, const int matriz[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            redFlujo->capacidad[i][j] = matriz[i][j];
        }
    }
}

int busquedaAmplitud(const struct RedFlujo* red, int fuente, int sumidero, struct BusquedaAmplitud* bfs) {
    memset(bfs->visitado, 0, sizeof(bfs->visitado));
    memset(bfs->camino, -1, sizeof(bfs->camino));

    int cola[V];
    int frente = 0, fin = 0;

    cola[fin++] = fuente;
    bfs->visitado[fuente] = true;

    while (frente < fin) {
        int u = cola[frente++];

        for (int v = 0; v < V; v++) {
            if (!bfs->visitado[v] && red->capacidad[u][v] > 0) {
                cola[fin++] = v;
                bfs->camino[v] = u;
                bfs->visitado[v] = true;
            }
        }
    }

    return (bfs->visitado[sumidero] == true);
}

int fordFulkerson(struct RedFlujo* red, int fuente, int sumidero) {
    struct RedFlujo redResidual = *red;
    int flujoMaximo = 0;

    struct BusquedaAmplitud bfs;

    while (busquedaAmplitud(&redResidual, fuente, sumidero, &bfs)) {
        int flujoCamino = INT_MAX;

        // Encuentra la capacidad mínima en el camino de aumento
        for (int v = sumidero; v != fuente; v = bfs.camino[v]) {
            int u = bfs.camino[v];
            flujoCamino = lower(flujoCamino, redResidual.capacidad[u][v]);
        }

        // Actualiza las capacidades en el grafo residual
        for (int v = sumidero; v != fuente; v = bfs.camino[v]) {
            int u = bfs.camino[v];
            redResidual.capacidad[u][v] -= flujoCamino;
            redResidual.capacidad[v][u] += flujoCamino; // Añadir flujo en sentido opuesto
        }

        flujoMaximo += flujoCamino;
    }

    return flujoMaximo;
}

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

    return 0;
}