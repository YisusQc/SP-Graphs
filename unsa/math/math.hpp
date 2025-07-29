#pragma once

namespace unsa {

inline double abs(double x) {
    return x < 0 ? -x : x;
}

inline double sqrt(double x) {
    double guess = x / 2.0;
    double epsilon = 1e-6;
    while (abs(guess * guess - x) > epsilon) {
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

inline double pow(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

} // namespace unsa
