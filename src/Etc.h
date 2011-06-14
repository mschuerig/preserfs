
#ifndef ETC_H_INCLUDED
#define ETC_H_INCLUDED

#include <sys/types.h>
#include <string>
#include <exception>
#include <boost/exception/all.hpp>
#include <boost/noncopyable.hpp>

struct EtcError : virtual std::exception, virtual boost::exception { };

class Etc : public boost::noncopyable {
public:
    const std::string lookupUsername(uid_t uid) const;
    const std::string lookupGroupname(gid_t uid) const;
    
    uid_t lookupUserId(const std::string& user) const;
    gid_t lookupGroupId(const std::string& group) const;
};

#endif // ETC_H_INCLUDED
