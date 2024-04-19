# Assignment: programming assignment 4
# Author: Aidan Kammerman
# Date: December 1st, 2020
# File: cipher.py is a program that encodes a message of the user's choice or decodes a previously encoded
# message inputted by the user using a Caesar Cipher.
# Input: User inputted strings / files
# Output: Encoded / Decoded messages through files / strings
# read text from a file and return text as a string

def readfile(file):
    f = open(file, "r")
    fstring = f.read()
    return fstring


# write a string (message) to a file (code.txt)
def writefile(string):
    File_object = open("code.txt", "w")
    File_object.write(string)


# write a string (message) to a file (plain.txt)
def writefilee(string):
    File_object = open("plain.txt", "w")
    File_object.write(string)


# make a list (tuple) of letters in the English alphabet
def make_alphabet():
    alphabet = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    for i in range(26):
        char = i + 65
        alphabet += (str(chr(char), ))
    # print (alphabet)
    return alphabet


# encode text letter by letter using a Caesar cipher
# return a list of encoded symbols
def encode(plaintext):
    plaintext = plaintext.upper()
    shift = 3
    ciphertext = []
    alphabet = make_alphabet()
    length = len(alphabet)
    for char in plaintext:
        found = False
        for i in range(length):
            if char == alphabet[i]:
                letter = alphabet[(i + shift) % length]
                ciphertext.append(letter)
                found = True
                break
        if not found:
            ciphertext.append(char)
    return ciphertext


# decode text letter by letter using a Caesar cipher
# return a list of decoded symbols
# check how the function encode() is implemented
# your implementation of the function decode() can be very similar
# to the implementation of the function encode()
def decode(text):
    shift = -3
    plaintext = []
    alphabet = make_alphabet()
    length = len(alphabet)
    for char in text:
        found = False
        for i in range(length):
            if char == alphabet[i]:
                letter = alphabet[(i + shift) % length]
                plaintext.append(letter)
                found = True
                break
        if not found:
            plaintext.append(char)
    return plaintext


# convert a list into a string
# for example, the list ["A", "B", "C"] to the string "ABC" or
# the list ["H", "O", "W", " ", "A", "R", "E", " ", "Y", "O", "U", "?"] to the string "HOW ARE YOU?"
def to_string(list):
    s = ""
    for item in list:
        s += item
    return s


# main program
while (True):
    print("Would you like to encode or decode the message?")
    choice = input("Type E to encode, D to decode, or Q to quit: ")

    if choice.upper() == "Q" or choice == "q":
        print("\nGoodbye!")
        break

    elif choice.upper() == "E" or choice == "e":
        file = input("Please enter a file for reading: ")
        writey = input("Please enter a file for writing: ")
        print("\nPlaintext:\n" + readfile(file) + "\n")
        print("Ciphertext:\n" + to_string(encode(readfile(file))) + "\n")
        string1 = to_string(encode(readfile(file)))
        writefile(string1)
    elif choice.upper() == "D" or choice == "d":
        file = input("Please enter a file for reading: ")
        writey = input("Please enter a file for writing: ")
        print("\nCiphertext:\n" + readfile(file) + "\n")
        print("Plaintext:\n" + to_string(decode(readfile(file))) + "\n")
        string2 = to_string(decode(readfile(file)))
        writefilee(string2)
    else:
        True == True

    try:
        a = 1
    except:
        a = 2
