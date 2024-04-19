#assignment: programming assignment 3
#author: Aidan Kammerman
#file: calculator.py is a program that simulates a simple calculator, taking in number inputs from the user
#and returning the correct outputs depending on which mathematical operation is selected by the user. It also
#will contain an error catch system that causes the program to never end prematurely regardless of user input.
# input: Any numbers, including floats, decimals, and integers. Will also provide error catch for strings if entered.
# output: integers, floats or decimals corresponding to correct mathematical operation of numbers provided. Also returns
#strings if an inputting error occurs.

import math

def isfloat (token) :
    dot = False
    minus = False
    for char in token :
        if char.isdigit() :  # allow many digits in a string
            continue
        elif char == "." :   # allow only one dot in a string
            if not dot :
                dot = True
            else :
                return False
        elif char == "-" and token[0] == "-": # allow one minus in front
            if not minus :
                minus = True
            else :
                return False
        else :               # do not allow any other characters in a string
            return False
    return True

def format (num, precision = 2):
    num = round(float(num), 2)
    if (num % 1) == 0:
        num = (int(num))
    return num

def add (num1, num2):
     sum = num1 + num2
     sum = format(sum)
     num1 = format(num1)
     num2 = format(num2)
     print(str(num1) + " + " + str(num2) + " = " + str(sum))
def subtract (num1, num2):
     dif = num1 - num2
     num1 = format(num1)
     num2 = format(num2)
     dif = format(dif)
     print(str(num1) + " - " + str(num2) + " = " + str(dif))
def multiply (num1, num2):
     prod = num1 * num2
     num1 = format(num1)
     num2 = format(num2)
     prod = format(prod)
     print(str(num1) + " x " + str(num2) + " = " + str(prod))
def divide (num1, num2):
     quotient = num1 / num2
     num1 = format(num1)
     num2 = format(num2)
     quotient = format(quotient)
     print(str(num1) + " / " + str(num2) + " = " + str(quotient))

print("Welcome to Calculator Program!")

bool = True

while bool == True:

    choice = input("Please choose one of the following operations:\nAddition - A\nSubtraction - S\nMultiplication - M\nDivision - D\n> ")

    while choice not in ("ASMD"):
        choice = input("You did not choose correctly.\nPlease choose one of the following operations:\nAddition - A\nSubtraction - S\nMultiplication - M\nDivision - D\n> ")

    if choice == "A":
        print("You chose addition.")
    elif choice == "S":
        print("You chose subtraction.")
    elif choice == "M":
        print("You chose multiplication.")
    elif choice == "D":
        print("You chose Division.")

    firstnum = input("Please enter the first number: ")
    value = isfloat(firstnum)
    while value == False:
        firstnum = input("You did not choose a number.\nPlease enter the first number: ")
        value = isfloat(firstnum)
    num1 = float(firstnum)
    print("The first number is " + firstnum + ".")
    secondnum = input("Please enter the second number: ")
    value2 = isfloat(secondnum)
    while value2 == False:
        secondnum = input("You did not choose a number.\nPlease enter the second number: ")
        value2 = isfloat(secondnum)
    num2 = float(secondnum)
    print("The second number is " + secondnum + ".")

    if (choice == "D" and format (num2) == 0):
        print("The division by zero is prohibited!")
    elif choice == "A":
        add (num1,num2)
    elif choice == "S":
        subtract (num1, num2)
    elif choice == "M":
        multiply (num1, num2)
    else:
        divide (num1, num2)

    con = input("Do you want to continue? [Y/N]: ")
    while con not in "YyNn":
        con = input("Do you want to continue? [Y/N]: ")
    if con in "Yy":
        bool = True
    elif con in "Nn":
        bool = False
        print("Goodbye!")