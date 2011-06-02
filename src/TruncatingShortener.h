
#ifndef TRUNCATING_SHORTENER_INCLUDED_H_
#define TRUNCATING_SHORTENER_INCLUDED_H_

#include "NameShortener.h"
#include <set>
#include <string>

class TruncatingShortener : public NameShortener {
public:
    TruncatingShortener( size_t maxNameLength );
    virtual std::string operator()(const std::string& longName);

private:
    std::set<std::string> shortNames_;
    const size_t maxNameLength_;
};

#endif // TRUNCATING_SHORTENER_INCLUDED_H_

 
