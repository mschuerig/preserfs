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
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/throw_exception.hpp>
#include "algorithm.h"
#include "DirectoryTree.h"

using namespace std;
namespace fs = boost::filesystem;
#define foreach BOOST_FOREACH

typedef map<string, DirectoryMetadata::Entry> EntryMap;


DirectoryTree::DirectoryTree(const string& rootPath)
    : rootPath_(rootPath) {
}

DirectoryTree::DirectoryTree(
    const string& rootPath,
    DirectoryTree::NameShortenerPtr shortener
) : rootPath_(rootPath), shortener_(shortener) {
}


DirectoryTree::Ptr
DirectoryTree::fromFilesystem(
    const string& rootPath,
    DirectoryTree::NameShortenerPtr shortener
) {
    return boost::make_shared<DirectoryTree>(rootPath, shortener);
}


// DirectoryTree::Ptr
// DirectoryTree::fromMetadataFiles(
//     const string& rootPath,
//     const string& filename
// ) {
// 
// }


DirectoryTree::lookupResult
DirectoryTree::lookup( const string& longPath ) const {
    const fs::path path(longPath);

    fs::path prefixPath;

    if ( path.is_absolute() ) {
        prefixPath = "/";
    } else {
        prefixPath = ".";
    }

    fs::path resultPath;
    DirectoryMetadata::Ptr dm;
    EntryMap::const_iterator ep;

    foreach( fs::path part, path ) {
        if ( fs::is_directory(prefixPath) ) {
            shortener_->reset();
            dm = DirectoryMetadata::fromFilesystem(prefixPath.string(), *shortener_);
        } else {
            BOOST_THROW_EXCEPTION(
                PathTranslationError()
                << boost::errinfo_file_name(prefixPath.string())
                << boost::errinfo_errno(ENOTDIR)
            );
        }

        EntryMap entryMap = algorithm::index_by(*dm, &DirectoryMetadata::Entry::longName);

        ep = entryMap.find(part.string());
        if ( ep != entryMap.end() ) {
            resultPath /= ep->second.shortName;
        } else {
            BOOST_THROW_EXCEPTION(
                PathTranslationError()
                << boost::errinfo_file_name(part.string())
                << boost::errinfo_errno(ENOENT)
            );
        }

        prefixPath /= part;
    }
    return make_pair(resultPath.string(), ep->second);
}
