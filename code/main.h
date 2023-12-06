// redflujo.h
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define V 6
#define lower(X, Y) ( (X < Y) ? X : Y )

struct RedFlujo {
    int **capacidad;
};

struct BusquedaAmplitud {
    int *visitado;
    int *camino;
};

void inicializarRedFlujoDesdeMatriz(struct RedFlujo* redFlujo, const int matriz[V][V]);
bool busquedaAmplitud(const struct RedFlujo* red, int fuente, int sumidero, struct BusquedaAmplitud* bfs);
int fordFulkerson(struct RedFlujo* red, int fuente, int sumidero);
void freeRedFlujo(struct RedFlujo* redFlujo);

#endif