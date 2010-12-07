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

#include "BZone.hh"

// Would be nice to have a single function handle transforming one BZone point
// into another instead of duplicating the traversal

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
