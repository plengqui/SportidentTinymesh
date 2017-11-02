# Wrote a punch generator for tests
Today I wrote a Teensy program (sketch) to generate synthetic Sportident punches for test purposes.
It went well. The sketch is checked in to [the github repository](https://github.com/plengqui/SportidentTinymesh/tree/master/RadioUnit/TeensySketches/punch-simulator).
The trickiest part was writing the CRC calculating function. I only found a java implementation, which i transcribed to C. 
Each iteration the sketch increments: SI card number by one, punch time by 256 seconds, and memory pointer by 8.
I let it churn out 2-3 punches per second and actually found a timing error in the comwrapper.py script which I fixed. After that it chugged along happily for hours :-)
