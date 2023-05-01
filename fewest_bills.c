#include <stdio.h>
/*
 * A program that descibes the fewest amount of bills when given an amount of money
 */

int main() {
    // ask for withdrawal amount and assign it to varible
    printf("Please enter the amount of money you wish to withdraw: ");
    int withdrawalAmount = 0;
    scanf("%d", &withdrawalAmount);

    // use withdrawal amount to calc the amount of each bill
    int hundreds = withdrawalAmount / 100;
    withdrawalAmount -= hundreds * 100;

    int fifties = withdrawalAmount / 50;
    withdrawalAmount -= fifties * 50;

    int twenties = withdrawalAmount / 20;
    withdrawalAmount -= twenties * 20;

    int tens = withdrawalAmount / 10;
    withdrawalAmount -= tens * 10;

    int fives = withdrawalAmount / 5;
    withdrawalAmount -= fives * 5;

    int ones = withdrawalAmount;

    // print the results
    printf("You received %d hundred(s)\n", hundreds);
    printf("You received %d fifty(s)\n", fifties);
    printf("You received %d twenty(s)\n", twenties);
    printf("You received %d ten(s)\n", tens);
    printf("You received %d five(s)\n", fives);
    printf("You received %d one(s)\n", ones);

    return 0;
}