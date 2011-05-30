
#ifndef UTIL_H_INCLUDED_
#define UTIL_H_INCLUDED_

#include <errno.h>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

namespace util
{

void inline
throw_errno(const std::string& msg, const boost::filesystem::path& path, int err = errno) {
    throw boost::filesystem::filesystem_error(
        msg, path,
        boost::system::error_code(err, boost::system::system_category())
    );
}

void inline
throw_errno(const std::string& msg, int err = errno) {
    throw boost::filesystem::filesystem_error(
        msg, boost::system::error_code(err, boost::system::system_category())
    );
}


} // namespace util

#endif // UTIL_H_INCLUDED_
