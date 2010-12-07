/****************************************************************************
 * Copyright (C) 2010 Timothy Lovorn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#ifndef __MFTS_SPECTRUM_H
#define __MFTS_SPECTRUM_H

#include <cmath>

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
    // term to be summed to calculate rhs of associated S-C equation
    static double innerD1(const State& st, double kx, double ky);
    static double innerMu(const State& st, double kx, double ky);
    static double innerF0(const State& st, double kx, double ky);
};

#endif
