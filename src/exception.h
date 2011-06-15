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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cerrno>
#include <string>
#include <boost/exception/all.hpp>
#include <boost/noncopyable.hpp>
#include <boost/system/system_error.hpp>

namespace exception
{

class CatchAllBase : public boost::noncopyable {
protected:
    static int reportError(const boost::exception& ex);
    static int reportError(const boost::system::system_error& ex);
};

template<typename R, typename A1, typename A2>
class CatchAll : protected CatchAllBase {
public:
    typedef R (*func_t)(A1, A2);

    CatchAll(func_t fn, A1 a1, A2 a2)
	: fn_(fn), a1_(a1), a2_(a2) {}

    int call() {
	try {
	    r_ = fn_(a1_, a2_);
	} catch(const boost::system::system_error& ex) {
	    return reportError(ex);
	} catch(const boost::exception& ex) {
        return reportError(ex);
    }
	return 0;
    }

    R result() {
	return r_;
    }

private:
    func_t fn_;
    R r_;
    A1 a1_;
    A2 a2_;
};

} // namespace exception

#endif // EXCEPTION_H
