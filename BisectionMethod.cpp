#include <iostream>
#include <cmath>
#include <iomanip>
/*Enter the degree of the polynomial (1 to 4): 3
Enter the coefficients from highest degree to constant term:
Coefficient of x^3: 1
Coefficient of x^2: 0
Coefficient of x^1: -1
Coefficient of x^0: -11
Enter the initial guesses for the root:
Lower bound (a): 2
Upper bound (b): 3
Enter the desired degree of accuracy: 0.0001
The root of the equation is approximately 2.3736*/
using namespace std;

// Function to calculate the value of the equation f(x) = a*x^n + b*x^(n-1) + ... + z
double calculateFunction(double x, double coeffs[], int degree)
{
    double result = 0.0;
    for (int i = 0; i <= degree; i++)
    {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result; // Return the calculated value of the polynomial
}

int main()
{
    cout.precision(4);     // Set the precision for output
    cout.setf(ios::fixed); // Fix the decimal places in output

    double lowerBound, upperBound, midpoint, tolerance, fLower, fUpper, fMid; // Variables for bounds and function values
    int degree;
    double coeffs[5]; // Declare coeffs outside the loop to be accessible later

    // Input loop to get valid initial guesses from the user
    do
    {
        cout << "Enter the degree of the polynomial (1 to 4): ";
        cin >> degree; // User inputs the degree of the polynomial

        if (degree < 1 || degree > 4)
        {
            cout << "Invalid degree. Please enter a value between 1 and 4.\n";
            continue; // Repeat if the degree is invalid
        }

        // Input coefficients based on the degree of the polynomial
        cout << "Enter the coefficients from highest degree to constant term:\n";
        for (int i = 0; i <= degree; i++)
        {
            cout << "Coefficient of x^" << (degree - i) << ": ";
            cin >> coeffs[i];
        }

        cout << "Enter the initial guesses for the root:\n";
        cout << "Lower bound (a): ";
        cin >> lowerBound; // User inputs the lower bound
        cout << "Upper bound (b): ";
        cin >> upperBound; // User inputs the upper bound
        cout << "Enter the desired degree of accuracy: ";
        cin >> tolerance; // User inputs the desired accuracy

        // Check if a root exists between lowerBound and upperBound
        if (calculateFunction(lowerBound, coeffs, degree) * calculateFunction(upperBound, coeffs, degree) > 0)
        {
            cout << "No root exists between the given bounds. Please enter different initial guesses.\n";
        }
    } while (calculateFunction(lowerBound, coeffs, degree) * calculateFunction(upperBound, coeffs, degree) > 0); // Repeat until valid guesses are provided

    // Bisection method to find the root
    while (fabs(lowerBound - upperBound) >= tolerance)
    {
        midpoint = (lowerBound + upperBound) / 2.0; // Calculate the midpoint
        fLower = calculateFunction(lowerBound, coeffs, degree);
        fUpper = calculateFunction(upperBound, coeffs, degree);
        fMid = calculateFunction(midpoint, coeffs, degree);

        // Display the current bounds and the midpoint value
        // cout << "Lower Bound (a) = " << lowerBound
        //      << " | Upper Bound (b) = " << upperBound
        //      << " | Midpoint (c) = " << midpoint
        //      << " | f(c) = " << fMid << endl;

        // Check if we have found the exact root
        if (fMid == 0)
        {
            cout << "The root of the equation is " << midpoint << endl;
            return 0; // Exit if the exact root is found
        }

        // Adjust the bounds based on the function values
        if (fLower * fMid > 0)
        {
            lowerBound = midpoint; // Move the lower bound up
        }
        else
        {
            upperBound = midpoint; // Move the upper bound down
        }
    }

    // Output the approximate root after finishing the iterations
    cout << "The root of the equation is approximately " << midpoint << endl;

    return 0; // End of the program
}
