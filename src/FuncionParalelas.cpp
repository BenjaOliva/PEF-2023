#include "../headers/FuncionesMath.h"
#include <omp.h>

double customCosParallel(double x) {
    const int terms = 1000;
    double result = 1.0;
    double term = 1.0;

    #pragma omp parallel for
    for (int n = 1; n < terms; n++) {
        term *= (-x * x) / ((2 * n) * (2 * n - 1));
        result += term;
    }
    return result;
}

double customSenParallel(double x) {
    const int n = 1000;
    double seno = 0.0;
    double term = x;
    int sign = 1;

    #pragma omp parallel for
    for (int i = 1; i <= n; i += 2) {
        seno += sign * term;
        sign *= -1;
        term *= (x * x) / ((i + 1) * (i + 2));
    }

    return seno;
}