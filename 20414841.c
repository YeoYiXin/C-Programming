/* Name: Yeo Yi Xin  Student ID: 20414841*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <malloc.h> //for dynamic allocation of the memory
# include <ctype.h>

struct visitData { //given struct to store visitor information
char *SrNo; //pointers of array
char *ticketNo; 
char *Name; 
char *ID; 
}; 

struct ticket { //given struct to store the data
struct visitData visitor; 
struct ticket *nextPtr; 
};

typedef struct ticket Visit; //synonym for struct ticket which is used to acccess visitData and pointer
struct ticket* head = NULL;  //globally initialised head for linked list 

void previous(void);    //to read previous input
int visitor(void);      //print out total visitor at the top of terminal/output screen
void instruction(void); //to print out instruction
void convert(void);     //get sr_num, name, ID, ticket
void search(void);      //search
void delete(void);      //delete selection
void display(void);     //to display
int c = 0, counter =0;  //for displaying total visitor

int main (void) {
    previous();     //to be able to access previous information after the program runs again
    char choice; 
    int done=0;
    while (done==0) //while true
    {
        counter = visitor(); //print out total visitors on terminal and in file
        instruction();       //func call to print instruction
        printf("\nPlease choose: ");
        scanf("%c", &choice);
        getchar();
        switch (choice) {
            case '1': { //appending
                if (counter==40){ /*if total visitor has reached 40 people which is the maximum, restrict user from appending*/
                FILE *max = fopen("output.txt", "a+");
                if (max == NULL) { /*Program exits if the max pointer returns NULL.*/
                    printf("Error! File cannot be opened.");
                    exit(1);
                }//end if
                char warn[200] = "\nMax visitor capacity. To add more, you have to delete other visitor information.\n";
                fprintf(max, "%s", warn);
                printf("%s", warn);
                fclose(max);
                break;
                }//end if
                else{
                    convert();  /*add serial number, ticket number, name and ID*/
                    break;
                }//end else
            }//end case 1
            case '2': { //Search
                search();
                break;
            }//end case 2
            case '3': { //delete
                delete();
                break;
            }//end case 3
            case '4': {  //Display Total Number of Ticket Sold
                display(); 
                break;
            } //end case 4
            case '5': { //exit program
                return 0;break;
            } //end case 5
            default: {
                printf("\nNo such choice! "); /*force user to choose other options if user choose the wrong one. Only way to get out of loop is choosing case 5*/
                printf("\nTry again. To exit, choose option 5");
                printf("\n");
            }//end default
         }//end switch
    }//end while
}//end main func

void previous(void){/*to be able to access previous visitor information*/
    FILE* prev = NULL;
    prev = fopen("Tickets.txt", "r"); //open in readable format
    if (prev == NULL){//if cannot open
        fclose(prev);
        prev = fopen("Tickets.txt", "w"); //then, create a new file
        fclose(prev);
    }//end if
    else{/*there is a file already*/
        if(fgetc(prev) == EOF){//no content
        }//end if

        else{//got words in it
            char done[1000];

            fseek(prev, 0, SEEK_SET); //start from the beginning
            fscanf(prev, "%[^\n]", done);//until it meets a new line

            while(fgetc(prev)!=EOF){ /*continue until content in file reach end of file*/
                struct ticket* node = (struct ticket*)malloc (sizeof(struct ticket)); //new node
                struct ticket* points = head; //set points as head of linked list
                
                //set character of arrays as NULL
                char serialnum[4]={0}; 
                char ticketnum[30]={0};
                char nametemp[32]={0};
                char IDnum[30]={0};
                fscanf(prev, "%s %s %s %s", serialnum, ticketnum, nametemp, IDnum); /*scan the value every time the loop iterates*/

                //set node pointing to struct and allocate memory
                node->visitor.SrNo = malloc(500);
                node->visitor.ticketNo = malloc(100+1);
                node->visitor.Name = malloc(34+1);
                node->visitor.ID = malloc(70+1);
             
                //copy previous information into the nodes
                strcpy(node->visitor.SrNo, serialnum);
                strcpy(node->visitor.ticketNo, ticketnum);
                strcpy(node->visitor.Name, nametemp);
                strcpy(node->visitor.ID, IDnum);

                node->nextPtr = NULL; //set next pointer node as NULL

                if (head == NULL){ //if head is empty, set first struct data as head and points to next head which is NULL
                    head = node;
                }//end if
                else{
                    while (points->nextPtr != NULL){ //traverse until it reach the last node in the list
                        points = points->nextPtr; //pointer points to next node
                    }//end while
                    points->nextPtr = node;
                }//end else
            }//end while
        }//end else
    }//end else
    fclose(prev);
}//end func

void instruction(void) {/*To print switch information*/
    printf("\nEnter your choice: ");
    printf("\n1. Add new visitor information, \n2. Search visitor information, \n3. Delete visitor information,");
    printf("\n4. Display Total Number of Ticket Sold, \n5. Exit the program");
} //end instruction function

