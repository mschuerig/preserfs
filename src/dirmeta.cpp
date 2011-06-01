
#include <iostream>
#include "DirectoryMetadata.h"
#include "MD5Shortener.h"

using namespace std;

int
main( int argc, char* argv[] ) {
    DirectoryMetadata::Ptr md;

    if ( argc > 1 && (string(argv[1]) == string("-f")) ) {
        md = argc > 2 ?
            DirectoryMetadata::fromMetadataFile(".", argv[2]) :
            DirectoryMetadata::fromMetadataFile(".");
    } else {
        MD5Shortener shortener;
        md = DirectoryMetadata::fromFilesystem(".", shortener);
    }

    md->write(cout);

    return 0;
}
