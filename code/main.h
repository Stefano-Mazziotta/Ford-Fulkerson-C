// redflujo.h
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define V 6
#define lower(X, Y) ( (X < Y) ? X : Y )

struct RedFlujo {
  int capacidad[V][V];
};

struct BusquedaAmplitud {
  int visitado[V];
  int camino[V];
};

void inicializarRedFlujoDesdeMatriz(struct RedFlujo* redFlujo, const int matriz[V][V]);
int busquedaAmplitud(const struct RedFlujo* red, int fuente, int sumidero, struct BusquedaAmplitud* bfs);
int fordFulkerson(struct RedFlujo* red, int fuente, int sumidero);

#endif