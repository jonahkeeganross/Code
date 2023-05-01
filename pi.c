#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/*
 * Write a program that simulates tests for the value of pi based on the
 * probability of a point being on a circle within a square
 */

double rand_double(double low, double high);
int getValidInt(const char* prompt);
bool isValidFormat(const int numArgsRead, const int numArgsNeed);
void find_pi(int iterations);

int main(){
    // runs the main function, gets input and passes into function to calculate pi
    int seed, iters;

    seed = getValidInt("Enter the seed for the random number generator: ");
    srand(seed);
    do{
        iters = getValidInt("Enter the number of iterations to run: ");
    }while(!(iters > 0));

    find_pi(iters);


    return 0;
}

void find_pi(int iterations){
    // finds the value of pi based off random x and y coordinates

    int numTimesInCirc = 0;
    for(int i = 0; i < iterations; i++){
        double x = rand_double(-1, 1);
        double y = rand_double(-1, 1);
        double circCheck = pow(x, 2) + pow(y, 2) - 1;
        if(circCheck <= 0){
            numTimesInCirc++;
        }
    }
    double probInsideCirc = (double) numTimesInCirc / (double) iterations;
    double pi = probInsideCirc * 4;
    printf("The value of pi is %.2lf.\n", pi);
}

double rand_double(double low, double high) {
/*
 * generate a random double between low and high inclusive
 * @low: the lowest possible double that can be generated
 * @high: the highest possible double that can be generated
 * @returns: a random number between low and high
 */
  return low + ((double) rand()) / (((double) RAND_MAX / (high - low)));
}

int getValidInt(const char* prompt){
   int num;
   const int numArgsNeeded = 1;
   int numArgsRead;
   do{
     printf("%s", prompt);
     numArgsRead = scanf(" %d", &num); // waffles 45\n
   }while(!isValidFormat(numArgsRead, numArgsNeeded));

   return num;
}

bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
   bool formatIsGood = numArgsRead == numArgsNeed;
   char character;
   do{
     scanf("%c", &character); //45  bob  \n
		 if(!isspace(character)){ //found a non whitespace character on the way to the end of the line
			 formatIsGood = false;
		 }
	 }while(character != '\n'); //read characters until the end of the line
   return formatIsGood;
}