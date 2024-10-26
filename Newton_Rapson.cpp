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

// Function to calculate the derivative of the polynomial given its coefficients
double calculateDerivative(double x, double coeffs[], int degree)
{
    double result = 0.0;
    for (int i = 0; i < degree; i++)
    { // Derivative degree is one less than the polynomial degree
        result += coeffs[i] * (degree - i) * pow(x, degree - i - 1);
    }
    return result;
}

int main()
{
    cout.precision(4); // Set the precision for output
    cout.setf(ios::fixed);

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

    double x, x1, e, fx, fx1;

    // Input loop for the initial guess
    do
    {
        cout << "Enter the initial guess: ";
        cin >> x1; // Take an initial guess

        // Check if the derivative at the initial guess is zero
        fx1 = calculateDerivative(x1, coeffs, degree);
        if (fx1 == 0)
        {
            cout << "The derivative is zero at x = " << x1 << ". Please choose a different initial guess." << endl;
        }
    } while (fx1 == 0); // Repeat until a valid initial guess is provided

    // Input for desired accuracy
    cout << "Enter desired accuracy: ";
    cin >> e;

    cout << "x{i}" << "    " << "x{i+1}" << "        " << "|x{i+1}-x{i}|" << endl;

    // Newton-Raphson iteration
    do
    {
        x = x1;                                       // Make x equal to the last calculated value of x1
        fx = calculateFunction(x, coeffs, degree);    // Calculate f(x)
        fx1 = calculateDerivative(x, coeffs, degree); // Calculate f'(x)
        x1 = x - (fx / fx1);                          // Calculate the next approximation
        cout << x << "     " << x1 << "           " << abs(x1 - x) << endl;
    } while (fabs(x1 - x) >= e); // Continue until the desired accuracy is met

    cout << "The root of the equation is " << x1 << endl;
    return 0; // End of the program
}
