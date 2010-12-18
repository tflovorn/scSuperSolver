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

#include "Utility.hh"

std::string Utility::joinPath(const std::string& path,
                              const std::string& fileName) {
    int lastIndex = path.length() - 1;
    std::string finalPath = path;
    // shortcut evaluation prevents out-of-bounds access for empty string
    if (lastIndex >= 0 && path[lastIndex] != '/') {
        finalPath.append("/");
    }
    finalPath.append(fileName);
    return finalPath;
}