int visitor(void){/*To print total visitors*/
    FILE* visit = fopen("Tickets.txt", "r+"); /*open file in readable and writable format*/
    if (visit == NULL){//cannot open
        fclose(visit);
        visit = fopen("Tickets.txt", "w"); /*If cannot open file, then create a new file*/
        char str[100] = "Total visitors: ";
        fseek(visit, strlen(str), SEEK_SET); /*reach till the end of str*/
        fscanf(visit, "%d", &c);             /*get the total visitor value*/
        fseek(visit, 0, SEEK_SET);           /*go back to the starting of the file*/
        fprintf(visit, "%s%d", str, c);      /*print out the total visitor value in file*/
        printf("\n\n-----------------------------------------------------\n");
        printf("Total visitors: %d", c);     /*print out in terminal*/
        printf("\n-----------------------------------------------------\n");
        fclose(visit);
        return c;
    }//end if
    else{
        char str[100] = "Total visitors: ";
        fseek(visit, strlen(str), SEEK_SET);    /*reach till the end of str*/
        fscanf(visit, "%d", &c);                /*get the total visitor value*/
        fseek(visit, 0, SEEK_SET);              /*go back to the starting of the file*/
        fprintf(visit, "%s%d", str, c);         /*print out the total visitor value in file*/
        printf("\n-----------------------------------------------------\n");
        printf("Total visitors: %d", c);        /*print out in terminal*/
        printf("\n-----------------------------------------------------\n");
        fclose(visit);
        return c; /*return value of total visitor to main function*/
    }//end else
}//end visitor func

