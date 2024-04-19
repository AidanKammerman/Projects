Lab 7 README File
CSE 13E Spring 2021
Aidan Kammerman
1760640
5/19/2021

In this lab, we were tasked with simulating a toaster oven user interface through the use of a state machine with different
modes. We had to allow the time and temperature to be altered through changing the position of the dial on the 
potentiometer. We also had to display LED's that decremented as the remaining cooking time approached zero. We also had 
to figure out how to get all of the necessary values displayed to reset back to their original states if the cooking 
happened to be cancelled partway through. The most important aspect of this lab in my opinion was determining how to 
switch between the states of the state machine when appropriate.

My general approach to this lab started with reading through the lab manual and establishing the necessary structures
and constants for it to function properly. I wrote the updateOvenOled() function first to make sure that the data would
be displayed properly. I then tested this function with varying input from the Oven struct that I created. Next, I created
the setup state constants so that the correct oven state would be displayed on the OLED. I then added the potentiometer,
button, and second events so that the OLED would be updated accordingly when each flag was triggered. After that, I had to
figure out how to determine how long a button had been pressed down, which was probably the most difficult part of this lab
for me. After everything had been implemented correctly according to the lab manual and rubric, I had to comment my code
so that it would be more easily interpreted by the grader. I did not get around to the extra credit this time.

After about 25 hours, I completed the lab and it worked exactly as depicted in the Lab 7 demo video. I liked the mini oven
display and how it changed based on which state that it's in. I struggled with getting my button input to actually trigger
an event for a long time but eventually I figured it out. Overall, this was a very worthwhile lab that taught me a great 
deal about how state machines are supposed to function. The points distribution seems fair and the lab manual definitely 
covered enough material this time for me to get started. The lab sections were also very helpful and I am very thankful
for the TA's that hosted them.