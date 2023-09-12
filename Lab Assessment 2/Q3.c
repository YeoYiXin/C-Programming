#include <stdio.h>
#include <ctype.h>
#include <string.h>
void strRev(char string[], int p, size_t i);
int main(void)
{
	char string[100]; //limit input character to 100
	printf("\nThe program started");
	printf("\nStart typing:\n");
	fgets(string, sizeof(string), stdin);

	//for loop
	int a = 0; //initialise a to 0
	string[strcspn(string, "\n")] = 0;
	a = strlen(string); //store length of string in variable a
	int i = 0; //initialise i to 0
	printf("\n\nThis is For Loop\n");
	for (; i < a; i++)
	{
		printf("%c", string[i]);
	}//end for loop

	//while loop
	int j = 0; //initialise j to 0
	printf("\n\nThis is While Loop\n");
	while (j < a)
	{
		printf("%c", string[j]);
		j++;
	}//end while loop
	
	//this is for recursive function
	printf("\n\nThis is string: \n%s", string);
	printf("\n\nThe reverse string is:\n");
	a = strlen(string);
	strRev(string, 0, a);
	return 0;
}

void strRev(char string[], int p, size_t i){
    if (p<i){
        strRev(string, p+1, i);
        printf("%c", string[p]);
    }
}