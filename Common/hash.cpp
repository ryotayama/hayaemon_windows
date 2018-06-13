
#include <string.h>

#include "oauth.h" // base64 encode fn's.
#include "sha1.h"

void hmac_sha1(unsigned char const *key, size_t keylen, unsigned char const *in, size_t inlen, unsigned char *resbuf)
{
	struct SHA1Context inner;
	struct SHA1Context outer;
	unsigned char tmpkey[20];
	unsigned char digest[20];
	unsigned char block[64];

	const int IPAD = 0x36;
	const int OPAD = 0x5c;

	if (keylen > 64) {
		struct SHA1Context keyhash;
		SHA1Reset(&keyhash);
		SHA1Input(&keyhash, key, keylen);
		SHA1Result(&keyhash, tmpkey);
		key = tmpkey;
		keylen = 20;
	}

	for (size_t i = 0; i < sizeof(block); i++) {
		block[i] = IPAD ^ (i < keylen ? key[i] : 0);
	}
	SHA1Reset(&inner);
	SHA1Input(&inner, block, 64);
	SHA1Input(&inner, in, inlen);
	SHA1Result(&inner, digest);

	for (size_t i = 0; i < sizeof(block); i++) {
		block[i] = OPAD ^ (i < keylen ? key[i] : 0);
	}
	SHA1Reset(&outer);
	SHA1Input(&outer, block, 64);
	SHA1Input(&outer, digest, 20);
	SHA1Result(&outer, resbuf);
}


std::string oauth_sign_hmac_sha1(const char *m, const char *k)
{
	return oauth_sign_hmac_sha1_raw(m, strlen(m), k, strlen(k));
}

std::string oauth_sign_hmac_sha1_raw(const char *m, const size_t ml, const char *k, const size_t kl)
{
	unsigned char result[20];
	hmac_sha1((unsigned char const *)k, kl, (unsigned char const *)m, ml, result);
	return oauth_encode_base64(result, 20);
}

