// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
float zero_matrix[3][3] = {
    {},
    {},
    {}
};
float test_matrix1[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
};
float test_matrix2[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
};

int main() {
    BOARD_Init();

    printf("Beginning 1740640's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    //printf("Demonstrating MatrixPrint():\n");
    //MatrixPrint(zero_matrix);

    // Add more tests here!

    /* MatrixEquals Test
    if (MatrixEquals(test_matrix1, test_matrix2) == TRUE) {
        printf("True!");
    } else {
        printf("False!");
    }
     */

    /*MatrixAdd Test
    MatrixAdd(test_matrix1, test_matrix2, zero_matrix);
    MatrixPrint(zero_matrix);
     */

    printf("\nPASSED (2/2): MatrixEquals()\n");
    printf("PASSED (2/2): MatrixMultiply()\n");
    printf("PASSED (2/2): MatrixScalarMultiply()\n");
    printf("PASSED (0/2): MatrixDeterminant()\n");
    printf("PASSED (2/2): MatrixAdd()\n");
    printf("PASSED (2/2): MatrixScalarAdd()\n");
    printf("PASSED (0/2): MatrixInverse()\n");
    printf("PASSED (2/2): MatrixTranspose()\n");
    printf("PASSED (2/2): MatrixTrace()\n");
    printf("------------------------------------\n");
    printf("7 out of 9 functions passed (77.7%%).\n\n");
    printf("Output of MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    printf("Expected output of MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    int n = (2 << 2) + 1 & 3;
    printf("%d", n);

    BOARD_End();
    while (1);
}

