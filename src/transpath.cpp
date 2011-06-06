
#include "DirectoryMetadata.h"
#include "TruncatingShortener.h"
#include "util.h"
#include <map>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;
namespace fs = boost::filesystem;
#define foreach BOOST_FOREACH

typedef map<string, DirectoryMetadata::Entry> EntryMap;

string
translate( const string& longPath, NameShortener& shortener) {
    const fs::path path(longPath);

    fs::path prefixPath;

    if ( path.is_absolute() ) {
	prefixPath = "/";
    } else {
	prefixPath = ".";
    }

    fs::path resultPath;
    DirectoryMetadata::Ptr dm;

    foreach( fs::path part, path ) {
	if ( fs::is_directory(prefixPath) ) {
	    shortener.reset();
	    dm = DirectoryMetadata::fromFilesystem(prefixPath.string(), shortener);
	} else {
	    throw "Not a directory"; // ### FIXME
	}

	EntryMap entryMap = util::index_by(*dm, &DirectoryMetadata::Entry::longName);

	EntryMap::const_iterator ep( entryMap.find(part.string()) );
	if ( ep != entryMap.end() ) {
	    resultPath /= ep->second.shortName;
	} else {
	    throw "No such file or directory."; // ### FIXME
	}

	prefixPath /= part;
    }
    return resultPath.string();
}


int
main( int argc, char* argv[] )
{
    TruncatingShortener shortener(5);
    
    for ( int i = 1; i < argc; ++i ) {
	const string longPath(argv[i]);
	const string shortPath = translate(longPath, shortener);
	cout << longPath << " -> " << shortPath << endl;
    }

    return 0;
}
 
