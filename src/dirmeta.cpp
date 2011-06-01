
#include "DirectoryMetadata.h"
#include <exception>
#include <iostream>

using namespace std;
using namespace boost;

class IdentityShortener : public DirectoryMetadata::NameShortener
{
public:
    virtual string operator()(const string& longName) {
        return std::string(longName, 0, 50);
    }
};

int
main(
    int argc,
    char* argv[]
) {
    DirectoryMetadata::Ptr md;

    if ( argc > 1 && (string(argv[1]) == string("-f")) ) {
        md = argc > 2 ?
            DirectoryMetadata::fromMetadataFile(".", argv[2]) :
            DirectoryMetadata::fromMetadataFile(".");
    } else {
        IdentityShortener shortener;
        md = DirectoryMetadata::fromFilesystem(".", shortener);
    }

    md->write(cout);

    return 0;
}
