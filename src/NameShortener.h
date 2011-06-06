
#ifndef NAME_SHORTENER_INCLUDED_H_
#define NAME_SHORTENER_INCLUDED_H_

#include <string>

class NameShortener {
public:
    std::string operator()(const std::string& longName) {
	return shorten(longName);
    }

    void reset() {
	doReset();
    }

    virtual ~NameShortener() {};

private:
    virtual std::string shorten(const std::string& longName) = 0;

    virtual void doReset() {}
};

#endif // NAME_SHORTENER_INCLUDED_H_
