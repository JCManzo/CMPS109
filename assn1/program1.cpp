// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

// Convert to a C++ version of monte carlo integration for pi
// Copyright Ira Pohl

#include <cstdlib>
#include <cmath>       // For "sqrt". Replaces: math.h
#include <ctime>       // For clock. Needed to seed random generator.
#include <iostream>    // For C++ I/O. Benefit: type safety.
#include <iomanip>     // For std::setprecision
#include <vector>      // For std::vector

// Replaces: #define MAXINT   32767
const int max_int = 32767;

// Inline function replaces the macro F(X) (sqrt(1-x*x))
inline double F(double x) { return sqrt(1-x*x); }

// Using "using namespace std" is gennerally considered
// bad practice. So "std::" will be used isntead.

double mcint(double a, double b, double max, int n) {
  int  below = 0, trials = 0;
  double x, y;

  for(trials = 0; trials < n; ++trials ) {
    x =  ((rand() % max_int)/(double)max_int)* (b - a)  + a;
    y =  (rand() % max_int)/(double)max_int;

    if (F(x) > y)
      ++below;
    }

    return ( (double)below/trials  * (b - a) * max);
}

int main() {
  // The following variables are not used in this scope:
  // pi, x, y, below
  // double   pi, x, y;
  // int below, trials,

  int mtrial, i, n_experiment = 5;

  // Standard vector declaration. Replaces array: pi_approx.
  std::vector<double> pi_approx;

  // cout replaces c's printf function to display output.
  // cin replaces the scanf function to read input.
  std::cout << "TRIALS = " << std::endl;
  std::cin >> mtrial;

  // Seed random generator with the current time of the system so that when
  // the program is run, the numbers used to calculate pi will be different.
  // Run only once.
  srand( (unsigned)time( NULL ) );

  for( i = 0; i < n_experiment; ++i ) {
    // Inserts trial result to the back of the vector.
    pi_approx.push_back(4 * mcint(0.0, 1.0, 1.0, mtrial) );
    mtrial = 10 * mtrial;
  }

  for( i = 0; i < n_experiment; ++i ) {
    // Replaces c's printf function. The "fixed" function is used so that
    // precision starts after the decimal, not at the begining of the number
    // and the "setprecision" function displays a minimum of 6 decimal places.
    std::cout << std::fixed;
    std::cout << std::setprecision(6) << "pi trial " << i << " = "
              << pi_approx[i] << ", " << std::endl;
   }

   return 0;
}
