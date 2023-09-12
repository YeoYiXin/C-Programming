#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 201

void wordCounter(char* words);
void modifyText(char* words);
void appendingText(char* words);

int main(void){
    char text[MAX] = {0};

    printf("Write text (maximum 200 characters):\n");
    fgets(text, MAX-1, stdin);

    size_t len = strlen(text); //because fgets append newline to string
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    wordCounter(text);
    modifyText(text);
    appendingText(text);

}

void wordCounter(char* words){
    int wordCount = 0;
    char cpytext[MAX] = {0};
    strcpy(cpytext, words);
    char* token = strtok(cpytext, " \n"); // Split by space or newline

    while (token != NULL) {
        wordCount++;
        token = strtok(NULL, " \n");
    }

    printf("Word count: %d\n", wordCount);
}

void modifyText(char* words){
    printf("\nOriginal text: %s", words);

    //modify text
    int textLength = strlen(words);
    int halfLength = textLength / 2;
    int j = halfLength;
    char cpytext[MAX] = {0};
    strcpy(cpytext, words);
    for (int i = 0; cpytext[j] != '\0'; i++, j++){ //copy second half of text into first half
        cpytext[i] = cpytext[j];
    }

    printf("\nModified text = %s", cpytext);
}

void appendingText(char* words){
    char cpyText[MAX] = {0};
    char firstHalf[MAX] = {0};
    char secondHalf[MAX] = {0};

    strcpy(cpyText, words);
    int length = strlen(cpyText);
    printf("\nOriginal length of string: %d", length);
    int halfLength = length / 2;
    int firstLength = length - halfLength;
    printf("\nLength of first half: %d", firstLength);
    printf("\nLength of second half: %d", halfLength);

    for (int i = 0; i < halfLength; i++){ //copy first half of the text
        firstHalf[i] = cpyText[i];
    }
    firstHalf[halfLength] = '\0';
    int i = 0;
    for (int j = halfLength; cpyText[j] != '\0'; j++, i++){ //copy second half of the text
        secondHalf[i] = cpyText[j];
    }

    printf("\nFirst Half: %s\nSecond Half: %s", firstHalf, secondHalf);

    if (firstLength < halfLength){
        printf("\nSecond Half is larger than first half.");
    }
    else if (firstLength > halfLength){
        printf("\nFirst Half is larger than second half.");
    }
    else{
        printf("\nBoth halves have same length.");
    }

    strcat(firstHalf, "AAAAAA");
    printf("\nReversed: %s",strrev(firstHalf));

}


