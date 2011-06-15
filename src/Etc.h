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

#ifndef ETC_H
#define ETC_H

#include <sys/types.h>
#include <string>
#include <exception>
#include <boost/exception/all.hpp>
#include <boost/noncopyable.hpp>

struct EtcError : virtual std::exception, virtual boost::exception { };

class Etc : public boost::noncopyable {
public:
    const std::string lookupUsername(uid_t uid) const;
    const std::string lookupGroupname(gid_t uid) const;
    
    uid_t lookupUserId(const std::string& user) const;
    gid_t lookupGroupId(const std::string& group) const;
};

#endif // ETC_H
