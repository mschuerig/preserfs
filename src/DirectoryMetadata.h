
#ifndef DIRECTORY_METADATA_H_INCLUDED_
#define DIRECTORY_METADATA_H_INCLUDED_

#include <ostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class Etc;

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
    typedef std::vector<Entry>::const_iterator EntryIter;

    
    static const std::string metadataFilename;
    
    static Ptr fromFilesystem(
        const std::string& directoryPath,
        const EtcPtr etc
    );

    static Ptr fromFilesystem(
        const std::string& directoryPath
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

    EntryIter cbegin() const {
        return entries_.begin();
    }

    EntryIter cend() const {
        return entries_.end();
    }
    
private:
    DirectoryMetadata(const boost::shared_ptr<Etc> etc);

    std::vector<Entry> entries_;
    const boost::shared_ptr<Etc> etc_;
};

#endif // DIRECTORY_METADATA_H_INCLUDED_
