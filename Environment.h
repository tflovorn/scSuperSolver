class Environment {
public:
    // Construct an Environment from configuration data.
    Environment(const ConfigData& cfg);
    // Brillouin zone length (number of points = grid length ^ 2).
    const double gridLen;
    // Physical parameters.
    const double t0,    // Overall energy scale (default = 1.0).
                 tz,    // z-direction hopping energy.
                 thp,   // Diagonal (next-nearest-neighbor) hopping energy.
                 x,     // Doping / holon excess.
                 th,    // One-holon hopping energy: th = t0 * (1 - x).
                 alpha; // alpha = {-1, 1} -> {d-wave, s-wave} symmetry
    // Initial conditions.
    const double initD1, initMu, initF0;
    // Tolerances.
    const double tolD1, tolMu, tolF0;
};
