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

#include "MD5Shortener.h"

#include <openssl/md5.h>
#include <string>
#include <vector>

using namespace std;

string
MD5Shortener::shorten(const std::string& longName) {
    vector<unsigned char> hash(MD5_DIGEST_LENGTH);

    MD5(reinterpret_cast<const unsigned char*>(longName.c_str()),
	longName.size(),
	&hash[0]);

    string shortName(2 * MD5_DIGEST_LENGTH, 'x');

    string::iterator k = shortName.begin();
    for ( int i = 0; i < MD5_DIGEST_LENGTH; ++i ) {
        *k++ = "0123456789abcdef"[hash[i] >> 4];
        *k++ = "0123456789abcdef"[hash[i] &  0x0f];
    }

    return shortName;
}
