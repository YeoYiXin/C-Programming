/* Name: Yeo Yi Xin  Student ID: 20414841*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <malloc.h> //for dynamic allocation of the memory
# include <ctype.h>
/* Create source, Open source, Process source, closer the source
1. fopen(), fclose(), getc() - get char, putc() - put char, fprintf() - print formatted output into the source,
fscanf() - reads the input from source, fgets() - read string/char from source, fputs() - write string/char into source, 
feof() - detects end of source, getw() - write integer, putw() - put integer
'a', 'w' 'r'*/

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
// Initialize nodes
struct ticket* head = NULL; //linked list for head

void previous(void); //to read previous input
void instruction(void); //to print out instruction
void convert(void); //get sr_num, name, ID, ticket
void search(void); //search
void delete(void); //delete selection
void display(void); //to display

int main (void) {//havent do 40 visitors
    previous();
    char choice;
    int done=0;
    while (done==0) //while true
    {
        printf("\n-----------------------------------------------------\n");
        instruction(); //func call to print instruction
        printf("\nPlease choose: ");
        scanf("%c", &choice);
        getchar();
        switch (choice) {
            case '1': { //appending
                FILE *source = fopen("Tickets.txt", "r+");
                //total visitor
                if (source == NULL){
                    fclose(source);
                    source = fopen("Tickets.txt", "w");
                }
                int c;
                char skip ='\n';
                char str[] = "Total visitors: ";
                fseek(source, strlen(str), SEEK_SET);
                fscanf(source, "%d", &c);
                fclose(source);
                printf("%s%d%c", str,c,skip);
                if (c>40){
                    printf("Reached maximum capacity. Sorry.");break;
                }
                convert(); //add
                break;
            }
            case '2': { //Search
                search();
                break;
            }
            case '3': { //delete
                delete();
                break;
            }
            case '4': {  //Display Total Number of Ticket Sold
                display(); //only ascending not working
                break;
            }
            case '5': { //exit program
                return 0;break;
            }
            default: {
                printf("\nNo such choice! ");
                printf("\nTry again. To exit, choose option 5");
                printf("\n");
            }//end default
        }//end switch
    }//end while
}//end main func

