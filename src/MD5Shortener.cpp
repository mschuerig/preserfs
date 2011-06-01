
#include "MD5Shortener.h"

#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

using namespace std;

string
MD5Shortener::operator()(const std::string& longName) {
    unsigned char* hash = MD5(reinterpret_cast<const unsigned char*>(longName.c_str()),
                              longName.size(), NULL);
    
    string shortName(2 * MD5_DIGEST_LENGTH, 'x');

    string::iterator k = shortName.begin();
    for ( int i = 0; i < MD5_DIGEST_LENGTH; ++i ) {
        *k++ = "0123456789abcdef"[hash[i] >> 4];
        *k++ = "0123456789abcdef"[hash[i] &  0x0f];
    }
    
    return shortName;
}
