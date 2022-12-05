#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(void) {
    int popn = 4;
    double beta = 0.5; // birth rate
    double delta = 0.250; // death rate
    double time = 0.0;

    double Gamma = (beta + delta) * popn;

    gsl_rng *rng = gsl_rng_alloc(gsl_rng_default);

    while ((popn > 0) && (popn < 1024 * 1024)) {
        // using the Gillespie algorithm we only have two calls to the RNG, and
        // always sample from the same distributions: uniform for X, and
        // exponential for tau. We don't need to do any mathematics beforehand
        // to know which distributions to use.
        double x = gsl_ran_flat(rng, 0, Gamma);
        if (x <= beta * popn) {
            // birth
            popn++;
            Gamma += beta + delta;
        } else {
            // death
            popn--;
            Gamma -= beta + delta;
            if (popn == 0)
                break;
        }

        double tau = gsl_ran_exponential(rng, 1.0 / Gamma);
        time += tau;
        // print out progress:
        printf("%g, %i\n", time, popn);
    }
    printf("%g, %i\n", time, popn);

    return 0;
}
