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
#include <string>

#include "Utility.hh"

int main(int argc, char *argv[]) {
    std::string path1 = "test/path1", path2 = "test/path2/",
                name1 = "file1.ff", name2 = "file2";
    std::cout << Utility::joinPath(path1, name1) << std::endl;
    std::cout << Utility::joinPath(path2, name2) << std::endl;
}
