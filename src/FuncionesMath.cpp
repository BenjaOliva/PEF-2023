#include "../headers/FuncionesMath.h"
#include <cmath>

double cosMath(double x) {
    return cos(x);
}

double senMath(double x) {
    return sin(x);
}

double customCos(double x) {
    const int terms = 1000;
    double result = 1.0;
    double term = 1.0;

    for (int n = 1; n < terms; n++) {
        term *= (-x * x) / ((2 * n) * (2 * n - 1));
        result += term;
    }
    return result;
}

double customSen(double x) {
    const int n = 1000;
    double seno = 0.0;
    double term = x;
    int sign = 1;

    for (int i = 1; i <= n; i += 2) {
        seno += sign * term;
        sign *= -1;
        term *= (x * x) / ((i + 1) * (i + 2));
    }

    return seno;
}