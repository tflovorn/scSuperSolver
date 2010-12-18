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

#ifndef __SCSS_LOGGER_H
#define __SCSS_LOGGER_H

#include <string>
#include <cstdarg>
#include <cstdio>

class Logger {
public:
    // This constructor opens file for writing with given name.
    // Destructor should close this file.
    Logger(const std::string& path, const std::string& fileName);
    // Destructor.
    ~Logger();
    // Client calls this to write to our open stream.
    void printf(const std::string& format, ...) const;
private:
    // Stream we'll write to.
    FILE *myLog;
};

#endif
