
#include "MD5Shortener.h"

#include <openssl/md5.h>
#include <string>
#include <vector>

using namespace std;

string
MD5Shortener::shorten(const std::string& longName) {
    vector<unsigned char> hash(MD5_DIGEST_LENGTH);

    MD5(reinterpret_cast<const unsigned char*>(longName.c_str()),
	longName.size(),
	&hash[0]);

    string shortName(2 * MD5_DIGEST_LENGTH, 'x');

    string::iterator k = shortName.begin();
    for ( int i = 0; i < MD5_DIGEST_LENGTH; ++i ) {
        *k++ = "0123456789abcdef"[hash[i] >> 4];
        *k++ = "0123456789abcdef"[hash[i] &  0x0f];
    }

    return shortName;
}
