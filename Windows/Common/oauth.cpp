/*
 * OAuth string functions in POSIX-C.
 *
 * Copyright 2007-2010 Robin Gareus <robin@gareus.org>
 * 
 * The base64 functions are by Jan-Henrik Haukeland, <hauk@tildeslash.com>
 * and un/escape_url() was inspired by libcurl's curl_escape under ISC-license
 * many thanks to Daniel Stenberg <daniel@haxx.se>.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 */
#if HAVE_CONFIG_H
# include <config.h>
#endif

#define WIPE_MEMORY ///< overwrite sensitve data before free()ing it.

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h> // isxdigit

#include "oauth.h"

#ifndef WIN32 // getpid() on POSIX systems
#include <sys/types.h>
#include <unistd.h>
#else
#define snprintf _snprintf
#define strncasecmp strnicmp
#pragma warning(disable:4996)
#endif

#include <vector>
#include <algorithm>
#include <sstream>

/**
 * Base64 encode one byte
 */
char oauth_b64_encode(unsigned char u)
{
	if (u < 26)  return 'A' + u;
	if (u < 52)  return 'a' + (u - 26);
	if (u < 62)  return '0' + (u - 52);
	if (u == 62) return '+';
	return '/';
}

/**
 * Decode a single base64 character.
 */
unsigned char oauth_b64_decode(char c)
{
	if (c >= 'A' && c <= 'Z') return(c - 'A');
	if (c >= 'a' && c <= 'z') return(c - 'a' + 26);
	if (c >= '0' && c <= '9') return(c - '0' + 52);
	if (c == '+')             return 62;
	return 63;
}

/**
 * Return TRUE if 'c' is a valid base64 character, otherwise FALSE
 */
bool oauth_b64_is_base64(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '+') || (c == '/') || (c == '='));
}

/**
 * Base64 encode and return size data in 'src'. The caller must free the
 * returned string.
 *
 * @param size The size of the data in src
 * @param src The data to be base64 encode
 * @return encoded string otherwise NULL
 */
std::string oauth_encode_base64(const unsigned char *src, int size)
{
	int i;
	std::stringbuf sb;

	if (!src) return NULL;
	if (!size) size= strlen((char *)src);

	for (i = 0; i < size; i += 3) {
		unsigned char b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0, b7 = 0;
		b1= src[i];
		if (i + 1 < size) b2 = src[i + 1];
		if (i + 2 < size) b3 = src[i + 2];

		b4= b1 >> 2;
		b5= ((b1 & 0x3) << 4) | (b2 >> 4);
		b6= ((b2 & 0xf) << 2) | (b3 >> 6);
		b7= b3 & 0x3f;

		sb.sputc(oauth_b64_encode(b4));
		sb.sputc(oauth_b64_encode(b5));

		if (i + 1 < size) {
			sb.sputc(oauth_b64_encode(b6));
		} else {
			sb.sputc('=');
		}

		if (i + 2 < size) {
			sb.sputc(oauth_b64_encode(b7));
		} else {
			sb.sputc('=');
		}
	}
	return sb.str();
}

/**
 * Decode the base64 encoded string 'src' into the memory pointed to by
 * 'dest'. 
 *
 * @param dest Pointer to memory for holding the decoded string.
 * Must be large enough to receive the decoded string.
 * @param src A base64 encoded string.
 * @return the length of the decoded string if decode
 * succeeded otherwise 0.
 */
std::string oauth_decode_base64(const char *src)
{
	if (src && *src) {
		std::stringbuf sb;
		//unsigned char *p= dest;
		int k, l= strlen(src)+1;
		std::vector<unsigned char> buf(l);

		/* Ignore non base64 chars as per the POSIX standard */
		for (k = 0, l = 0; src[k]; k++) {
			if (oauth_b64_is_base64(src[k])) {
				buf[l++]= src[k];
			}
		} 

		for (k = 0; k < l; k += 4) {
			char c1='A', c2='A', c3='A', c4='A';
			unsigned char b1 = 0, b2 = 0, b3 = 0, b4 = 0;
			c1= buf[k];

			if (k + 1 < l) c2 = buf[k + 1];
			if (k + 2 < l) c3 = buf[k + 2];
			if (k + 3 < l) c4 = buf[k + 3];

			b1 = oauth_b64_decode(c1);
			b2 = oauth_b64_decode(c2);
			b3 = oauth_b64_decode(c3);
			b4 = oauth_b64_decode(c4);

			sb.sputc((b1 << 2) | (b2 >> 4));

			if (c3 != '=') sb.sputc(((b2 & 0xf) << 4) | (b3 >> 2));
			if (c4 != '=') sb.sputc(((b3 & 0x3) << 6) | b4);
		}

		return sb.str();
	}
	return 0;
}

