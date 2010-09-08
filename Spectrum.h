#ifndef __MFTS_SPECTRUM_H
#define __MFTS_SPECTRUM_H

#include "State.h"

class Spectrum {
    static double epsilon(const State& st, double kx, double ky);
    static double epsilonBar(const State& st, double kx, double ky);
    static double xi(const State& st, double kx, double ky);
    static double delta(const State& st, double kx, double ky);
    static double pairEnergy(const State& st, double kx, double ky);
    static double fermi(const State& st, double energy);
};

#endif
