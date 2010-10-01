#include <cmath>
#include "Spectrum.h"

double Spectrum::epsilon(const State& st, double kx, double ky) {
    return epsilonBar(st, kx, ky) - st.getEpsilonMin();
}

double Spectrum::epsilonBar(const State& st, double kx, double ky) {
    const Environment& env = st.env;
    const double sx = sin(kx);
    const double sy = sin(ky);
    return 2 * env.th * ((sx + sy) * (sx + sy) - 1)
         + 4 * (st.getD1() * env.t0 - env.thp) * sx * sy;
}

double xi(const State& st, double kx, double ky) {
    return Spectrum::epsilon(st, kx, ky) - st.getMu();
}

double delta(const State& st, double kx, double ky) {
    return 2 * st.getF0() * (sin(kx) + st.env.alpha * sin(ky));
}

double pairEnergy(const State& st, double kx, double ky) {
    const double xi = Spectrum::xi(st, kx, ky);
    const double delta = Spectrum::delta(st, kx, ky);
    return sqrt(xi * xi + delta * delta);
}

double fermi(const State& st, double energy) {
    if (energy < st.getMu()) {
        return 1;
    }
    else {
        return 0;
    }
}
