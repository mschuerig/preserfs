
#ifndef TRUNCATING_SHORTENER_INCLUDED_H_
#define TRUNCATING_SHORTENER_INCLUDED_H_

#include "NameShortener.h"
#include <set>
#include <string>

class TruncatingShortener : public NameShortener {
public:
    TruncatingShortener( size_t maxNameLength );

private:
    std::set<std::string> shortNames_;
    const size_t maxNameLength_;

    virtual std::string shorten(const std::string& longName);
    virtual void reset();
};

#endif // TRUNCATING_SHORTENER_INCLUDED_H_

 
