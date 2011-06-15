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

#include "exception.h"
#include <cstring>
#include <iostream>

namespace exception {

int
CatchAllBase::reportError(const boost::exception& ex) {
    std::cerr << boost::diagnostic_information(ex) << std::endl;

    if ( int const* err = boost::get_error_info<boost::errinfo_errno>(ex) ) {
        return *err;
    }
    return -1;
}

int
CatchAllBase::reportError(const boost::system::system_error& ex) {
    const boost::system::error_code err = ex.code();
    std::cerr << ex.what() << std::endl;
    return err.value();
}

} // namespace exception
