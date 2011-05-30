
#include "DirectoryMetadata.h"
#include <iostream>

using namespace std;

int
main(
    int argc,
    char* argv[]
) {
//    DirectoryMetadata::Ptr md = DirectoryMetadata::fromFilesystem(".");
    DirectoryMetadata::Ptr md = argc > 1 ?
        DirectoryMetadata::fromMetadataFile(".", argv[1]) :
        DirectoryMetadata::fromMetadataFile(".");

//    for (DirectoryMetadata::EntryIter it = md->cbegin(); it != md->cend(); ++it) {
//        cout << it->shortName << "\t" << it->longName << "\t" << it->uid << "\t" << oct << it->mode << dec << endl;
//    }
    
    md->write(cout);

    return 0;
}
