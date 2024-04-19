#include "MatrixMath.h"
#include <stdlib.h>
#include "BOARD.h"
#include <string.h>

int i;
int j;
int z;
float a;
float b;

/******************************************************************************
 * Matrix Display:
 *****************************************************************************/

/**
 * MatrixPrint displays a 3x3 array to standard output with clean, readable, 
 * consistent formatting.  
 * @param: mat, pointer to a 3x3 float array
 * @return: none
 * The printed matrix should be aligned in a grid when called with positive or
 *  negative numbers.  It should be able to display at least FP_DELTA precision, and
 *  should handle numbers as large as 999.0 or -999.0
 */
void MatrixPrint(float mat[3][3]) {
    printf(" ___________________________________\n");
    printf("| %09.4f | %09.4f | %09.4f |\n", mat[0][0], mat[0][1], mat[0][2]);
    printf(" -----------------------------------\n");
    printf("| %09.4f | %09.4f | %09.4f |\n", mat[1][0], mat[1][1], mat[1][2]);
    printf(" -----------------------------------\n");
    printf("| %09.4f | %09.4f | %09.4f |\n", mat[2][0], mat[2][1], mat[2][2]);
    printf(" -----------------------------------\n");
}

/******************************************************************************
 * Matrix - Matrix Operations
 *****************************************************************************/

/**
 * MatrixEquals checks if the two matrix arguments are equal (to within FP_DELTA).
 * @param: mat1, pointer to a 3x3 float array
 * @param: mat2, pointer to a 3x3 float array
 * @return: TRUE if and only if every element of mat1 is within FP_DELTA of the corresponding element of mat2,  otherwise return FALSE
 * Neither mat1 nor mat2 is modified by this function.
 */
int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            a = (mat1[i][j] - mat2[i][j]);
            if (a < 0) {
                a = a * -1;
            }
            if (a > FP_DELTA) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/**
 * MatrixAdd performs an element-wise matrix addition operation on two 3x3 matrices and 
 * "returns" the result by modifying the third argument.
 * @param: mat1, pointer to a summand 3x3 matrix
 * @param: mat2, pointer to a summand 3x3 matrix
 * @param: result, pointer to a 3x3 matrix that is modified to contain the sum of mat1 and mat2.
 * @return:  None
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];

        }
    }
}

/**
 * MatrixMultiply performs a matrix-matrix multiplication operation on two 3x3
 * matrices and "returns" the result by modifying the third argument.
 * @param: mat1, pointer to left factor 3x3 matrix
 * @param: mat2, pointer to right factor 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain the matrix product of mat1 and mat2.
 * @return: none
 * mat1 and mat2 are not modified by this function.  result is modified by this function.
 */
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (z = 0; z < DIM; z++) {
                result[i][j] += mat1[i][z] * mat2[z][j];
            }
        }
    }
}


/******************************************************************************
 * Matrix - Scalar Operations
 *****************************************************************************/

/**
 * MatrixScalarAdd performs the addition of a matrix and a scalar.  Each element of the matrix is increased by x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]) {
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            result[i][j] = mat[i][j] + x;

        }
    }
}

/**
 * MatrixScalarAdd performs the multiplication of a matrix and a scalar.
 * Each element of the matrix is multiplied x.
 * The result is "returned"by modifying the third argument.
 * @param: x, a scalar float
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to contain mat + x.
 * @return: none
 * x and mat are not modified by this function.  result is modified by this function.
 */
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            result[i][j] = mat[i][j] * x;

        }
    }
}


/******************************************************************************
 * Unary Matrix Operations
 *****************************************************************************/

/**
 * MatrixTrace calculates the trace of a 3x3 matrix.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the trace of mat
 */
float MatrixTrace(float mat[3][3]) {
    return mat[0][0] + mat[1][1] + mat[2][2];
}

/**
 * MatrixTranspose calculates the transpose of a matrix and "returns" the
 * result through the second argument.
 * @param: mat, pointer to a 3x3 matrix
 * @param: result, pointer to matrix that is modified to transpose of mat
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixTranspose(float mat[3][3], float result[3][3]) {
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            result[i][j] = mat[j][i];
        }
    }
}

/**
 * MatrixSubmatrix finds a submatrix of a 3x3 matrix that is 
 * formed by removing the i-th row and the j-th column.  The 
 * submatrix is "returned" by modifying the final argument.
 * 
 * @param: i, a row of the matrix, INDEXING FROM 0
 * @param: j, a column of the matrix, INDEXING FROM 0
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 2x2 matrix
 * @return: none
 * 
 * mat is not modified by this function.  Result is modified by this function.
 */
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]) {
    if (i == 0 && j == 0) {
        result[0][0] = mat[1][1];
        result[0][1] = mat[1][2];
        result[1][0] = mat[2][1];
        result[1][1] = mat[2][2];
    } else if (i == 0 && j == 1) {
        result[0][0] = mat[1][0];
        result[0][1] = mat[1][2];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][2];
    } else if (i == 0 && j == 2) {
        result[0][0] = mat[1][0];
        result[0][1] = mat[1][1];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][1];
    } else if (i == 1 && j == 0) {
        result[0][0] = mat[0][1];
        result[0][1] = mat[0][2];
        result[1][0] = mat[2][1];
        result[1][1] = mat[2][2];
    } else if (i == 1 && j == 1) {
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][2];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][2];
    } else if (i == 1 && j == 2) {
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][1];
        result[1][0] = mat[2][0];
        result[1][1] = mat[2][1];
    } else if (i == 2 && j == 0) {
        result[0][0] = mat[0][1];
        result[0][1] = mat[0][2];
        result[1][0] = mat[1][1];
        result[1][1] = mat[1][2];
    } else if (i == 2 && j == 1) {
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][2];
        result[1][0] = mat[1][0];
        result[1][1] = mat[1][2];
    } else if (i == 2 && j == 2) {
        result[0][0] = mat[0][0];
        result[0][1] = mat[0][1];
        result[1][0] = mat[1][0];
        result[1][1] = mat[1][1];
    }
}

/**
 * MatrixDeterminant calculates the determinant of a 3x3 matrix 
 * and returns the value as a float.
 * @param: mat, a pointer to a 3x3 matrix
 * @return: the determinant of mat
 * mat is not modified by this function.
 * */
float MatrixDeterminant(float mat[3][3]){

}


/* MatrixInverse calculates the inverse of a matrix and
 * "returns" the result by modifying the second argument.
 * @param: mat, a pointer to a 3x3 matrix
 * @param: result, a pointer to a 3x3 matrix that is modified to contain the inverse of mat
 * @return: none
 * mat is not modified by this function.  result is modified by this function.
 */
void MatrixInverse(float mat[3][3], float result[3][3]){
    
}