void convert(void) {/*To update total visitors, get serial number, name, ticket number and ID*/
    FILE *source = fopen("Tickets.txt", "r+");  /*open file in readable and writable format*/
    if (source == NULL){
        fclose(source);
        source = fopen("Tickets.txt", "w");     /*If cannot open file, then create a new file*/
    }//end if
    int sr_no = 0;                              /*serial number*/
    fseek(source, 0, SEEK_SET);                 /*pointer starts from the starting of the file*/
    char temp_sr[2];    
    char buff[1024];
    memset(buff, 0, 1024);                      /*set memory to 0*/
    while(fgets(buff, 1024, source) != NULL) {} /*reads each line till the end*/
    sscanf(buff, "%s %*s %*s %*s", temp_sr);    /*scan only the serial numer*/
    sr_no = (int)strtod(temp_sr, NULL);         /*convert the character serial number to integer*/
    ++sr_no;                                    /*increase serial number by 1*/
    fclose(source);

    char temp_num[6];
    sprintf(temp_num, "%02d",sr_no);            /*store integer serial number into a character variable*/
    printf("\nSerial number: %s", temp_num);

    char name_temp[100];                        /*to store name*/
    char name_temp1[33];                        /*act as temporary variable for name_temp*/
    char tick_temp[100];                        /*to store ticket number*/
    printf("\nEnter your name (Max: 30 characters): ");
    fgets(name_temp, 50, stdin);
    
    //obtain ticket number
    char temp[500];                             /*as temporary storage to store only 6 characters of name*/
    int length = (strlen(name_temp))-1;         /*obtain length of name*/

    while (length>30){                          /*if length more than 30, prompt user input*/
        printf("\n\nPlease enter your name (Max: 30 characters): ");
        fgets(name_temp, 50, stdin);
        length=(strlen(name_temp))-1;
        printf("\nCurrent length of your name: %d", length);
    }//end while

    memset(name_temp1, 0, sizeof(name_temp1));  /*set memory to 0*/
    strncpy(name_temp1, name_temp, length);
    name_temp1[length] = 0;                     /*set last character as terminating null characer*/
    printf("\nLength: %d", length);
    if (length>=6) {                            /*if name length>=6, copy first 6 chars into temp*/
        memset(temp, 0, sizeof(temp));
        strncpy(temp, name_temp, 6);            
        temp[6] = 0;
        memset(tick_temp, 0, 100+1);
        char *z=tick_temp;                      /*set pointer z as tick temp*/
        for (int i=0;temp[i]!='\0';++i){
            z+=sprintf(z, "%d", (int)(temp[i]));/*store explicitly converted temp variable into a character variable*/
        }//end for
        printf("\nYour ticket number: %s", tick_temp); /*print out ticket number on terminal/output screen */
    }//end if
    else if (length<6) {  /*if name less than 6 characters*/
        memset(temp, 0, sizeof(temp));
        strncpy(temp, name_temp, length);
        temp[length] = 0;
        strrev(temp); /*reverse the string*/

        for (int i=0; strlen(temp)<6;i++){ /*concatenate string to make the string 6 words*/
            strcat(temp, " "); 
        }//end for

        strrev(temp); //reverse the string
        memset(tick_temp, 0, 100+1);
        char *y=tick_temp;
        for (int i=0;temp[i]!='\0';++i){ /*convert to ticket number*/
            y+=sprintf(y, "%d", (int)(temp[i]));
        }//end for
        printf("\nYour ticket number: %s", tick_temp);
    }//end else-if

    for (int i=0;name_temp[i]!='\0';i++){ /*replacing space with underscore and removing newline*/
        if (isspace(name_temp[i]) && name_temp[i]!='\n'){
            name_temp[i]='_';
        } //end if
        if(name_temp[i] == '\n'){ /*replacing newline with terminating null character*/
            name_temp[i] = 0;
        } //end if
    }//end while loop
    
    char ID_temp[70];
    char choice1;
    while (1) { //get IC for international or local visitor
        printf("\n\nPlease choose accordingly to your nationality:\n1. Local (has Malaysian identification card)");
        printf("\n2. International\nChoice: ");
        scanf("%c", &choice1); /*Prompt user to choose the nationality*/
        getchar();
        switch (choice1) {
            case '1':{//Local
                char ID1[30];
                char start[50] = "IC";
                memset(ID1, 0,30);
                printf("\n\nPlease enter your IC number (Max: 20 num): ");
                fgets(ID1, 25, stdin);      /*Prompt user to enter IC*/
                int length1=(strlen(ID1))-1;
                printf("\nLength ID: %d", length1);
                while (length1>20){ /*IC should not exceed 20 characters. If exceeds, prompt user for IC until <=20*/
                    printf("\n\nPlease enter your IC number (Max: 20 num): ");
                    fgets(ID1, 22, stdin); 
                    length1=(strlen(ID1))-1;
                    printf("\nCurrent length - ID: %d", length1);
                }//end while

                strcat(start, ID1);   /*add IC to the numbers*/
                int length = strlen(start);
                memset(ID_temp, 0, 70);
                strncpy(ID_temp, start, length); /*copy the IC into ID_temp*/
                ID_temp[length] = 0;
                printf("\nID: %s\n", ID_temp); /*print out*/
                break;
            }//end case 1
            case '2': { //International
                char ID1[30];
                char start[50] = "PASS";
                memset(ID1, 0,30);
                printf("\n\nPlease enter your Passport number (Max: 20 num): ");
                fgets(ID1, 25, stdin);    /*Prompt user to enter passport*/
                int length1=(strlen(ID1))-1;
                printf("\nLength Passport: %d", length1);
                while (length1>20){ /*PASS should not exceed 20 characters. If exceeds, prompt user for PASS until <=20*/
                    printf("\n\nPlease enter your IC number (Max: 20 num): ");
                    fgets(ID1, 25, stdin);
                    length1=(strlen(ID1))-1;
                    printf("\nPassport: %d", length1);
                }//end while

                strcat(start, ID1);    /*add PASS to the numbers*/
                int length = strlen(start);
                memset(ID_temp, 0, 70);
                strncpy(ID_temp, start, length);  /*copy the PASS into ID_temp*/
                ID_temp[length] = 0;
                printf("\nID: %s\n", ID_temp);  /*print out*/
                break;
            }//end case 2
            default:{    
                printf("\nNo such choice! ");
            }//end default
        }//end switch
        if (choice1 != '1' && choice1 != '2'){  /*Prompt user to input the IC again and again if user did not choose either 1 or 2*/
            printf("\nTry again");
            printf("\n");
        }//end switch
        else{
            break;
        }//end else
    }//end while

    ID_temp[strcspn(ID_temp, "\n")] = 0;  /*Replace newline with terminating null character*/

    source = fopen("Tickets.txt", "a");
    if(source == NULL) { /*show error when source cannot be created*/
        printf("Error in creating the source\n");
        exit(1); //exit the program
    }//end if

    struct ticket* node = (struct ticket*)malloc (sizeof(struct ticket)); /*assigning memory to node*/
    struct ticket* points = head; /*set as head*/
 
    /*set node pointing to struct*/ 
    node->visitor.SrNo = malloc(8);
    node->visitor.ticketNo = malloc(100+1);
    node->visitor.Name = malloc(34+1);
    node->visitor.ID = malloc(70+1);

    /*copy all the information into linked list*/
    strcpy(node->visitor.SrNo, temp_num);
    strcpy(node->visitor.ticketNo, tick_temp);
    strcpy(node->visitor.Name, name_temp);
    strcpy(node->visitor.ID, ID_temp);

    if (head == NULL){ /*if head is empty, set first struct data as head and points to next head which is NULL*/
        head = node;   /*set head as node*/
        points = head; /*set points as head*/
        points->nextPtr = NULL; /*The next pointer will points to NULL until more information is added*/
    }//end if
    else{
        while (points->nextPtr != NULL){ /*traverse until it reach the last node in the list*/
            points = points->nextPtr;    /*pointer points to next node*/
        }//end while
        node->nextPtr = NULL; /*set nextPtr of node to be empty*/
        points->nextPtr = node; /*Set nextPtr of points to be node*/
    }//end else

    source = fopen("Tickets.txt", "r+"); /*open the file as read and write mode*/
    //total visitor
    if (source == NULL){ /*if no file, then open one using write mode*/
        fclose(source);
        source = fopen("Tickets.txt", "w");
    }//end if
    char str[] = "Total visitors: ";
    int c = 1;
    fseek(source,0,SEEK_SET);
    if(fgetc(source) == EOF){  /*If Total visitors is not printed yet, print and set it to be 0*/
        fprintf(source, "%s%d", str, c);
    }//end if
    else{  /*If there is total visitors already, then update value by adding with 1*/
        fseek(source, strlen(str), SEEK_SET);
        fscanf(source, "%d", &c);
        fseek(source, 0, SEEK_SET);
        fprintf(source, "%s%d", str, ++c);
    }//end else
    fclose(source);

    source = fopen("Tickets.txt", "a+"); /*open file as append and write mode*/
    if (source == NULL){  /*exit if file cannot be open*/
        printf("File cannot be open");
        exit(1);
    }//end if
    FILE* target = fopen("output.txt", "a+"); /*open file as append and write mode*/
    if (target == NULL) { /*exit if file cannot be open*/
        printf("Error! File cannot be opened.");
        exit(1);
    }//end if
    fprintf(source, "\n%s %s %s %s\n", node->visitor.SrNo, node->visitor.ticketNo, node->visitor.Name, node->visitor.ID); /*for Tickets.txt*/
    fclose(source);/*close source*/

    fprintf(target, "%s %s %s %s\n",  node->visitor.SrNo, node->visitor.ticketNo, node->visitor.Name, node->visitor.ID); /*for output.txt*/
    printf("\nThe information of the visitor %s is recorded.", node->visitor.Name); /*print to terminal*/
    fprintf(target, "\nThe information of the visitor %s is recorded.\n", node->visitor.Name); /*for output.txt*/
    fclose(target); /*close target*/
}//end convert func

