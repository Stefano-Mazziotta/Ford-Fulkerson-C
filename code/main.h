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

typedef struct {
    int **capacidades;
} Red;

typedef struct {
    int *visitados;
    int *camino;
} BreadthFirstSearch;

void inicializarRed( Red *red, const int matriz[V][V]);

bool bfsAlgorithm(const Red *red, BreadthFirstSearch *bfs, int fuente, int sumidero);
int fordFulkerson(Red *red, BreadthFirstSearch *bfs, int fuente, int sumidero);

void freeRed(Red *red);
void freeBfs(BreadthFirstSearch *bfs);
void freeMemory(Red *red, BreadthFirstSearch* bfs);

#endif