#include <stdio.h>
#include <math.h>

// Define PI since it's not a standard constant in C
#define PI 3.14159265358979323846

// Function to calculate Pi using inscribed and circumscribed polygons
void calculate_pi(unsigned int n_sides, double *pi_lower, double *pi_upper) {
    double radius = 1.0;
    *pi_lower = n_sides * 2.0 * radius * sin(PI / n_sides) / (2.0 * radius);
    *pi_upper = n_sides * 2.0 * radius * tan(PI / n_sides) / (2.0 * radius);
}

int main() {
    unsigned int n_sides = 3;
    double pi_lower, pi_upper;
    
    while (1) {
        calculate_pi(n_sides, &pi_lower, &pi_upper);
        if (fabs(pi_upper - pi_lower) < 1e-15) {
            printf("Value of N is: %u\n", n_sides);
            printf("Estimated value of π is: %.15f\n", (pi_lower + pi_upper) / 2.0);
            break;
        }
        n_sides += 1;
    }
    
    return 0;
}