/*
    Copyright (C) 2011  Michael Schuerig <michael@schuerig.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NAMESHORTENER_H
#define NAMESHORTENER_H

#include <string>

class NameShortener {
public:
    std::string operator()(const std::string& longName) {
        return shorten(longName);
    }

    void reset() {
        doReset();
    }

    virtual ~NameShortener() {};

private:
    virtual std::string shorten(const std::string& longName) = 0;

    virtual void doReset() {}
};

#endif // NAMESHORTENER_H
