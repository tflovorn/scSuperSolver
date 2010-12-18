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

#include "Logger.hh"
#include "ConfigData.hh"
#include "Environment.hh"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "usage: test_Environment.out path" << std::endl;
    }
    const std::string& cfgFileName = "test_cfg",
                       path = argv[1];
    ConfigData *cfg = new ConfigData(path, cfgFileName);
    const Environment& env((const ConfigData&)(*cfg));
    env.outputLog.printf("Output log is running!\n");
    env.errorLog.printf("Error log is running!  Hooray!\n");
    std::cout << env.x << std::endl;
}
