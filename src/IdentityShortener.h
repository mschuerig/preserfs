
#ifndef IDENTITY_SHORTENER_H_INCLUDED_
#define IDENTITY_SHORTENER_H_INCLUDED_

#include "NameShortener.h"
#include <string>

class IdentityShortener : public NameShortener
{
private:
    virtual std::string shorten(const std::string& longName) {
        return longName;
    }
};
 
#endif // IDENTITY_SHORTENER_H_INCLUDED_
