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

#ifndef DIRECTORYTREE_H
#define DIRECTORYTREE_H

#include <string>
#include <utility>
#include <vector>
#include <boost/exception/all.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "DirectoryMetadata.h"
#include "NameShortener.h"

struct PathTranslationError : virtual std::exception, virtual boost::exception { };

class DirectoryTree : public boost::noncopyable {
public:
    typedef boost::shared_ptr<DirectoryTree> Ptr;
    typedef boost::shared_ptr<NameShortener> NameShortenerPtr;
    typedef std::pair<std::string, DirectoryMetadata::Entry> lookupResult;

    class Node {
    };
    typedef boost::shared_ptr<Node> NodePtr;

    static Ptr fromFilesystem(
        const std::string& rootPath,
        NameShortenerPtr shortener
    );

    static Ptr fromMetadataFiles(
        const std::string& rootPath,
        const std::string& filename
    );

    lookupResult lookup(const std::string& path) const;

private:
    DirectoryTree(const std::string& rootPath);
    DirectoryTree(const std::string& rootPath, NameShortenerPtr shortener);
    friend Ptr boost::make_shared<DirectoryTree, std::string>(const std::string&);
    friend Ptr boost::make_shared<DirectoryTree, std::string, NameShortenerPtr>(const std::string&, const NameShortenerPtr&);

    std::string rootPath_;
    mutable NameShortenerPtr shortener_;
    mutable NodePtr root_;
};

#endif // DIRECTORYTREE_H
