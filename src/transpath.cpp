
#include "DirectoryMetadata.h"
#include "TruncatingShortener.h"
#include "algorithm.h"
#include "exception.h"
#include <map>
#include <utility>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;
namespace fs = boost::filesystem;
using namespace exception;
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
	    throw_errno("Not a directory", prefixPath, ENOTDIR);
	}

	EntryMap entryMap = algorithm::index_by(*dm, &DirectoryMetadata::Entry::longName);

	EntryMap::const_iterator ep( entryMap.find(part.string()) );
	if ( ep != entryMap.end() ) {
	    resultPath /= ep->second.shortName;
	} else {
	    throw_errno("No such file or directory", part, ENOENT);
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
	
	CatchAll<string, const string&, NameShortener&> catcher(
	    &translate, longPath, shortener);
	if ( int err = catcher.call() ) {
	    return err;
	}

	cout << longPath << " -> " << catcher.result() << endl;
    }

    return 0;
}
 
