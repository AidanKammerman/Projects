Lab 5 README File
CSE 13E Spring 2021
Aidan Kammerman
1760640
5/6/2021

Results of the timing experiment in sort.c :

SelectionSort(): 49.271 ms
InsertionSort(): 28.183 ms

It is clear that InsertionSort() is faster by about 21 ms. This is consistently true because the best case scenario
for InsertionSort() is O(n) while the best case scenario for SelectionSort() is O(n^2) as expressed by
Big Oh Notation for determining the time. The average and worst cases for both sorting methods are O(n^2), so it is clear
that InsertionSort()will always be faster than SelectionSort(). This is what I expected because I have had prior 
experience with both of these sorting methods among others like bubblesort() and mergesort() in my AP CompSci Class
in high school.

In this lab, we were tasked with completing various functions pertaining to the creating and modification of 
Linked Lists. We had to figure out how to add elements to a Linked List and modify their position as well.
We also had to figure out how to traverse through the Linked List in order to get to the first and last elements.
The most important aspects of this lab included the creation of multiple test harnesses for each function as well as 
the proper implementation of these functions in our two unique sorting methods. We had to have a very firm understanding
of how pointers work and we also had to create many error catch systems in the event that we were trying to modify 
the head or tail element of our Linked List. These goals did not differ from how the lab manual presented things as 
far as I am aware of.

My general approach to the lab was to figure out how to create a new linked list first because it was necessary that
this step functioned properly before moving on to any of the additional functions. From there, I read through the manual 
and followed the "Approaching this lab" steps as best I could. I figured out that it was necessary to get my 
LinkedListGetFirst() function working properly before attempting the LinkedListGetSize() function, although the order 
of these functions is swapped on the LinkedList_Template.c file that we were provided with. I kept getting this error:
W0011-CORE: Access attempt to unimplemented RAM memory. It was frustrating me for a long time until I realized that 
my Null Checkers for the head and tail elements of the list were not properly implemented at first. Once I made this fix,
it became much easier to complete the remainder of the lab. I probably would not approach this lab differently if I had a
second chance other than starting earlier to ensure that I could get it turned in on time.

After about 20+ hours, my lab finally ended up functioning properly. I liked that the pseudocode was provided for
the two sorting methods as it made it much easier to code them in a timely manner. I disliked the idea of Linked Lists
at firs because I didn't fully understand them, but after completing this lab they have actually grown on me a lot. Overall,
this was a very worthwhile lab and I am happy that I stuck with it long enough to understand it fully. The point distribution
seemed fair and appropriate, and the lab manual as well as the lectures covered the material well enough for me to get a firm
grasp on the information after scanning through it many times.