/**
 * Escape 'string' according to RFC3986 and
 * http://oauth.net/core/1.0/#encoding_parameters.
 *
 * @param string The data to be encoded
 * @return encoded string otherwise NULL
 * The caller must free the returned string.
 */
std::string oauth_url_escape(const char *string)
{
	unsigned char in; 
	size_t length;

	if (!string) {
		return std::string();
	}

	length = strlen(string);

	std::stringbuf sb;

	while (length--) {
		in = *string;
		if (strchr("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_~.-", in)) {
			sb.sputc(in);
		} else {
			char tmp[10];
			snprintf(tmp, 4, "%%%02X", in);
			sb.sputc(tmp[0]);
			sb.sputc(tmp[1]);
			sb.sputc(tmp[2]);
		}
		string++;
	}
	return sb.str();
}

#ifndef ISXDIGIT
# define ISXDIGIT(x) (isxdigit((int) ((unsigned char)x)))
#endif

/**
 * Parse RFC3986 encoded 'string' back to  unescaped version.
 *
 * @param string The data to be unescaped
 * @param olen unless NULL the length of the returned string is stored there.
 * @return decoded string or NULL
 * The caller must free the returned string.
 */
std::string oauth_url_unescape(const char *string)
{
	size_t alloc, strindex=0;
	unsigned char in;
	long hex;

	if (!string) return NULL;

	alloc = strlen(string)+1;
	std::vector<char> ns(alloc);

	while(--alloc > 0) {
		in = *string;
		if (('%' == in) && ISXDIGIT(string[1]) && ISXDIGIT(string[2])) {
			char hexstr[3]; // '%XX'
			hexstr[0] = string[1];
			hexstr[1] = string[2];
			hexstr[2] = 0;
			hex = strtol(hexstr, NULL, 16);
			in = (unsigned char)hex; /* hex is always < 256 */
			string += 2;
			alloc -= 2;
		}
		ns[strindex++] = in;
		string++;
	}
	ns[strindex]=0;
	return &ns[0];
}

/**
 * returns plaintext signature for the given key.
 *
 * the returned string needs to be freed by the caller
 *
 * @param m message to be signed
 * @param k key used for signing
 * @return signature string
 */
std::string oauth_sign_plaintext (const char *m, const char *k)
{
	return oauth_url_escape(k);
}

/**
 * encode strings and concatenate with '&' separator.
 * The number of strings to be concatenated must be
 * given as first argument.
 * all arguments thereafter must be of type (char *) 
 *
 * @param len the number of arguments to follow this parameter
 * @param ... string to escape and added (may be NULL)
 *
 * @return pointer to memory holding the concatenated 
 * strings - needs to be free(d) by the caller. or NULL
 * in case we ran out of memory.
 */
std::string oauth_catenc(int len, ...)
{
	va_list va;
	std::string str;
	va_start(va, len);
	for (int i = 0; i < len; i++) {
		char *arg = va_arg(va, char *);
		std::string enc = oauth_url_escape(arg);
		if (i > 0) str += "&";
		str += enc;
	}
	va_end(va);
	return str;
}

/**
 * splits the given url into a parameter array. 
 * (see \ref oauth_serialize_url and \ref oauth_serialize_url_parameters for the reverse)
 *
 * NOTE: Request-parameters-values may include an ampersand character.
 * However if unescaped this function will use them as parameter delimiter. 
 * If you need to make such a request, this function since version 0.3.5 allows
 * to use the ASCII SOH (0x01) character as alias for '&' (0x26).
 * (the motivation is convenience: SOH is /untypeable/ and much more 
 * unlikely to appear than '&' - If you plan to sign fancy URLs you 
 * should not split a query-string, but rather provide the parameter array
 * directly to \ref oauth_serialize_url)
 *
 * @param url the url or query-string to parse. 
 * @param argv pointer to a (char *) array where the results are stored.
 *  The array is re-allocated to match the number of parameters and each 
 *  parameter-string is allocated with strdup. - The memory needs to be freed
 *  by the caller.
 * @param qesc use query parameter escape (vs post-param-escape) - if set
 *        to 1 all '+' are treated as spaces ' '
 * 
 * @return number of parameter(s) in array.
 */
