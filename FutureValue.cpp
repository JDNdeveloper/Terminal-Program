/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include <cmath>
#include "FutureValue.h"
using namespace std;

/*
 * Main method, gets information from
 * user and calls functions
 */
void FutureValue::start(string bob[]) {
    double investment;
    double interest;
    int compound;
    int time;
    cout << "\nHow much money would you like to invest?: ";
    cin >> investment;
    cout << "\nEnter interest rate as percentage: ";
    cin >> interest;
    cout << "\nEnter number of compounds each year: ";
    cin >> compound;
    cout << "\nEnter number of years to be invested: ";
    cin >> time;

    double futureValue = calcFuture(investment, interest, compound, time);

    cout << "\n\nThe future value will be: $";
    printf("%.2f", futureValue);
    cout << "\n\n";
}
/*
 * Calculates future balance
 */
double FutureValue::calcFuture(double newInvestment, double newInterest,
    int newCompound, int newTime) {
    double totalCompounds = newCompound * newTime;
    double interest1 = ( newInterest / 100 ) / newCompound;
    double futureValue = newInvestment * pow(( 1 + interest1 ), totalCompounds);
    return futureValue;
}
