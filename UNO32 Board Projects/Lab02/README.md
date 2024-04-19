CSE 13E Lab 2 

Aidan Kammerman 1760640

4/14/2021

Spring 2021

What happens if the line “scanf(" ");” executes? Why?

If this code statement executes, it will still prompt the user
for an input however it won't be able to store it anywhere for later recollection.
This is because the scanf() function requires at least one argument in order to successfully store an input.

In this lab, we forbid you from using printf() or scanf() inside of certain
functions. Explain why a rule like this is useful.

A rule like this one would be useful in case we need to call certain functions within other functions
as a sort of intermediate step without necessarily printing the values obtained along the way.
We also pre-define a certain amount of arguments that a function requires and these arguments should
definitely be established before the actual execution of the function itself.

How long did this lab take you? Was it harder or easier than you expected?

This lab took me about 10 hours. It was actually much easier than I expected once 
I started to get the hang of the program flow and syntax. Much of it was simply repetition of else-if statements.
