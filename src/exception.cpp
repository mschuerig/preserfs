
#include "exception.h"
#include <cstring>
#include <iostream>

namespace exception {

int
CatchAllBase::reportError(const boost::system::system_error& ex) {
    const boost::system::error_code err = ex.code();
    std::cerr << ex.what() << std::endl;
    return err.value();
}

} // namespace exception
