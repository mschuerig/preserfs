
#include "Etc.h"

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <boost/system/system_error.hpp>
#include "exception.h"

using namespace std;
namespace sys = boost::system;
namespace ex = exception;

const string
Etc::lookupUsername(uid_t uid) const
{
    errno = 0;
    struct passwd* pwd = getpwuid(uid);
    if (!pwd && errno) {
        ex::throw_errno("getpwuid");
    }
    return string(pwd->pw_name);
}

const string
Etc::lookupGroupname(gid_t gid) const {
    errno = 0;
    struct group* gr = getgrgid(gid);
    if (!gr && errno) {
        ex::throw_errno("getgrgid");
    }
    return string(gr->gr_name);
}

uid_t
Etc::lookupUserId(const string& user) const {
    errno = 0;
    struct passwd* pwd = getpwnam(user.c_str());
    if (!pwd && errno) {
        ex::throw_errno("getpwnam");
    }
    return pwd->pw_uid;
}

gid_t
Etc::lookupGroupId(const string& group) const {
    errno = 0;
    struct group* gr = getgrnam(group.c_str());
    if (!gr && errno) {
        ex::throw_errno("getgrnam");
    }
    return gr->gr_gid;
}
