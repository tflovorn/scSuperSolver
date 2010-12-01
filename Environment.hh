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

#ifndef __MFTS_ENVIRONMENT_H
#define __MFTS_ENVIRONMENT_H

#include "ConfigData.hh"
#include "Logger.hh"

class Environment {
public:
    // Construct an Environment from configuration data. Build loggers.
    Environment(const ConfigData& cfg);
    // Log stuff with these.  (default destructor calls their destructors)
    Logger outputLog, errorLog, debugLog;
    // Physical parameters.
    const int gridLen,  // Brillouin zone side length 
              alpha;    // alpha = {-1, 1} -> {d-wave, s-wave} symmetry
    const double t0,    // Overall energy scale (default = 1.0).
                 tz,    // z-direction hopping energy.
                 thp,   // Diagonal (next-nearest-neighbor) hopping energy.
                 x,     // Doping / holon excess.
                 th;    // One-holon hopping energy: th = t0 * (1 - x).
    // Initial conditions.
    const double initD1, initMu, initF0;
    // Tolerances.
    const double tolD1, tolMu, tolF0;
};

#endif
