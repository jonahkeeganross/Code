#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
 * Write a program that displays pascals triangle for as many lines as requested by the user
 */

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
int getValidInt(const char* prompt);
void doPascalsTriangle(int triLen);

int main() {
    // runs the main function and gets the valid input from the user
    int triLen;

    do{
        triLen = getValidInt("Please enter how many levels of Pascal's Triangle you would like to see: ");
    }while((!(triLen < 29)) && (!(triLen > 0)));

    doPascalsTriangle(triLen);
    
    return 0;
}

void doPascalsTriangle(int triLen) {
    // builds pascals triangle by line and prints them out then loops and makes the next line
    int lineLen = 1;
    int pascalsTri[triLen];
    int tempTri[triLen];
    for(int j = 0; j < triLen; ++j) {
        for(int l = 0; l < lineLen; ++l){
            tempTri[l] = pascalsTri[l];
        }
        for(int i = 0; i < lineLen; ++i) {
            if(lineLen == 1){
                pascalsTri[i] = 1;
                break;
            }
            if(lineLen == 2){
                pascalsTri[i + 1] = 1;
                break;
            }
            if(i == 0){
                pascalsTri[i] = 1;
            }
            if(!(i == 0) && !(i == lineLen - 1)){
                pascalsTri[i] = tempTri[i] + tempTri[i - 1];
            }
            if(i == lineLen - 1){
                pascalsTri[i] = 1;
            }

        }
        for(int k = 0; k < lineLen; ++k){
            printf("%d ", pascalsTri[k]);
        }
        printf("\n");
        lineLen += 1;
    }
}

bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
    // checks if input is in the valid format
    bool formatIsGood = numArgsRead == numArgsNeed;
    char character;
    do{
        scanf("%c", &character);
            if(!isspace(character)){ //found a non whitespace character on the way to the end of the line
            formatIsGood = false;
            }
        }while(character != '\n'); //read characters until the end of the line
    return formatIsGood;
}


int getValidInt(const char* prompt){
    // gets a valid int
    int num;
    const int numArgsNeeded = 1;
    int numArgsRead;
    do{
        printf("%s", prompt);
        numArgsRead = scanf(" %d", &num);
    }while(!isValidFormat(numArgsRead, numArgsNeeded));


    return num;
}