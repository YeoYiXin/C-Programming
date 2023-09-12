#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 30
void printName (char* name);
void lettersOccurence(char* name);
void nameLength(char* name);
void nameChange(char* name);
void sumID(char *ID);
void telNum(char *telephoneNum);

int main(void){
    char studentName[MAX] = {0};
    char studentID[MAX] = {0};
    char studentNum[MAX] = {0};
    printf("Full Name: ");
    fgets(studentName, MAX-1, stdin);

    size_t len = strlen(studentName); //because fgets append newline to string
    if (len > 0 && studentName[len - 1] == '\n') {
        studentName[len - 1] = '\0';
    }

    printf("Student ID: ");
    fgets(studentID, MAX-1, stdin);

    size_t lenID = strlen(studentID); //because fgets append newline to string
    if (lenID > 0 && studentID[lenID - 1] == '\n') {
        studentID[lenID - 1] = '\0';
    }

    printf("Telephone No in the form of, for example (0060) 11-123456: ");
    fgets(studentNum, MAX-1, stdin);

    size_t lenNum = strlen(studentNum); //because fgets append newline to string
    if (lenNum > 0 && studentNum[lenNum - 1] == '\n') {
        studentNum[lenNum - 1] = '\0';
    }

    printName(studentName);
    lettersOccurence(studentName);
    nameLength(studentName);
    nameChange(studentName);
    sumID(studentID);
    telNum(studentNum);
}

void printName (char* name){
    int choice = 0;
    printf("Do you want to print your name in\n1. Uppercase\n2. Lowercase\nChoice (1/2): ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: {
            for (int i =0; name[i] != '\0'; i++){
                putchar(toupper(name[i]));
            }
            break;
        }
        case 2: {
            for (int i =0; name[i] != '\0'; i++){
                putchar(tolower(name[i]));
            }
            break;
        }
        default: {
            printf("No such choice\n"); break;
        }
    }
}

void lettersOccurence(char* name){
    char firstTwo[3] = {0};
    char remainingName[MAX] = {0};
    int j = 0;
    int occurence = 0;
    for (int i = 0; i < 2; i++){
        firstTwo[i] = tolower(name[i]);
    }
    int i = 2;
    for (; name[i] != '\0'; i++) {
        if (tolower(name[i]) == firstTwo[0] && tolower(name[i + 1]) == firstTwo[1]) {
            occurence++;
            if (occurence == 1){
                j = i;
            }
        }
    }
    if (occurence > 0){
        strncpy(remainingName, name+j, strlen(name) - j);
        printf("\nThe occurrence of %s is %d. The remaining name where first two letters is found is %s\n", firstTwo, occurence, remainingName);
    }
    else{
        printf("\nThe occurrence of %s is %d.\n", firstTwo, occurence);
    }
}

void nameLength(char* name){
    printf("Length: %d", strlen(name));
}

void nameChange(char* name) {
    char lastChar = name[strlen(name) - 1];    
    name[0] = lastChar; // Replace the first character with the last character
    printf("\nChanged Name: %s", name);
}

void sumID(char *ID){
    unsigned long int value = 0;
    for (int i = 0; ID[i]!='\0'; i++){
        if (isdigit(ID[i])) {
            value = value * 10 + (ID[i] - '0'); //add integer in string to numeric value
        }
    }
    unsigned long int temp = value;
    unsigned long int j = 0;
    unsigned long int sum = 0;
    while(value>0){
        j = value%10;
        sum += j;
        value = value / 10;
    }
    printf("\nThe ID is %lu and the sum is %lu", temp, sum);
}

void telNum(char *telephoneNum) {
    char *tokenPtr = strtok(telephoneNum, " ");
    char *numPortion[2] = {NULL}; // Array of pointer to store country code and city code + telephone number
    int i = 0;

    while (tokenPtr != NULL && i < 2) {
        numPortion[i] = tokenPtr;
        tokenPtr = strtok(NULL, " ");
        i++;
    }
 
    if (i == 2 && numPortion[1] != NULL) {
        char *cityTokenPtr = strtok(numPortion[1], "-");
        char *cityNum[2] = {NULL}; // Array to store city code and telephone number
        int j = 0;

        while (cityTokenPtr != NULL && j < 2) {
            cityNum[j] = cityTokenPtr;
            cityTokenPtr = strtok(NULL, "-");
            j++;
        }

        if (j == 2 && cityNum[0] != NULL && cityNum[1] != NULL) {
            printf("\nCountry Code = %s", numPortion[0]);
            printf("\nCity Code = %s", cityNum[0]);
            printf("\nTelephone Number = %s", cityNum[1]);

            // Extract the last six digits
            char *lastDigits = cityNum[1] + strlen(cityNum[1]) - 6; //-6 to position pointer at the start of telephne number
            printf("\nLast six digits as ASCII: ");

            // Convert and print each pair of digits
            for (int k = 0; k < 6; k += 2) {
                int digit1 = lastDigits[k] - '0';
                int digit2 = lastDigits[k + 1] - '0';
                int asciiValue = (digit1 * 10 + digit2);

                printf("%c", (char)asciiValue);
            }

            printf("\n");

        } else {
            printf("\nInvalid telephone number format.\n");
        }
    } else {
        printf("\nInvalid telephone number format.\n");
    }
}