void oauth_split_post_paramters(const char *url, std::vector<std::string> *argv, short qesc)
{
	int argc=0;
	char *token, *tmp;
	if (!argv) return;
	if (!url) return;
	std::vector<char> t1(strlen(url) + 1);
	strcpy(&t1[0], url);

	// '+' represents a space, in a URL query string
	while ((qesc&1) && (tmp=strchr(&t1[0],'+'))) *tmp = ' ';

	tmp = &t1[0];
	while ((token = strtok(tmp,"&?"))) {
		if (!strncasecmp("oauth_signature=", token, 16)) continue;
		while (!(qesc & 2) && (tmp = strchr(token, '\001'))) *tmp = '&';
		argv->push_back(oauth_url_unescape(token));
		if (argc == 0 && strstr(token, ":/")) {
			// HTTP does not allow empty absolute paths, so the URL 
			// 'http://example.com' is equivalent to 'http://example.com/' and should
			// be treated as such for the purposes of OAuth signing (rfc2616, section 3.2.1)
			// see http://groups.google.com/group/oauth/browse_thread/thread/c44b6f061bfd98c?hl=en
			char *slash = strstr(token, ":/");
			while (slash && *(++slash) == '/')  ; // skip slashes eg /xxx:[\/]*/
#if 0
			// skip possibly unescaped slashes in the userinfo - they're not allowed by RFC2396 but have been seen.
			// the hostname/IP may only contain alphanumeric characters - so we're safe there.
			if (slash && strchr(slash,'@')) slash=strchr(slash, '@'); 
#endif
			if (slash && !strchr(slash,'/')) {
#ifdef DEBUG_OAUTH
				fprintf(stderr, "\nliboauth: added trailing slash to URL: '%s'\n\n", token);
#endif
				argv->push_back(std::string(token) + "/");
			}
		}
		if (argc == 0 && (tmp = strstr((char *)argv->at(argc).c_str(), ":80/"))) {
			memmove(tmp, tmp + 3, strlen(tmp + 2));
		}
		tmp = NULL;
		argc++;
	}
}

void oauth_split_url_parameters(const char *url, std::vector<std::string> *argv)
{
	oauth_split_post_paramters(url, argv, 1);
}

/**
 * build a url query string from an array.
 *
 * @param argc the total number of elements in the array
 * @param start element in the array at which to start concatenating.
 * @param argv parameter-array to concatenate.
 * @return url string needs to be freed by the caller.
 *
 */
std::string oauth_serialize_url (std::vector<std::string> const &argv, int start)
{
	return oauth_serialize_url_sep(argv, start, "&", 0);
}

/**
 * encode query parameters from an array.
 *
 * @param argc the total number of elements in the array
 * @param start element in the array at which to start concatenating.
 * @param argv parameter-array to concatenate.
 * @param sep separator for parameters (usually "&") 
 * @param mod - bitwise modifiers: 
 *   1: skip all values that start with "oauth_"
 *   2: skip all values that don't start with "oauth_"
 *   4: add double quotation marks around values (use with sep=", " to generate HTTP Authorization header).
 * @return url string needs to be freed by the caller.
 */
std::string oauth_serialize_url_sep(std::vector<std::string> const &argv, int start, char const *sep, int mod)
{
	int i;
	int first = 0;
	int seplen = strlen(sep);
	std::string query;
	for (i = start; i < (int)argv.size(); i++) {
		std::string tmp;

		if ((mod & 1) == 1 && (strncmp(argv[i].c_str(), "oauth_", 6) == 0 || strncmp(argv[i].c_str(), "x_oauth_", 8) == 0)) continue;
		if ((mod & 2) == 2 && (strncmp(argv[i].c_str(), "oauth_", 6) != 0 && strncmp(argv[i].c_str(), "x_oauth_", 8) != 0) && i != 0) continue;

		if (i == start && i == 0 && strstr(argv[i].c_str(), ":/")) {
			tmp = argv[i];
		} else {
			char *p = strchr((char *)argv[i].c_str(), '=');
			if (p) {
				tmp = oauth_url_escape(std::string(argv[i].c_str(), (char const *)p).c_str());
				std::string t2 = oauth_url_escape(p + 1);
				tmp += "=";
				if (mod & 4) tmp += "\"";
				tmp += t2;
				if (mod & 4) tmp += "\"";
			} else {
				// see http://oauth.net/core/1.0/#anchor14
				// escape parameter names and arguments but not the '='
				tmp=argv[i];
				tmp += "=";
			}
		}
		query += ((i == start || first) ? "" : sep);
		query += tmp;
		first = 0;
		if (i == start && i == 0 && strstr((char *)tmp.c_str(), ":/")) {
			query += "?";
			first = 1;
		}
	}
	return (query);
}

