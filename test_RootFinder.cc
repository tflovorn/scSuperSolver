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

#include <iostream>

#include "RootFinder.hh"

double test_root_linear(double x, void *params) {
    return 1 - x;
}

int main(int argc, char *argv[]) {
    RootFinder rf(&test_root_linear, NULL, 0.0, -10.0, 10.0, 1e-6);
    const RootData& rd = rf.findRoot();
    std::cout << rd.converged << std::endl << rd.root << std::endl
        << rd.fnvalue << std::endl;
    return 0;
}
