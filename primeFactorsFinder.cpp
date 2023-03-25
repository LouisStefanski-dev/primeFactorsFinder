#include <iostream>
#include <math.h>

//Finds two prime factors of a product of factor(undoing the method used for RSA)
//Using the following formula
//  g^r = mN + 1
//  where g is an arbitrary number that does not share any factors with N
//  where r is the exponent that satisfies mN + 1
//
//Rewriting this equation we get,
//  (g^(r/2) + 1)(g^(r/2) - 1) = mN 

//This determines how many loops the while loops should make before stopping.
int attemptLimit = 1000;

struct vector2 {
    int n1;
    int n2;
};

//base is g in the above equation
//goal is the number we are attempting to factor
int findR(const int base, const int goal) {
    int ans = 0;
    int r = 1;
    int attempts = 0;
    while (attempts < attemptLimit) {
        std::cout << "Calculating power. Guess: " << base << "^" << r << std::endl;
        ans = pow(base, r);
        if ((ans % goal) == 1) return r;
        r++;
        attempts++;
    }
}

//this function solves (g^(r/2) + 1)(g^(r/2) - 1) and returns the result as a vector2
//base is g in the above equation
//r is the exponent
vector2 factor(const int base, const int r) {
    vector2 sol;
    std::cout << "Factoring..." << std::endl;
    long double factor = pow(base, r / 2);
    sol.n1 = factor + 1;
    sol.n2 = factor - 1;
    return sol;
}

//Applies euclides algorithm to the solution vector2
//vSol is the solution obtained from factor
//goal is the number we are attempting to factor
vector2 euclidesAlgorithm(const vector2 vSol, const int goal) {
    vector2 solution;
    int n = vSol.n1;
    int dividend = n;
    int divisor = goal;
    int remainder = INT_MAX;

    while (remainder != 0) {
        std::cout << "Applying euclides algorithm, dividend: " << dividend << " divisor: " << divisor << std::endl;
        remainder = dividend % divisor;
        if (remainder == 0) break;
        dividend = divisor;
        divisor = remainder;
    }
    solution.n1 = divisor;
    solution.n2 = goal / solution.n1;
    return solution;
}

int main()
{
    //478, 5
    int productOfFactors = 77;
    int g = 8;
    vector2 factors = euclidesAlgorithm(factor(g, findR(g, productOfFactors)), productOfFactors);
    std::cout << "The factors of " << productOfFactors << " are: " << factors.n1 << " : " << factors.n2 << std::endl;
}