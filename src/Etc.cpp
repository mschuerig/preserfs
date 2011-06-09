
#include "Etc.h"

#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <cerrno>
#include <boost/shared_ptr.hpp>
#include "exception.h"

using namespace std;
namespace sys = boost::system;
namespace ex = exception;

namespace {

template<typename S>
struct struct_bufsize {};

template<>
struct struct_bufsize<struct passwd> {
    const static int sysconf_name = _SC_GETPW_R_SIZE_MAX;
};

template<>
struct struct_bufsize<struct group> {
    const static int sysconf_name = _SC_GETGR_R_SIZE_MAX;
};


template<typename S>
struct struct_storage {
    typedef struct_storage<S> type;

    S       s;
    size_t  datasize;
    char    data[1];

    static type* alloc() {
        int datasize = sysconf(struct_bufsize<S>::sysconf_name);
        if ( datasize == -1 ) {     // Value was indeterminate
            datasize = 16384;       // Should be more than enough
        }

        void* addr = ::operator new(sizeof(type) + datasize - 1);
        type* r = new (addr) struct_storage;
        r->datasize = datasize;
        return r;
    }
};

template <typename S, typename A>
struct etc_traits {
  typedef A arg_t;
  typedef S struct_t;
  typedef int (*func)(arg_t, struct_t*, char*, size_t, struct_t**);
  typedef boost::shared_ptr<struct_t> ptr;
  typedef struct_storage<struct_t> storage_t;
  typedef boost::shared_ptr<storage_t> storage_ptr;
};

template<typename E>
typename E::ptr
safe_etc(typename E::func func, const typename E::arg_t arg) {
    typename E::storage_ptr storage( E::storage_t::alloc() );
    typename E::ptr result( storage, &storage->s );

    typename E::struct_t* sentinel;
    int err = func(arg, &storage->s, storage->data, storage->datasize, &sentinel);
    if ( err != 0 || sentinel == NULL ) {
        exception::throw_errno(err || ENOENT);
    }

    return result;
}


} // anonymous namespace


const string
Etc::lookupUsername(uid_t uid) const {
    typedef etc_traits<struct passwd, uid_t> passwd_from_uid;
    const passwd_from_uid::ptr pwd( safe_etc<passwd_from_uid>(&getpwuid_r, uid) );
    return string(pwd->pw_name);
}

const string
Etc::lookupGroupname(gid_t gid) const {
    typedef etc_traits<struct group, gid_t> group_from_gid;
    const group_from_gid::ptr gr( safe_etc<group_from_gid>(&getgrgid_r, gid) );
    return string(gr->gr_name);
}

uid_t
Etc::lookupUserId(const string& user) const {
    typedef etc_traits<struct passwd, const char*> passwd_from_name;
    const passwd_from_name::ptr pwd( safe_etc<passwd_from_name>(&getpwnam_r, user.c_str()) );
    return pwd->pw_uid;
}

gid_t
Etc::lookupGroupId(const string& group) const {
    typedef etc_traits<struct group, const char*> group_from_name;
    const group_from_name::ptr gr( safe_etc<group_from_name>(&getgrnam_r, group.c_str()) );
    return gr->gr_gid;
}
