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

#include "TruncatingShortener.h"
#include <cassert>
#include <boost/lexical_cast.hpp>

using namespace std;

TruncatingShortener::TruncatingShortener(size_t maxNameLength)
    : maxNameLength_(maxNameLength)
{
    // TODO ensure minimum length
}


string
TruncatingShortener::shorten(const std::string& longName) {
    if ( longName.size() <= maxNameLength_ ) {
        shortNames_.insert(longName);
        return longName;
    }

    string prefix(longName.substr(0, maxNameLength_ - 1));
    string shortName;
    
    for ( int i = 1; ; ++i ) {
        const string counter(boost::lexical_cast<string>(i));
        assert( counter.size() <= maxNameLength_ ); // TODO throw something sensible
        prefix.resize(maxNameLength_ - counter.size());
        shortName = prefix + counter;

        if ( shortNames_.insert(shortName).second ) {
            return shortName;
        }
    }
    
    assert( !"Error in TruncatingShortener" );
}
 
void
TruncatingShortener::reset() {
    shortNames_.clear();
}
