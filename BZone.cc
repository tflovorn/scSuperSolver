#include <cmath>
#include <cfloat>

#include "BZone.hh"

// Would be nice to have a single function handle transforming one BZone point into another
// instead of duplicating the traversal

double BZone::minimum(const State& st, bzFunction func) {
    double kx = -M_PI, ky = -M_PI, min = DBL_MAX, val;
    int N = st.env.gridLen;
    double step = 2 * M_PI / N;
    while (ky < M_PI) {
        while (kx < M_PI) {
            val = func(st, kx, ky);
            if (val < min) {
                min = val;
            }      
            kx += step;      
        }
        ky += step;
        kx = -M_PI;
    }
    return min;
}

double BZone::average(const State& st, bzFunction func) {
    double kx = -M_PI, ky = -M_PI, min = DBL_MAX, sum = 0.0;
    int N = st.env.gridLen;
    double step = 2 * M_PI / N;
    while (ky < M_PI) {
        while (kx < M_PI) {
            sum += func(st, kx, ky);
            kx += step;      
        }
        ky += step;
        kx = -M_PI;
    }
    return sum / (N * N);
}
