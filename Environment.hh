#ifndef __MFTS_ENVIRONMENT_H
#define __MFTS_ENVIRONMENT_H

#include "ConfigData.hh"
#include "Logger.hh"

class Environment {
public:
    // Construct an Environment from configuration data. Build loggers.
    Environment(const ConfigData& cfg);
    // Log stuff with these.  (default destructor calls their destructors)
    Logger outputLog;
    Logger errorLog;
    const int gridLen,  // Brillouin zone side length 
              alpha;    // alpha = {-1, 1} -> {d-wave, s-wave} symmetry
    // Physical parameters.
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
