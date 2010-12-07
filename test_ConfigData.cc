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

#include "ConfigData.hh"

int main(int argc, char *argv[]) {
    const std::string& cfgFileName("test_cfg");
    ConfigData *cfg = new ConfigData(cfgFileName);
    std::cout << cfg->getValue<int>("gridLen") << std::endl;
    std::cout << cfg->getValue<double>("tolD1") << std::endl;
    cfg->writeToFile(cfgFileName + std::string("_rewrite"));
    return 0;
}
