
#include "DirectoryMetadata.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <memory>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include "Etc.h"
#include "util.h"

using namespace std;
namespace fs = boost::filesystem;
namespace ser = boost::serialization;
namespace sys = boost::system;

const string DirectoryMetadata::metadataFilename = ".preserfs";

DirectoryMetadata::Ptr
DirectoryMetadata::fromFilesystem(
    const string& directoryPath
) {
    fs::path path(directoryPath);
    Ptr dm(new DirectoryMetadata);
    
    for ( fs::directory_iterator it(path); it != fs::directory_iterator(); ++it ) {
        const string name = it->path().filename().string();

        struct stat st;
        if ( lstat(name.c_str(), &st) < 0 ) {
            util::throw_errno("lstat", it->path());
        }
        
        Entry entry = {
            longName    : name,
            shortName   : name,
            uid         : st.st_uid,
            gid         : st.st_gid,
            mode        : st.st_mode,
            mtime       : st.st_mtime
        };

        dm->entries_.push_back(entry);
    }

    return dm;
}

DirectoryMetadata::Ptr
DirectoryMetadata::fromMetadataFile(
    const string& directoryPath,
    const string& filename
) {
    fs::path path(directoryPath);
    path /= filename;
    Ptr dm(new DirectoryMetadata);
    
    ifstream ifs(path.string().c_str());

    boost::archive::xml_iarchive ia(ifs);
    ia >> ser::make_nvp("entries", dm->entries_);

    return dm;
}


DirectoryMetadata::DirectoryMetadata()
{
}


void
DirectoryMetadata::write() const
{
    boost::archive::xml_oarchive oa(cout);
    oa << ser::make_nvp("entries", entries_);
}


namespace boost {
namespace serialization {

template<class Archive>
inline void serialize(
    Archive& ar,
    DirectoryMetadata::Entry& e,
    const unsigned int file_version
) {
    boost::serialization::split_free(ar, e, file_version);
}

template<class Archive>
void save(
    Archive& ar,
    const DirectoryMetadata::Entry& e,
    const unsigned int /*version*/
) {
    Etc etc;
    ar & ser::make_nvp("longname",  e.longName);
    ar & ser::make_nvp("shortname", e.shortName);
    ar & ser::make_nvp("owner",     etc.lookupUsername(e.uid));
    ar & ser::make_nvp("group",     etc.lookupGroupname(e.gid));
    ar & ser::make_nvp("mode",      e.mode);
    ar & ser::make_nvp("mtime",     e.mtime);
}

template<class Archive>
void load(
    Archive& ar,
    DirectoryMetadata::Entry& e,
    const unsigned int /*version*/
) {
    Etc etc;
    ar & ser::make_nvp("longname",  e.longName);
    ar & ser::make_nvp("shortname", e.shortName);

    string owner;
    ar & ser::make_nvp("owner",     owner);
    e.uid = etc.lookupUserId(owner);

    string group;
    ar & ser::make_nvp("group",     group);
    e.gid = etc.lookupGroupId(group);

    ar & ser::make_nvp("mode",      e.mode);
    ar & ser::make_nvp("mtime",     e.mtime);
}

} // namespace serialization
} // namespace boost
