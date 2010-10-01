#include "Environment.hh"

// Grab all the data from cfg.  Is there a less ugly way to do this?
// Also, need to make loggers.
Environment::Environment(const ConfigData& cfg) :
    gridLen(cfg.gridLen), t0(cfg.t0), tz(cfg.tz), thp(cfg.thp), x(cfg.x),
    alpha(cfg.alpha), th(cfg.t0 * (1 - cfg.x)),  
    initD1(cfg.initD1), initMu(cfg.initMu), initF0(cfg.initF0),
    tolD1(cfg.initD1), tolMu(cfg.initMu), tolF0(cfg.initF0),
    outputLog(cfg.outputLogName), errorLog(cfg.errorLogName) { }
