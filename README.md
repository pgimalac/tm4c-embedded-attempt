# My (almost) first embedded attempt
This repository contains my code for the [`Embedded Systems - Shape The World`](http://users.ece.utexas.edu/~valvano/Volume1/E-Book/) course from Austin university by Jonathan Valvano and Ramesh Yerraballi.

### ♥ Linux ♥
This course was made for Windows (using Keil uVision), but I use Arch, so obviously I had to tinker - for my greatest pleasure - to follow it on Linux. I don't have access to the correction, the templates nor the evaluator so I can't really check that what I'm doing is perfect, but I hope so.

### Repository
Each lab will be on a separate branch, either coming from the `dev` branch or from another lab.

#### How to run
A makefile is provided to build and flash the code onto the board.

I tried to use CCStudio but without success.

### edX
I followed the course from the [edX website](https://www.edx.org/course/embedded-systems-shape-the-world-microcontroller-i).

### Lab n°9
The led flashes at a frequency of 10Hz if either SW1 or SW2 are pressed, otherwise it is off.

Every time the input (SW1 or SW2) changes, add the values of PF4, PF1, PF0 in an array.
