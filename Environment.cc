#include "Environment.hh"

// Grab all the data from cfg.  Is there a less ugly way to do this?
// Also, need to make loggers.
Environment::Environment(const ConfigData& cfg) :
    gridLen(cfg.getValue<int>("gridLen")),
    t0(cfg.getValue<double>("t0")), 
    tz(cfg.getValue<double>("tz")),
    thp(cfg.getValue<double>("thp")),
    x(cfg.getValue<double>("x")),
    alpha(cfg.getValue<int>("alpha")),
    th(t0 * (1 - x)),  
    initD1(cfg.getValue<double>("initD1")),
    initMu(cfg.getValue<double>("initMu")),
    initF0(cfg.getValue<double>("initF0")),
    tolD1(cfg.getValue<double>("tolD1")),
    tolMu(cfg.getValue<double>("tolMu")),
    tolF0(cfg.getValue<double>("tolF0")),
    outputLog(cfg.getValue<std::string>("outputLogName")),
    errorLog(cfg.getValue<std::string>("errorLogName")),
    debugLog(cfg.getValue<std::string>("debugLogName"))
{ }
