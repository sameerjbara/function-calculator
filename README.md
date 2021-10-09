# function-calculator
The calculator holds a list of functions that it is capable of performing. 
The two functions that already exist when running the calculator are:
1) sin(x)
2) ln(x)
the program can do many operations such as Functions sum, multiplication ...
The program gets from the user the name of the operation he wants to do and the number of the function. 
The program according to the user request perform the operation 
the available operations are:
1) eval num x 
  Calculates the value of the function numbered num, at point x.
2) poly n C0 C1 ... Cn-1
  Adds to the list of functions a polynomial with n coefficients
3) mul num1 num2 
  Adds to the list of functions a function that is a multiplication of the functions numbered num1 and num2.
4) add num1 num2
  Adds to the list of functions a function that is a sum of the functions numbered num1 and num2.
5) comp num1 num2
   Adds to the list of functions a function that is a composition of the functions numbered num1 and num2.
6) log N num
  Adds to the functions list a function that calculates the value of a log at base N for the function numbered num
7) del num
  Deletes the function numbered num from the list of functions
8) help
9) exit

