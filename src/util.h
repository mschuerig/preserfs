
#ifndef UTIL_H_INCLUDED_
#define UTIL_H_INCLUDED_

#include <cerrno>
#include <map>
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

template<typename T, typename R>
std::map<R, typename T::value_type>
index_by(const T& t, R T::value_type::*ptr_to_mem)
{
    std::map<R, typename T::value_type> idx;
    for ( typename T::const_iterator i = t.begin(), end = t.end();
          i != end;
          ++i ) {
        idx[((*i).*ptr_to_mem)] = *i;
    }
    return  idx;
}

} // namespace util

#endif // UTIL_H_INCLUDED_
