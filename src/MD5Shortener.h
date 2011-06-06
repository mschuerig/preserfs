
#ifndef MD5_SHORTENER_INCLUDED_H_
#define MD5_SHORTENER_INCLUDED_H_

#include "NameShortener.h"
#include <string>

class MD5Shortener : public NameShortener {
private:
    virtual std::string shorten(const std::string& longName);
};

#endif // MD5_SHORTENER_INCLUDED_H_
 
