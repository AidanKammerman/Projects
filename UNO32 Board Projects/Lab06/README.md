Lab 6 README File
CSE 13E Spring 2021
Aidan Kammerman
1760640
5/14/2021

In order to complete Lab 6, we were first tasked with creating three different timers that produced unique
output when their respective timeRemaining decreased to zero. In addition to producing digital output on the 
coolterm display, we had to sync up LEDs to toggle on and off with each timer. Next, we were tasked with
figuring out how to make a single LED "move" across the development board, one step at a time. The most difficult
part of this section for me was figuring out when the moving LED had reached its left-most and right-most positions.
We had to increase or decrease the speed of this moving LED dependent upon the current Switch States. We had to make 
the maximum speed occur when all of the switches were flipped down. After that, we had to display an analog voltage
from the IO shield’s potentiometer on the OLED as well as a percentage value. The toughest part of this section was 
figuring out how to prevent this voltage value from flickering when there was no addition human input to the
potentiometer dial.

The more challenging portion of the lab started at Part 4 (Buttons.c) because it was very difficult to determine how 
to accurately and consistently record the correct input when multiple buttons were pushed at once. We also had to account
for button "debouncing" by only reporting an event after a stable button reading over a number of measurements has occured.
After completing ButtonsTest, it was fairly easy to implement the Buttons library into Bounce_Buttons. In Bounce_Buttons,
we had to figure out how to toggle each set of LEDS depending on their respective button state as well as the state of 
Switch 1. I saw that many people were confused on the discord about how many switches to include for this portion, but 
ultimately I followed the Lab Manual and only varied the LED toggling based on the state of Switch 1. The ISR portion
of this section was probably the nicest because it only required one line of code which Called ButtonsCheckEvents() and 
stored the result in a temporary variable. 

I read the manual first and went to Chris's section which helped tremendously to clarify my confusion regarding how to store
which buttons had been pushed and released. I was stuck on this portion for an extremely long time prior to joining section.
One thing that went wrong was my output for ButtonsTest kept spamming over and over, long after I had pushed or released any 
of the buttons. I realized that I had to set my temporary ButtonValue equal to Button_Event_None so that my if statement at
the top would not be triggered again immediately after reaching the end. After figuring that out, implementing my Buttons library
in Bounce_Buttons actually went really well. This part took the least amount of time for me by far. I would approach this lab differently
next time by starting much earlier than I did.

After around 40 hours of struggling and pondering, my lab finally ended up working functionally except for the extra credit 
portion. I really liked being able to alter the speed of the moving LED with the state of the switches. I disliked how complicated
it was to figure out how to store button states when we had to take into account that multiple buttons could be pushed and 
released at once. Overall, this lab was definitely worthwhile and heightened my understanding of how to process input
from the Micro-Controller. The point distribution certainly seems fair, and the lab manual covereed enough details for me 
to get started off nicely. I didn't like how some of the demo videos seemed to contradict the instructions provided
in the lab manual though. I would also like to mention that I was hospitalized for three days due to Covid which is
why my lab submission is so late. Please take this into consideration when grading. 