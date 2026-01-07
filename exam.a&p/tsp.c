#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_CITIES 20
#define INF 999999

typedef struct {
    int matrix[MAX_CITIES][MAX_CITIES]; // матрица затрат на данной стадии
    int n; // размер
    int visited[MAX_CITIES]; // посещенные города отмеченные флагами
    int path[MAX_CITIES]; // посещенные города
    int pathLen; // длина пути в городах
    int lowerBound; // нижняя граница затрат на данной стадии
} State;

int bestCost = INF;
int bestPath[MAX_CITIES];
int bestPathLen = 0;

void printMatrix(int matrix[][MAX_CITIES], int n);
int reduceRows(int matrix[][MAX_CITIES], int n);
int reduceColumns(int matrix[][MAX_CITIES], int n);
int reduceMatrix(int matrix[][MAX_CITIES], int n);
void copyMatrix(int dest[][MAX_CITIES], int src[][MAX_CITIES], int n);
void branchAndBound(State state, int start, int end);
void solveLittle(int matrix[][MAX_CITIES], int n, int start, int end);

int main(void) {
    int n = 6;
    int matrix[MAX_CITIES][MAX_CITIES] = {
        //  A    V1   V2   V3   V4   B
        {INF,  10,  15, INF, INF, INF},  // A
        {INF, INF, INF,  20, INF,  25},  // V1
        {INF, INF, INF,  20, INF, INF},  // V2
        {INF, INF, INF, INF,  10,  30},  // V3
        {INF, INF, INF, INF, INF,  35},  // V4
        {INF, INF, INF, INF, INF, INF}   // B
    };
    
    printf("Исходная матрица стоимостей:");
    printMatrix(matrix, n);

    solveLittle(matrix, n, 0, 5);
    
    return 0;
}

void solveLittle(int matrix[][MAX_CITIES], int n, int start, int end) {

    State initialState;
    initialState.n = n;
    initialState.pathLen = 1;
    initialState.path[0] = start;
    initialState.visited[start] = 1;
    for (int i = 1; i < n; i++) {
        initialState.visited[i] = 0;
    }
    
    copyMatrix(initialState.matrix, matrix, n);
    initialState.lowerBound = reduceMatrix(initialState.matrix, n);
    
    branchAndBound(initialState, start, end);
    
    if (bestCost == INF) {
        printf("Путь не найден!\n");
    } else {
        printf("Кратчайший путь: ");
        for (int i = 0; i < bestPathLen; i++) {
            printf("%d ", bestPath[i]);
        }
        printf("\nСтоимость: %d\n", bestCost);
    }
}

void branchAndBound(State state, int start, int end) {
    if (state.pathLen > 0 && state.path[state.pathLen - 1] == end) { // базовый случай (дошли до конца)
        if (state.lowerBound < bestCost) {
            bestCost = state.lowerBound;
            bestPathLen = state.pathLen;
            memcpy(bestPath, state.path, state.pathLen * sizeof(int));
            
            printf("\n*** Найден лучший путь с стоимостью %d ***\n", bestCost);
            printf("Путь: ");
            for (int i = 0; i < bestPathLen; i++) {
                printf("%d ", bestPath[i]);
            }
            printf("\n");
        }
        return;
    }
    
    if (state.lowerBound >= bestCost) { // уже превышает границу
        return;
    }
    
    int current = (state.pathLen == 0) ? start : state.path[state.pathLen - 1]; // текущий город
    
    for (int next = 0; next < state.n; next++) {
        if (state.visited[next] || state.matrix[current][next] == INF) { // посещен или сам в себя
            continue;
        }
        
        State newState;
        newState.n = state.n;
        newState.pathLen = state.pathLen + 1;
        newState.lowerBound = state.lowerBound + state.matrix[current][next];
        
        memcpy(newState.path, state.path, state.pathLen * sizeof(int));
        newState.path[state.pathLen] = next; // добавляем в новую стадию посещенный город
        memcpy(newState.visited, state.visited, state.n * sizeof(int));
        newState.visited[next] = 1; // отмечаем 1
        copyMatrix(newState.matrix, state.matrix, state.n); // записываем матрицу
        
        for (int i = 0; i < state.n; i++) {
            newState.matrix[current][i] = INF; // из текущей вершины
            newState.matrix[i][next] = INF;     // в следующую вершину
        }
        newState.matrix[next][current] = INF; // обратный путь
        
        int reduction = reduceMatrix(newState.matrix, newState.n);
        newState.lowerBound += reduction;
        
        branchAndBound(newState, start, end);
    }
}

void printMatrix(int matrix[][MAX_CITIES], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF)
                printf("  ∞ ");
            else
                printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int reduceRows(int matrix[][MAX_CITIES], int n) {
    int reduction = 0;
    for (int i = 0; i < n; i++) {
        int minVal = INF;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        if (minVal != INF && minVal > 0) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minVal;
                }
            }
            reduction += minVal;
        }
    }
    return reduction;
}

int reduceColumns(int matrix[][MAX_CITIES], int n) {
    int reduction = 0;
    for (int j = 0; j < n; j++) {
        int minVal = INF;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        if (minVal != INF && minVal > 0) {
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minVal;
                }
            }
            reduction += minVal;
        }
    }
    return reduction;
}

int reduceMatrix(int matrix[][MAX_CITIES], int n) {    
    int rowReduction = reduceRows(matrix, n);
    int colReduction = reduceColumns(matrix, n);   
    return rowReduction + colReduction;
}

void copyMatrix(int dest[][MAX_CITIES], int src[][MAX_CITIES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}