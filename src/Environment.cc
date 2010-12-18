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
    outputLog(cfg.getPath(), cfg.getValue<std::string>("outputLogName")),
    errorLog(cfg.getPath(), cfg.getValue<std::string>("errorLogName")),
    debugLog(cfg.getPath(), cfg.getValue<std::string>("debugLogName"))
{ }
