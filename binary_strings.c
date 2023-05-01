#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bin_strings(char* binString, int permLen);

/*
 * recursively show all the possible binary strings based on the amount of X's in the string that can represet 0 or 1
 */

int main(int argc, char* argv[]){

    if(argc != 2){
        exit(0);
    }

    char* binString = argv[1];

    int stringLen = strlen(binString);

    print_bin_strings(binString, stringLen); 

    return 0;
}

void print_bin_strings(char* binString, int permLen){
    // prints all the permutations of the binary string
    // XX
    // 0X
    // 1X
    int count = 0;
    for (int i = 0; i < permLen; i++){
        if (binString[i] == 'x' || binString[i] == 'X'){
            count ++;
        }
    }
    if (count == 0){
        printf("%s\n", binString);
    }
    else if (count > 1){
        for (int i = 0; i < permLen; i++){
            if (binString[i] == 'x' || binString[i] == 'X'){
                char* firstBinString;
                firstBinString = (char*)malloc(permLen);
                strcpy(firstBinString, binString);
                char* secBinString;
                secBinString = (char*)malloc(permLen);
                strcpy(secBinString, binString);
                firstBinString[i] = '0';
                secBinString[i] = '1';
                print_bin_strings(firstBinString, permLen);
                print_bin_strings(secBinString, permLen);
                break;
            }
        }
    }
    else {
        char* firstBinString;
        firstBinString = (char*)malloc(permLen);
        strcpy(firstBinString, binString);
        char* secBinString;
        secBinString = (char*)malloc(permLen);
        strcpy(secBinString, binString);
        for (int i = 0; i < permLen; i++){
            if (binString[i] == 'x' || binString[i] == 'X'){
                firstBinString[i] = '0';
                secBinString[i] = '1';
                break;
            }
        }
        printf("%s\n", firstBinString);
        printf("%s\n", secBinString);
    }

}
