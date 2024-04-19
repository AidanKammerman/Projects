/*
 * File:   Calculator.c
 * Author: Aidan Kammerman
 *
 * Created on April 12, 2021, 6:36 PM
 * 
 */

// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"




// **** Declare function prototypes ****
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Average(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Round(double operand);

void CalculatorRun(void) {
    printf("\n\nWelcome to Aidan's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    // Your code here

    while (1) {
        char g;
        double op1;
        double op2;
        double sum;
        double result;
        char trash;
        printf("\nEnter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,r): ");
        scanf("%c%c", &g, &trash);
        if (!(g == '*' || g == '/' || g == '+' || g == '-' || g == 'm' || g == 'a' || g == 'c' || g == 'f' || g == 't' || g == 'r' || g == 'q')) {
            g = 0;
            printf("Error, not a valid operator\n");
        }
        if (g == 'q') {
            return;
        }

        if (g != 0) {
            printf("   Enter the first operand: ");
            scanf("%lf%c", &op1, &trash);

        }
        if (g == '*' || g == '/' || g == '+' || g == '-' || g == 'm') {
            printf("   Enter the second operand: ");
            scanf("%lf%c", &op2, &trash);
        }
        if (g == '+') {
            result = Add((double) op1, (double) op2);
            printf("   Result of (%lf + %lf): %lf\n", op1, op2, result);
        } else if (g == '*') {
            result = Multiply((double) op1, (double) op2);
            printf("   Result of (%lf * %lf): %lf\n", op1, op2, result);
        } else if (g == '/') {
            if (op2 == 0) {
                printf("   Divide by zero error!\n");
            } else {
                result = Divide((double) op1, (double) op2);
                printf("   Result of (%lf / %lf): %lf\n", op1, op2, result);
            }
        } else if (g == '-') {
            result = Subtract((double) op1, (double) op2);
            printf("   Result of (%lf - %lf): %lf\n", op1, op2, result);
        } else if (g == 'm') {
            result = Average((double) op1, (double) op2);
            printf("   The average of %lf and %lf: %lf\n", op1, op2, result);
        } else if (g == 'a') {
            result = AbsoluteValue((double) op1);
            printf("   Result of |%lf|: %lf\n", op1, result);
        } else if (g == 'c') {
            result = FahrenheitToCelsius((double) op1);
            printf("   Result of (%lf deg->C): %lf\n", op1, result);
        } else if (g == 'f') {
            result = CelsiusToFahrenheit((double) op1);
            printf("   Result of (%lf deg->F): %lf\n", op1, result);
        } else if (g == 't') {
            result = Tangent((double) op1);
            printf("   Result of tan(%lf): %lf\n", op1, result);
        } else if (g == 'r') {
            result = Round((double) op1);
            printf("   Result of round(%lf): %lf\n", op1, result);
        }
    }
    while (1); // this while(1) can be removed as needed.

}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    return operand1 * operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {
    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand) {
    if (operand < 0) {
        operand = operand * -1;
    }
    return operand;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand) {
    return (5.0 / 9.0)*(operand - 32.0);
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand) {
    return (9.0 / 5.0)*(operand) + (32.0);
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2) {
    double sum = operand1 + operand2;
    return (sum / 2);
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand) {
    return tan(operand * (3.14159265 / 180));
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    int whole = operand;
    if (operand > 0) {
        double partial = operand - whole;
        if (partial < .5) {
            return whole;
        } else {
            return whole + 1;
        }
    } else {
        double partial = operand - whole;
        if (partial <= -.5) {
            return whole - 1;
        } else {
            return whole;
        }
    }
}


