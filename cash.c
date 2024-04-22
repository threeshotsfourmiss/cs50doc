#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // intialize our variables
    int change = 0;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    // get the change we owe
    do
    {
        change = get_int("Change owed: ");
    }
    // keep prompting if the answer is less than 0 or not an int
    while (change <= 0);

    // similar pattern for all cases, find the amount of whole coins the current
    // change amount can be divided into , then subtract that number of coins
    // multiplied by their value, then move on to the lower valued coins. finally,
    // sum the amount of each coin (if you wanted, you could easily print the amount
    // of each coin given)
    quarters = change / 25;
    change = change - 25 * quarters;
    dimes = change / 10;
    change = change - 10 * dimes;
    nickels = change / 5;
    change = change - 5 * nickels;
    pennies = change;
    int coins = quarters + dimes + nickels + pennies;
    printf("%i\n", coins);
    // printf("%i\n", quarters);
    // printf("%i\n", dimes);
    // printf("%i\n", nickels);
    // printf("%i\n", pennies);
}
