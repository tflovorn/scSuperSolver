#ifndef __MFTS_SPECTRUM_H
#define __MFTS_SPECTRUM_H

#include "State.hh"

class Spectrum {
public:
    // One-hole spectrum to be used, minimum at 0
    static double epsilon(const State& st, double kx, double ky);
    // One-hole spectrum unmodified from theory
    static double epsilonBar(const State& st, double kx, double ky);
    // One-hole energy, epsilon - mu
    static double xi(const State& st, double kx, double ky);
    // Superconducting gap
    static double delta(const State& st, double kx, double ky);
    // Energy of a superconducting pair
    static double pairEnergy(const State& st, double kx, double ky);
    // Fermi distribution function (for T=0)
    static double fermi(const State& st, double energy);
};

#endif
