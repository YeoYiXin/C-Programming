//Student's Name: Yeo Yi Xin
//Student's ID: 20414841
//Assignment Question 2

#include <stdio.h> //include standard input output library
int main (void) //start of main function
{
    int rows=0, i=0, j=0;
    for (rows=0;rows<10;rows++) //start for loop - triangle one
    {
        for (i=0;i<=rows;i++)//start nested for loop
        {
            printf("^");
        } //end nested for loop
        puts(" "); //enter a new line
    } //end for loop
    puts(" "); // enter new line

    for (rows=0;rows<10;rows++) //start for loop - triangle two
    {
        for (i=9;i>=rows;i--)//start nested for loop
        {
            printf("^");
        } //end nested for loop
        puts(" "); //enter a new line
    } //end for loop
    puts(" "); // enter new line

    for (rows=0;rows<10;rows++) //start for loop - triangle 3
    {
        for (i=0;i<=rows;i++)//start nested for loop
        {
            printf(" ");
        } //end nested for loop
        for (j=9;j>=rows;j--)//start nested for loop
        {
            printf("^");
        } //end nested for loop
        puts(" "); //enter a new line
    } //end for loop
     puts(" "); // enter new line

     for (rows=0;rows<10;rows++) //start for loop
    {
        for (i=9;i>=rows;i--)//start nested for loop
        {
            printf(" ");
        } //end nested for loop
        for (j=0;j<=rows;j++)//start nested for loop
        {
            printf("^");
        } //end nested for loop
        puts(" "); //enter a new line
    } //end for loop
    puts(" "); // enter new line
    return 0; //tell the compiler that it has finished compiling successfully
}//end of main function
