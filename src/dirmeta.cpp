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

#include <iostream>
#include "DirectoryMetadata.h"
#include "MD5Shortener.h"
#include "TruncatingShortener.h"

using namespace std;

int
main( int argc, char* argv[] ) {
    DirectoryMetadata::Ptr md;

    if ( argc > 1 && (string(argv[1]) == string("-f")) ) {
        md = argc > 2 ?
            DirectoryMetadata::fromMetadataFile(".", argv[2]) :
            DirectoryMetadata::fromMetadataFile(".");
    } else {
        MD5Shortener shortener;
//        TruncatingShortener shortener(5);
        md = DirectoryMetadata::fromFilesystem(".", shortener);
    }

    md->write(cout);

    return 0;
}
