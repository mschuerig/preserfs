
#include "DirectoryMetadata.h"
#include <iostream>

using namespace std;

int
main(
    int argc,
    char* argv[]
) {
//    DirectoryMetadata::Ptr md = DirectoryMetadata::fromFilesystem(".");
    DirectoryMetadata::Ptr md = DirectoryMetadata::fromMetadataFile(".", argc > 1 ? argv[1] : 0);

//    for (DirectoryMetadata::EntryIter it = md->cbegin(); it != md->cend(); ++it) {
//        cout << it->shortName << "\t" << it->longName << "\t" << it->uid << "\t" << oct << it->mode << dec << endl;
//    }
    
    md->write();

    return 0;
}
