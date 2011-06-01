
#ifndef IDENTITY_SHORTENER_H_INCLUDED_
#define IDENTITY_SHORTENER_H_INCLUDED_

#include "NameShortener.h"

class IdentityShortener : public NameShortener
{
public:
    virtual std::string operator()(const std::string& longName) {
        return longName;
    }
};
 
#endif // IDENTITY_SHORTENER_H_INCLUDED_
