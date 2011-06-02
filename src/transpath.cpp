
#include "DirectoryMetadata.h"
#include "TruncatingShortener.h"
#include <map>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;
namespace fs = boost::filesystem;
#define foreach BOOST_FOREACH

int
main( int argc, char* argv[] )
{
    if ( argc < 2 ) {
        cerr << "Usage: transpath path" << endl;
        return -1;
    }
    
    const fs::path path(argv[1]);
    boost::scoped_ptr<NameShortener> shortener( new TruncatingShortener(5) );
    DirectoryMetadata::Ptr dm;


    fs::path prefixPath;
    
    if ( path.is_absolute() ) {
        prefixPath = "/";
    } else {
        prefixPath = ".";
    }

    fs::path resultPath;
    dm = DirectoryMetadata::fromFilesystem(prefixPath.string(), *shortener);

    foreach( fs::path part, path ) {
        map<string, DirectoryMetadata::Entry> entryMap;

        // TODO use copy algo
        foreach( const DirectoryMetadata::Entry& e, make_pair(dm->cbegin(), dm->cend()) ) {
           entryMap[e.longName] = e;
        }

        resultPath /= entryMap[part.string()].shortName;
        
        prefixPath /= part;
        if ( fs::is_directory(prefixPath) ) {
            shortener.reset( new TruncatingShortener(5) );
            dm = DirectoryMetadata::fromFilesystem(prefixPath.string(), *shortener);
        } else {
            break;
        }
    }

    cout << path << " -> " << resultPath << endl;
    
    return 0;
}
 
