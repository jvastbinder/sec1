# Stack-based Buffer Overflow Attack
## Why the code is vulnerable
The code has buffers of a fixed size, but does not check to insure that only input of the correct size is being put into that buffer. It uses scanf which just blindly copies from stdin and puts into a buffer. If a user was only inputting the right input into the program, it would work correctly, but a malicious user could craft input in such a way as to overwrite the buffer to make the program act in an unintended manner.
## How the exploit works
The exploit works by overwriting the previously filled buffer with other data. In this case, the user inputs their own name into the name field, and the code checks to make sure that they are trying to look at their own grade. Then it asks for the class they want to look at. The malicious user then writes the class of another user whose grade he/she would like to see. The buffer and space between the class and name buffer is overwritten with random garbage. Then when the address for the student name buffer is reached, the user inputs the name of the student whose grade the attacker wants to see.
## How to prevent the attack
Instead of blindly trusting the user, the developer could use a function which copies only enough characters to fill the buffer and allow for a null pointer at the end of the string.
## Potential payoff of the attack
In this case, cofidentiality was compromised. The attacker was able to view the grades of other students. This kind of vulnerability could also lead to a return-oriented programming attack in which the attacker could execute arbitrary code.
# 
# 
# 
# 
# 
# Integer Overflow Attack
## Why the code is vulnerable
When stored in a computer, integers have a finite limit. In this case, that max value is 2147483647. When that value is asked to go above that, it wraps back around to its minimum value -2147483647 and continues counting up. This code does its job in checking to insure that value will not be over 100 (the maximum value for a student grade), but it fails to take into account that integers have a maximum value. If a number is so large that it causes wraparound and ends less than 100, then it will end at whatever value that is.
## How the exploit works
The exploit works by entering a very large number such that it causes the integer to go over its maximum value and wraparound to the minimum. Since the only check is that the resulting value is less than 100, it does not know anything is awry. 
## How to prevent the attack
Instead of check the result, the developer could check the input number to make sure it is a reasonable value (<=100) then check the resulting grade.
## Potential payoff of the attack
In this case, the malicious or prehaps ignorant user was able to put the data in an unintended state. He/she was also able to go into a conditional that was not supposed to run in that case. Large numbers could be used to continue loops or execute conditional blocks if the numbers are not checked properly. As a result, data could be left in a wrong state or information could get out as a result of the unchecked integers.