/**
 * build a query parameter string from an array.
 *
 * This function is a shortcut for \ref oauth_serialize_url (argc, 1, argv). 
 * It strips the leading host/path, which is usually the first 
 * element when using oauth_split_url_parameters on an URL.
 *
 * @param argc the total number of elements in the array
 * @param argv parameter-array to concatenate.
 * @return url string needs to be freed by the caller.
 */
std::string oauth_serialize_url_parameters (std::vector<std::string> const &argv)
{
	return oauth_serialize_url(argv, 1);
}

/**
 * generate a random string between 15 and 32 chars length
 * and return a pointer to it. The value needs to be freed by the
 * caller
 *
 * @return zero terminated random string.
 */
std::string oauth_gen_nonce()
{
	static const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	const unsigned int max = 26 + 26 + 10 + 1; //strlen(chars);
	char tmp[50];
	int i, len;

	srand((unsigned int)time(0));
	len = 15 + rand() % 16;
	for (i = 0; i < len; i++) {
		tmp[i] = chars[rand() % max];
	}
	tmp[i]='\0';
	return &tmp[0];
}

/**
 * string compare function for oauth parameters.
 *
 * used with qsort. needed to normalize request parameters.
 * see http://oauth.net/core/1.0/#anchor14
 */
int oauth_cmpstringp(const void *p1, const void *p2)
{
	char const *e1;
	char const *e2;
	e1 = strchr((char *)p1, '=');
	e2 = strchr((char *)p2, '=');
	if (e1 && e2) {
		std::string left((char const *)p1, e1);
		std::string right((char const *)p2, e2);
		return strcmp(left.c_str(), right.c_str());
	}

	std::string left = oauth_url_escape((char const *)p1);
	std::string right = oauth_url_escape((char const *)p2);
	return strcmp(left.c_str(), right.c_str());
}

bool oauth_cmpstringp_ex(std::string const &left, std::string const &right)
{
	return oauth_cmpstringp(left.c_str(), right.c_str()) < 0;
}

/**
 * search array for parameter key.
 * @param argv length of array to search
 * @param argc parameter array to search
 * @param key key of parameter to check.
 *
 * @return FALSE (0) if array does not contain a parameter with given key, TRUE (1) otherwise.
 */
bool oauth_param_exists(std::vector<std::string> const &argv, char const *key)
{
	int i;
	size_t l = strlen(key);
	for (i = 0; i < (int)argv.size(); i++) {
		if (!strncmp(argv[i].c_str(), key, l) && argv[i][l] == '=') {
			return true;
		}
	}
	return false;
}

/**
 *
 */
void oauth_add_protocol(
	std::vector<std::string> *argvp, 
	OAuthMethod method, 
	const char *c_key, //< consumer key - posted plain text
	const char *t_key //< token key - posted plain text in URL
)
{
	char oarg[1024];

	// add OAuth specific arguments
	if (!oauth_param_exists(*argvp,"oauth_nonce")) {
		std::string tmp = oauth_gen_nonce();
		snprintf(oarg, 1024, "oauth_nonce=%s", tmp.c_str());
		argvp->push_back(oarg);
	}

	if (!oauth_param_exists(*argvp,"oauth_timestamp")) {
		snprintf(oarg, 1024, "oauth_timestamp=%li", (long int) time(NULL));
		argvp->push_back(oarg);
	}

	if (t_key) {
		snprintf(oarg, 1024, "oauth_token=%s", t_key);
		argvp->push_back(oarg);
	}

	snprintf(oarg, 1024, "oauth_consumer_key=%s", c_key);
	argvp->push_back(oarg);

	snprintf(oarg, 1024, "oauth_signature_method=%s", method==0?"HMAC-SHA1":method==1?"RSA-SHA1":"PLAINTEXT");
	argvp->push_back(oarg);

	if (!oauth_param_exists(*argvp,"oauth_version")) {
		snprintf(oarg, 1024, "oauth_version=1.0");
		argvp->push_back(oarg);
	}

#if 0 // oauth_version 1.0 Rev A
	if (!oauth_param_exists(argv,argc,"oauth_callback")) {
		snprintf(oarg, 1024, "oauth_callback=oob");
		argvp->push_back(oarg);
	}
#endif

}

std::string oauth_sign_url(
	const char *url,
	std::string *postargs, 
	OAuthMethod method, 
	const char *c_key, //< consumer key - posted plain text
	const char *c_secret, //< consumer secret - used as 1st part of secret-key 
	const char *t_key, //< token key - posted plain text in URL
	const char *t_secret //< token secret - used as 2st part of secret-key
)
{
	return oauth_sign_url2(url, postargs, method, NULL, c_key, c_secret, t_key, t_secret);
} 

