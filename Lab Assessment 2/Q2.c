//Recursive linear search
#include <stdio.h>
#define SIZE 500 //initialise SIZE to 500
int search(int a[], int key, int l, int h); // l is low, h is high, key is search key

int main(void)
{
	int arr[SIZE] = { 0 }; //initialize array of SIZE 500 to 0
	int searchkey = 0;
	for (size_t i = 0; i < 500; i++)
	{
		arr[i] = 2 * i; //creating value in array arr
	}//end for loop
	printf("\nEnter integer search key multiple of 6: ");
	scanf("%d", &searchkey);
	while (searchkey % 6 != 0) //if searchkey is not a multiple of 6
	{
		printf("\nSearch key is not multiple of 6");
		printf("\nEnter the integer search key multiple of 6: ");
		scanf("%d", &searchkey);
	}//end while loop

	//to locate searchkey in the array arr
	int elementposition = 0;
	elementposition = search(arr, searchkey, 0, SIZE - 1); //fuction call

	if (elementposition != -1)//if element is found
	{
		printf("\nFound value in element %d \n", elementposition);
	}
	else //if element not found
	{
		printf("\nValue not found \n");
	}//end if-else condition
	return 0;
}//end main function
int search(int a[], int key, int l, int h){
	int counter = 0; //act as counter to return index of the element found in array
	if (l >= h) //if value still not found even after all the elements in the array is searched
	{
		return -1; //return -1 to show value not found
	}//end if
	else if (a[l] == key) //if value is found
	{
		counter = l;
		return counter;
	}//end else if
	else //recursive function to continue until base case is recognised
	{
		return search(a, key, l + 1, h); //increase low by 1
	}//end if-else if condition
	return -1;
}//end search function