void previous(void){//still cannot access previous input
    FILE* prev = fopen("Tickets.txt", "r");
    if (prev == NULL){
        fclose(prev);
        prev = fopen("Tickets.txt", "w");
    }//end if
    
    char done[1000];

    fseek(prev, 0, SEEK_SET); //start from the beginning
    fscanf(prev, "%[^\n]", done);
    if (fgetc(prev)==EOF){//if 0
        exit(1);
    }//end if
    while(fgetc(prev)!=EOF){
        struct ticket* node = (struct ticket*)malloc (sizeof(struct ticket)); //new node
        struct ticket* points = head;
        
        char serialnum[4]={};
        char ticketnum[30]={};
        char nametemp[32]={};
        char IDnum[30]={};

        fscanf(prev, "%s %s %s %s", serialnum, ticketnum, nametemp, IDnum);

        //set node pointing to struct and allocate memory
        node->visitor.SrNo = malloc(8);
        node->visitor.ticketNo = malloc(100+1);
        node->visitor.Name = malloc(34+1);
        node->visitor.ID = malloc(70+1);

        strcpy(node->visitor.SrNo, serialnum);
        strcpy(node->visitor.ticketNo, ticketnum);
        strcpy(node->visitor.Name,nametemp);
        strcpy(node->visitor.ID, IDnum);

        node->nextPtr = NULL; //set node as NULL

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
    fclose(prev);
}//end func

void instruction(void) {//done
    printf("\nEnter your choice: ");
    printf("\n1. Add new visitor information, \n2. Search visitor information, \n3. Delete visitor information,");
    printf("\n4. Display Total Number of Ticket Sold, \n5. Exit the program");
} //end instruction function

void convert(void) {//done   
    FILE *source = fopen("Tickets.txt", "r+");
    //total visitor
    if (source == NULL){
        fclose(source);
        source = fopen("Tickets.txt", "w");
    }
    char str[] = "Total visitors: ";
    int c = 1;
    char skip= '\n';
    fseek(source,0,SEEK_SET);
    if(fgetc(source) == EOF){
        //fprintf(source, "%s%d", str, c);
        fprintf(source, "%s%d%c", str, c, skip);
    }//end if
    else{ 
        fseek(source, strlen(str), SEEK_SET);
        fscanf(source, "%d", &c);
        fseek(source, 0, SEEK_SET);
        fprintf(source, "%s%d%c", str, ++c, skip);
    }

    if (c>40)
    {
        exit(0); //stops  
    }

    int sr_no = 0;
    char temp_num[6];

    //serial number
    fseek(source, 0, SEEK_SET);
    char temp_sr[2];
    char buff[1024];
    memset(buff, 0, 1024);
    while(fgets(buff, 1024, source) != NULL) {} //reads each line till the end
    sscanf(buff, "%s %*s %*s %*s", temp_sr);
    sr_no = (int) strtod(temp_sr, NULL);
    ++sr_no;
    
    if (c != sr_no){
        c = sr_no;
    }//change c to be equal to serial number if its greater than serial number

    fclose(source);

    //for serial number
    sprintf(temp_num, "%02d",sr_no);
    printf("\nSerial number: %s", temp_num);

    char name_temp[32]; //to store name
    char name_temp1[33];
    char tick_temp[100]; //to store ticket number
    printf("\nEnter your name (Full Name): ");
    fgets(name_temp, 31, stdin);
    
    //obtain ticket number
    char temp[500]; //as temporary storage
    int length = (strlen(name_temp))-1; //obtain length of name
    memset(name_temp1, 0, sizeof(name_temp1));
    strncpy(name_temp1, name_temp, length);
    name_temp1[length] = 0;
    printf("\nLength: %d", length);
    //copy first 6 chars into temp
    if (length>=6)
    {
        memset(temp, 0, sizeof(temp));
        strncpy(temp, name_temp, 6);
        temp[6] = 0;
        // for (int j=0;temp[j]!='\0';++j){
        //     temp[j]=toupper(temp[j]);
        // }
        printf("\nName after strncpy: %s\n", temp);
        memset(tick_temp, 0, 100+1);
        char *z=tick_temp;
        for (int i=0;temp[i]!='\0';++i){
            z+=sprintf(z, "%d", (int)(temp[i]));
        }
    printf("\nString after using sprintf(): %s", tick_temp);
    }
    else if (length<6)
    {
        //reverse the string
        memset(temp, 0, sizeof(temp));
        strncpy(temp, name_temp, length);
        temp[length] = 0;
        printf("\nName after strncpy: %s\n", temp);
        printf("\nName after name after strcpy: %s\n", name_temp);
        strrev(temp);

        // for (int j=0;temp[j]!='\0';++j){
        //     temp[j]=toupper(temp[j]);
        // }
        // printf("\nString after using strrev1(): %s", temp);

        //concatenate string to make the string 6 words
        for (int i=0; strlen(temp)<6;i++){
            strcat(temp, " ");
        }

        strrev(temp);
        printf("\nString after using strrev2():%s", temp);
        //convert to ticket number
        memset(tick_temp, 0, 100+1);
        char *y=tick_temp;
        for (int i=0;temp[i]!='\0';++i){
            y+=sprintf(y, "%d", (int)(temp[i]));
        }
        printf("\nString after using sprintf(): %s", tick_temp);
    }//end else-if

    //replacing space with underscore and removing \n
    for (int i=0;name_temp[i]!='\0';i++){
        if (isspace(name_temp[i]) && name_temp[i]!='\n'){
            name_temp[i]='_';
        } 
        if(name_temp[i] == '\n'){
            name_temp[i] = 0;
        }
    }//end while loop
    //printf("\nName after change = %s", name_temp);
    
    char ID_temp[70];
    //get IC for international and local visitor
    int choice1=0;
    while (1)
    { //start switch statement
        printf("\n\nPlease choose accordingly to your nationality:\n1. Local (has Malaysian identification card)");
        printf("\n2. International\nChoice: ");
        scanf("%d", &choice1);
        getchar();
        switch (choice1) 
        {
            case 1:{//Local
                char ID1[12];
                char start[50] = "IC";
                memset(ID1, 0,12);
                printf("\n\nPlease enter your IC number (9 numbers): ");
                fgets(ID1, 15, stdin);
                int length1=(strlen(ID1))-1;
                printf("\nLength ID: %d", length1);
                while (length1<9 || length1>9){
                    printf("\n\nPlease enter your IC number (9 numbers): ");
                    fgets(ID1, 15, stdin);
                    length1=(strlen(ID1))-1;
                    printf("\nCurrent length ID: %d", length1);
                }//end while

                strcat(start, ID1);
                int length = strlen(start);
                memset(ID_temp, 0, 70);
                strncpy(ID_temp, start, length);
                ID_temp[length] = 0;
                printf("\nLocal ID after strncpy: %s\n", ID_temp);
                break;
            }//end case 1
            case 2: { //International
                char ID1[14];
                char start[50] = "PASS";
                memset(ID1, 0,12);
                printf("\n\nPlease enter your Passport number (9 numbers): ");
                fgets(ID1, 15, stdin);
                int length1=(strlen(ID1))-1;
                printf("\nLength Passport: %d", length1);
                while (length1<9 || length1>9){
                    printf("\n\nPlease enter your IC number (9 numbers): ");
                    fgets(ID1, 15, stdin);
                    length1=(strlen(ID1))-1;
                    printf("\nCurrent length ID: %d", length1);
                }//end while

                strcat(start, ID1);
                int length = strlen(start);
                memset(ID_temp, 0, 70);
                strncpy(ID_temp, start, length);
                ID_temp[length] = 0;
                printf("\nInternational ID after strncpy: %s\n", ID_temp); 
                break;
            }//end case 2
            default:{
                printf("\nNo such choice! ");
            }//end default
        }//end switch
        if (choice1 != 1 && choice1 !=2){
            printf("\nTry again");
            printf("\n");
        }//end switch
        else{
            break;
        }//end else
    }//end while

    ID_temp[strcspn(ID_temp, "\n")] = 0;

    source = fopen("Tickets.txt", "a");
    if(source == NULL) { //show error when source cannot be created
        printf("Error in creating the source\n");
        exit(1); //exit the program
    }//end if

    struct ticket* node = (struct ticket*)malloc (sizeof(struct ticket)); //new node
    struct ticket* points = head;

    //set node pointing to struct 
    node->visitor.SrNo = malloc(8);
    node->visitor.ticketNo = malloc(100+1);
    node->visitor.Name = malloc(34+1);
    node->visitor.ID = malloc(70+1);

    strcpy(node->visitor.SrNo, temp_num);
    strcpy(node->visitor.ticketNo, tick_temp);
    strcpy(node->visitor.Name, name_temp);
    strcpy(node->visitor.ID, ID_temp);

    if (head == NULL){ //if head is empty, set first struct data as head and points to next head which is NULL
        head = node;
        points = head;
        points->nextPtr = NULL;
    }
    else{
        while (points->nextPtr != NULL){ //traverse until it reach the last node in the list
            points = points->nextPtr; //pointer points to next node
        }
        node->nextPtr = NULL; //next pointer is empty
        points->nextPtr = node;
    }

    FILE* target = fopen("output.txt", "a+");
    if (target == NULL) {
        printf("Error! File cannot be opened.");
        // Program exits if the target pointer returns NULL.
        exit(1);
    }//end if
    fprintf(source, "%s %s %s %s\n", node->visitor.SrNo, node->visitor.ticketNo, node->visitor.Name, node->visitor.ID); //for Tickets.txt
    fclose(source);//close source

    fprintf(target, "%s %s %s %s\n",  node->visitor.SrNo, node->visitor.ticketNo, node->visitor.Name, node->visitor.ID); //for output.txt
    printf("\nThe information of the visitor %s is recorded.", node->visitor.Name);
    fprintf(target, "\nThe information of the visitor %s is recorded.\n\n", node->visitor.Name); //for output.txt
    fclose(target); //close target
}//end convert func

void search(void){//done
    struct ticket* points = head;
    FILE *result = fopen("output.txt", "a");
    if(result == NULL) { //show error when result cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if
    //Search visitor information based on Ticket No, Name, or ID
    int choice3;
    char name_temp[32]; //to store name
    char tick_num[50]; //to store ticket number
    //char g[20];
    char ID_temp[70];
    char temp_node[80];
    while (1)
    {//start switch statement
        printf("\nHow do you want to search by?\n1. Ticket Number\n2. Full Name\n3. ID ");
        printf("\nChoice: ");
        scanf("%d", &choice3);
        getchar();
        switch (choice3){
            case 1: {  //Ticket number
                int repeat=0;
                printf("\nPlease input your ticket number: ");
                fgets(tick_num, 50, stdin);
                for (int i=0;tick_num[i]!='\0';i++){
                    if(tick_num[i] == '\n'){
                        tick_num[i] = 0;
                    } //end nested if
                }//end for loop
                while (points!=NULL){//check for similarity in names
                    if (strcmp(points->visitor.ticketNo, tick_num)==0){
                        if (repeat<1){
                            char str[100]= "\nThe following record of the visitor is found:";
                            printf("\nThe following record of the visitor is found:");
                            fprintf(result, "%s", str);
                            repeat++;
                        }
                        printf("\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                        fprintf(result, "\n%s %s %s %s\n", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                    }//end nested if
                    points = points->nextPtr;
                }//end while
                free(points);
                break;
            }//end case 1 - ticket number
            case 2: {//Name
                int repeat=0;
                printf("\nPlease input the full name: ");
                fgets(name_temp, 31, stdin);
                for (int i=0;name_temp[i]!='\0';i++){
                    if (isspace(name_temp[i]) && name_temp[i]!='\n'){
                        name_temp[i]='_';
                    } //end nested if
                    if(name_temp[i] == '\n'){
                        name_temp[i] = 0;
                    } //end nested if
                }//end for loop
                int j=0;
                //change to uppercase
                for (j=0; name_temp[j]!='\0'; j++) {
                    if(name_temp[j]>='a' && name_temp[j]<='z') {
                        name_temp[j] = name_temp[j] - 32;
                    }//end nested if
                }//end for loop
                while (points!=NULL){//check for similarity in names
                //change to uppercase
                    strcpy(temp_node, points->visitor.Name);
                    for (j=0; temp_node[j]!='\0'; j++) {
                        if(temp_node[j]>='a' && temp_node[j]<='z') {
                            temp_node[j] = temp_node[j] - 32;
                        }//end nested if
                    }//end for loop
                    if (strcmp(temp_node, name_temp)==0){
                        if (repeat<1){
                            char str[100]= "\nThe following record of the visitor is found:";
                            printf("\nThe following record of the visitor is found:");
                            fprintf(result, "%s", str);
                            repeat++;
                        }
                        printf("\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                        fprintf(result, "\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                    } //end nested if
                    points = points->nextPtr;
                } //end while
                free(points);
                break;
            }//end case 2 - name
            case 3: { //ID - not working
                int repeat=0;
                printf("\nIf the ID you are finding belongs to Malaysian, please add IC.");
                printf("\nIf not, add PASS. Note that both IC and PASS should have 9 digits (case-sensitive). If not, you won't be able to find it.");
                printf("\nPlease enter the ID you would like to find: ");
                fgets(ID_temp, 20, stdin);
                for (int i=0;ID_temp[i]!='\0';i++){
                    if(ID_temp[i] == '\n'){
                        ID_temp[i] = 0;
                    }//end nested if
                }//end for loop
                while (points!=NULL){//check for similarity in names
                    if (strcmp(points->visitor.ID, ID_temp)==0){
                        if (repeat<1){
                            char str[100]= "\nThe following record of the visitor is found:";
                            printf("\nThe following record of the visitor is found:");
                            fprintf(result, "%s", str);
                            repeat++;
                        }
                        printf("\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                        fprintf(result, "\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
                    }//end nested if
                    points = points->nextPtr;
                }//end while loop
                free(points);
                break;
            }//end case 3 - ID
            default: {
                printf("No such choices!");
                printf("\nTry again");
                printf("\n");
            }
        }//end switch
        if (choice3 == 1 || choice3 ==2 || choice3 == 3){
            break;
        }//end switch
    }//end while loop
    fclose(result);
}//search func end

void delete (void){//delete selection
    int choice_3;
    //void updates(void);
    void del_ticknum(void);
    //void del_name(void);
    //void del_ID(void);
    while (1) {//start switch statement
        printf("\nThrough which way do you want to delete?\n1. Ticket Number\n2. Full Name\n3. ID ");
        printf("\nChoice: ");
        scanf("%d", &choice_3);
        getchar();
        switch (choice_3){
            case 1: {  //Ticket number
                del_ticknum();//updates();
                break;
            }//end case 1 - ticket number
            case 2: {//Name
                //del_name();
                break;
            }//end case 2 - name
            case 3: { //ID - not working - if name duplicated, not working
                //del_ID();updates();
                break; 
            }//end case 3 - ID
            default:{
                printf("No such choices!");
                printf("\nTry again");
                printf("\n");
            }
        }//end switch
        if (choice_3 == 1 || choice_3 ==2 || choice_3 == 3){
            break;
        }//end switch
    }//end while loop
}//delete function ends

void del_ticknum(void){
    // struct ticket* node;
    struct ticket* cur = head; //to free up memory
    struct ticket* prev = head; //to free up memory

    FILE* search = fopen("Tickets.txt","w");
    if (search == NULL) {
        printf("Error! File cannot be opened.");
        // Program exits if the source pointer returns NULL.
        exit(1);
    }//end if

    FILE *ticknum = fopen("output.txt", "a");
    if(ticknum == NULL) { //show error when ticknum cannot be created
        printf("Error in creating result\n");
        exit(1); //exit the program
    }//end if

    char tick_num2[15]; //to store ticket number
    printf("\nPlease input the ticket number you want to delete: ");
    fgets(tick_num2, 13, stdin);

    for (int i=0;tick_num2[i]!='\0';i++){//changing next line to terminating null char
        if(tick_num2[i] == '\n'){
            tick_num2[i] = 0;
        } //end nested if
    }//end for loop

    if (head == NULL){
        printf("\nIt is empty list");
    }
    else if (strcmp(cur->visitor.ticketNo, tick_num2)== 0){
        printf("\nThe visitor with Ticket No.: %s, information is deleted.", cur->visitor.ticketNo);
        fprintf(ticknum, "\nThe visitor with Ticket No.: %s, information is deleted.", cur->visitor.ticketNo);
        head = cur->nextPtr;
        free(cur);
        cur = NULL;
    }
    else{
        while(strcmp(cur->visitor.ticketNo, tick_num2)!=0){
            prev = cur;
            cur = cur->nextPtr;
        }
        prev->nextPtr = cur->nextPtr;
        printf("\nThe visitor with Ticket No.: %s, information is deleted.", cur->visitor.ticketNo);
        fprintf(ticknum, "\nThe visitor with Ticket No.: %s, information is deleted.", cur->visitor.ticketNo);
        free(cur);
        cur=NULL;
    }

    //Hence, the final value has been deleted
    int c;
    char str[100]="Total visitors: ";
    char skip = '\n';
     //update total visitors
    fseek(search, strlen(str), SEEK_SET);
    fscanf(search, "%d", &c);
    fseek(search, 0, SEEK_SET);
    fprintf(search, "%s%d%c", str, --c, skip);
    fseek(search, 0, SEEK_CUR);
    while(cur!=NULL){
        fprintf(search, "%s %s %s %s\n", cur->visitor.SrNo, cur->visitor.ticketNo, cur->visitor.Name, cur->visitor.ID); //for Tickets.txt
        cur=cur->nextPtr;
    }//end while
    //fprintf(search, "%s %s %s %s\n", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID); //for Tickets.txt
    fclose(ticknum);
    fclose(search);
} //end del_ticknum function

//name is in try.txt
// void del_ID(void) {//not working because it clashes with name
//     struct ticket* points = head;
//     struct ticket* temp;
//     struct ticket* temp2;
//     FILE *source = fopen("Tickets.txt", "a");
//     if(source == NULL) { //show error when source cannot be created
//         printf("Error in creating result\n");
//         exit(1); //exit the program
//     }//end if

//     FILE *ticknum2 = fopen("output.txt", "a");
//     if(ticknum2 == NULL) { //show error when result cannot be created
//         printf("Error in creating result\n");
//         exit(1); //exit the program
//     }//end if
//     char ID_temp2[70];
//     printf("\nPlease input the ID you want to delete: ");
//     fgets(ID_temp2, 20, stdin);

//     for (int i=0;ID_temp2[i]!='\0';i++){
//         if(ID_temp2[i] == '\n'){
//             ID_temp2[i] = 0;
//         } //end nested if
//     }//end for loop
//     /*if the information to be deleted is in the head*/
//     if (points == head && (strcmp(points->visitor.ID, ID_temp2)==0)) {
//         puts("In if");
//         temp = head;
//         head = head->nextPtr;
//         //fprintf(source, "\n%s %s %s %s", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID);
//         printf("\nThe visitor with ID: %s information is deleted\n", points->visitor.ID);
//         puts("After 1st if head");
//         free(temp); //free dethreaded node
//     }//end if
//     else{
//         struct ticket* prev = head;
//         struct ticket* current = head->nextPtr;
//         puts("In else");
//         while(points!=NULL && (strcmp(points->visitor.ID, ID_temp2)!=0)){//while there is still node
//             puts("In while");
//             prev = current; //prev points to points because singly linked list needs an extra node so that it fixed where all the linked list element points when an information is deleted
//             current = current->nextPtr;
//         }

//         if (points!=NULL && strcmp(points->visitor.ID, ID_temp2)==0){
//             temp2 = current;
//             prev->nextPtr = current->nextPtr;
//             printf("\nThe visitor with ID: %s information is deleted\n", current->visitor.ID);
//             fprintf(ticknum2, "\nThe visitor with ID: %s information is deleted", current->visitor.ID);
//             free(temp2);
//             puts("In nexted if");
//         }//end nested if
//             // puts("just out of nested if");
//             // prev=points->nextPtr; //prev points to next pointer before points
//             // free(points);//this is to free up memory once every loop ends
//     }//end else

//     fclose(source);
//     fclose(ticknum2);
// } //end del_ID function

// void updates(void){ //deletes the whole thing
//     struct ticket* points = head;
//     FILE* update = fopen("Tickets.txt","w");
//     if (update == NULL) {
//         printf("Error! File cannot be opened.");
//         // Program exits if the source pointer returns NULL.
//         exit(1);
//     }//end if
//     fseek(update, 0, SEEK_SET);

//     int c;
//     char str[100]="Total visitors: ";
//     char skip = '\n';
//     //update total visitors
//     fseek(update, strlen(str), SEEK_SET);
//     fscanf(update, "%d", &c);
//     fseek(update, 0, SEEK_SET);
//     fprintf(update, "%s%d%c", str, --c, skip);
//     fseek(update, 0, SEEK_CUR);
//     while(points!=NULL){
//         fprintf(update, "%s %s %s %s\n", points->visitor.SrNo, points->visitor.ticketNo, points->visitor.Name, points->visitor.ID); //for Tickets.txt
//         points=points->nextPtr;
//     }//end while

//     fclose(update);
// }//end update func

void display(void) {//left ascending order
    FILE* source = fopen ("Tickets.txt", "r"); //source source
    if (source == NULL) {
        printf("Error! File cannot be opened.");
        // Program exits if the source pointer returns NULL.
        exit(1);
    }

    FILE* target = fopen("output.txt", "a");
    if (target == NULL) {
        printf("Error! File cannot be opened.");
        // Program exits if the target pointer returns NULL.
        exit(1);
    }

    //void swap(char *[], char *[]); //function prototype

    int choice0;
    printf("\nPrinting choice:\n1. Display normally\n2. Display in ascending order");
    printf("\nChoice: ");
    scanf("%d", &choice0);
    getchar();
    switch (choice0){
        case 1:{//display normally on terminal
        char buff;
        char done[1000];
        fseek(source, 0, SEEK_SET);
        fscanf(source, "%[^\n]", done);
        while ((buff=fgetc(source))!= EOF) {//reading char by char from file
            putchar(buff);/* Print character read on console */
            fprintf(target, "%c", buff);
        } 
        fclose(source); fclose(target); break;
        }//end case 1

        case 2:{//display according to ascending order using name on terminal
            break;
        }//end case 2
        default: printf("\nNo such choice!");break;
    }//end switch
}//end display func

// // // void swap(char *oddstr[], char *evenstr[]){
//     char temporary[32];
//     memset(temporary, 0, 32);
//     int oddlength = strlen(*oddstr);
//     int evenlength = strlen(*evenstr);
//     for(int i=0;i<2;i++){
//           for(int j=i+1;j<2;j++){
//                if(strcmp(*oddstr, *evenstr)>0){//binary sort
//                     strcpy(temporary, *oddstr);
//                     temporary[oddlength]=0;
//                     strcpy(*oddstr, *evenstr);
//                     *oddstr[evenlength]=0;
//                     strcpy(*evenstr, temporary);
//                     *evenstr[oddlength]=0;
//                }//end if
//           }//end nested for
//      }//end for
//      printf(" %s %s ", *oddstr, *evenstr);
// }//swap func