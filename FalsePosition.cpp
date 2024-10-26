#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to calculate the value of the polynomial given its coefficients
double calculateFunction(double x, double coeffs[], int degree) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

int main() {
    // Set precision for output
    cout.precision(4);
    cout.setf(ios::fixed);

    double x0, x1;    
    double f0, f1, f2, x2, e;
    int iterationCount = 0;
    int degree;

    // Input for polynomial degree
    cout << "Enter the degree of the polynomial (1 to 4): ";
    cin >> degree;

    // Validate degree
    if (degree < 1 || degree > 4) {
        cout << "Invalid degree. Please enter a value between 1 and 4.\n";
        return 1; // Exit if the degree is invalid
    }

    double coeffs[5]; // Array to hold coefficients for polynomials up to degree 4

    // Input coefficients for the polynomial
    cout << "Enter the coefficients from highest degree to constant term:\n";
    for (int i = 0; i <= degree; i++) {
        cout << "Coefficient of x^" << (degree - i) << ": ";
        cin >> coeffs[i];
    }

    // Input loop to get valid initial guesses
    do {
        cout << "Enter two initial guesses (x0 and x1) such that f(x0) < 0 and f(x1) > 0:\n";
        cout << "x0: ";
        cin >> x0;
        cout << "x1: ";
        cin >> x1;

        // Calculate function values at the bounds
        f0 = calculateFunction(x0, coeffs, degree);
        f1 = calculateFunction(x1, coeffs, degree);

        // Check if the function values at the bounds have opposite signs
        if (f0 * f1 >= 0) {
            cout << "Invalid input! The function must have opposite signs at the two bounds. Please try again.\n";
        }
    } while (f0 * f1 >= 0); // Repeat until valid guesses are provided

    // Input for accuracy tolerance
    cout << "Enter desired accuracy (e): ";
    cin >> e;

    // Iterative method to find the root using the False Position Method
    do {
        // Calculate the next point using the false position formula
        x2 = (x0 * f1 - x1 * f0) / (f1 - f0);
        f2 = calculateFunction(x2, coeffs, degree);
        
        // Display the current iteration's results
        iterationCount++;
        //cout << "Iteration " << iterationCount << ": x = " << x2 << ", f(x) = " << f2 << endl;

        // Update bounds based on the sign of f(x2)
        if (f2 < 0) {
            x0 = x2; // Move lower bound up
            f0 = f2; // Update function value at the new lower bound
        } else {
            x1 = x2; // Move upper bound down
            f1 = f2; // Update function value at the new upper bound
        }

    } while (abs(f2) > e); // Continue until the function value is within tolerance

    // Output the root
    cout << "\nThe approximate root is: " << x2 << endl;

    return 0; // End of the program
}
