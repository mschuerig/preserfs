
#ifndef NAME_SHORTENER_INCLUDED_H_
#define NAME_SHORTENER_INCLUDED_H_

#include <string>

struct NameShortener {
    virtual std::string operator()(const std::string& longName) = 0;
    virtual ~NameShortener() {};
};

#endif // NAME_SHORTENER_INCLUDED_H_
