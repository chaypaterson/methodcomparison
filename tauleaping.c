#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(void) {
    int popn = 4;
    double beta = 0.5; // birth rate
    double delta = 0.250; // death rate
    double time = 0.0;

    double tau = 0.1;

    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);

    while ((popn > 0) && (popn < 1024 * 1024)) {
        // generate events and update populations:
        int born = gsl_ran_poisson(rng, popn * beta * tau);
        int died = gsl_ran_poisson(rng, popn * delta * tau);
        popn += born - died;

        time += tau;
        // print out progress:
        printf("%g, %i\n", time, popn);
    }
    printf("%g, %i\n", time, popn);

    return 0;
}
