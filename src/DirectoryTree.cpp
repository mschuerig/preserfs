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
#include "DirectoryTree.h"

using namespace std;
namespace fs = boost::filesystem;
#define foreach BOOST_FOREACH

typedef map<string, DirectoryEntry> EntryMap;

struct DirectoryTree::Gardener {
    virtual void growAt(DirectoryTree::Node& node, const fs::path& path) = 0;
};


namespace {

void
addChildrenToNode(
    const DirectoryMetadata::Ptr dm,
    DirectoryTree::Node& node,
    std::string DirectoryEntry::*indexName
) {
    for ( DirectoryMetadata::const_iterator iter = dm->begin(), end = dm->end();  iter != end; ++iter ) {
        DirectoryTree::Node child = { entry: *iter, children: DirectoryTree::Node::Children() };
        node.children[(*iter).*indexName] = child;
    }
}


class FilesystemGardner : public DirectoryTree::Gardener {
public:
    FilesystemGardner( DirectoryTree::NameShortenerPtr shortener )
        : shortener_(shortener) {}

    virtual void growAt( DirectoryTree::Node& node, const fs::path& path ) {
        if ( !node.children.empty() ) {
            return;
        }
        if ( fs::is_directory(path) ) {
            shortener_->reset();
            addChildrenToNode(
                DirectoryMetadata::fromFilesystem(path.string(), *shortener_),
                node,
                &DirectoryEntry::longName
            );
        } else {
            BOOST_THROW_EXCEPTION(
                PathTranslationError()
                << boost::errinfo_file_name(path.string())
                << boost::errinfo_errno(ENOTDIR)
            );
        }
    }

private:
    const DirectoryTree::NameShortenerPtr shortener_;
};

class MetadataGardner : public DirectoryTree::Gardener {

};

} // anonymous namespace



DirectoryTree::DirectoryTree(const string& rootPath, Gardener* gardener)
    : rootPath_(rootPath), gardener_(gardener) {
}

DirectoryTree::Ptr
DirectoryTree::fromFilesystem(
    const string& rootPath,
    DirectoryTree::NameShortenerPtr shortener
) {
    Gardener* gardener = new FilesystemGardner(shortener);
    return DirectoryTree::Ptr(new DirectoryTree(rootPath, gardener));
}


// DirectoryTree::Ptr
// DirectoryTree::fromMetadataFiles(
//     const string& rootPath,
//     const string& filename
// ) {
//
// }


DirectoryTree::lookupResult
DirectoryTree::lookup(
    const string& longPath,
    std::string DirectoryEntry::*resultName
) const {
    const fs::path path(longPath);

    fs::path prefixPath;

    //### FIXME absolute paths only, but interpreted relative to rootPath_
    if ( path.is_absolute() ) {
        prefixPath = "/";
    } else {
        prefixPath = ".";
    }

    fs::path resultPath;
    Node& node = root_;
    Node::Children::const_iterator found;

    foreach( const fs::path& pathElement, path ) {
        gardener_->growAt( node, prefixPath );

        found = node.children.find(pathElement.string());
        if ( found != node.children.end() ) {
            node = found->second;
            resultPath /= node.entry.*resultName;
        } else {
            BOOST_THROW_EXCEPTION(
                PathTranslationError()
                << boost::errinfo_file_name( pathElement.string() )
                << boost::errinfo_errno(ENOENT)
            );
        }

        prefixPath /= pathElement;
    }

    return make_pair(resultPath.string(), found->second.entry);
}
