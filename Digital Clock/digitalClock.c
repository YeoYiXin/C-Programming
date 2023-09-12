#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void calendar();
void decoration();
void decoration1();

int main(void){
	int hour, minute, seconds;
    hour=0;
	minute=0;
	seconds=0;
	
    while(1){
		system("cls"); //"clear" for non-Windows user
    	seconds++;
    	if(seconds==60){
	    	minute+=1;  
	    	seconds=0;
	    }
	    if(minute==60){
	    	hour+=1;
	    	minute=0;
	    }
	    if (hour==24){
	    	hour=0;
	    }
	    if (hour<12){
	    	decoration();
			printf("%02d : %02d : %02d AM\n", hour, minute, seconds);
	    }
	    else {
	    	decoration();
			printf("%02d : %02d : %02d PM\n", hour, minute, seconds);
    	
	    }
		calendar(); //to display today's date
		decoration1();
        // Clear the output buffer in gcc
        fflush(stdout);
		sleep(1); //delay for 1000 milliseconds  
    }
}

void decoration(){
	printf("------------------------------------\n");

}

void calendar(){
 	time_t t; 
    t = time(NULL); //to get current time
    struct tm tdy = *localtime(&t); //to use tm members. struct means type of structure
    int m, w;
    w = tdy.tm_wday+1; //to get current days

    switch(w){
		case 1:  printf(" Sunday, "); break;
		case 2:  printf(" Monday, "); break;
		case 3:  printf(" Tuesday, "); break;
		case 4:  printf(" Wednesday, "); break;
		case 5:  printf(" Thursday, "); break;
		case 6:  printf(" Friday, "); break;
		case 7:  printf(" Saturday, "); break;
		default: printf(" Wrong week of the day!"); 
    }
    
    printf("%d ", tdy.tm_mday); //to get current day of the month
    m = tdy.tm_mon+1; //to show that the starting month is January and not 0th month

    switch(m){
        case 1: printf("January, "); break;
        case 2: printf("February, "); break;
        case 3: printf("March, "); break;
        case 4: printf("April, "); break;
        case 5: printf("May, "); break;
        case 6: printf("June, "); break;
        case 7: printf("July, "); break;
        case 8: printf("August, "); break;
        case 9: printf("September, "); break;
        case 10: printf("October, "); break;
        case 11: printf("November, "); break;
        case 12: printf("December, "); break;
        default: printf("Wrong month!"); 
    }
    printf("%d\n", tdy.tm_year+1900); //to get current year	
}

void decoration1(){
	printf("------------------------------------\n");
}
