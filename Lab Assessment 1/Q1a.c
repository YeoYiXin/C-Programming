//Student's Name: Yeo Yi Xin
//Student's ID: 20414841
//Assignment Question 1 a

#include <stdio.h> //include standard input output library
#include <math.h> //include math library
int main (void) //start of main function
{
    /*initialize double of variable a as 4.5 because we only want multiple of 4.5 and first value
    as shown in the example starts with 4.5. Then, initialize the variable square_val as 0. This variable will store the
    value of squares of multiple of 4.5. Lastly, initialize the variable cube_var as 0. This variable will store the
    value of cube of multiple of 4.5.*/
    double a=4.5,square_val=0,cube_val=0;
    puts(" "); //skip a line
    printf("\t %6s\t\t\t %6s\t\t\t %6s", "number", "square", "cube");
    for (a=4.5;a<=10000;a+=4.5)//start for loop
    {
        square_val=pow(a,2);
        cube_val=pow(a,3);
        printf("\n\t %lf\t\t %lf\t\t %lf\n", a, square_val, cube_val);
    }//end for loop
    return 0; //tell the compiler that it has finished compiling successfully.
} //end main function
