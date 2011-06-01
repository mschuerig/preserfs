
#ifndef MD5_SHORTENER_INCLUDED_H_
#define MD5_SHORTENER_INCLUDED_H_

#include "NameShortener.h"
#include <string>

struct MD5Shortener : public NameShortener {
    virtual std::string operator()(const std::string& longName);
};

#endif // MD5_SHORTENER_INCLUDED_H_
 
