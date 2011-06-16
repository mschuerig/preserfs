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

#ifndef TRUNCATINGSHORTENER_H
#define TRUNCATINGSHORTENER_H

#include "NameShortener.h"
#include <set>
#include <string>

class TruncatingShortener : public NameShortener {
public:
    TruncatingShortener( size_t maxNameLength );

private:
    std::set<std::string> shortNames_;
    const size_t maxNameLength_;

    virtual std::string shorten(const std::string& longName);
    virtual void doReset();
};

#endif // TRUNCATINGSHORTENER_H
