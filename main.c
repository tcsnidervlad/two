#include <stdio.h>
#include <malloc.h>
#include <math.h>
# include <stdbool.h>
# include <assert.h>


typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

void outPutPos(position m) {
    printf("(%d,%d)", m.rowIndex, m.colIndex);

}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}


matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}


void freeMemMatrix(matrix m) {
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(ms[i]);
    }
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d ", &m.values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(ms[i]);
    }
}


void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%4d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}


void swapRows(matrix m, int i1, int i2) {
    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nRows; i++) {
        swap(&m.values[i][j1], &m.values[i][j2]);
    }
}


bool isSquareMatrix(matrix m) {
    return m.nCols == m.nRows;
}

bool twoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols)
        return 0;
    else {
        for (int i = 0; i < m1.nRows; i++) {
            for (int j = 0; j < m1.nCols; j++) {
                if (m1.values[i][j] != m2.values[i][j])
                    return 0;
            }
        }
    }
    return 1;
}

bool isEMatrix(matrix m) {
    int i = 0;
    if (!isSquareMatrix(m))
        return 0;
    while (i < m.nRows) {
        if (m.values[i][i] != 1)
            return 0;
        i++;
    }
    return 1;
}


void transposeSquareMatrix(matrix m) {
    int t;
    for (int i = 0; i < m.nRows; ++i) {
        for (int j = i; j < m.nCols; ++j) {
            t = m.values[i][j];
            m.values[i][j] = m.values[j][i];
            m.values[j][i] = t;
        }
    }
}

void transpose(matrix m, int tr[m.nCols][m.nRows]) {
    for (int i = 0; i < m.nCols; i++)
        for (int j = 0; j < m.nRows; j++)
            tr[i][j] = m.values[j][i];
}

bool isSymmetricMatrix(matrix m) {
    int tr[m.nCols][m.nRows];
    transpose(m, tr);
    for (int i = 0; i < m.nCols; i++) {
        for (int j = 0; j < m.nRows; j++) {
            if (m.values[i][j] != tr[i][j])
                return false;
        }
    }
    return true;
}

position getMinValuePos(matrix m) {
    int minIndex = 0;
    int minIndex1 = 0;
    int min = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (min > m.values[i][j]) {
                min = m.values[i][j];
                minIndex = i;
                minIndex1 = j;
            }
        }
    }
    return (position) {minIndex, minIndex1};
}


position getMaxValuePos(matrix m) {
    int maxIndex = 0;
    int maxIndex1 = 0;
    int max = m.values[0][0];
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (max < m.values[i][j]) {
                max = m.values[i][j];
                maxIndex = i;
                maxIndex1 = j;
            }
        }
    }
    return (position) {maxIndex, maxIndex1};
}


matrix createMatrixFromArray(const int *a,
                             int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values,
                                     int nMatrices, int nRows, int nCols) {

    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}


int main() {

    return 0;
}
