/****************************************************************************
 * Copyright (C) 2010 Tim Lovorn
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

#include "Spectrum.hh"

double Spectrum::epsilon(const State& st, double kx, double ky) {
    return epsilonBar(st, kx, ky) - st.getEpsilonMin();
}

double Spectrum::epsilonBar(const State& st, double kx, double ky) {
    const Environment& env = st.env;
    const double sx = sin(kx);
    const double sy = sin(ky);
    return 2.0 * env.th * ((sx + sy) * (sx + sy) - 1.0)
         + 4.0 * (st.getD1() * env.t0 - env.thp) * sx * sy;
}

double Spectrum::xi(const State& st, double kx, double ky) {
    return Spectrum::epsilon(st, kx, ky) - st.getMu();
}

double Spectrum::delta(const State& st, double kx, double ky) {
    return 4.0 * st.getF0() * (st.env.t0 + st.env.tz)
               * (sin(kx) + st.env.alpha * sin(ky));
}

double Spectrum::pairEnergy(const State& st, double kx, double ky) {
    const double xi = Spectrum::xi(st, kx, ky);
    const double delta = Spectrum::delta(st, kx, ky);
    return sqrt(xi * xi + delta * delta);
}

double Spectrum::fermi(const State& st, double energy) {
    if (energy <= 0.0) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

double Spectrum::innerD1(const State& st, double kx, double ky) {
    return -0.5*(1 - xi(st, kx, ky)/pairEnergy(st, kx, ky)) * sin(kx)*sin(ky);
}

double Spectrum::innerMu(const State& st, double kx, double ky) {
    return 0.5 * (1 - xi(st, kx, ky)/pairEnergy(st, kx, ky));
}

double Spectrum::innerF0(const State& st, double kx, double ky) {
    const double sin_part = sin(kx) + st.env.alpha * sin(ky);
    return sin_part * sin_part / pairEnergy(st, kx, ky);
}
