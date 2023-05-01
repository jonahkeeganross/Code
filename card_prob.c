#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Write a program that calculates the probabilty of drawing a card based on the total cards, amount of cards
 * mulliganed, and the turn you want to check the probability at
 */

bool isValidFormat(const int numArgsRead, const int numArgsNeed);
int getValidInt(const char* prompt);
void findProbability(int deckSize, int cardsDesired, int initHandSize, int cardsMulliganed, int finalTurn);
double initDrawProbability(int deckSize, int cardsDesired, int initHandSize);
double probUntilFinalTurn(int deckSize, int cardsDesired, int initHandSize, int finalTurn);
double mulliganProbability(int deckSize, int cardsDesired, int initHandSize, int cardsMulliganed);

int main(){
    // runs the main function and get the inputs and checks if they are valid
    
    int deckSize, cardsDesired, initHandSize, cardsMulliganed, finalTurn;

    do{
        deckSize = getValidInt("Enter how many total cards there are in the deck: ");
    }while(!(deckSize > 0));
    do{
        cardsDesired = getValidInt("Enter how many copies of the card that you are looking for are in the deck: ");
    }while(!(cardsDesired > 0));
    do{
        initHandSize = getValidInt("Enter your initial hand size: ");
    }while(!(initHandSize >= 0));
    do{
        cardsMulliganed = getValidInt("Enter how many cards you are mulliganing: ");
    }while(!(cardsMulliganed >= 0));
    do{
        finalTurn = getValidInt("Enter what turn you want to draw the card by: ");
    }while(!(finalTurn >= 0));

    findProbability(deckSize, cardsDesired, initHandSize, cardsMulliganed, finalTurn);

    return 0;
}

void findProbability(int deckSize, int cardsDesired, int initHandSize, int cardsMulliganed, int finalTurn){
    // runs the functions to check for the probability at different stages of the game
    // computes the final calculations and prints the results
    double prob1 = initDrawProbability(deckSize, cardsDesired, initHandSize);
    double prob2 = mulliganProbability(deckSize, cardsDesired, initHandSize, cardsMulliganed);
    double prob3 = probUntilFinalTurn(deckSize, cardsDesired, initHandSize, finalTurn);

    double finalProb = 1 - (prob1 * prob2 * prob3);

    printf("The probability of drawing at least one of the cards by turn %d given you mulliganed %d cards is %.2lf\n", finalTurn, cardsMulliganed, finalProb);

}

double initDrawProbability(int deckSize, int cardsDesired, int initHandSize){
    // find the probability during the initial drawing stage
    double i = 0;
    double probability = 1;
    while(i < initHandSize){
        probability = probability * (((double)deckSize - (double)cardsDesired) - i) / ((double)deckSize - i);
        i++;
    }

    return probability;
}

double mulliganProbability(int deckSize, int cardsDesired, int initHandSize, int cardsMulliganed){
    // finds the probability during the mulligan stage of the game
    deckSize -= initHandSize;
    double probability = 1;
    double i = 0;
    while(i < cardsMulliganed){
        probability = probability * (((double)deckSize - (double)cardsDesired) - i) / ((double)deckSize - i);
        i++;
    }

    return probability;
}

double probUntilFinalTurn(int deckSize, int cardsDesired, int initHandSize, int finalTurn){
    // finds the probability during the final stage of the game until the final turn
    deckSize -= initHandSize;
    double probability = 1;
    double i = 0;
    while(i < finalTurn){
        probability = probability * (((double)deckSize - (double)cardsDesired) - i) / ((double)deckSize - i);
        i++;
    }

    return probability;
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