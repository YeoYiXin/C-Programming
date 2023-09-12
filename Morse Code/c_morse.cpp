#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
void choice();
void English_to_Morse();
void Morse_to_English();
#define MAX_STR 1000
main()
{
	 //change background color to white and text color to black
	 system("COLOR F0"); 
	 system("CLS");
	 //set error message to red
     char *alphamorse[]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
	                    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",
	     "...-",".--","-..-","-.--","--.."};
     char *nummorse[]={"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};
	 int i;
	 char str[1000],str1[1000];
	 int chc;
	 int a;
	 char ans;
	 fflush(stdin);
	 printf("\n Morse code translator \n To continue, type 'y' and enter. \n");
     scanf("%c",&ans);
	 //start the program
   	 int exitloop = 0;
	 int last_input_invalid = 0;
	 int last_input_blinker = 0;
	 while (ans == 'y' || ans == 'Y')
	 {
	 	 system("CLS");
	 	 fflush(stdin);
		 choice();
	     if (last_input_invalid)
		 {
			printf("\n");
			if (last_input_blinker)
			{
				printf("\033[91;1m");
				printf("Wrong input. Please try again!");
				printf("\033[107;30m");
				last_input_blinker = 0;
			}
			else
			{
				printf("\033[101;37;1m");
				printf("Wrong input. Please try again!!");
				printf("\033[107;30m");
				last_input_blinker = 1;
			}

			last_input_invalid = 0;
		 }
	  	 chc = 0;
		 printf("\n Enter your choice: ");
		 scanf("%d", &chc); 
	 	 switch (chc)
	 	 { 
	 	 	case 1: 
			  English_to_Morse(); 
			  break;
	 	 	case 2: 
			  Morse_to_English();
			   break;
	 	 	case 3: 
			  printf("Thank you! See you next time!\n");
			  exit(0); 
			  break;
	 	 	default: 
			  last_input_invalid = 1;
	 	  }
	 }   
} //end of main function

//choice function
void choice()
{
	printf("\n WELCOME TO MORSE CODE TRANSLATOR \n");
	printf("----------------------------------------------------------------------------------\n");
	printf("These are the few rules to follow to produce an output: \n");
	printf("a) Do not use symbols like ',' and '.' and special characters like '@' and '#' \n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\n Choices available \n");
	printf("1) Translate from English to Morse Code \n");
	printf("2) Translate from Morse Code to English \n");
	printf("3) Exit \n");	
} //end of Function to for choice()

//change from text to Morse code
void English_to_Morse()
{
	 char *alphamorse[]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
	                    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-",
	     "...-",".--","-..-","-.--","--.."};
     char *nummorse[]={"-----",".----","..---","...--","....-",".....","-....","--...","---..","----."};
	 int i, j, a;
	 char str[1000],str1[1000], b;
	 system("CLS");
	 printf ("You have chosen to convert Text to Morse Code.\n");
   	 printf("Enter a sentence\n");
 	 fflush(stdin);
   	 scanf(" %499[^\n]",str);
     //check for the word 'stop'
     if (strcmp(str,"stop")==0 || strcmp(str,"STOP")==0)
     {
     	return;
     }
	 j = 0;
	 a = strlen(str);
	 i = 0;
	 //check for special characters
	 int input_valid = 1;
	 for (j = 0; j < a; j++)
	 {
		 if (isalpha(str[j]) == 0 && isdigit(str[j]) == 0)
		 {
			 if (str[j] != ' ')
			 {
			 	 printf("\033[101;37;1m");
				 printf("\nInvalid input! Do not include ',' , '.' and any special characters in your sentence!\n\n");
				 printf("\033[107;30m");
				 input_valid = 0;
				 break;
			 }
		 }
	 }
	 //print length of string
	 printf("\nLetter Count: %d \n", a);
	 //convert to Morse code
	 if (input_valid)
	 {
     while(str[i]!='\0')
	  {
	    if(str[i]!=' '&&(!isdigit(str[i])))  
	    {
	    	 printf("%s ",alphamorse[toupper(str[i])-65]);  //to convert alphabet
	    } 
        else if(str[i]==' ')
	    {
	    	 printf("/"); //if encounter whitespace
	    }
	    else if(isdigit(str[i])&&str[i]!=' ')
	    {
	    	  printf("%s ",nummorse[str[i]-48]);    //to convert numbers 
	    }
	   i++;
	  }
	 }
	  printf("\n");
	  printf("Do you want to try again? [Y/N]");
	  fflush(stdin);
	  scanf("%d", &b);
	  return;
}//end of Function to convert text to Morse code 

