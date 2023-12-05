#include <stdio.h>
#include <limits.h>
#include <string.h>

#define V 6 // Número de vértices en el gráfico dado
#define true 1
#define false 0
#define lower(X, Y) ( (X < Y) ? X : Y )

int busqueda_camino(int red_aux[V][V], int fuente, int sumidero, int semicamino[]);
int fordFulkerson(int red[V][V], int fuente, int sumidero);

// Red como matríz de adyacencia.
int red[V][V] = {
  {0, 4, 6, 0, 0, 0},
  {0, 0, 0, 3, 5, 0},
  {0, 0, 0, 0, 6, 0},
  {0, 0, 9, 0, 0, 5},
  {0, 0, 0, 0, 0, 4},
  {0, 0, 0, 0, 0, 0}
};