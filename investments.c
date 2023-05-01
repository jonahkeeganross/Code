#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

/*
 * Write a program that determines whether you should pay off all loans first then invest or pay loans and invest simultaneously
 */


bool isValidFormat(const int numArgsRead, const int numArgsNeed);
int getValidInt(const char* prompt);
double getValidDouble(const char* prompt);
double payLoanThenInvest(double moneyOwed, double annualInterestRate, double moneyToLoans,
                         int curAge, int retireAge, double annualROR);
void doMoneyCalculations(double moneyOwed, double annualInterestRate, double minLoanPayment, double moneyToLoans,
                         int curAge, int retireAge, double annualROR);
double payBothSimultaneously(double moneyOwed, double annualInterestRate, double minLoanPayment, double moneyToLoans,
                         int curAge, int retireAge, double annualROR);

int main(){
    // gets the inputs and pases them through validation checks
    // then pases the values into functions to perform the calculations needed
    double moneyOwed, annualInterestRate, minLoanPayment, moneyToLoans, annualROR;
    int curAge, retireAge;

    do{
        moneyOwed = getValidDouble("Enter how much you owe in loans: ");
    }while(!(moneyOwed >= 0));
    do{
        annualInterestRate = getValidDouble("Enter the annual interest rate of the loans: ");
    }while(!(annualInterestRate >= 0));
    do{
        minLoanPayment = getValidDouble("Enter your minimum monthly loan payment: ");
    }while(!(minLoanPayment >= 0));
    do{
        moneyToLoans = getValidDouble("Enter how much money you will be putting towards loans/retirement each month: ");
    }while(!(moneyToLoans >= minLoanPayment));
    do{
        curAge = getValidInt("Enter your current age: ");
    }while(!(curAge >= 0));
    do{
        retireAge = getValidInt("Enter the age you plan to retire at: ");
    }while(!(retireAge >= curAge));
    do{
        annualROR = getValidDouble("Enter your predicted annual rate of return: ");
    }while(!(annualROR >= 0));

    doMoneyCalculations(moneyOwed, annualInterestRate, minLoanPayment, moneyToLoans, curAge, retireAge, annualROR);
   
    return 0;
}

void doMoneyCalculations(double moneyOwed, double annualInterestRate, double minLoanPayment, double moneyToLoans,
                         int curAge, int retireAge, double annualROR){
    // runs both calculations for the different paying methods and prints the results
    double money1 = payLoanThenInvest(moneyOwed, annualInterestRate, moneyToLoans, curAge, retireAge, annualROR);
    double money2 = payBothSimultaneously(moneyOwed, annualInterestRate, minLoanPayment, moneyToLoans, curAge, retireAge, annualROR);

    if(money1 > money2){
        printf("You should apply all $%.2lf towards your loan before making any investments.\n", moneyToLoans);
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.\n", money1, money2);
    }
    else if(money2 > money1){
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.\n", money2, money1);
    }
    else{
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.\n", money2, money1);
    }
}

double payBothSimultaneously(double moneyOwed, double annualInterestRate, double minLoanPayment, double moneyToLoans,
                         int curAge, int retireAge, double annualROR){
    // calculates retirement fund if you pay minimum loan payments and invest the rest
    int monthsUntilRetirement = (retireAge - curAge) * 12;
    double monthlyInterestRate = annualInterestRate / 12;
    double monthlyROR = annualROR / 12;
    double retirementFund = 0;

    while(moneyOwed > 0 || monthsUntilRetirement > 0){
        moneyOwed = (moneyOwed + (moneyOwed * monthlyInterestRate)) - minLoanPayment;
        retirementFund = (retirementFund + (retirementFund * monthlyROR)) + (moneyToLoans - minLoanPayment);
        monthsUntilRetirement--;
        if(moneyOwed <= 0){
            if(moneyOwed < 0){
                retirementFund += fabs(moneyOwed);
                moneyOwed = 0;
                break;
            }
            break;
        }
        if(monthsUntilRetirement == 0 && moneyOwed > 0){
            retirementFund -= moneyOwed;
            moneyOwed = 0;
        }
    }
    while(monthsUntilRetirement > 0 && moneyOwed == 0){
        retirementFund = (retirementFund + (retirementFund * monthlyROR)) + moneyToLoans;
        monthsUntilRetirement--;
    }
    return retirementFund;
}

double payLoanThenInvest(double moneyOwed, double annualInterestRate, double moneyToLoans,
                         int curAge, int retireAge, double annualROR){
    // calculates retirement fund if you pay loans first and then invest
    double retirementFund = 0;
    int monthsUntilRetirement = (retireAge - curAge) * 12;
    double monthlyInterestRate = annualInterestRate / 12;
    double monthlyROR = annualROR / 12;
    while(moneyOwed > 0 || monthsUntilRetirement > 0){
        moneyOwed = (moneyOwed + (moneyOwed * monthlyInterestRate)) - moneyToLoans;
        monthsUntilRetirement--;
        if(moneyOwed <= 0){
            if(moneyOwed < 0){
                retirementFund = fabs(moneyOwed);
                moneyOwed = 0;
                break;
            }
            break;
        }
        if(monthsUntilRetirement == 0 && moneyOwed > 0){
            retirementFund -= moneyOwed;
            moneyOwed = 0;
        }
    }
    while(monthsUntilRetirement > 0){
        retirementFund = (retirementFund + (retirementFund * monthlyROR)) + moneyToLoans;
        monthsUntilRetirement--;
        if(monthsUntilRetirement == 0){
            break;
        }
    }
    return retirementFund;
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


double getValidDouble(const char* prompt){
    // gets a valid
    double num;
    const int numArgsNeeded = 1;
    int numArgsRead;
    do{
        printf("%s", prompt);
        numArgsRead = scanf(" %lf", &num);
    }while(!isValidFormat(numArgsRead, numArgsNeeded));


    return num;
}

