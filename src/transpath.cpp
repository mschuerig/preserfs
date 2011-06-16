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

#include <map>
#include <utility>
#include <boost/bind.hpp>
#include <boost/exception/all.hpp>
#include <boost/function.hpp>
#include <boost/throw_exception.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include "DirectoryMetadata.h"
#include "DirectoryTree.h"
#include "TruncatingShortener.h"
#include "exception.h"


using namespace std;
namespace fs = boost::filesystem;
using namespace exception;
#define foreach BOOST_FOREACH

typedef map<string, DirectoryEntry> EntryMap;
typedef boost::function<DirectoryTree::lookupResult (const string&)> LookupFunc;
typedef CatchAll<DirectoryTree::lookupResult, const string&> LookupCatchAll;


int
main( int argc, char* argv[] )
{
    boost::shared_ptr<NameShortener> shortener( boost::make_shared<TruncatingShortener>(5) );
    DirectoryTree::Ptr tree( DirectoryTree::fromFilesystem(".", shortener) );

    LookupFunc translate = boost::bind(&DirectoryTree::lookup, tree, _1, &DirectoryEntry::shortName);

    for ( int i = 1; i < argc; ++i ) {
        const string longPath(argv[i]);

        LookupCatchAll catcher(translate, longPath);
        if ( int err = catcher() ) {
            return err;
        }

        cout << longPath << " -> " << catcher.result().first << endl;
    }

    return 0;
}

