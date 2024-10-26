#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to calculate the value of the polynomial given its coefficients
double calculateFunction(double x, double coeffs[], int degree)
{
    double result = 0.0;
    for (int i = 0; i <= degree; i++)
    {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

// Helper function to validate the user-provided initial guesses
bool validateInitialGuesses(double coeffs[], int degree, double a, double b)
{
    double f_a = calculateFunction(a, coeffs, degree);
    double f_b = calculateFunction(b, coeffs, degree);

    if (f_a * f_b < 0)
    {                // Check if there's a sign change
        return true; // Valid guesses
    }
    else
    {
        cout << "Invalid initial guesses! f(a) and f(b) must have opposite signs.\n";
        return false; // Invalid guesses
    }
}

int main()
{
    cout.precision(4);
    cout.setf(ios::fixed); // Set the precision of the output

    int degree;
    cout << "Enter the degree of the polynomial (1 to 4): ";
    cin >> degree;

    // Validate degree input
    if (degree < 1 || degree > 4)
    {
        cout << "Invalid degree. Please enter a value between 1 and 4.\n";
        return 1; // Exit if the degree is invalid
    }

    double coeffs[5]; // Array to hold coefficients for polynomials up to degree 4

    // Input coefficients for the polynomial
    cout << "Enter the coefficients from highest degree to constant term:\n";
    for (int i = 0; i <= degree; i++)
    {
        cout << "Coefficient of x^" << (degree - i) << ": ";
        cin >> coeffs[i];
    }

    double a, b, e; // Variables for the initial guesses and the desired accuracy

    // Input initial guesses from the user
    cout << "Enter the initial guesses:\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;

    // Validate initial guesses
    while (!validateInitialGuesses(coeffs, degree, a, b))
    {
        cout << "Please enter new guesses:\n";
        cout << "a = ";
        cin >> a;
        cout << "b = ";
        cin >> b;
    }

    cout << "Enter the degree of accuracy e: ";
    cin >> e; // Take the desired accuracy

    // Secant method implementation
    double c; // Variable for the new guess
    do
    {
        // Calculate the next point using the secant formula
        c = b - (b - a) / (calculateFunction(b, coeffs, degree) - calculateFunction(a, coeffs, degree)) * calculateFunction(b, coeffs, degree);

        if (calculateFunction(c, coeffs, degree) == 0)
        {
            cout << "\nThe root of the equation is " << c; // Print the root
            return 0;
        }

        a = b;
        b = c;

    } while (abs(c - b) >= e); // Check if the error is greater than the desired accuracy

    cout << "\nThe root of the equation is " << c; // Print the root
    return 0;                                      // End of the program
}
