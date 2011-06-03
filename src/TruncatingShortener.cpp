
#include "TruncatingShortener.h"
#include <cassert>
#include <boost/lexical_cast.hpp>

using namespace std;

TruncatingShortener::TruncatingShortener(size_t maxNameLength)
    : maxNameLength_(maxNameLength)
{
    // TODO ensure minimum length
}


string
TruncatingShortener::operator()(const std::string& longName) {
    if ( longName.size() < maxNameLength_ ) {
        shortNames_.insert(longName);
        return longName;
    }

    string prefix(longName.substr(0, maxNameLength_ - 1));
    string shortName;
    
    for ( int i = 1; ; ++i ) {
        const string counter(boost::lexical_cast<string>(i));
        assert( counter.size() <= maxNameLength_ ); // TODO throw something sensible
        prefix.resize(maxNameLength_ - counter.size());
        shortName = prefix + counter;

        if ( shortNames_.insert(shortName).second ) {
            return shortName;
        }
    }
    
    assert( !"Error in TruncatingShortener" );
}
 