std::string oauth_sign_url2(
	const char *url,
	std::string *postargs, 
	OAuthMethod method, 
	const char *http_method, //< HTTP request method
	const char *c_key, //< consumer key - posted plain text
	const char *c_secret, //< consumer secret - used as 1st part of secret-key 
	const char *t_key, //< token key - posted plain text in URL
	const char *t_secret //< token secret - used as 2st part of secret-key
)
{
	//char **argv = NULL;
	std::vector<std::string> argv;
	std::string rv;

	if (postargs) {
		oauth_split_post_paramters(url, &argv, 0);
	} else {
		oauth_split_url_parameters(url, &argv);
	}

	rv = oauth_sign_array2(&argv, postargs, method, http_method, c_key, c_secret, t_key, t_secret);

	return(rv);
}

std::string oauth_sign_array(
	std::vector<std::string> *argvp,
	std::string *postargs,
	OAuthMethod method, 
	const char *c_key, //< consumer key - posted plain text
	const char *c_secret, //< consumer secret - used as 1st part of secret-key 
	const char *t_key, //< token key - posted plain text in URL
	const char *t_secret //< token secret - used as 2st part of secret-key
)
{
	return oauth_sign_array2(
		argvp, 
		postargs, method,
		NULL,
		c_key, c_secret,
		t_key, t_secret
		);
}

void oauth_sign_array2_process(
	std::vector<std::string> *argvp,
	std::string *postargs,
	OAuthMethod method, 
	const char *http_method, //< HTTP request method
	const char *c_key, //< consumer key - posted plain text
	const char *c_secret, //< consumer secret - used as 1st part of secret-key 
	const char *t_key, //< token key - posted plain text in URL
	const char *t_secret //< token secret - used as 2st part of secret-key
)
{
	char oarg[1024];
	std::string query;
	std::string sign;
	std::string http_request_method;

	if (!http_method) {
		http_request_method = postargs ? "POST" : "GET";
	} else {
		std::vector<char> tmp(strlen(http_method) + 1);
		int i;
		for (i = 0; http_method[i]; i++) {
			tmp[i] = toupper(http_method[i]);
		}
		tmp[i] = 0;
		http_request_method = &tmp[0];
	}

	// add required OAuth protocol parameters
	oauth_add_protocol(argvp, method, c_key, t_key);

	// sort parameters
	//qsort(&(*argvp)[1], (*argcp)-1, sizeof(char *), oauth_cmpstringp);
	std::sort(argvp->begin() + 1, argvp->end(), oauth_cmpstringp_ex);

	// serialize URL - base-url 
	query= oauth_serialize_url_parameters(*argvp);

	// generate signature
	std::string okey = oauth_catenc(2, c_secret, t_secret);
	std::string odat = oauth_catenc(3, http_request_method.c_str(), (*argvp)[0].c_str(), query.c_str()); // base-string
#ifdef DEBUG_OAUTH
	fprintf (stderr, "\nliboauth: data to sign='%s'\n\n", odat.c_str());
	fprintf (stderr, "\nliboauth: key='%s'\n\n", okey.c_str());
#endif
	switch(method) {
	//case OA_RSA:
	//	sign = oauth_sign_rsa_sha1(odat.c_str(), okey.c_str()); // XXX okey needs to be RSA key!
	//	break;
	case OA_PLAINTEXT:
		sign = oauth_sign_plaintext(odat.c_str(), okey.c_str()).c_str();
		break;
	default:
		sign = oauth_sign_hmac_sha1(odat.c_str(), okey.c_str());
		break;
	}

	// append signature to query args.
	snprintf(oarg, 1024, "oauth_signature=%s",sign.c_str());
	argvp->push_back(oarg);
}

std::string oauth_sign_array2(
	std::vector<std::string> *argvp,
	std::string *postargs,
	OAuthMethod method, 
	const char *http_method, //< HTTP request method
	const char *c_key, //< consumer key - posted plain text
	const char *c_secret, //< consumer secret - used as 1st part of secret-key 
	const char *t_key, //< token key - posted plain text in URL
	const char *t_secret //< token secret - used as 2st part of secret-key
)
{

	std::string result;
	oauth_sign_array2_process(argvp, postargs, method, http_method, c_key, c_secret, t_key, t_secret);

	// build URL params
	result = oauth_serialize_url(*argvp, (postargs?1:0));

	if (postargs) { 
		*postargs = result;
		result = argvp->at(0);
	}

	return result;
}

