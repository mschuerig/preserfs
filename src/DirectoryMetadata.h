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

#ifndef DIRECTORYMETADATA_H
#define DIRECTORYMETADATA_H

#include "NameShortener.h"

#include <ostream>
#include <string>
#include <vector>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class Etc;

struct MetadataError : virtual std::exception, virtual boost::exception { };

class DirectoryMetadata : public boost::noncopyable {
public:
    typedef boost::shared_ptr<DirectoryMetadata> Ptr;
    typedef boost::shared_ptr<Etc> EtcPtr;

    struct Entry {
        std::string longName;
        std::string shortName;
        uid_t       uid;
        gid_t       gid;
        mode_t      mode;
        time_t      mtime;
    };
    typedef Entry value_type;
    typedef std::vector<Entry>::const_iterator const_iterator; // TODO use a dequeue?

    static const std::string metadataFilename;

    static Ptr fromFilesystem(
        const std::string& directoryPath,
        NameShortener& shortener,
        const EtcPtr etc
    );

    static Ptr fromFilesystem(
        const std::string& directoryPath,
        NameShortener& shortener
    );

    static Ptr fromMetadataFile(
        const std::string& directoryPath,
        const EtcPtr etc,
        const std::string& filename
    );
    static Ptr fromMetadataFile(
        const std::string& directoryPath
    );
    static Ptr fromMetadataFile(
        const std::string& directoryPath,
        const std::string& filename
    );
    
    void write() const;
    void write(std::ostream& os) const;

    const_iterator begin() const {
        return entries_.begin();
    }

    const_iterator end() const {
        return entries_.end();
    }
    
private:
    DirectoryMetadata(const EtcPtr etc);
    friend Ptr boost::make_shared<DirectoryMetadata, EtcPtr>(const EtcPtr&);

    std::vector<Entry> entries_;
    const boost::shared_ptr<Etc> etc_;
};

#endif // DIRECTORYMETADATA_H