void search(void){/*To search using name, ID or ticket number*/
    struct ticket* points = head;
    FILE *result = fopen("output.txt", "a");
    if(result == NULL) { /*show error when result cannot be created*/
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if
    /*Search visitor information based on Ticket No, Name, or ID*/
    char choice3;
    char name_temp[32]; /*to store name*/
    char tick_num[20]; /*to store ticket number*/
    char ID_temp[70];
    char temp_node[80];
    while (1)
    {//start switch statement
        printf("\nHow do you want to search by?\n1. Ticket Number\n2. Full Name\n3. ID ");
        printf("\nChoice: ");
        scanf("%c", &choice3); /*Prompt user to choose which way they want to search with*/
        getchar();
        switch (choice3){
            case '1': {  //Ticket number
                int repeat=0, flag=0;
                printf("\nPlease input your ticket number: ");
                fgets(tick_num, 20, stdin);   /*Prompt user to enter the ticket number*/
                for (int i=0;tick_num[i]!='\0';i++){
                    if(tick_num[i] == '\n'){ /*Change newline to terminating null characters*/
                        tick_num[i] = 0;
                    } //end nested if
                }//end for loop
                while (points!=NULL){/*check for similarity in names*/
                    if (strcmp(points->visitor.ticketNo, tick_num)==0){
                        flag=1;
                        if (repeat<1){ /*only print this once*/
                            char str[100]= "\nThe following record of the visitor is found:\n";
                            printf("\nThe following record of the visitor is found:");
                            fprintf(result, "\n%s\n", str);
                            repeat++; /*add repeat*/
                        }
                        printf("\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                        fprintf(result, "\n%s %s %s %s\n", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                    }//end nested if
                    points = points->nextPtr;
                }//end while
                if (flag == 0){ /*If visitor information is not found*/
                    printf("\nVisitor information not found. Try again next time.\n");
                }//end if
                free(points); /*Free the de-threaded node*/
                break;
            }//end case 1 - ticket number

            case '2': {//Name
                int repeat=0, flag =0;
                printf("\nPlease input the full name: ");
                fgets(name_temp, 31, stdin);   /*Prompt user to enter the name*/
                for (int i=0;name_temp[i]!='\0';i++){ /*Replace space with underscores and newline with terminating null character*/
                    if (isspace(name_temp[i]) && name_temp[i]!='\n'){
                        name_temp[i]='_';
                    } //end nested if
                    if(name_temp[i] == '\n'){
                        name_temp[i] = 0;
                    } //end nested if
                }//end for loop
                int j=0;

                for (j=0; name_temp[j]!='\0'; j++) { /*change to uppercase*/
                    if(name_temp[j]>='a' && name_temp[j]<='z') {
                        name_temp[j] = name_temp[j] - 32;
                    }//end nested if
                }//end for loop
                while (points!=NULL){/*check for similarity in names*/
                    strcpy(temp_node, points->visitor.Name); /*copy into temporary variable*/

                    for (j=0; temp_node[j]!='\0'; j++) { /*change to uppercase*/
                        if(temp_node[j]>='a' && temp_node[j]<='z') {
                            temp_node[j] = temp_node[j] - 32;
                        }//end nested if
                    }//end for loop
                    if (strcmp(temp_node, name_temp)==0){ /*if it is the same*/
                        flag=1;
                        if (repeat<1){
                            char str[100]= "\nThe following record of the visitor is found:\n";
                            printf("\nThe following record of the visitor is found:");
                            fprintf(result, "%s", str);
                            repeat++;
                        }//end if
                        printf("\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                        fprintf(result, "\n%s %s %s %s\n", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                    } //end nested if
                    points = points->nextPtr; /*point to the next one*/
                } //end while
                if (flag == 0){ /*If visitor information is not found*/
                    printf("\nVisitor information not found. Try again next time.\n");
                }
                free(points); /*Free the de-threaded node*/
                break;
            }//end case 2 - name

            case '3': { //ID 
                int repeat=0, flag =0;
                printf("\nIf the ID you are finding belongs to Malaysian, please add IC.");
                printf("\nIf not, add PASS. Note that both IC and PASS should have 9 digits (case-sensitive). If not, you won't be able to find it.");
                printf("\nPlease enter the ID you would like to find: ");
                fgets(ID_temp, 20, stdin);   /*Prompt user to enter the ID*/
                for (int i=0;ID_temp[i]!='\0';i++){  /*Change newline to terminating null characters*/
                    if(ID_temp[i] == '\n'){ 
                        ID_temp[i] = 0;
                    }//end nested if
                }//end for loop
                while (points!=NULL){/*check for similarity in names*/
                    if (strcmp(points->visitor.ID, ID_temp)==0){ /*compare if it is the same*/
                        flag =1;
                        if (repeat<1){ /*print only once*/
                            char str[100]= "\nThe following record of the visitor is found:\n";
                            printf("\nThe following record of the visitor is found:");
                            fprintf(result, "%s", str);
                            repeat++;
                        }
                        printf("\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                        fprintf(result, "\n%s %s %s %s\n", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                    }//end nested if
                    points = points->nextPtr;
                }//end while loop
                if (flag == 0){ /*If visitor information is not found*/
                    printf("\nVisitor information not found. Try again next time.\n");
                }
                free(points); /*Free the de-threaded node*/
                break;
            }//end case 3 - ID

            default: {
                printf("No such choices!\nTry again\n");
            }//end default
        }//end switch
        if (choice3 == '1' || choice3 =='2' || choice3 == '3'){ /*If user choose either one of this, the go out of while loop*/
            break;
        }//end if
    }//end while loop
    fclose(result);
}//search func end

void delete (void){/*To delete using name, ID or ticket number*/
    char choice_3;
    void del_ticknum(void);
    int del_name(void);
    void del_ID(void);
    while (1) {//start switch statement
        printf("\nThrough which way do you want to delete?\n1. Ticket Number\n2. Full Name\n3. ID ");
        printf("\nChoice: ");
        scanf("%c", &choice_3); /*Prompt user to choose*/
        getchar();
        switch (choice_3){
            case '1': {  //Ticket number
                del_ticknum();
                break;
            }//end case 1 - ticket number
            case '2': {//Name
                del_name();
                break;
            }//end case 2 - name
            case '3': { 
                del_ID();
                break; 
            }//end case 3 - ID
            default:{
                printf("No such choices! Try again");
            }//end default
        }//end switch
        if (choice_3 == '1' || choice_3 =='2' || choice_3 == '3'){
            break;
        }//end switch
    }//end while loop
}//delete function ends

void del_ticknum(void){//delete ticket number
    struct ticket* points = head; /*current node is head*/
    struct ticket* nodes = head; /*when info is not found in the first node in linked list, act as previous*/

    FILE *ticknum = fopen("output.txt", "a");
    if(ticknum == NULL) { /*show error when ticknum cannot be created*/
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if

    char tick_num2[22]; /*to store ticket number*/
    printf("\nPlease input the ticket number you want to delete (must be the same!): ");
    fgets(tick_num2, 20, stdin);

    for (int i=0;tick_num2[i]!='\0';i++){/*changing next line to terminating null character*/
        if(tick_num2[i] == '\n'){
            tick_num2[i] = 0;
        } //end nested if
    }//end for loop

    if (points==NULL){//if no element is stored in linked list
        printf("\nIt is an empty list");
        exit(0);
    }//end if

    else if (strcmp(points->visitor.ticketNo, tick_num2)==0) {//element found in head
        printf("\nThe visitor with Ticket No.: %s information is deleted\n", points->visitor.ticketNo);
        fprintf(ticknum, "\nThe visitor with Ticket No.: %s information is deleted\n\n", points->visitor.ticketNo);
        head =points->nextPtr;
        free(points);
        points=NULL;
    }//end if

    else{
        while(strcmp(points->visitor.ticketNo, tick_num2)!=0){//while there is still node
            nodes = points; /*prev points to points because singly linked list needs an extra node so that it fixed where all the linked list element points when an information is deleted*/
            points = points->nextPtr;
            if((points==NULL)){
                printf("\nYou have entered an incorrect ticket number.");
                break;
            }
            else if (strcmp(points->visitor.ticketNo, tick_num2)==0){ /*if it is found*/
                nodes->nextPtr = points->nextPtr;
                printf("\nThe visitor with Ticket No.: %s information is deleted\n", points->visitor.ticketNo);
                fprintf(ticknum, "\nThe visitor with Ticket No.: %s information is deleted\n\n", points->visitor.ticketNo);
                points = NULL;
                break;
            }//end if
        }//end while
    }//end else

    //update the toal visitor
    FILE *source = fopen("Tickets.txt", "w"); /*Update list*/
    struct ticket* reupdate = head;
        if(source == NULL) { //show error when source cannot be created
            printf("Error in creating result\n");
            exit(1); //exit the program
        }//end if

        //update total visitor
        char str[100]="Total visitors: "; 
        fseek(source, strlen(str), SEEK_SET); /*Update total visitor value*/
        fscanf(source, "%d", &c);
        fseek(source, 0, SEEK_SET);
        fprintf(source, "%s%d", str, --c);
        while(reupdate!=NULL){ /*update visitor information*/
            fprintf(source, "\n%s %s %s %s", reupdate->visitor.SrNo, reupdate->visitor.ticketNo, reupdate->visitor.Name, reupdate->visitor.ID); 
            reupdate=reupdate->nextPtr;
        }//end while
    fclose(source);
    fclose(ticknum);
} //end del_ticknum function

int del_name(void){/*delete name*/
    void del_try(char str[]);
    struct ticket* points = head; /*current node is head*/
    struct ticket* nodes = head;  /*when info is not found in the first node in linked list*/
    struct ticket* prev;          /*use when there's duplication in name*/
    struct ticket* dup[200];      /*use when there's duplication in name*/

    FILE *tempfile = fopen("output.txt", "a");
    if(tempfile == NULL) { //show error when tempfile cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if

    char nametemp[100]; //to store ticket number
    printf("\nPlease input the name you want to delete (spelling and spacing must be the same!): ");
    fgets(nametemp, 35, stdin);

    for (int i=0;nametemp[i]!='\0';i++){ /*put in underscore and replace newline with termination null character*/
        if (isspace(nametemp[i]) && nametemp[i]!='\n'){
            nametemp[i]='_';
        } //end nested if
        if(nametemp[i] == '\n'){
            nametemp[i] = 0;
        } //end nested if
    }//end for loop
    
    for (int j=0; nametemp[j]!='\0'; j++) { /*change to uppercase*/
        if(nametemp[j]>='a' && nametemp[j]<='z') {
            nametemp[j] = nametemp[j] - 32;
        }//end nested if
    }//end for loop

    if (points==NULL){//if no element is stored in linked list
        printf("\nIt is an empty list");
        exit(0);
    }//end if

    char check[100]; /*copy the name into a temporary character name array, then compare it with the input*/
    struct ticket* count = head; //for calculating
    int flag=0, i=0;//calculate whether there's similarity
    while (count!=NULL){
        strcpy(check,count->visitor.Name);   /*copy first name into temporary storage*/
        for (int j=0; check[j]!='\0'; j++) { /*change to uppercase*/
            if(check[j]>='a' && check[j]<='z') {
                check[j] = check[j] - 32;
            }//end nested if
        }//end for loop

        if (strcmp(check, nametemp)==0){ /*compare if check and nametemp are the same*/
            flag+=1;                     /*check for duplication*/
            dup[i] = prev;               /*store linked list node for previous*/
            dup[i+1] = count;           
            i+=2;                       
        }//end if

        prev=count->nextPtr;
        count=count->nextPtr; /*go to next pointer and continue looping until count == NULL*/
    }//end while

    if (flag == 0){ /*If no similar name is found*/
        printf("\nPlease check the spelling. If not, the name is not in Tickets.txt.");
    }//end if

    else if (flag >1){ /*If more than one similar names is found. If flag > 1, ask for ID and find according to ID*/
        int p=1;
        char str[100]= "\nDuplicated value is found\n";
        printf("\n%s", str);
        fprintf(tempfile, "%s", str);
        printf("\nValue of i is: %d", i);
        while (p<=i){ /*print out duplicated value*/         
            fprintf(tempfile, "\n%s %s %s %s", dup[p]->visitor.SrNo, dup[p]->visitor.ticketNo, dup[p]->visitor.Name, dup[p]->visitor.ID);
            printf("\n%s %s %s %s", dup[p]->visitor.SrNo, dup[p]->visitor.ticketNo, dup[p]->visitor.Name, dup[p]->visitor.ID);
            p+=2;
        }//end while
        char ID_delete[100];
        printf("\n\nPlease enter the ID to be deleted: ");
        fgets(ID_delete, 50, stdin);

        for (int j=0;ID_delete[j]!='\0';j++){//changing next line to terminating null char
            if(ID_delete[j] == '\n'){
                ID_delete[j] = 0;
            } //end nested if
        }//end for loop

        int m=1;
        for (; m<i; m+=2){
            if (strcmp(dup[m]->visitor.ID, ID_delete)==0){
                del_try(ID_delete);
                break;
            }//end if
        }//end for
        if (m>=i){
            printf("\nThe ID that you have entered is not among the duplicated names.");
            return 0; 
        }//end if
    }//end else
    else if (flag == 1){ /*copy the name into a temporary character name array, then compare it with the input*/
        char store[100];
        strcpy(store, points->visitor.Name); /*copy first name into temporary storage*/

        for (int j=0; store[j]!='\0'; j++) { /*change to uppercase*/
            if(store[j]>='a' && store[j]<='z') {
                store[j] = store[j] - 32;
            }//end nested if
        }//end for loop

        if (strcmp(store, nametemp)==0) {/*element found in head*/
            printf("\nThe visitor with Name.: %s information is deleted\n", points->visitor.Name);
            fprintf(tempfile, "\n\nThe visitor with Name: %s information is deleted\n\n", points->visitor.Name);
            head =points->nextPtr;
            free(points);
            points=NULL;
        }//end if
        else{
            while(points!=NULL){/*while there is still node*/
                nodes = points; /*prev points to points because singly linked list needs an extra node so that it fixed where all the linked list element points when an information is deleted*/
                points = points->nextPtr;
                strcpy(store, points->visitor.Name); /*copy second name into temporary storage*/
                for (int j=0; store[j]!='\0'; j++) { /*change to uppercase*/
                    if(store[j]>='a' && store[j]<='z') {
                        store[j] = store[j] - 32;
                    }//end nested if
                }//end for loop
                if (strcmp(store, nametemp)==0){ /*value found in list*/
                    nodes->nextPtr = points->nextPtr;
                    printf("\nThe visitor with Name: %s information is deleted\n", points->visitor.Name);
                    fprintf(tempfile, "\nThe visitor with Name: %s information is deleted\n\n", points->visitor.Name);
                    points = NULL;
                    break;
                }//end if
            }//end while
        }//end else
    }//end else if
    //update total visitor
    FILE *source = fopen("Tickets.txt", "w"); /*Update information in tickets.txt*/
    struct ticket* reupdate = head; //start is head and variable name is reupdate
    if(source == NULL) { //show error when source cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if

    char str[100]="Total visitors: ";
    fseek(source,strlen(str), SEEK_SET); /*Update total visitors*/
    fscanf(source, "%d", &c);
    fseek(source, 0, SEEK_SET);
    fprintf(source, "%s%d", str, --c);
    while(reupdate!=NULL){ /*Update visitor list*/
        fprintf(source, "\n%s %s %s %s", reupdate->visitor.SrNo, reupdate->visitor.ticketNo, reupdate->visitor.Name, reupdate->visitor.ID);
        reupdate=reupdate->nextPtr;   
    }//end else if
    fclose(source);
    fclose(tempfile);
    return flag;
}//end del_name function

void del_try(char str[]){/*if there's duplication in name*/
    struct ticket* points = head; //current node is head
    struct ticket* nodes = head; //when info is not found in the first node in linked list

    FILE *IDnum = fopen("output.txt", "a");
    if(IDnum == NULL) { //show error when IDnum cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if

    if (strcmp(points->visitor.ID, str)==0) {/*element found in head*/
        printf("\nThe visitor with ID: %s information is deleted\n", points->visitor.ID);
        fprintf(IDnum, "\nThe visitor with ID: %s information is deleted\n\n", points->visitor.ID);
        head =points->nextPtr;
        free(points);
        points=NULL;
    }//end if

    else{
        while(strcmp(points->visitor.ID, str)!=0){/*while there is still node*/
            nodes = points; /*prev points to points because singly linked list needs an extra node so that it fixed where all the linked list element points when an information is deleted*/
            points = points->nextPtr;
            if (strcmp(points->visitor.ID, str)==0){/*value is found in list*/
                nodes->nextPtr = points->nextPtr;
                printf("\nThe visitor with ID: %s information is deleted\n", points->visitor.ID);
                fprintf(IDnum, "\nThe visitor with ID: %s information is deleted\n\n", points->visitor.ID);
                points = NULL;
                break;
            }//end if
        }//end while
    }//end else

    FILE *source = fopen("Tickets.txt", "w"); //update total visitor
    if(source == NULL) { //show error when source cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if
    struct ticket* reupdate = head;
    //updates total visitor
    char str1[100]="Total visitors: ";
    fseek(source,strlen(str1), SEEK_SET); /*update total visitor*/
    fscanf(source, "%d", &c);
    fseek(source, 0, SEEK_SET);
    fprintf(source, "%s%d", str1, --c);
    while(reupdate!=NULL){ /*update visitor list*/
        fprintf(source, "\n%s %s %s %s", reupdate->visitor.SrNo, reupdate->visitor.ticketNo, reupdate->visitor.Name, reupdate->visitor.ID); //for Tickets.txt
        reupdate=reupdate->nextPtr;
    }//end while
    fclose(source);
    fclose(IDnum);
} //end del_try func

void del_ID(void){/*delete based on ID*/
    struct ticket* points = head; //current node is head
    struct ticket* nodes = head; //when info is not found in the first node in linked list

    FILE *IDnum = fopen("output.txt", "a");
    if(IDnum == NULL) { //show error when IDnum cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if

    char ID_num2[50]; //to store ticket number
    printf("\n\nIf the ID you want to delete belong to Malaysian, please add IC.");
    printf("\nIf not, add PASS. Note that both IC and PASS should have 9 digits (case-sensitive). If not, you won't be able to find it.");
    printf("\nPlease input the ID number you want to delete: ");
    fgets(ID_num2, 30, stdin);

    for (int i=0;ID_num2[i]!='\0';i++){//changing next line to terminating null char
        if(ID_num2[i] == '\n'){
            ID_num2[i] = 0;
        } //end nested if
    }//end for loop

    if (points==NULL){//if no element is stored in linked list
        printf("\nIt is an empty list");
        exit(0);
    }//end if

    else if (strcmp(points->visitor.ID, ID_num2)==0) {//element found in head
        printf("\nThe visitor with ID: %s information is deleted\n", points->visitor.ID);
        fprintf(IDnum, "\nThe visitor with ID: %s information is deleted\n\n", points->visitor.ID);
        head =points->nextPtr;
        free(points);
        points=NULL;
    }//end if

    else{
        while(strcmp(points->visitor.ID, ID_num2)!=0){//while there is still node
            nodes = points; /*prev points to points because singly linked list needs an extra node so that it fixed where all the linked list element points when an information is deleted*/
            points = points->nextPtr;
            if((points==NULL)){ /*if information cannot be found*/
                printf("\nYou have entered an incorrect ID.");
                break;
            }
            else if (strcmp(points->visitor.ID, ID_num2)==0){ /*if information is found*/
                nodes->nextPtr = points->nextPtr;
                printf("\nThe visitor with ID: %s information is deleted\n", points->visitor.ID);
                fprintf(IDnum, "\nThe visitor with ID: %s information is deleted\n\n", points->visitor.ID);
                points = NULL;
                break;
            }//end if
        }//end while
    }//end else

    FILE *source = fopen("Tickets.txt", "w"); //update total visitor
    if(source == NULL) { //show error when source cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if
    struct ticket* reupdate = head;

    //updates total visitor
    char str[100]="Total visitors: ";
    fseek(source,strlen(str), SEEK_SET); /*update total visitor*/
    fscanf(source, "%d", &c);
    fseek(source, 0, SEEK_SET);
    fprintf(source, "%s%d", str, --c);
    while(reupdate!=NULL){ /*update visitor informatio list*/
        fprintf(source, "\n%s %s %s %s", reupdate->visitor.SrNo, reupdate->visitor.ticketNo, reupdate->visitor.Name, reupdate->visitor.ID); //for Tickets.txt
        reupdate=reupdate->nextPtr;
    }//end while
    fclose(source);
    fclose(IDnum);
}//end del_id function

void display(void) {/*display*/
    FILE* source = fopen ("Tickets.txt", "r"); /*open file in read mode*/
    if (source == NULL) {    /*Program exits if the source pointer returns NULL*/
        printf("Error! File cannot be opened.");
        exit(1);
    }//end if

    FILE* target = fopen("output.txt", "a"); /*open file in append mode*/
    if (target == NULL) { /*Program exits if the target pointer returns NULL*/
        printf("Error! File cannot be opened.");
        exit(1);
    }//end if

    int choice0 = 0;
    while (1){
        printf("\nPrinting choice:\n1. Display normally\n2. Display in ascending order");
        printf("\nChoice: ");
        scanf("%d", &choice0); /*prompt user to give input*/
        getchar();
        switch (choice0){
            case 1:{/*display normally on terminal*/
            char buff;
            char done[1000];
            fseek(source, 0, SEEK_SET); /*start from the starting of the file*/
            fscanf(source, "%[^\n]", done); /*read until newline*/
            while ((buff=fgetc(source))!= EOF) {//reading char by char from file
                putchar(buff);   /*print out*/
                fprintf(target, "%c", buff); /*print out in output.txt*/
            } //end while
            fclose(source); fclose(target); 
            break;
            }//end case 1

            case 2:{/*display according to ascending order using name on terminal*/
                struct ticket* cur = head;
                struct ticket* node = NULL; /*pointing to the next node*/
                if (cur == NULL){
                    printf("\nThis list is empty");
                    break;
                }//end if
                else{ /*uppercase is lower value, so its up in the list*/
                    char *sptr, *tptr, *nptr, *iptr; /*Temporary pointers used to swap the position of names in list. Change as a whole*/
                    int swap; /*check whether the list is still being swapped*/
                    do{ /*do until swap remains 0. If value of swap != 1, then break out of loop*/
                        swap = 0; 
                        for (cur = head ;cur->nextPtr != NULL;cur = cur->nextPtr) {
                            node = cur->nextPtr;  /*pointing to the next node*/
                            if (strcmp(cur->visitor.Name, node->visitor.Name) > 0) { /*if 1st node > 2nd node*/
                                /*Using the logic of bubble sort which is:
                                if (a>b){
                                    temp = a;
                                    a = b;
                                    b = temp;
                                }, now variable a contains value of b and b contains value of a*/

                                sptr = node->visitor.SrNo; /*translate to temp = a (as shown above)*/
                                tptr = node->visitor.ticketNo;
                                nptr = node->visitor.Name;
                                iptr = node->visitor.ID;

                                node->visitor.SrNo = cur->visitor.SrNo; /*translate to a = b (as shown above)*/
                                node->visitor.ticketNo = cur->visitor.ticketNo;
                                node->visitor.Name = cur->visitor.Name;
                                node->visitor.ID = cur->visitor.ID;

                                cur->visitor.SrNo = sptr;  /*translate to b = temp (as shown above)*/
                                cur->visitor.ticketNo = tptr;
                                cur->visitor.Name = nptr;
                                cur->visitor.ID = iptr;

                                swap = 1; /*show that the order of visitor information has been modified*/
                            }//end nested if
                        }//end for loop
                    } while(swap == 1); /*continue looping if the list is still being swapped*/
                } //end else

                struct ticket* again = head;
                char str[200]= "\n\nArranging in ascending order (taking into consideration of uppercase and lowercase)\n";
                printf("%s", str);
                fprintf(target, "%s", str);
                while (again!=NULL){ /*print out*/
                    fprintf(target, "\n%s %s %s %s", again->visitor.SrNo,again->visitor.ticketNo, again->visitor.Name, again->visitor.ID);
                    printf("\n%s %s %s %s", again->visitor.SrNo,again->visitor.ticketNo, again->visitor.Name, again->visitor.ID);
                    again=again->nextPtr;
                }//end while

                fclose(source); fclose(target);
                break;
            }//end case 2
            default: printf("\nNo such choice! Try again.");break;
        }//end switch
        if (choice0==1 || choice0==2){
            break;
        }
    }//end while
}//end display function