
#ifndef DIRECTORY_METADATA_H_INCLUDED_
#define DIRECTORY_METADATA_H_INCLUDED_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class DirectoryMetadata : public boost::noncopyable {
public:
    typedef boost::shared_ptr<DirectoryMetadata> Ptr;

    struct Entry {
        std::string longName;
        std::string shortName;
        uid_t       uid;
        gid_t       gid;
        mode_t      mode;
        time_t      mtime;
    };
    typedef std::vector<Entry>::const_iterator EntryIter;
    
    static const std::string metadataFilename;
    
    static Ptr fromFilesystem( const std::string& directoryPath );

    static Ptr fromMetadataFile(
        const std::string& directoryPath,
        const std::string& filename
    );
    
    static Ptr fromMetadataFile(
        const std::string& directoryPath,
        const char* filename = 0
    ) {
        return fromMetadataFile(
            directoryPath,
            filename ? std::string(filename) : metadataFilename
        );
    }

    void write() const;

    EntryIter cbegin() const {
        return entries_.begin();
    }

    EntryIter cend() const {
        return entries_.end();
    }
    
private:
    DirectoryMetadata();

    std::vector<Entry> entries_;
};

#endif // DIRECTORY_METADATA_H_INCLUDED_
