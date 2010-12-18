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

#ifndef __SCSS__BZONE_H
#define __SCSS__BZONE_H

#include <cmath>
#include <cfloat>

#include "State.hh"

typedef double (*bzFunction)(const State&, double, double);

class BZone {
public:
    static double average(const State& st, bzFunction func);
    static double minimum(const State& st, bzFunction func);
};

#endif
