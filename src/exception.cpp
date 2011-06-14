
#include "exception.h"
#include <cstring>
#include <iostream>

namespace exception {

int
CatchAllBase::reportError(const boost::exception& ex) {
    std::cerr << boost::diagnostic_information(ex) << std::endl;

    if ( int const* err = boost::get_error_info<boost::errinfo_errno>(ex) ) {
        return *err;
    }
    return -1;
}

int
CatchAllBase::reportError(const boost::system::system_error& ex) {
    const boost::system::error_code err = ex.code();
    std::cerr << ex.what() << std::endl;
    return err.value();
}

} // namespace exception
