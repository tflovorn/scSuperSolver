#include "Environment.h"

// Boy is this ugly.  Considering removing ConfigData class and just doing
// config file reading in Environment.
Environment::Environment(const ConfigData& cfg) :
    gridLen(cfg.gridLen),
    t0(cfg.t0),
    tz(cfg.tz),
    thp(cfg.thp),
    x(cfg.x),
    th(cfg.t0 * (1 - cfg.x)),
    alpha(cfg.alpha),
    initD1(cfg.initD1),
    initMu(cfg.initMu),
    initF0(cfg.initF0),
    tolD1(cfg.initD1),
    tolMu(cfg.initMu),
    tolF0(cfg.initF0) {}
