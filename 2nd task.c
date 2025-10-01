#include <stdio.h>

#define MAX 10

void inputMatrix(int mat[MAX][MAX], int rows, int cols) {
    printf("Enter elements (%dx%d):\n", rows, cols);
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            scanf("%d", &mat[i][j]);
}

void printMatrix(int mat[MAX][MAX], int rows, int cols) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void addMatrix(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int rows, int cols) {
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            res[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX], int res[MAX][MAX], int r1, int c1, int r2, int c2) {
    for(int i=0; i<r1; i++)
        for(int j=0; j<c2; j++) {
            res[i][j] = 0;
            for(int k=0; k<c1; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
}

void transposeMatrix(int mat[MAX][MAX], int res[MAX][MAX], int rows, int cols) {
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            res[j][i] = mat[i][j];
}

int main() {
    int a[MAX][MAX], b[MAX][MAX], res[MAX][MAX];
    int r1, c1, r2, c2;

    printf("Enter rows and columns for Matrix A: ");
    scanf("%d%d", &r1, &c1);
    inputMatrix(a, r1, c1);

    printf("Enter rows and columns for Matrix B: ");
    scanf("%d%d", &r2, &c2);
    inputMatrix(b, r2, c2);

    // Addition
    if(r1 == r2 && c1 == c2) {
        addMatrix(a, b, res, r1, c1);
        printf("Addition Result:\n");
        printMatrix(res, r1, c1);
    } else {
        printf("Addition not possible (size mismatch).\n");
    }

    // Multiplication
    if(c1 == r2) {
        multiplyMatrix(a, b, res, r1, c1, r2, c2);
        printf("Multiplication Result:\n");
        printMatrix(res, r1, c2);
    } else {
        printf("Multiplication not possible (size mismatch).\n");
    }

    // Transpose
    printf("Transpose of Matrix A:\n");
    transposeMatrix(a, res, r1, c1);
    printMatrix(res, c1, r1);

    printf("Transpose of Matrix B:\n");
    transposeMatrix(b, res, r2, c2);
    printMatrix(res, c2, r2);

    return 0;
}