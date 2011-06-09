
#ifndef EXCEPTION_H_INCLUDED_
#define EXCEPTION_H_INCLUDED_

#include <cerrno>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/noncopyable.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

namespace exception
{

void inline
throw_errno(const boost::filesystem::path& path, int err = errno) {
    throw boost::filesystem::filesystem_error(
        "", path,
        boost::system::error_code(err, boost::system::system_category())
    );
}

void inline
throw_errno(const std::string& msg, const boost::filesystem::path& path, int err = errno) {
    throw boost::filesystem::filesystem_error(
        msg, path,
        boost::system::error_code(err, boost::system::system_category())
    );
}

void inline
throw_errno(int err = errno) {
    throw boost::system::system_error(
        boost::system::error_code(err, boost::system::system_category())
    );
}

void inline
throw_errno(const std::string& msg, int err = errno) {
    throw boost::system::system_error(
        boost::system::error_code(err, boost::system::system_category()),
	msg
    );
}

class CatchAllBase : public boost::noncopyable {
protected:
    static int reportError(const boost::system::system_error& ex);
};

template<typename R, typename A1, typename A2>
class CatchAll : protected CatchAllBase {
public:
    typedef R (*func_t)(A1, A2);

    CatchAll(func_t fn, A1 a1, A2 a2)
	: fn_(fn), a1_(a1), a2_(a2) {}

    int call() {
	try {
	    r_ = fn_(a1_, a2_);
	} catch(const boost::system::system_error& ex) {
	    return reportError(ex);
	}
	return 0;
    }

    R result() {
	return r_;
    }

private:
    func_t fn_;
    R r_;
    A1 a1_;
    A2 a2_;
};

} // namespace exception

#endif // EXCEPTION_H_INCLUDED_
