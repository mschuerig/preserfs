
#ifndef DIRECTORY_METADATA_H_INCLUDED_
#define DIRECTORY_METADATA_H_INCLUDED_

#include "NameShortener.h"

#include <ostream>
#include <string>
#include <vector>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class Etc;

class DirectoryMetadata : public boost::noncopyable {
    // TODO What traits does this class have to expose
    // so that it works, e.g., with BOOST_FOREACH?
    
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
    typedef std::vector<Entry>::const_iterator const_iterator;
   
    static const std::string metadataFilename;
    
    DirectoryMetadata(const EtcPtr etc);
        // The ctor ought to be private, but that won't work with make_shared

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
    std::vector<Entry> entries_;
    const boost::shared_ptr<Etc> etc_;
};

#endif // DIRECTORY_METADATA_H_INCLUDED_