//change from Morse code to text
void Morse_to_English()
{ 
   int a,j,i,c,d;
   char str[MAX_STR];
   char b;
   char alphabet[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
   int num[10]={0,1,2,3,4,5,6,7,8,9};
   char *morse[36]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                   "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                   "..-","...-",".--","-..-","-.--","--.."};
   char *morse_num[] = {"-----", ".----", "..---", "...--", "....-",
     ".....", "-....", "--...", "---..", "----." } ;
    system("CLS");
    printf ("You have chosen to convert Morse Code to Text.\n");
    //guideline for user
    printf ("\nYou may use this as your guideline\n");
    printf ("-----------------------------------------------------------------------------------------------------------------------\n");
    printf(" Letter Morse Code | Letter  Morse Code | Letter  Morse Code | Numbers         Morse Code | Numbers  Morse Code\n");
    printf(" A      .-           J      .---          S       ...          Spacing (' ')   /            8        ---..\n");
    printf(" B      -...         K      -.-           T       -            0               -----        9        ----.\n");
    printf(" C      -.-.         L      .-..          U       ..-          1               .----\n");
    printf(" D      -..          M      --            V       ...-         2               ..---\n"); 
    printf(" E      .            N      -.            W       .--          3               ...--\n");
    printf(" F      ..-.         O      ---           X       -..-         4               ....- \n");
    printf(" G      --.          P      .--.          Y       -.--         5               .....\n");
    printf(" H      ....         Q      --.-          Z       --..         6               -....\n");
    printf(" I      ..           R      .-.           Stop    .-.-.-       7               --...\n");
    printf ("-----------------------------------------------------------------------------------------------------------------------\n\n");
    
    printf("Enter a sentence\n");
    scanf(" %499[^\n]",str);
    //check for the word 'stop'
     if (strcmp(str,".-.-.-")==0)
     {
     	return;
     }
     a=strlen(str);
     printf("\nLetter Count: %d \n", a);
     //convert to text
    char convert[100]="";
    
     for(i=0;i<=a;i++)
     {
	    	if (str[i]==' ' || str[i]=='/' || i==a)
	    	{
	    		for(c=0;c<26;c++)
	    		{
				     if (strcmp(convert, morse[c])==0)
				     {
				        printf("%c", alphabet[c]);
				        break;
				     }
	    		}
	    		for (c=0;c<10;c++)
	    		{
		    		if (strcmp(convert, morse_num[c])==0)
				     {
				        printf("%d", num[c]);
				        break;
				     }
	    		}
    			if (str[i]=='/')
		    	{
			        printf(" ");  
		    	}    
                strcpy(convert,"");
	    	}              
            else if (str[i]=='.' || str[i]=='-'){
                sprintf(convert,"%s%c",convert,str[i]);
            }
            else
		    {
				// in case user input non space, dash, dot, it will be an invalid input!
				printf("\033[91;1m");
				printf("Invalid character detected!! %c\n");
				printf("\033[30m");
				break;
		    }
     }
     printf("\n");
     printf("Do you want to try again? [Y/N]");
     scanf("%d", &b);
     return;  
} //end of Function to convert Morse code to text

